#pragma once
#include "Point.h"
#include <vector>
#include "Timer.h"

class Map
{
private:
	std::vector<Point> m_v_points;
	std::vector<std::string> best_path_force;
	std::string m_name;
	Timer* stopper;
	double best_distans{ 0 };
public:
	friend std::ostream& operator<<(std::ostream& o, const Map & m);

	Map(std::string m_name);
	void Print_path_force() const;
	bool Add_point(std::string name, int &&x, int&& y);
	void Del_point(std::string name);
	void Del_all_points();
	void Random_begin();
	void Custom_begin(std::string name);
	void Count_path();
	void Generating_instance(const int &how_m, const int &max_x, const int &max_y);
	void Read_instance();
	void AntHill();
	double** Initialize_Pheromone(int vertex_count);
	int Next_Vertex(int ind, double ** pheromones, bool * visitted);
	void Ant(int ind, double** pheromones);
};

