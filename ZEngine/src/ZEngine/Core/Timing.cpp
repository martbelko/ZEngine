#include "zpch.hpp"
#include "Timing.hpp"

#include "ZEngine/Core/Log.hpp"

namespace ZEngine {

	Timer::Timer(std::string_view name)
		: m_Name(name)
	{
		m_StartPoint = std::chrono::high_resolution_clock::now();
	}

	Timer::~Timer()
	{
		if (!m_Stopped)
			Stop();
	}

	void Timer::Stop()
	{
		auto endTimePoint = std::chrono::high_resolution_clock::now();

		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartPoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();

		m_Stopped = true;

		ZE_CORE_TRACE("Duration: % ms", (end - start) / 1000.0f);
	}

}