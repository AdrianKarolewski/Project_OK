#include "Point.h"
std::ostream& operator<<(std::ostream& o,const Point& p)
{
	o << p.m_name <<" x: " << p.m_x << " y: " << p.m_y <<std::endl;
	return o;
}
Point::Point(std::string name, int x, int y)
{
	m_x = x;
	m_y = y;
	m_name = name;
}
Point::~Point()
{

}
std::string Point::Get_name()
{
	return m_name;
}
double Point::Count_distanse(const Point& other)
{
	return sqrt((other.m_x - m_x) * (other.m_x - m_x) + (other.m_y - m_y) * (other.m_y - m_y));
}
double Point::Get_x() const
{
	return m_x;
}
double Point::Get_y() const
{
	return m_y;
}