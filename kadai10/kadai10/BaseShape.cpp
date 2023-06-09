#include "BaseShape.h"

#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include < GL/freeglut.h>
#include <sstream>
#include <iomanip>

BaseShape::BaseShape() {

}

void BaseShape::myBox(double x, double y, double z,double * color_rgba) //原点中心に±x,y,z
{

    GLdouble vertex[][3] = {
      { -x, -y, -z },
      {  x, -y, -z },
      {  x,  y, -z },
      { -x,  y, -z },
      { -x, -y,  z },
      {  x, -y,  z },
      {  x,  y,  z },
      { -x,  y,  z }
    };

    const static int face[][4] = {
      { 0, 1, 2, 3 },
      { 1, 5, 6, 2 },
      { 5, 4, 7, 6 },
      { 4, 0, 3, 7 },
      { 4, 5, 1, 0 },
      { 3, 2, 6, 7 }
    };

    const static GLdouble normal[][3] = {
      { 0.0, 0.0,-1.0 },
      { 1.0, 0.0, 0.0 },
      { 0.0, 0.0, 1.0 },
      {-1.0, 0.0, 0.0 },
      { 0.0,-1.0, 0.0 },
      { 0.0, 1.0, 0.0 }
    };

    const static GLfloat color[] = { color_rgba[0], color_rgba[1], color_rgba[2], color_rgba[3] };

    int i, j;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    /* 材質を設定する */
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color);

    glBegin(GL_QUADS);
    for (j = 0; j < 6; ++j) {
        glNormal3dv(normal[j]);
        for (i = 4; --i >= 0;) {
            glVertex3dv(vertex[face[j][i]]);
        }
    }
    glEnd();
    glDisable(GL_BLEND);
}

void BaseShape::myBox(double x, double y, double z) //原点中心に±x,y,z
{
    GLdouble vertex[][3] = {
      { -x, -y, -z },
      {  x, -y, -z },
      {  x,  y, -z },
      { -x,  y, -z },
      { -x, -y,  z },
      {  x, -y,  z },
      {  x,  y,  z },
      { -x,  y,  z }
    };

    const static int face[][4] = {
      { 0, 1, 2, 3 },
      { 1, 5, 6, 2 },
      { 5, 4, 7, 6 },
      { 4, 0, 3, 7 },
      { 4, 5, 1, 0 },
      { 3, 2, 6, 7 }
    };

    const static GLdouble normal[][3] = {
      { 0.0, 0.0,-1.0 },
      { 1.0, 0.0, 0.0 },
      { 0.0, 0.0, 1.0 },
      {-1.0, 0.0, 0.0 },
      { 0.0,-1.0, 0.0 },
      { 0.0, 1.0, 0.0 }
    };

    const static GLfloat red[] = { 0.8, 0.2, 0.2, 0.4 };

    int i, j;

    /* 材質を設定する */
    glMaterialfv(GL_FRONT, GL_DIFFUSE, red);

    glBegin(GL_QUADS);
    for (j = 0; j < 6; ++j) {
        glNormal3dv(normal[j]);
        for (i = 4; --i >= 0;) {
            glVertex3dv(vertex[face[j][i]]);
        }
    }
    glEnd();
}

/*
 * 円柱を描く
 */
 void BaseShape::myCylinder(double radius, double height, int sides)
{
    const static GLfloat yellow[] = { 0.8, 0.8, 0.2, 1.0 };
    double step = 6.28318530717958647692 / (double)sides;
    int i = sides;

    /* 材質を設定する */
    glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow);

    /* 上面 */
    glNormal3d(0.0, 0.0, 1.0);
    glBegin(GL_TRIANGLE_FAN);
    while (i > 0) {
        double t = step * (double)i--;
        glVertex3d(radius * sin(t), radius * cos(t), height);
    }
    glEnd();

    /* 底面 */
    glNormal3d(0.0, 0.0, -1.0);
    glBegin(GL_TRIANGLE_FAN);

    while (i < sides) {
        double t = step * (double)i++;
        glVertex3d(radius * sin(t), radius * cos(t), -height);
    }
    glEnd();

    /* 側面 */
    glBegin(GL_QUAD_STRIP);
    while (i >= 0) {
        double t = step * (double)i--;
        double x = sin(t);
        double y = cos(t);

        glNormal3d(x, y, 0.0);
        glVertex3f(radius * x, radius * y, height);
        glVertex3f(radius * x, radius * y, -height);
    }
    glEnd();
}

/*
 * 地面を描く
 */
 void BaseShape::myGround(double height,int length)
{
    const static GLfloat ground[][4] = {
      { 0.6, 0.6, 0.6, 1.0 },
      { 0.3, 0.3, 0.3, 1.0 }
    };

    int i, j;

    glBegin(GL_QUADS);
    glNormal3d(0.0, 0.0, 1.0);
    for (j = length; j > -length; --j) {
        for (i = length; i > -length; --i) {
            glMaterialfv(GL_FRONT, GL_DIFFUSE, ground[(i + j) & 1]);
            glVertex3d((GLdouble)(i - 1), (GLdouble)j, height);
            glVertex3d((GLdouble)(i - 1), (GLdouble)(j - 1), height);
            glVertex3d((GLdouble)(i), (GLdouble)(j - 1), height);
            glVertex3d((GLdouble)(i), (GLdouble)j, height);
        }
    }
    glEnd();
}

 void BaseShape::triangle(std::vector<double>p0, std::vector<double>p1, std::vector<double>p2, double* color)
 {
     const static GLfloat colors[] = { color[0], color[1], color[2], color[3] };
     glMaterialfv(GL_FRONT, GL_DIFFUSE, colors);

     glBegin(GL_TRIANGLES);
     glVertex3d(p0[0], p0[1], p0[2]);
     glVertex3d(p1[0], p1[1], p1[2]);
     glVertex3d(p2[0], p2[1], p2[2]);
     glEnd();
 }



