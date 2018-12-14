#ifndef BLACKLINE_H
#define BLACKLINE_H
#include<string>
#include<sstream>
#include<algorithm>
#include<iomanip>
#include <QLine>
#include"Arc_utils.h"

using std::string;

//arc(93600,93600,-0.50,-0.50,s,0.00,1.00,0,none,true);
class Blackline{
public:
    int start_time;
    int end_time;
    double x_s;
    double x_e;
    double y_s;
    double y_e;

    Blackline(int st, int et, double xs, double xe,double ys, double ye):
        start_time(st),end_time(et),x_s(xs), x_e(xe),y_s(ys), y_e(ye){}
    Blackline(const string &s){
        auto p1 = s.find('(');
        auto p2 = s.find(',');
        auto p3 = s.find(',', p2 + 1);
        auto p4 = s.find(',', p3 + 1);
        auto p5 = s.find(',', p4 + 1);
        auto p6 = s.find(',', p5 + 1);
        auto p7 = s.find(',', p6 + 1);
        auto p8 = s.find(',', p7 + 1);

        start_time = stoi(s, p1, p2);
        end_time = stoi(s, p2, p3);
        x_s = stod(s, p3, p4);
        x_e = stod(s, p4, p5);
        y_s = stod(s, p6, p7);
        y_e = stod(s, p7, p8);
    }
    Blackline(const QLine& l){
        double x1=l.x1();
        double y1=l.y1();
        double x2=l.x2();
        double y2=l.y2();
        to_arc_num(x1,y1);
        to_arc_num(x2,y2);
        x_s=x1;
        y_s=y1;
        x_e=x2;
        y_e=y2;
        start_time=end_time=0;
    }
    string str(){
        std::ostringstream s;
        s<<"arc(" << start_time << "," << end_time << ","
        << std::fixed << std::setprecision(2) << x_s << ","
        << std::fixed << std::setprecision(2) << x_e <<
           ",s,"
        << std::fixed << std::setprecision(2) << y_s << ","
        << std::fixed << std::setprecision(2) << y_e
        << ",0,none,true);";

        return s.str();
    }

    QLine qline(){
        double x1=x_s;
        double y1=y_s;
        double x2=x_e;
        double y2=y_e;
        to_mouse_num(x1,y1);
        to_mouse_num(x2,y2);
        return QLine(x1,y1,x2,y2);
    }

    Blackline& up(double a){
        if(y_s>1)
            y_s=(y_s-1)*a+1;
        if(y_e>1)
            y_e=(y_e-1)*a+1;
        return *this;
    }
    Blackline& down(double a){
        if(y_s<1)
            y_s=1-(1-y_s)*a;
        if(y_e<1)
            y_e=1-(1-y_e)*a;
        return *this;
    }
    Blackline& left(double a){
        if(x_s<0.5)
            x_s=0.5-(0.5-x_s)*a;
        if(x_e<0.5)
            x_e=0.5-(0.5-x_e)*a;
        return *this;
    }
    Blackline& right(double a){
        if(x_s>0.5)
            x_s=(x_s-0.5)*a+0.5;
        if(x_e>0.5)
            x_e=(x_e-0.5)*a+0.5;
        return *this;
    }

    Blackline& move_x(double a){
        x_s+=a;
        x_e+=a;
        return *this;
    }
    Blackline& move_y(double a){
            y_s+=a;
            y_e+=a;
        return *this;
    }
};

#endif // BLACKLINE_H
