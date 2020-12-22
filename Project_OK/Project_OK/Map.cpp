#include "Map.h"
#include <ctime>
#include <cstring>
#include <fstream>
#include <cstdlib>
const double pheromone_INIT = 0.5;
const double pheromone_importance = 1;
const double distance_importance = 3;
const double evaporation = 0.9;
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
		std::cout << " czas: " << *stopper << " dystans: "<<best_distans;
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
		best_distans += min_distans;
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
		pheromone[i] = new double[vertex_count];
	for (int i = 0; i<vertex_count; i++)
		for (int j = 0; j < vertex_count; j++)
		{
			if (i != j)
				pheromone[i][j] = pheromone_INIT;
			else
				pheromone[i][j] = 0;
		}
	return pheromone;
}
int Map::Next_Vertex(int ind, double ** pheromone, bool * visitted)
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
			x = 1/m_v_points[ind].Count_distanse(m_v_points[i]);
			prob[i] = (pow(pheromone[ind][i], pheromone_importance)*pow(x, distance_importance))/suma;
		}
		else
		{
			prob[i] = 0;
		}
	}
	/*std::cout << "prob" << std::endl;
	for (int i = 0; i < m_v_points.size(); i++)
	{
		std::cout << prob[i] << " ";
	}
	std::cout << std::endl; */
	double ** sections = new double*[m_v_points.size()];//tworzenie sekcji prawwdopodobieñstwa
	double sumado = 0;
	for (int i = 0; i < m_v_points.size(); i++)
	{

			sections[i] = new double[2];
			/*if (i == 0)
			{
				sections[i][0] = sumado;
				sections[i][1] = prob[i];
			}
			else //if (i == m_v_points.size() - 1)
			{*/
				sections[i][0] = sumado;
				sections[i][1] = sumado + prob[i];
			//}
			sumado += prob[i];
			/*else
			{
				sections[i][0] = prob[i - 1];
				sections[i][1] = prob[i-1]+prob[i];
			} */
	}
	/*for (int i = 1; i < m_v_points.size() + 1; i++)
	{
		if (i != ind && !visitted[i])
		{
			sections[i] = prob[i-1] + sections[i - 1];
		}
		else
		{
			sections[i] = sections[i - 1];
		}
	}*/
	/*std::cout << "sections" << std::endl;
	for (int i = 0; i < m_v_points.size(); i++)
	{
		std::cout << sections[i][0] << " " << sections[i][1]<<std::endl;
	} */
	double draw = ((double)((int)rand()%100) / 100.0); // losuje double od 0 do 1
	//std::cout << draw << std::endl;
	int next_vertex;
	for (int i = 0; i < m_v_points.size()-1; i++)
	{
		if (draw >= sections[i][0] && draw < sections[i][1])
		{
			return i;		
		}
	}
}
void Map::Ant(int ind, double** pheromones)
{
	bool* visitted = new bool[m_v_points.size()];
	for (int i = 0; i < m_v_points.size(); i++)
	{
		visitted[i] = false;
	}
	bool koniec = false;
	while (!koniec)
	{
		visitted[ind] = true;
		koniec = true;
		for (int i = 0; i < m_v_points.size(); i++)
		{
			if (!visitted[i])
			{
				koniec = false;
				break;
			}
		}
		if (koniec)
			return;
		int next_ind = Next_Vertex(ind, pheromones, visitted);
		for (int i = 0; i < m_v_points.size(); i++)
		{
			for (int j = 0; j < m_v_points.size(); j++)
			{
				pheromones[i][j] *= evaporation;
			}
		}
		std::cout <<"index: "<<ind<< " next index: " << next_ind << std::endl;
		pheromones[ind][next_ind]+=1/m_v_points[ind].Count_distanse(m_v_points[next_ind]);
		ind = next_ind;
	}
	delete visitted;
}
void Map::AntHill()
{
	int vertex_count = m_v_points.size();
	/*double suma = 0;
	for (int i = 0; i < 1000; i++)
		suma += ((double)((int)rand() % 101) / 100.0);
	std::cout << suma / 1000 << std::endl;*/
	double ** pheromone = Initialize_Pheromone(vertex_count);
	bool* visitted = new bool[vertex_count];
	for (int i = 0; i < vertex_count; i++)
	{
		visitted[i] = false;
	}
	//std::cout <<"next vertex = " << Next_Vertex(0, pheromone, visitted)<<std::endl;
	//visitted[4] = true;
	//std::cout << Next_Vertex(4, pheromone, visitted)<<std::endl;
	for (int i = 0; i < 10; i++)
	{
		int ind = rand() % m_v_points.size();
		Ant(ind, pheromone);
		//std::cout << Next_Vertex(4, pheromone, visitted);
		std::cout << std::endl;
	}
	for (int i = 0; i < vertex_count; i++)
	{
		for (int j = 0; j < vertex_count; j++)
		{
			std::cout << pheromone[i][j]<<" ";
		}
		std::cout << std::endl;
	}
	std::vector<std::string> best_path_meta;
	double best = 0;
	int first = 0;
	int vertex = first;
	int next = first;
	bool* been_to = new bool[vertex_count];
	for (int i = 0; i < vertex_count; i++)
		been_to[i] = false;
	been_to[first] = true;
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
		for (int i = 0; i < vertex_count; i++)
			std::cout<<been_to[i]<<std::endl;
		been_to[next] = true;
		best_path_meta.push_back(m_v_points[vertex].Get_name());
		vertex = next;
		best = 0;
	}
	best_path_meta.push_back(m_v_points[first].Get_name());
	for (int i = 0; i < m_v_points.size() + 1; i++)
		std::cout << best_path_meta[i] << " ";
	std::cout << std::endl;
	for (int i = 0; i < vertex_count; i++)
	{
		delete[] pheromone[i];
	}
	delete[] pheromone;
	//delete[] visitted;
}