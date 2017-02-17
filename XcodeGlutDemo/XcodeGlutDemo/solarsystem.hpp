#ifndef solarsystem_hpp
#define solarsystem_hpp

#include <GLUT/GLUT.h>
#include "stars.hpp"

const int STARS_NUM = 10;//星球数

class SolarSystem{
public:
    SolarSystem();
    ~SolarSystem();
    void onDisplay();
    void onUpdate();
    void onKeyboard(unsigned char key, int x,int y);
private:
    Star *stars[STARS_NUM];
    // 定义观察视角的参数
    GLdouble viewX,viewY,viewZ;
    GLdouble centerX,centerY,centerZ;
    GLdouble upX,upY,upZ;
};

#endif /* solarsystem_hpp */