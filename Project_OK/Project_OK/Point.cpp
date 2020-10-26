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