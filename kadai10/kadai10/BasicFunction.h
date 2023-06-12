#pragma once

#include <vector>
#include <string>

#define PI 3.14159265359

std::vector<double> mySplit(std::string str, char del); 
std::vector<std::vector<double>> readFile(std::string file_name);//vector<double>‚Ìvector‚ð•Ô‚·
double radToDegree(double input_rad);