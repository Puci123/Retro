#include "Timer.h"

Timer::Timer(){}

Timer::~Timer(){}

void Timer::Start()
{
	m_Start = std::chrono::high_resolution_clock::now();
}

void Timer::Stop()
{
	m_Stop = std::chrono::high_resolution_clock::now();
	auto diuration = std::chrono::duration_cast<std::chrono::microseconds>(m_Stop - m_Start);

	m_LastTimeMS = diuration.count() / 1000.0f;
}

std::ostream& operator<<(std::ostream& os, const Timer& dt)
{
	os << dt.m_LastTimeMS << "ms";
	return os;
}
