#pragma once
#include<string>
#include<iostream>
#include<ostream>
#include<fstream>
#include<vector>
#include<iomanip>
#include<algorithm>

using std::ostream;
using std::cout;
using std::cin;
using std::string;
using std::vector;

int stoi(string& i, size_t b, size_t e) {
	auto it = i.begin();
	string s = string(it + b + 1, it + e);

	/*int index = 0;
	while ((index = s.find(' ')) != string::npos)
	{
		s.erase(index, 1);
	}*/

	return std::stoi(s);
}

double stod(string& i, size_t b, size_t e) {
	auto it = i.begin();
	string s = string(it + b + 1, it + e);

	/*int index = 0;
	while ((index = s.find(' ')) != string::npos)
	{
		s.erase(index, 1);
	}*/

	return std::stod(s);
}

//example:
//AudioOffset:83
class Offset {
public:
	int offset;
	Offset(int o) :offset(o) {};
	Offset(string& s) {
		auto p = s.find(':');
		offset = stoi(s, p, s.length()); 
	}

	void print(ostream& of) {
		of << "AudioOffset:" << offset << "\n";
	}

	Offset& speed(double b) {
		offset = double(offset) / b;
		return *this;
	}
};

//example:
//timing(0,100.00,4.00);
//timing(100,100.00,4.00);
class Timing {
public:
	int time;
	double bpm;
    double beat;

    Timing(int t, double b,double be) :time(t), bpm(b), beat(be) {};
	Timing(string& s) {
		auto p1 = s.find('(');
		auto p2 = s.find(',');
		auto p3 = s.find(',', p2 + 1);
        auto p4 = s.find(')');
		time = stoi(s, p1, p2);
		bpm = stod(s, p2, p3);
        beat = stod(s,p3,p4);
	}

	void print(ostream& of) {
        of << "timing(" << time << ","
           << std::fixed << std::setprecision(2)<< bpm << ","
           << std::fixed << std::setprecision(2)<< beat << ");\n";
	}

	Timing& move(int t) {
		if (time == 0)
			;
		else
			time += t;
		return *this;
	}

	Timing& speed(double b) {
		time = double(time) / b;
		bpm *= b;
		return *this;
	}
};

//example:
//(100,3);
class Note {
public:
	int time;
	int track;

	Note(int s, int t) :time(s), track(t) {};
	Note(string& s) {
		auto p1 = s.find('(');
		auto p2 = s.find(',');
		auto p3 = s.find(')');
		time = stoi(s, p1, p2);
		track = stoi(s, p2, p3);
	}

	void print(ostream& of) {
		of << "(" << time << "," << track << ");\n";
	}

	Note& move(int t) {
		time += t;
		return *this;
	}

	Note& speed(double b) {
		time = double(time) / b;
		return *this;
	}

	Note& mirror() {
		track = 5 - track;
		return *this;
	}
};

//example:
//hold(100,1000,2);
class Hold {
public:
	int start_time;
	int end_time;
	int track;

	Hold(int s, int e, int t) :start_time(s), end_time(e), track(t) {};
	Hold(string& s) {
		auto p1 = s.find('(');
		auto p2 = s.find(',');
		auto p3 = s.find(',', p2 + 1);
		auto p4 = s.find(')');
		start_time = stoi(s,p1, p2);
		end_time = stoi(s, p2, p3);
		track = stoi(s, p3, p4);
	}

	void print(ostream& of) {
		of << "hold(" << start_time << "," << end_time << "," << track << ");\n";
	}

	Hold& move(int t) {
		start_time += t;
		end_time += t;
		return *this;
	}

	Hold& speed(double b) {
		start_time = double(start_time) / b;
		end_time = double(end_time) / b;
		return *this;
	}

	Hold& mirror() {
		track = 5 - track;
		return *this;
	}
};

//example:
//arc(100,1000,0.00,0.62,b,1.00,1.00,0,none,false);
class Snake {
public:
	int start_time;
	int end_time;
	double x_s;
	double x_e;
	string snake_type;
	double y_s;
	double y_e;
	int color;
	string unknow;
	string mark;

