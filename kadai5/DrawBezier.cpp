#include "DrawBezier.h"
#include <gl/glut.h>
#include <vector>
#include <iostream>
#include < GL/freeglut.h>
#include <string>

inline void glutBitmapString(void* font, const char* string) //文字表示をしやすくするためのオーバーロード
{
	glutBitmapString(font, reinterpret_cast<const unsigned char*>(string));
}

DrawBezier::DrawBezier(std::vector<std::vector<float>> control_points){
	this->control_points = control_points;
}

void DrawBezier::set_t(float t) {
	this->t = t;
}

float DrawBezier::get_t() {
	return t;
}

std::vector<float> DrawBezier::get_ith_control_point(int i) {
	return control_points[i];
}

void DrawBezier::set_ith_control_points(int i,float x, float y) {
	this->control_points[i][0] = x;
	this->control_points[i][1] = y;
}



void DrawBezier::drawPoint(std::vector<float> p) {
	glPointSize(5);
	glColor3d(0.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	{
		glVertex2f(p[0], p[1]);
	}
	glEnd();
}

void DrawBezier::drawLine(std::vector<float> p0, std::vector<float> p1) {
	glLineWidth(3);
	glColor3d(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	{
		glColor3d(0.0, 0.0, 0.0);
		glVertex2f(p0[0], p0[1]);
		glVertex2f(p1[0], p1[1]);
	}
	glEnd();
}

void DrawBezier::drawString(std::vector < float >p, std::string string){
	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2d(p[0] + 0.03, p[1] + 0.04);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, string.c_str());
}



//第一,第二引数p0, p1を第三引数t:1-tで内分する点の描画
std::vector<float> DrawBezier::drawInternalDivisionPoint(std::vector<float> p0, std::vector<float> p1, float t) {
	std::vector<float> p_internal = { (1 - t) * p0[0] + t * p1[0],(1 - t) * p0[1] + t * p1[1] }; //内分点

	glPointSize(5);
	glColor3d(0.0, 0.0, 1.0); //色に関しては要訂正
	glBegin(GL_POINTS);
	{
		glVertex2f(p_internal[0], p_internal[1]);
	}
	glEnd();

	return p_internal;

}



std::vector<float> DrawBezier::drawNDimensionBezier() {
	std::vector<std::vector<float>> internal_points;

	//点の描画 ここをやると全ての点が黒くなる可能性あり
	for (int i = 0; i < control_points.size(); i++) {
		std::string p = "p" + std::to_string(i) ;
		drawPoint(control_points[i]);
		drawString(control_points[i],p);
	}

	//線の描画、内分点の算出
	for (int i = 0; i < control_points.size()-1; i++) {
		drawLine(control_points[i] , control_points[i+1]);
		internal_points.push_back(drawInternalDivisionPoint(control_points[i],control_points[i+1], t));
	}

	return CalAndDrawInternalPoints(internal_points); //再帰関数

}



//中間点を求めるプログラム
std::vector<float> DrawBezier::CalAndDrawInternalPoints(std::vector<std::vector<float>> input_internal_points) {
	std::vector<std::vector<float>> internal_points;

	if (input_internal_points.size() == 1) { //中間点が一つになるまで繰り返す。
		return input_internal_points[0];
	}

	//線の描画、内分点の算出
	for (int i = 0; i < input_internal_points.size() - 1; i++) {
		drawLine(input_internal_points[i], input_internal_points[i + 1]);
		internal_points.push_back(drawInternalDivisionPoint(input_internal_points[i], input_internal_points[i + 1], t));
	}

	return CalAndDrawInternalPoints(internal_points);
}