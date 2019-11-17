#pragma once

#include <string>
#include <chrono>

namespace ZEngine {

	class Timer
	{
	public:
		Timer(std::string_view name);
		~Timer();

		void Stop();
	private:
		std::string m_Name;
		std::chrono::time_point<std::chrono::steady_clock> m_StartPoint;
		bool m_Stopped = false;
	};

}
