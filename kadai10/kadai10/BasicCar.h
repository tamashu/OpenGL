#pragma once
#include "BaseShape.h"

#define WHEEL_WIDTH 0.2
#define TILE_LENGTH 40

class BasicCar : public BaseShape
{
public:
	BasicCar(double wheel_base, double width, double overhang,double height,double wheel_radius);
	void DrawCar(double x, double y);

private:
	
	//�Ԃ̃X�e�[�^�X
	double wheel_base;	//�z�C���x�[�X
	double width;		//��
	double overhang;	//�ԗւ���O�A���܂�
	double height;		//����
	double wheel_radius;//�^�C���̔��a

	double length;		//�S��
	double center_z;		//�Ԃ̒��S��z���W
	
};

