#pragma once
#include "BasicCar.h"
#define L1 1.0
#define L2 3.0
#define L3 1.0


class CooperativeTruck : public BaseShape
{
public:
	CooperativeTruck(double front_car_wheel_base, double carrier_length, double rear_car_wheel_base );
	void DrawTruck(double t, double v1,  double x1, double y1, double theta1_rad, double phi1_rad,  //�O�̎�
										 double x2, double y2, double theta2_rad,					//�ב�
										 double x3, double y3, double theta3_rad, double phi2_rad); //���̎�

private:
	void drawCarrier(double x2, double y2, double theta2_rad, double thick);

	BasicCar front_car;
	BasicCar rear_car;

	double carrier_length; //�ב�̒���
	double carrier_width;  //�ב�̕�
	double center_z;

	

};

