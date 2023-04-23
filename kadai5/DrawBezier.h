#pragma once
#include <gl/glut.h>
#include <vector>
#include <string>

class DrawBezier{
public:
	DrawBezier(std::vector<std::vector<float>>); //����_�ŏ�����k
	void set_t(float t);
	float get_t();
	std::vector<float> get_ith_control_point(int i);
	void set_ith_control_points(int i,float x, float y);

	



	//N�����̃x�W�F(�R���X�g���N�^�̈����̃x�N�g���̌�-1����)
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

