#pragma once

#include <iostream>
#include <string>
#include<vector>

class Point
{
private:
	int m_x = 0, m_y = 0;
	std::string m_name;
public:
	friend std::ostream& operator<<(std::ostream& o, const Point& p);

	Point(std::string name,int x, int y);
	~Point();
	std::string Get_name();
	double Get_x() const;
	double Get_y() const;
	double Count_distanse(const Point& other);
};

