#pragma once
#include <gl/glut.h>
#include <vector>
#include <string>

class DrawBezier{
public:
	DrawBezier(std::vector<std::vector<float>>); //制御点で初期化k
	void set_t(float t);
	float get_t();
	std::vector<float> get_ith_control_point(int i);
	void set_ith_control_points(int i,float x, float y);

	



	//N次元のベジェ(コンストラクタの引数のベクトルの個数-1次元)
	std::vector<float> drawNDimensionBezier();
	void drawString(std::vector < float >p, std::string string);


	
	
	

private:
	std::vector<std::vector<float>> control_points;
	float t;
	void drawPoint(std::vector<float> p);
	void drawLine(std::vector<float> p0, std::vector<float> p1);
	

	std::vector<float> drawInternalDivisionPoint(std::vector<float> p0, std::vector<float> p1, float t);
	std::vector<float> CalAndDrawInternalPoints(std::vector<std::vector<float>> internal_points);


};

