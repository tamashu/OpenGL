#include "CooperativeTruck.h"
#include "BasicFunction.h"
#include "BaseShape.h"

#include <GL/glut.h>

CooperativeTruck::CooperativeTruck(double front_car_wheel_base, double carrier_length, double rear_car_wheel_base)
	:front_car(front_car_wheel_base), rear_car(rear_car_wheel_base) 
{
	this->carrier_length = carrier_length;
	this->carrier_width = 0.647 * front_car_wheel_base; //ŽÔ‚Ì•‚Æ“¯‚¶‚É‚µ‚Ä‚¢‚é
	this->center_z = front_car.getCenterZ();
}

void CooperativeTruck::DrawTruck(double t, double v1, double x1, double y1, double theta1_rad, double phi1_rad,  //‘O‚ÌŽÔ
									  double x2, double y2, double theta2_rad,					//‰×‘ä
									  double x3, double y3, double theta3_rad, double phi2_rad)  //Œã‚ë‚ÌŽÔ
{
	drawCarrier(x2, y2, theta2_rad, 0.02);
	front_car.DrawCar(t, x1, y1, theta1_rad, phi1_rad, v1);
	rear_car.DrawCar(t, x3, y3, theta3_rad+PI , phi2_rad+PI, -v1);
}

void CooperativeTruck::drawCarrier(double x2, double y2, double theta2_rad , double thick) {
	double theta2_deg = radToDegree(theta2_rad+ PI);

	glPushMatrix();
	
	glTranslated(x2,y2,center_z+thick );
	
	
	
	glRotated(theta2_deg, 0.0, 0.0, 1.0);

	myBox(  carrier_length/3.0, carrier_width/2.0, thick);

	glPushMatrix();
	glTranslated(carrier_length / 3.0, 0.0, 0.0);
	glRotated(-90, 0.0, 0.0, 1.0);
	trianglePole(carrier_width/2.0, carrier_length / 6.0, thick);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-carrier_length / 3.0, 0.0,0.0);
	glRotated(90, 0.0, 0.0, 1.0);
	trianglePole(carrier_width / 2.0, carrier_length / 6.0, thick);
	glPopMatrix();

	glPopMatrix();
}