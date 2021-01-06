#include "Map.h"
#include <ctime>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <thread>
#include <mutex>
std::mutex my_mutex_to_ant;
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
Map::Map(std::string name) : 
	m_name(name),
	stopper_force(new Timer()),
	stopper_meta(new Timer())
{

}
void Map::Print_path_force() const
{
	std::cout << "Algorytm silowy" << std::endl;
	for (int i = 0; i < best_path_force.size(); i++)
	{
		std::cout << best_path_force[i] << " ";
	}
	if (best_path_force.size() > 0)
	{
		std::cout << std::endl;
		std::cout << " czas: " << *stopper_force << " dystans: "<<best_distans_force<<std::endl;
	}	
}
void Map::Print_path_meta() const
{
	std::cout << "Algorytm mrowkowy" << std::endl;
	for (int i = 0; i < best_path_meta.size(); i++)
	{
		std::cout << best_path_meta[i].Get_name() << " ";
	}
	if (best_path_meta.size() > 0)
	{
		std::cout << std::endl;
		std::cout << " czas: " << *stopper_meta << " dystans: " << best_distans_meta<<std::endl;
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
	std::swap(m_v_points[0], m_v_points[static_cast<int>(rand() % m_v_points.size())]);
}
void Map::Custom_begin(std::string nazwa)
{
	int first{ -1 };
	for (int i = 0; i < m_v_points.size(); i++)
	{
		if (m_v_points[i].Get_name() == nazwa)
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
// algorytm si³owy 
void Map::Count_path()
{
	stopper_force->Reset_timer();
	stopper_force->Start_timer();
	if (m_v_points.size() < 1)
	{
		return;
	}
	best_path_force.clear();
	std::vector<Point> h_v_points = m_v_points;
	best_path_force.push_back(h_v_points[0].Get_name());
	double distance_result = 0;
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
		best_distans_force += min_distans;
		best_path_force.push_back(h_v_points[next_point].Get_name());
		h_v_points.erase(h_v_points.begin() + current_point);
	
		if (current_point < next_point)
		{
			next_point--;
		}
		current_point = next_point;
	}
	best_distans_force += h_v_points[next_point].Count_distanse(m_v_points[0]);
	best_path_force.push_back(m_v_points[0].Get_name());
	stopper_force->Stop_timer();
}
void Map::Del_all_points()
{
	m_v_points.clear();
}
void Map::Generating_instance(const int &how_m, const int &max_x, const int &max_y)
{
	std::fstream file;
	file.open("dane.txt", std::ios_base::trunc);
	file <<how_m<< std::endl;
	int x{ 0 };
	int y{ 0 };
	for (int i = 0; i < how_m; i++)
	{
		x = (random(max_x) + (random(i + 1) + 1) % max_x);
		y = ((random(max_y) * random(i + 3)) % max_y);
		while (!(Add_point(std::to_string(i + 1),std::move(x),std::move(y) )))
		{
			x = (random(max_x) + (random(i + 1) + 1) % max_x);
			y = ((random(max_y) * random(i + 3)) % max_y);
		}
		file << i+1<<" "<<x<<" "<<y<< std::endl;
	}
	file.close();
}
void Map::Read_instance()
{
	std::fstream file;
	file.open("dane.txt", std::ios_base::in);

	int how_m;
	int wsp[2]{ 0,0 };
	int p{ 0 };

	std::string help_s;

	std::getline(file, help_s);
	how_m = stoi(help_s);
	
	while (std::getline(file, help_s))
	{
		std::cout << help_s;
		int j = 0;
		std::string h_string = "";
		for (int i = 0; i < help_s.size(); i++)
		{
			if (help_s[i] != ' ')
			{
				h_string += help_s[i];
			}	
			if ((help_s[i] == ' ')||(i == help_s.size() - 1))
			{
				if (j == 0)
				{
					p = stoi(h_string);
					h_string = "";
					j++;
				}
				else
				{
					wsp[j - 1] = stoi(h_string);
					h_string = "";
					j++;
				}
				if (j == 3)
				{
					break;
				}			
			}
		}
		Add_point(std::to_string(p),std::move(wsp[0]),std::move(wsp[1]));
	}
	file.close();
}
 double** Map::Initialize_Pheromone(int vertex_count)
{
	double** pheromone = new double* [vertex_count];
	for (int i = 0; i < vertex_count; ++i)
	{
		pheromone[i] = new double[vertex_count];
	}	
	for (int i = 0; i < vertex_count; i++)
	{
		for (int j = 0; j < vertex_count; j++)
		{
			if (i != j)
			{
				pheromone[i][j] = pheromone_INIT;
			}			
			else
			{
				pheromone[i][j] = 0;
			}				
		}
	}
	return pheromone;
}
int Map::Next_Vertex(int ind, double ** pheromone, const std::vector<bool> & visitted)
{
	double suma = 0;
	double * prob = new double[m_v_points.size()];
	double x;
	for (int i = 0; i < m_v_points.size(); i++)//suma prawdopodobieñstw
	{
		if (i != ind && !visitted[i])
		{
			x = 1/m_v_points[ind].Count_distanse(m_v_points[i]);
			suma += pow(pheromone[ind][i], pheromone_importance) * pow(x, distance_importance);
		}
	}
	for (int i = 0; i < m_v_points.size(); i++)//poszczególne prawdopodobieñstwa
	{
		if (i != ind && !visitted[i])
		{
			x = 1 / m_v_points[ind].Count_distanse(m_v_points[i]);
			prob[i] = (pow(pheromone[ind][i], pheromone_importance) * pow(x, distance_importance)) / suma;
		}
		else
		{
			prob[i] = 0;
		}
	}
	double draw = ((double)((int)rand() % 100) / 100.0); // losuje double od 0 do 1
	double sumado = 0;
	for (int i = 0; i < m_v_points.size() - 1; i++)
	{
		if ((draw >= sumado) && (draw < (sumado + prob[i])))
		{
			return i;		
		}
		sumado += prob[i];
	}
}
void Ant(int ind, double** pheromones, Map * m)
{
	std::vector<bool> visited(m->m_v_points.size());

	std::vector<Point> points;
	points.reserve(m->m_v_points.size() + 1);
	bool koniec = false;
	while (!koniec)
	{
		my_mutex_to_ant.lock();
		points.push_back(m->m_v_points[ind]);
		my_mutex_to_ant.unlock();
		visited[ind] = true;
		koniec = true;
		for (int i = 0; i < m->m_v_points.size(); i++)
		{
			if (!visited[i])
			{
				koniec = false;
				break;
			}
		}
		if (koniec)
		{
			my_mutex_to_ant.lock();
			points.push_back(m->m_v_points[0]);
			int x, y;
			
			for (int i = 0; i < points.size() - 1; i++)
			{
				x = stoi(points[i].Get_name()) - 1;
				y = stoi(points[i + 1].Get_name()) - 1;
				pheromones[x][y] += 1 / points[i].Count_distanse(points[i+1]);
			}
			for (int i = 0; i < m->m_v_points.size(); i++)
			{
				for (int j = 0; j < m->m_v_points.size(); j++)
				{
					pheromones[i][j] *= m->evaporation;
				}
			}
			my_mutex_to_ant.unlock();
			return;
		}		
		ind = m->Next_Vertex(ind, pheromones, visited);
	}
}
void Map::AntHill()
{
	stopper_meta->Reset_timer();
	stopper_meta->Start_timer();
	best_path_meta.clear();
	int vertex_count = m_v_points.size();
	double ** pheromone = Initialize_Pheromone(vertex_count);

	int ind{ 0 };
	for (int i = 0; i < m_v_points.size(); i++)
	{	
		ind = rand() % m_v_points.size();
	
		std::thread t1(Ant, ind, pheromone, this);
		ind = rand() % m_v_points.size();

		std::thread t2(Ant, ind, pheromone, this);
		ind = rand() % m_v_points.size();

		std::thread t3(Ant, ind, pheromone, this);
		ind = rand() % m_v_points.size();

		std::thread t4(Ant, ind, pheromone, this);
		ind = rand() % m_v_points.size();

		std::thread t5(Ant, ind, pheromone, this);
		ind = rand() % m_v_points.size();

		std::thread t6(Ant, ind, pheromone, this);

		t1.join();
		t2.join();
		t3.join();
		t4.join();
		t5.join();
		t6.join();
	}
	double best = 0;
	int vertex = 0;
	int next = 0;

	std::vector<bool> been_to(vertex_count);
	been_to[0] = 1;

	for (int i = 0; i < vertex_count; i++)
	{
		for (int j = 0; j < vertex_count; j++)
		{
			if (been_to[j] == false)
			{
				if (best < pheromone[vertex][j])
				{
					best = pheromone[vertex][j];
					next = j;
				}
			}
		}
		std::cout << "teraz - " << vertex << " " << "potem - " << next << std::endl;
		
		been_to[next] = true;
		best_path_meta.push_back(m_v_points[vertex]);
		vertex = next;
		best = 0;
	}
	////////////////////////////////////////////////////////////
	stopper_meta->Stop_timer();
	best_path_meta.push_back(m_v_points[0]);
	best_distans_meta = 0;
	
	for (int i = 0; i < vertex_count; i++)
	{	
		best_distans_meta += best_path_meta[i].Count_distanse(best_path_meta[i + 1]);	
	}
	for (int i = 0; i < vertex_count; i++)
	{
		delete[] pheromone[i];
	}
	delete[] pheromone;
}