#include "Timer.h"
std::ostream& operator<<(std::ostream& o, const Timer& t)
{
	o << t.time;
	return o;
}
Timer::Timer()
{
	time = 0;
}
Timer::~Timer()
{

}
void Timer::Start_timer()
{
	start = std::chrono::high_resolution_clock::now();
}
void Timer::Stop_timer()
{
	time += std::chrono::duration_cast<std::chrono::duration<double>>
		(std::chrono::high_resolution_clock::now() - start).count();
}
void Timer::Reset_timer()
{
	time = 0;
}
double Timer::Get_time()
{
	return time;
}