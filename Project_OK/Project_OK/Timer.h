#pragma once
#include <chrono>
#include <iostream>

class Timer
{
private:
	std::chrono::high_resolution_clock::time_point start;
	double time;
public:
	friend std::ostream& operator<<(std::ostream& o, const Timer& t);
	Timer();
	~Timer();
	void Start_timer();
	void Stop_timer();
	void Reset_timer();
	double Get_time();
};

