#pragma once
#include "Point.h"
#include <vector>

class Map
{
private:
	std::vector<Point> m_v_points;
	std::string m_name;
public:
	Map(std::string m_name);
	void Print_points() const;
	void Add_point(std::string name, int &x, int& y);
	void Del_point(std::string name);
};

