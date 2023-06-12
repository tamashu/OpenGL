#include "BasicFunction.h"
#include <fstream>
#include <iostream>

std::vector<double>mySplit(std::string str, char del) {
    int first = 0;
    int last = str.find_first_of(del);
    
    //std::cout << str << std::endl;

    std::vector<double> result;

    while (first < str.size()) {
        std::string subStr(str, first, last - first);

        result.push_back(std::stod(subStr));

        first = last + 1;
        last = str.find_first_of(del, first);

        if (last == std::string::npos) {
            last = str.size();
        }
    }

    
    return result;
}

std::vector<std::vector<double>>readFile(std::string file_name) {
    std::vector<std::vector<double>> ret;
    std::vector<double> line;

    std::ifstream ifs(file_name);
    std::string str;

    if (ifs.fail()) {
        std::cerr << "Failed to open file." << std::endl;
        exit(1);
    }
    while (getline(ifs, str)) {
        getline(ifs, str);
       // std::cout << str << std::endl;
        line = mySplit(str, ',');
 
        ret.push_back(line);
    }

    std::cout << ret.size() << std::endl;
    std::cout << ret[0].size() << std::endl;
    
    return ret;
}

double radToDegree(double input_rad) {
    double ret = input_rad * (180 / PI);
    return ret;
}