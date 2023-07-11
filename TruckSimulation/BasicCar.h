#pragma once
#include "BaseShape.h"

#define TILE_LENGTH 40
//#define WHEEL_WIDTH 0.2
//#define HEIGHT_MARGIN 0.05
//#define WHEEL_MARGIN 0.05

class BasicCar : public BaseShape
{
public:
	BasicCar(double wheel_base);
	void DrawCar(double t, double x, double y, double theta_rad, double phi_rad,double v1);

private:
	void myWheel(double r, double width, int sides);

	//�Ԃ̃X�e�[�^�X
	double wheel_base;	//�z�C���x�[�X
	double width;		//��
	double overhang;	//�ԗւ���O�A���܂�
	double height;		//����
	double wheel_radius;//�^�C���̔��a

	double length;		//�S��
	double center_z;		//�Ԃ̒��S��z���W
	double  back_body_center_x;
	double  front_body_center_x;

	double v1;//�Ԃ̑��x
	double wheel_rps;//�^�C���̉�]���x
	double t;
	double wheel_rotation;

	const double WHEEL_WIDTH; //�^�C���̕�
	const double HEIGHT_MARGIN; //�ԑ̂ƃ^�C�������̋󂫃X�y�[�X
	const double WHEEL_MARGIN; //�ԑ̂ƃ^�C�����̋󂫃X�y�[�X


};

