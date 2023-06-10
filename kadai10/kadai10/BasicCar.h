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
	
	//車のステータス
	double wheel_base;	//ホイルベース
	double width;		//幅
	double overhang;	//車輪から前、後ろまで
	double height;		//高さ
	double wheel_radius;//タイヤの半径

	double length;		//全長
	double center_z;		//車の中心のz座標
	
};

