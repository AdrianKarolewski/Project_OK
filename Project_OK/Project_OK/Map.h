#pragma once
#include "Point.h"
#include <vector>

class Map
{
private:
	std::vector<Point> m_v_points;
	std::vector<std::string> best_path_force;
	std::string m_name;
public:
	Map(std::string m_name);
	void Print_points() const;
	void Print_path_force() const;
	bool Add_point(std::string name, int &&x, int&& y);
	void Del_point(std::string name);
	void Del_all_points();
	void Random_begin();
	void Custom_begin(std::string name);
	void Count_path();
	void Generating_instance(const int &how_m, const int &max_x, const int &max_y);
};