	Snake(int st, int et, double xs, double xe, string t,
        double ys, double ye,int c,string ma="false")
		:start_time(st), end_time(et), x_s(xs), x_e(xe), snake_type(t),
        y_s(ys), y_e(ye), color(c),unknow("none"), mark(ma) {};
	Snake(string& s) {
		auto p1 = s.find('(');
		auto p2 = s.find(',');
		auto p3 = s.find(',', p2 + 1);
		auto p4 = s.find(',', p3 + 1);
		auto p5 = s.find(',', p4 + 1);
		auto p6 = s.find(',', p5 + 1);
		auto p7 = s.find(',', p6 + 1);
		auto p8 = s.find(',', p7 + 1);
		auto p9 = s.find(',', p8 + 1);
		start_time = stoi(s, p1, p2);
		end_time = stoi(s, p2, p3);
		x_s = stod(s, p3, p4);
		x_e = stod(s, p4, p5);
		snake_type = s.substr(p5 + 1, p6 - p5 - 1);
		y_s = stod(s, p6, p7);
		y_e = stod(s, p7, p8);
		color = stoi(s, p8, p9);
		unknow = "none";
		auto p10 = s.find_last_of(',');
		auto p11 = s.find(')');
		mark = s.substr(p10+1,p11-p10-1);
	}

	void print(ostream& of) {
		of << "arc(" << start_time << "," << end_time << ","
			<< std::fixed << std::setprecision(2) << x_s << ","
			<< std::fixed << std::setprecision(2) << x_e << ","
			<< snake_type << ","
			<< std::fixed << std::setprecision(2) << y_s << ","
			<< std::fixed << std::setprecision(2) << y_e << ","
			<< color<<","<<unknow << "," << mark << ");\n";
	}

	Snake& move(int t) {
		start_time += t;
		end_time += t;
		return *this;
	}

	Snake& speed(double b) {
		start_time = double(start_time) / b;
		end_time = double(end_time) / b;
		return *this;
	}

	Snake& mirror() {
		x_s = 1 - x_s;
		x_e = 1 - x_e;
		color = 1 - color;
		return *this;
	}
};

//example:
//arc(100,1000,0.75,0.75,s,1.00,1.00,0,none,true)[arctap(200),arctap(500)];
class Skynote {
public:
	int start_time;
	int end_time;
	double x_s;
	double x_e;
	string snake_type;
	double y_s;
	double y_e;
	int color;
	string unknow;
	string mark;
	vector<int> tap;

	Skynote(int st, int et, double xs, double xe, string t,
		double ys, double ye, int c)
		:start_time(st), end_time(et), x_s(xs), x_e(xe), snake_type(t),
		y_s(ys), y_e(ye), color(c),unknow("none"), mark("true"), tap(vector<int>()) {};
	Skynote(string& s) {
		auto p1 = s.find('(');
		auto p2 = s.find(',');
		auto p3 = s.find(',', p2 + 1);
		auto p4 = s.find(',', p3 + 1);
		auto p5 = s.find(',', p4 + 1);
		auto p6 = s.find(',', p5 + 1);
		auto p7 = s.find(',', p6 + 1);
		auto p8 = s.find(',', p7 + 1);
		auto p9 = s.find(',', p8 + 1);
		start_time = stoi(s, p1, p2);
		end_time = stoi(s, p2, p3);
		x_s = stod(s, p3, p4);
		x_e = stod(s, p4, p5);
		snake_type = s.substr(p5 + 1, p6 - p5 - 1);
		y_s = stod(s, p6, p7);
		y_e = stod(s, p7, p8);
		color = stoi(s, p8, p9);
		unknow = "none";
		mark = "true";
		tap = vector<int>();

		auto q1 = s.find('(', p1 + 1);
		size_t q2;
		while (true) {
			q2 = s.find(')', q1);
			tap.push_back(stoi(s, q1, q2));
			q1 = s.find('(', q2);
			if (q1 == string::npos)
				break;
		}
	}

	void print(ostream& of) {
		of << "arc(" << start_time << "," << end_time << ","
			<< std::fixed << std::setprecision(2) << x_s << ","
			<< std::fixed << std::setprecision(2) << x_e << ","
			<< snake_type << ","
			<< std::fixed << std::setprecision(2) << y_s << ","
			<< std::fixed << std::setprecision(2) << y_e << ","
			<< color << "," << unknow << "," << mark << ")[";
		for (auto i = tap.begin(); i != tap.end() - 1; i++)
			of << "arctap(" << *i << "),";
		of << "arctap(" << tap.back() << ")];\n";
	}

	Skynote& move(int t) {
		start_time += t;
		end_time += t;
		std::for_each(tap.begin(), tap.end(), [t](int& a) {a += t; });
		return *this;
	}

	Skynote& speed(double b) {
		start_time = double(start_time) / b;
		end_time = double(end_time) / b;
		std::for_each(tap.begin(), tap.end(), [b](int& a) {a = double(a) / b; });
		return *this;
	}

	Skynote& mirror() {
		x_s = 1 - x_s;
		x_e = 1 - x_e;
		return *this;
	}
};
