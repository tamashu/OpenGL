#include "BasicCar.h"
#include <GL/glut.h>
#include <iostream>

#include "BasicFunction.h"


BasicCar::BasicCar(double wheel_base, double width, double overhang, double height,double wheel_radius) {
	this->wheel_base = wheel_base;
	this->width = width;
	this->overhang = overhang;
	this->height = height;
	this->wheel_radius = wheel_radius;

	this->length = wheel_base + 2 * overhang;
	this->center_z = height / 2 + wheel_radius;
	this->back_body_center_x = length / 4.0 - overhang;
	this->front_body_center_x = 3.0*length / 4.0 - overhang;

	this->v1 = 1.0;
	this->wheel_rps = v1 / wheel_radius;//rad/s


}

void BasicCar::DrawCar(double t,double x, double y,double theta_rad,double phi_rad) {
	double front_body_color[] = { 0.0,0.0,1.0,1.0 };
	double theta_deg = radToDegree(theta_rad);
	double phi_deg = radToDegree(phi_rad);
	double wheel_rotation = radToDegree( wheel_rps * t);
	double steer_cylinder_width = 0.05;

	myGround(0.0,TILE_LENGTH);
	//ボディーの描画
	glTranslated(x, y, center_z+ MARGIN);
	glRotated(theta_deg, 0.0, 0.0, 1.0);
	glPushMatrix();
	glTranslated(back_body_center_x, 0.0, -height/4.0);
	myBox(length/4.0, width / 2.0, height / 4);
	glPopMatrix();
	glPushMatrix();
	glTranslated(front_body_center_x, 0.0, 0.0);
	myBox(length / 4.0, width / 2.0, height / 2,front_body_color);
	glPopMatrix();

	
	//前輪(右)
	glPushMatrix();
	glTranslated(wheel_base, -width / 2, -height / 2-MARGIN);
	glPushMatrix();
	glRotated(phi_deg, 0.0, 0.0, 1.0);
	glRotated(90.0, 1.0, 0.0, 0.0);
	glRotated(wheel_rotation, 0.0, 0.0, -1.0);//車輪の回転
	myWheel(wheel_radius, WHEEL_WIDTH, 16);
	glPopMatrix();

	//前輪(左)
	glPushMatrix();
	glTranslated(wheel_base, width / 2, -height / 2 - MARGIN);
	glRotated(phi_deg, 0.0, 0.0, 1.0);
	glRotated(-90.0, 1.0, 0.0, 0.0);
	glRotated(wheel_rotation, 0.0, 0.0, 1.0);//車輪の回転
	myWheel(wheel_radius, WHEEL_WIDTH, 16);
	glPopMatrix();

	//後輪(右)
	glPushMatrix();
	glTranslated(0.0, -width / 2, -height / 2 - MARGIN);
	glRotated(90.0, 1.0, 0.0, 0.0);
	glRotated(wheel_rotation, 0.0, 0.0, -1.0);//車輪の回転
	myWheel(wheel_radius, WHEEL_WIDTH, 16);
	glPopMatrix();

	//後輪(左)
	glPushMatrix();
	glTranslated( 0.0, width / 2, -height/2 - MARGIN);
	glRotated(-90.0, 1.0, 0.0, 0.0);
	glRotated(wheel_rotation, 0.0, 0.0, 1.0);//車輪の回転
	myWheel(wheel_radius, WHEEL_WIDTH, 16);
	glPopMatrix();

	
	
	//前輪輪ステアリングの棒
	glPushMatrix();
	glTranslated(wheel_base, 0.0, -height / 2 - MARGIN);
	glRotated(90.0, 1.0, 0.0, 0.0);
	myCylinder(steer_cylinder_width, width/2.0, 16);
	std::cout << width / 2.0 << std::endl;
	glPopMatrix();

	//後輪ステアリングの棒
	glPushMatrix();
	glTranslated(0.0, 0.0, -height / 2 - MARGIN);
	glRotated(90.0, 1.0, 0.0, 0.0);
	myCylinder(steer_cylinder_width, width/2.0,16);
	glPopMatrix();
}

void BasicCar::myWheel(double r, double width, int sides) {
	const int tire_line = 8; //タイヤの線の本数
	int line_size = 4;

	myCylinder(r, width, sides);
	glPushMatrix();

	glTranslated(0.0, 0.0, width);
	glLineWidth(line_size);
	glColor3d(0.0, 0.0, 0.0);
	for (int i = 0; i < tire_line; i++) {
		glBegin(GL_LINES);
		glVertex3d(0.0, 0.0, 0.0);
		glVertex3d(r * sin((2 * PI * i) / tire_line) , wheel_radius * cos((2 * PI * i) / tire_line) ,0.0);
		glEnd();
		 
	}


	glPopMatrix();

}