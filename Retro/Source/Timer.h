#pragma once
#include<chrono>
#include<iostream>

class Timer
{
	public:
		Timer();
		~Timer();

		void Start();
		void Stop();

		friend std::ostream& operator<<(std::ostream& os, const Timer& dt);

	private:
		std::chrono::steady_clock::time_point m_Start;
		std::chrono::steady_clock::time_point m_Stop;
		float m_LastTimeMS = 0.0f;
};

