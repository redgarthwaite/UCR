 #include<iostream>

using namespace std;

#ifndef Point_H
#define Point_H

class Point
{

public:
	//constructors of this class
	Point(double xx, double yy) : x(xx), y(yy) {};
	Point() : x(0), y(0) {};
	Point(string);
	
	void operator =(Point a) { x = a.x; y = a.y;};

    	friend std::ostream& operator <<(std::ostream &s, Point a); // coudouble << a;
    	friend std::istream& operator >>(std::istream &s, Point &a);// cin >> a;

	double x;
	double y;

};
bool less_y(const Point& p1, const Point& p2);
bool less_x(const Point& p1, const Point& p2);

#endif;
