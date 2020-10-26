#include "Map.h"

Map::Map(std::string name)
{
	m_name = name;
}
void Map::Print_points() const
{
	for (const Point & p : m_v_points)
	{
		std::cout << p;
	}
}
void Map::Print_path_force() const
{
	for (int i = 0; i < best_path_force.size(); i++)
	{
		std::cout << best_path_force[i]<<" ";
	}
	std::cout << std::endl;
}
void Map::Add_point(std::string name,int &x, int &y)
{
	m_v_points.push_back(Point(name, x, y));
}
void Map::Del_point(std::string name)
{
	again:
	for (int i = 0; i < m_v_points.size(); i++)
	{
		if (m_v_points[i].Get_name() == name);
		{
			m_v_points.erase(m_v_points.begin() + i);
			goto again;
		}
	}
}
void Map::Count_path()
{
	if (m_v_points.size() < 1)
	{
		return;
	}
	best_path_force.clear();
	std::vector<Point> h_v_points = m_v_points;
	best_path_force.push_back(h_v_points[0].Get_name());

	double current_distance = 0;
	int current_point = 0;
	int next_point = 0;
	while (h_v_points.size() > 1)
	{
		double min_distans = 100000000000000000;
		for (int j = 0; j < h_v_points.size(); j++)
		{
			if (j != current_point)
			{
				current_distance = h_v_points[current_point].Count_distanse(h_v_points[j]);
				if (current_distance < min_distans)
				{
					min_distans = current_distance;
					next_point = j;
				}
			}
		}
		best_path_force.push_back(h_v_points[next_point].Get_name());
		h_v_points.erase(h_v_points.begin() + current_point);
		std::cout << std::endl;
		if (current_point < next_point)
		{
			next_point--;
		}
		current_point = next_point;
	}
}