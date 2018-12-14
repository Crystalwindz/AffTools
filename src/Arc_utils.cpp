#include "Arc_utils.h"
#include<string>
#include<sstream>
#include<iomanip>
#include<cmath>
#include"Blackline.h"
using std::string;

void to_arc_num(double &x,double &y){
    x=std::round((x/980.0*2.8-0.9)*100)/100.0;
    y=y<280.0
            ?std::round(((280.0-y)/280.0*0.6+1.0)*100)/100.0:
           std::round(((560.0-y)/560.0*2.4-0.2)*100)/100.0;
}

void to_mouse_num(double &x,double &y){
    x=(x+0.9)/2.8*980.0;
    y=y>1.0
            ?280.0-(y-1.0)/0.6*280.0
           :560.0-(y+0.2)/2.4*560.0 ;
}

int stoi(const string& i, size_t b, size_t e) {
    auto it = i.begin();
    string s = string(it + b + 1, it + e);

    return std::stoi(s);
}

double stod(const string& i, size_t b, size_t e) {
    auto it = i.begin();
    string s = string(it + b + 1, it + e);

    return std::stod(s);
}
