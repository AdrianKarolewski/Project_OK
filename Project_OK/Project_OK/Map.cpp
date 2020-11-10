#include "Map.h"
#include <ctime>
#include <cstring>

int random(int max)
{
	srand(time(NULL));
	return rand() % (max + 1);
}
std::ostream& operator<<(std::ostream& o, const Map& m)
{
	for (const Point& p : m.m_v_points)
	{
		std::cout << p;
	}
	return o;
}
bool equals_string(std::string s1, std::string s2)
{
	if (s1.size() != s2.size())
	{
		return 0;
	}
	else
	{
		for (int i = 0; i < s1.size(); i++)
		{
			if (s1[i] != s2[i])
			{
				return 0;
			}
		}
	}
	return 1;
}
Map::Map(std::string name) : 
	m_name(name),
	stopper(new Timer())
{

}
void Map::Print_path_force() const
{
	for (int i = 0; i < best_path_force.size(); i++)
	{
		std::cout << best_path_force[i] << " ";
	}
	if (best_path_force.size() > 0)
	{
		std::cout << std::endl;
		std::cout << " czas: " << *stopper;
	}	
}
bool Map::Add_point(std::string name,int &&x, int &&y)
{
	for (const Point & p : m_v_points)
	{
		if (p.Get_x() == x)
		{
			if (p.Get_y() == y)
			{
				return 0;
			}
		}
	}
	m_v_points.push_back(Point(name, x, y));
	return 1;
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
void Map::Random_begin()
{
	srand(time(NULL));
	std::swap(m_v_points[0], m_v_points[static_cast<int>(rand() % m_v_points.size())]);
}
void Map::Custom_begin(std::string nazwa)
{
	int first{ -1 };
	for (int i = 0; i < m_v_points.size(); i++)
	{
		if (equals_string(m_v_points[i].Get_name(), nazwa))
		{	
			first = i;
		}
	}
	if (first == -1)
	{
		printf("Nie znaleziono wierzcholka o podanej nazwie!\n");
	}
	else
	{
		std::swap(m_v_points[0], m_v_points[first]);
	}
}
void Map::Count_path()
{
	stopper->Reset_timer();
	stopper->Start_timer();
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
	stopper->Stop_timer();
}
void Map::Del_all_points()
{
	m_v_points.clear();
}
void Map::Generating_instance(const int &how_m, const int &max_x, const int &max_y)
{
	for (int i = 0; i < how_m; i++)
	{
		while (!(Add_point(std::to_string(i), (random(max_x) + (random(i+1) + 1)) % max_x, (random(max_y) * random (i+3)) % max_y)));
	}
}