#include "BasicCar.h"
#include <GL/glut.h>
#include <iostream>


BasicCar::BasicCar(double wheel_base, double width, double overhang, double height,double wheel_radius) {
	this->wheel_base = wheel_base;
	this->width = width;
	this->overhang = overhang;
	this->height = height;
	this->wheel_radius = wheel_radius;

	this->length = wheel_base + 2 * overhang;
	this->center_z = height / 2 + wheel_radius;


}

void BasicCar::DrawCar(double x, double y) {

	myGround(0.0,TILE_LENGTH);
	//�{�f�B�[�̕`��
	
	glTranslated(x, y, center_z);
	myBox(width/2, length/2, height/2);

	//�O��(�E)
	glPushMatrix();
	glTranslated(width/2, wheel_base/2, -height/2);
	glPushMatrix();
	glRotated(90.0, 0.0, 1.0, 0.0);
	myCylinder(wheel_radius, WHEEL_WIDTH, 16);
	glPopMatrix();
	glPopMatrix();

	//�O��(��)
	glPushMatrix();
	glTranslated(-width / 2, wheel_base / 2, -height / 2);
	glPushMatrix();
	glRotated(90.0, 0.0, 1.0, 0.0);
	myCylinder(wheel_radius, WHEEL_WIDTH, 16);
	glPopMatrix();
	glPopMatrix();

	//���(�E)
	glPushMatrix();
	glTranslated(width / 2, -wheel_base / 2, -height / 2);
	glPushMatrix();
	glRotated(90.0, 0.0, 1.0, 0.0);
	myCylinder(wheel_radius, WHEEL_WIDTH, 16);
	glPopMatrix();
	glPopMatrix();

	//���(��)
	glPushMatrix();
	glTranslated(-width / 2, -wheel_base / 2, -height / 2);
	glPushMatrix();
	glRotated(90.0, 0.0, 1.0, 0.0);
	myCylinder(wheel_radius, WHEEL_WIDTH, 16);
	glPopMatrix();
	glPopMatrix();

}