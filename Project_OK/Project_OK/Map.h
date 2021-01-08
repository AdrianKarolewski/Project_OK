#pragma once
#include "Point.h"
#include <vector>
#include "Timer.h"

class Map
{
private:
	std::vector<Point> m_v_points;
	std::vector<std::string> best_path_force;
	std::vector<Point> best_path_meta;
	std::string m_name;
	Timer* stopper_force;
	double best_distans_force{ 0 };

	Timer* stopper_meta;
	double best_distans_meta{ 0 };

	double pheromone_INIT = 20;
	const double pheromone_importance = 2;
	const double distance_importance = 5;
	const double evaporation = 0.5;
	const double Qdens = 2;

public:
	friend std::ostream& operator<<(std::ostream& o, const Map & m);
	friend void Ant(int, double**, Map* );
	Map(std::string m_name);
	void Print_path_force() const;
	void Print_path_meta() const;
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
	int Next_Vertex(int ind, double ** pheromones, const std::vector<bool>& visitted);

};

