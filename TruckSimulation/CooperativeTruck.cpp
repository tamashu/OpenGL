#include "CooperativeTruck.h"
CooperativeTruck::CooperativeTruck(double front_car_wheel_base, double carrier_length, double rear_car_wheel_base)
	:front_car(front_car_wheel_base), rear_car(rear_car_wheel_base) 
{
	this->carrier_length = carrier_length;
	this->carrier_width = 0.647 * front_car_wheel_base; //車の幅と同じにしている
}

void CooperativeTruck::DrawTruck(double t, double v1, double x1, double y1, double theta1_rad, double phi1_rad,  //前の車
									  double x2, double y2, double theta2_rad,					//荷台
									  double x3, double y3, double theta3_rad, double phi2_rad)  //後ろの車
{
	front_car.DrawCar(t, x1, y1, theta1_rad, phi1_rad, v1);
	//rear_car.DrawCar(t, x3, y3, theta3_rad, phi2_rad, v1);

}