#include "Map.h"


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
// algorytm siłowy 
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

	best_distans_force = 0;
	double current_distance = 0;
	int current_point = 0;
	int next_point = 0;
	while (h_v_points.size() > 1)
	{
		double min_distans = 999999999999999;
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
 int Map::Next_Vertex(int ind, double** pheromone, const std::vector<bool>& visitted, double * prob)
 {
	 std::random_device device;
	 std::mt19937 generator(device());
	 std::uniform_int_distribution<int> distribution(0, 100000000);
	 double suma = 0;
	 
	 double x;
	 for (int i = 0; i < m_v_points.size(); i++)//suma prawdopodobieñstw
	 {
		 if (i != ind && !visitted[i])
		 {
			 x = 1 / m_v_points[ind].Count_distanse(m_v_points[i]);
			 mutex_to_pheromone.lock();
			 suma += pow(pheromone[ind][i], pheromone_importance) * pow(x, distance_importance);
			 mutex_to_pheromone.unlock();
		 }
	 }
	 for (int i = 0; i < m_v_points.size(); i++)//poszczególne prawdopodobieñstwa
	 {
		 if (i != ind && !visitted[i])
		 {
			 x = 1 / m_v_points[ind].Count_distanse(m_v_points[i]);
			 mutex_to_pheromone.lock();
			 prob[i] = (pow(pheromone[ind][i], pheromone_importance) * pow(x, distance_importance)) / suma;
			 mutex_to_pheromone.unlock();
		 }
		 else
		 {
			 prob[i] = 0;
		 }
	 }
	 double draw = ((double)((int)distribution(generator)) / 100000000.0); // losuje double od 0 do 1
	 while (visitted[0] && draw == 0)
	 {
		 draw = ((double)((int)distribution(generator)) / 100000000.0);
	 }
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
 void Map::Ant(int ind, double** pheromones, std::vector<Point> & best_iter, double & bestlen)
 {
	 std::vector<bool> visited(m_v_points.size());
	 std::vector<Point> points;
	 double* p = new double[m_v_points.size()];
	 points.reserve(m_v_points.size() + 1);
	 bool koniec = false;
	 double dodaj;
	 while (!koniec)
	 {
		 my_mutex_to_ant.lock();
		 points.push_back(m_v_points[ind]);
		 my_mutex_to_ant.unlock();
		 std::cout << ind << " ";
		 visited[ind] = true;
		 koniec = true;
		 for (int i = 0; i < m_v_points.size(); i++)
		 {
			 if (!visited[i])
			 {
				 koniec = false;
				 break;
			 }
		 }
		 if (koniec)
		 {
			 points.push_back(points[0]);	 
			 break;
		 }
		 ind = Next_Vertex(ind, pheromones, visited, p);
	 }
	 double length = 0;
	 for (int i = 0; i < points.size() - 1; i++)
	 {
		 length += points[i].Count_distanse(points[i + 1]);
	 }
	 if (length < bestlen)
	 {
		 bestlen = length;
		 best_iter.clear();
		 for (int i = 0; i < points.size(); i++)
			 best_iter.push_back(points[i]);
	 }
	 delete[] p;
 }
void threadwork(Map * m, double ** p)
{
	int ind{ 0 };
	std::vector<Point> best_path_for_iteration;
	double best_lenth_iter = 99999999999999;
	m->stopper_meta->Reset_timer();
	while(m->stopper_meta->Get_time() < 5)
	{
		m->stopper_meta->Stop_timer();
		m->stopper_meta->Start_timer();

		best_lenth_iter = 99999999999999;
		best_path_for_iteration.clear();

		for (int i = 0; i < m->m_v_points.size(); i++)
		{
			ind = rand() % m->m_v_points.size();
			m->Ant(ind, p, best_path_for_iteration, best_lenth_iter);
		}
		int x, y;
		
		m->mutex_to_pheromone.lock();
		for (int i = 0; i < best_path_for_iteration.size() - 1; i++)
		{
			x = stoi(best_path_for_iteration[i].Get_name()) - 1;
			y = stoi(best_path_for_iteration[i + 1].Get_name()) - 1;
			p[x][y] += m->Qdens / best_path_for_iteration[i].Count_distanse(best_path_for_iteration[i + 1]);
		}
		for (int i = 0; i < m->m_v_points.size(); i++)
		{
			for (int j = 0; j < m->m_v_points.size(); j++)
			{
				p[i][j] *= m->evaporation;
			}
		}
		m->mutex_to_pheromone.unlock();

		m->my_mutex_to_ant.lock();
		if (best_lenth_iter < m->best)
		{
			m->best = best_lenth_iter;
			m->best_path_meta.clear();
			for (int i = 0; i < best_path_for_iteration.size(); i++)
				m->best_path_meta.push_back(best_path_for_iteration[i]);
		}	
		m->my_mutex_to_ant.unlock();	
	}
}
void Map::AntHill()
{
	stopper_meta->Reset_timer();
	stopper_meta->Start_timer();
	int vertex_count = m_v_points.size();
	for (int i = 0; i < 1; i++)
	{
		double** pheromone = Initialize_Pheromone(vertex_count);

		std::thread t1(threadwork, this, pheromone);
		std::thread t2(threadwork, this, pheromone);
		std::thread t3(threadwork, this, pheromone);
		std::thread t4(threadwork, this, pheromone);
		std::thread t5(threadwork, this, pheromone);

		t1.join();
		t2.join();
		t3.join();
		t4.join();
		t5.join();

		stopper_meta->Stop_timer();

		best_distans_meta = best;

		for (int i = 0; i < vertex_count; i++)
		{
			delete[] pheromone[i];
		}
		delete[] pheromone;
	}
	
}