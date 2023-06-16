#pragma once
#include <vector>
#include <string>

class BaseShape{
public:
	BaseShape();
	void myBox(double x, double y, double z);
	void myBox(double x, double y, double z, double* color);
	void myCylinder(double radius, double height, int sides);
	void myGround(double height,int length);
	void triangle(std::vector<double>p0, std::vector<double>p1, std::vector<double>p2, double*  color );

private: 

};

