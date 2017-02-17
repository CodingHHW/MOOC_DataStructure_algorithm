#ifndef star_hpp
#define star_hpp

#include <GLUT/GLUT.h>

class Star{
public:
    GLfloat radius;// 星球的运行半径
    GLfloat speed, selfSpeed;// 星球的公转、自传速度
    GLfloat distance;// 星球的中心与父节点星球中心的距离
    GLfloat rgbaColor[4];// 星球的颜色
    Star *parentStar;// 父节点星球
    // 构造函数，构造一颗星球时必须提供旋转半径、与父节点星球距离、旋转速度、自转速度、绕行(父节点)星球
    Star(GLfloat radius,GLfloat distance,GLfloat speed,GLfloat selfSpeed,Star* parent);
    void drawStar();// 对一般的星球的移动、旋转等活动进行绘制
    virtual void draw(){// 提供默认实现，负责调用 drawStar()
        drawStar();
    }
    virtual void update(long timeSpan);// 参数为每次刷新画面时的时间跨度
protected:
    GLfloat alphaSelf, alpha;
};

class Planet : public Star{
public:
    // 构造函数
    Planet(GLfloat radius,GLfloat distance,GLfloat speed,GLfloat selfSpeed,Star* parent,GLfloat rgbColor[3]);
    void drawPlanet();// 增加对具备自身材质的行星绘制材质
    virtual void draw(){// 继续向其子类开放重写功能
        drawPlanet();
        drawStar();
    }
};

class LightPlanet : public Planet{
public:
    LightPlanet(GLfloat radius,GLfloat distance,GLfloat speed,GLfloat selfSpeed,Star* parent,GLfloat rgbColor[]);
    void drawLight();// 增加对提供光源的恒星绘制光照
    virtual void draw(){
        drawLight();
        drawPlanet();
        drawStar();
    }
};

#endif /* star_hpp */