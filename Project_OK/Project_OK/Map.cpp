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