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
	double body_color[] = { 0.5,0.2,0.2,0.8 };
	double theta_deg = radToDegree(theta_rad);
	double phi_deg = radToDegree(phi_rad);
	double wheel_rotation = radToDegree( wheel_rps * t);
	double steer_cylinder_width = 0.05;

	myGround(0.0,TILE_LENGTH);
	
	glTranslated(x, y, center_z+ HEIGHT_MARGIN);
	glRotated(theta_deg, 0.0, 0.0, 1.0);


	//前輪輪ステアリングの棒
	glPushMatrix();
	glTranslated(wheel_base, 0.0, -height / 2 - HEIGHT_MARGIN);
	glRotated(90.0, 1.0, 0.0, 0.0);
	myCylinder(steer_cylinder_width, width / 2.0 + WHEEL_MARGIN, 16);
	std::cout << width / 2.0 << std::endl;
	glPopMatrix();

	//後輪ステアリングの棒
	glPushMatrix();
	glTranslated(0.0, 0.0, -height / 2 - HEIGHT_MARGIN);
	glRotated(90.0, 1.0, 0.0, 0.0);
	myCylinder(steer_cylinder_width, width / 2.0 + WHEEL_MARGIN, 16);
	glPopMatrix();

	//ボディーの描画
	glPushMatrix();
	glTranslated(back_body_center_x, 0.0, -height/4.0);
	myBox(length/4.0, width / 2.0, height / 4, body_color);
	glPopMatrix();
	glPushMatrix();
	glTranslated(front_body_center_x, 0.0, 0.0);
	myBox(length / 4.0, width / 2.0, height / 2,body_color);
	glPopMatrix();

	

	//後輪(右)
	glPushMatrix();
	glTranslated(0.0, -width / 2 - WHEEL_MARGIN, -height / 2 - HEIGHT_MARGIN);
	glRotated(90.0, 1.0, 0.0, 0.0);
	glRotated(wheel_rotation, 0.0, 0.0, -1.0);//車輪の回転
	myWheel(wheel_radius, WHEEL_WIDTH, 16);
	glPopMatrix();

	//後輪(左)
	glPushMatrix();
	glTranslated(0.0, width / 2 + WHEEL_MARGIN, -height / 2 - HEIGHT_MARGIN);
	glRotated(-90.0, 1.0, 0.0, 0.0);
	glRotated(wheel_rotation, 0.0, 0.0, 1.0);//車輪の回転
	myWheel(wheel_radius, WHEEL_WIDTH, 16);
	glPopMatrix();

	//前輪(右)
	glPushMatrix();
	glTranslated(wheel_base, -width / 2 - WHEEL_MARGIN, -height / 2 - HEIGHT_MARGIN);
	glPushMatrix();
	glRotated(phi_deg, 0.0, 0.0, 1.0);
	glRotated(90.0, 1.0, 0.0, 0.0);
	glRotated(wheel_rotation, 0.0, 0.0, -1.0);//車輪の回転
	myWheel(wheel_radius, WHEEL_WIDTH, 16);
	glPopMatrix();

	//前輪(左)
	glPushMatrix();
	glTranslated(wheel_base, width / 2 + WHEEL_MARGIN, -height / 2 - HEIGHT_MARGIN);
	glRotated(phi_deg, 0.0, 0.0, 1.0);
	glRotated(-90.0, 1.0, 0.0, 0.0);
	glRotated(wheel_rotation, 0.0, 0.0, 1.0);//車輪の回転
	myWheel(wheel_radius, WHEEL_WIDTH, 16);
	glPopMatrix();

	

	
	
	
}

void BasicCar::myWheel(double radius, double height, int sides) {
	const static GLfloat yellow[] = { 0.8, 0.8, 0.2, 1.0 };
	const static GLfloat blue[] = { 0.2, 0.2, 0.8, 1.0 };
	double step = 6.28318530717958647692 / (double)sides;
	int i = sides;

	//車輪を90度ごとに色を変えるための変数
	bool isYellow = false;//90度毎にon,offが切り替わる

	/* 材質を設定する */
	

	/* 上面 */
	glNormal3d(0.0, 0.0, 1.0);
	
	for(i=0;i<sides;i++) {
		if (i % 4 == 0) {
			if (isYellow) {
				isYellow = false;
			}
			else {
				isYellow = true;
			}
		}
		if (isYellow) {
			glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow);
		}
		else {
			glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
		}
		double t = step * (double)i;
		double t_next = step * (double)(i + 1);

		glBegin(GL_TRIANGLE_FAN);
		glVertex3d(0.0, 0.0, height);
		glVertex3d(radius * cos(t), radius * sin(t), height);
		glVertex3d(radius * cos(t_next), radius * sin(t_next), height);
		glEnd();
	}
	

	isYellow = false;
	/* 底面 */
	glNormal3d(0.0, 0.0, -1.0);
	for(int i =0; i<sides; i++) {
		if (i % 4 == 0) {
			if (isYellow) {
				isYellow = false;
			}
			else {
				isYellow = true;
			}
		}
		if (isYellow) {
			glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow);
		}
		else {
			glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
		}

		double t = step * (double)i;
		double t_next = step * (double)(i + 1);

		glBegin(GL_TRIANGLE_FAN);
		glVertex3d(0.0, 0.0, -height);
		glVertex3d(radius * cos(t_next), radius * sin(t_next), -height);
		glVertex3d(radius * cos(t), radius * sin(t), -height);
		
		glEnd();
	}


	isYellow = false;
	/* 側面 */
	for (int i = 0; i < sides; i++) {
		double t = step * (double)i;
		double t_next = step * (double)(i + 1);
		double x = radius *sin(t);
		double y = radius*cos(t);
		double x_next = radius*sin(t_next);
		double y_next = radius*cos(t_next);

		if (i % 4 == 0) {
			if (isYellow) {
				isYellow = false;
			}
			else {
				isYellow = true;
			}
		}
		if (isYellow) {
			glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow);
		}
		else {
			glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
		}

		glNormal3d(x_next+ x, y_next+y, 0.0);
		glBegin(GL_TRIANGLES);
		glVertex3d(x, y, height);
		glVertex3d(x_next, y_next, height);
		glVertex3d(x, y, -height);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex3d(x_next, y_next, -height);
		glVertex3d(x, y, -height);
		glVertex3d(x_next, y_next, height);
		
		
		glEnd();

	}

	

}