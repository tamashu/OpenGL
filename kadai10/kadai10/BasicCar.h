#pragma once
#include "BaseShape.h"

#define WHEEL_WIDTH 0.2
#define TILE_LENGTH 40
#define HEIGHT_MARGIN 0.05
#define WHEEL_MARGIN 0.05

class BasicCar : public BaseShape
{
public:
	BasicCar(double wheel_base, double width, double overhang,double height,double wheel_radius);
	void DrawCar(double t, double x, double y, double theta_rad, double phi_rad,double v1);

private:
	void myWheel(double r, double width, int sides);

	//車のステータス
	double wheel_base;	//ホイルベース
	double width;		//幅
	double overhang;	//車輪から前、後ろまで
	double height;		//高さ
	double wheel_radius;//タイヤの半径

	double length;		//全長
	double center_z;		//車の中心のz座標
	double  back_body_center_x;
	double  front_body_center_x;

	double v1;//車の速度
	double wheel_rps;//タイヤの回転速度
	double t;
	double wheel_rotation;
};

