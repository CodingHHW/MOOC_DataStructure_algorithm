//
//  star.cpp
//  solarsystem
//
/*
常用的 OpenGL 图像绘制 API
OpenGL 中提供了很多常用的与图形绘制相关的 API，这里我们挑几个常用的进行简单介绍，并在接下来的代码中进行使用：

glEnable(GLenum cap): 这个函数用于激活 OpenGL 中提供的各种功能，传入的参数 cap 是OpenGL 内部的宏，提供诸如光源、雾化、抖动等效果；

glPushMatrix() 和 glPopMatrix(): 将当前矩阵保存到堆栈栈顶（保存当前矩阵）；

glRotatef(alpha, x, y, z): 表示当前图形沿 (x,y,z) 逆时针旋转 alpha 度;

glTranslatef(distance, x, y): 表示当前图形沿 (x,y) 方向平移 distance 距离;

glutSolidSphere(GLdouble radius , GLint slices , GLint stacks): 绘制球体， radius 为半径，slices 为经线条数, stacks 为纬线条数;

glBegin() 和 glEnd()：当我们要进行图形绘制时，需要在开始回之前和绘制完成后调用这两个函数，glBegin()指定了绘制图形的类型，例如 GL_POINTS 表示绘制点、 GL_LINES 表示绘制依次画出的点及他们之间的连线、GL_TRIANGLES 则是在每绘制的三个点中完成一个三角形、GL_POLYGON 则是绘制一个从第一个点到第 n 个点的多边形，等等。例如当我们需要绘制一个圆时可以边很多的多边形来模拟
*/

#include "stars.hpp"
#include <cmath>

#define PI 3.1415926535

Star::Star(GLfloat radius, GLfloat distance,
           GLfloat speed,  GLfloat selfSpeed,
           Star* parent) {
    this->radius = radius;
    this->selfSpeed = selfSpeed;
    this->alphaSelf = this->alpha = 0;
    this->distance = distance;
    
    for (int i = 0; i < 4; i++)
        this->rgbaColor[i] = 1.0f;
    
    this->parentStar = parent;
    if (speed > 0)
        this->speed = 360.0f / speed;
    else
        this->speed = 0.0f;
}

void Star::drawStar() {
    
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    
    int n = 1440;
    
    glPushMatrix();// 保存 OpenGL 当前的矩阵环境
    {   // 公转
        // 如果是行星，且距离不为0，那么且向原点平移一个半径
        // 这部分用于处理卫星
        
        if (parentStar != 0 && parentStar->distance > 0) {
            glRotatef(parentStar->alpha, 0, 0, 1);//将绘制的图形沿 z 轴旋转 alpha
            glTranslatef(parentStar->distance, 0.0, 0.0);// x 轴方向上平移 distance , y,z 方向不变
        }
        // 绘制运行轨道
        glBegin(GL_LINES);//画点与点之间的连线
        for(int i=0; i<n; ++i)
            glVertex2f(distance * cos(2 * PI * i / n),
                       distance * sin(2 * PI * i / n));
        glEnd();
        
        glRotatef(alpha, 0, 0, 1);// 绕 z 轴旋转 alpha
        glTranslatef(distance, 0.0, 0.0);// x 轴方向平移 distance, y,z 方向不变
        
        glRotatef(alphaSelf, 0, 0, 1);// 自转
        
        glColor3f(rgbaColor[0], rgbaColor[1], rgbaColor[2]);// 绘制行星颜色
        glutSolidSphere(radius, 40, 32);
    }
    glPopMatrix();// 恢复绘制前的矩阵环境
    
}

void Star::update(long timeSpan) {
    alpha += timeSpan * speed;// 更新角度
    alphaSelf += selfSpeed;// 更新自转角度
}


Planet::Planet(GLfloat radius, GLfloat distance,
               GLfloat speed,  GLfloat selfSpeed,
               Star* parent, GLfloat rgbColor[3]) :
Star(radius, distance, speed, selfSpeed, parent) {
    rgbaColor[0] = rgbColor[0];
    rgbaColor[1] = rgbColor[1];
    rgbaColor[2] = rgbColor[2];
    rgbaColor[3] = 1.0f;
}

void Planet::drawPlanet() {
    GLfloat mat_ambient[]  = {0.0f, 0.0f, 0.5f, 1.0f};
    GLfloat mat_diffuse[]  = {0.0f, 0.0f, 0.5f, 1.0f};
    GLfloat mat_specular[] = {0.0f, 0.0f, 1.0f, 1.0f};
    GLfloat mat_emission[] = {rgbaColor[0], rgbaColor[1], rgbaColor[2], rgbaColor[3]};
    GLfloat mat_shininess  = 90.0f;
    
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_EMISSION,  mat_emission);
    glMaterialf (GL_FRONT, GL_SHININESS, mat_shininess);
}

LightPlanet::LightPlanet(GLfloat radius,    GLfloat distance, GLfloat speed,
                         GLfloat selfSpeed, Star* parent,   GLfloat rgbColor[3]) :
Planet(radius, distance, speed, selfSpeed, parent, rgbColor) {
    ;
}

void LightPlanet::drawLight() {
    
    GLfloat light_position[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat light_ambient[]  = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat light_diffuse[]  = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    // 指定零号光源的位置
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    // 表示各种光线照射到该材质上，经过很多次反射后追踪遗留在环境中的光线强度
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    // 漫反射后的光照强度
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    // 镜面反射后的光照强度
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    
}