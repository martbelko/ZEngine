#pragma once

#include "Core.hpp"

namespace ZEngine {

	class Logger
	{
	public:
		enum class Colors
		{
			RED,
			GREEN,
			BLUE,
			WHITE,
			YELLOW,
			PURPLE,
			CYAN
		};

		Logger() = default;

		Logger(const std::string& name);

		void trace(const char* format);
		void info(const char* format);
		void warn(const char* format);
		void error(const char* format);
		void fatal(const char* format);

		template<typename T, typename... Targs>
		void trace(const char* format, T value, Targs... Fargs)
		{
			changeOutputColor(Colors::GREEN);
			printLoggerName();
			print(format, value, Fargs...);
		}

		template<typename T, typename... Targs>
		void info(const char* format, T value, Targs... Fargs)
		{
			changeOutputColor(Colors::CYAN);
			printLoggerName();
			print(format, value, Fargs...);
		}

		template<typename T, typename... Targs>
		void warn(const char* format, T value, Targs... Fargs)
		{
			changeOutputColor(Colors::WHITE);
			printLoggerName();
			print(format, value, Fargs...);
		}

		template<typename T, typename... Targs>
		void error(const char* format, T value, Targs... Fargs)
		{
			changeOutputColor(Colors::YELLOW);
			printLoggerName();
			print(format, value, Fargs...);
		}

		template<typename T, typename... Targs>
		void fatal(const char* format, T value, Targs... Fargs)
		{
			changeOutputColor(Colors::RED);
			printLoggerName();
			print(format, value, Fargs...);
		}
	private:
		void print(const char* format);

		template<typename T, typename... Targs>
		void print(const char* format, T value, Targs... Fargs)
		{
			for (; *format != 0; ++format)
			{
				if (*format == '/' && *(format + 1) == '%')
				{
					format += 1;
				}
				else if (*format == '%')
				{
					std::cout << value;
					print(format + 1, Fargs...);
					return;
				}
				std::cout << *format;
			}
			std::cout << '\n';
		}

		void printLoggerName();

		void changeOutputColor(Logger::Colors color);
	private:
		std::string m_strName;
		HANDLE hStdout;
	};

	class Log
	{
	public:
		static void Init()
		{
			s_EngineLogger = std::make_shared<Logger>("ZEngine");
			s_ClientLogger = std::make_shared<Logger>("APP");
		}

		static inline std::shared_ptr<Logger>& GetCoreLogger() { return s_EngineLogger; }
		static inline std::shared_ptr<Logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<Logger> s_EngineLogger;
		static std::shared_ptr<Logger> s_ClientLogger;
	};

}

// Core log macros
#define ZE_CORE_TRACE(...)    Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ZE_CORE_INFO(...)     Log::GetCoreLogger()->info(__VA_ARGS__)
#define ZE_CORE_WARN(...)     Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ZE_CORE_ERROR(...)    Log::GetCoreLogger()->error(__VA_ARGS__)
#define ZE_CORE_FATAL(...)    Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define ZE_TRACE(...)         Log::GetClientLogger()->trace(__VA_ARGS__)
#define ZE_INFO(...)          Log::GetClientLogger()->info(__VA_ARGS__)
#define ZE_WARN(...)          Log::GetClientLogger()->warn(__VA_ARGS__)
#define ZE_ERROR(...)         Log::GetClientLogger()->error(__VA_ARGS__)
#define ZE_FATAL(...)         Log::GetClientLogger()->fatal(__VA_ARGS__)
