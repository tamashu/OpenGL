#pragma once
#include <string>
#include <vector>

class DrawLine
{	
public:
	void drawCurve(std::vector<std::vector<double>>points,double z,double * color);
	void drawCarTranjectory(std::vector<std::vector<double>>points, double z, double* color);
	void drawCarTranjectory1(std::vector<std::vector<double>>points, double z, double* color);
	void drawCarTranjectory2(std::vector<std::vector<double>>points, double z, double* color);

private:
	void drawLine(std::vector<double> p1, std::vector<double> p2,double z);
};

