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
		~Logger();
		
		template<typename T>
		void Trace(const T& value)
		{
			ChangeOutputColor(Colors::GREEN);
			PrintLoggerName();
			Print(value);
		}

		template<typename T>
		void Info(const T& value)
		{
			ChangeOutputColor(Colors::CYAN);
			PrintLoggerName();
			Print(value);
		}

		template<typename T>
		void Warn(const T& value)
		{
			ChangeOutputColor(Colors::WHITE);
			PrintLoggerName();
			Print(value);
		}

		template<typename T>
		void Error(const T& value)
		{
			ChangeOutputColor(Colors::YELLOW);
			PrintLoggerName();
			Print(value);
		}

		template<typename T>
		void Fatal(const T& value)
		{
			ChangeOutputColor(Colors::RED);
			PrintLoggerName();
			Print(value);
		}

		template<typename T, typename... Targs>
		void Trace(const char* format, T value, Targs... Fargs)
		{
			ChangeOutputColor(Colors::GREEN);
			PrintLoggerName();
			Print(format, value, Fargs...);
		}

		template<typename T, typename... Targs>
		void Info(const char* format, T value, Targs... Fargs)
		{
			ChangeOutputColor(Colors::CYAN);
			PrintLoggerName();
			Print(format, value, Fargs...);
		}

		template<typename T, typename... Targs>
		void Warn(const char* format, T value, Targs... Fargs)
		{
			ChangeOutputColor(Colors::WHITE);
			PrintLoggerName();
			Print(format, value, Fargs...);
		}

		template<typename T, typename... Targs>
		void Error(const char* format, T value, Targs... Fargs)
		{
			ChangeOutputColor(Colors::YELLOW);
			PrintLoggerName();
			Print(format, value, Fargs...);
		}

		template<typename T, typename... Targs>
		void Fatal(const char* format, T value, Targs... Fargs)
		{
			ChangeOutputColor(Colors::RED);
			PrintLoggerName();
			Print(format, value, Fargs...);
		}
	private:
		template<typename T>
		void Print(const T& value)
		{
			std::cout << value << '\n';
		}

		template<typename T, typename... Targs>
		void Print(const char* format, T value, Targs... Fargs)
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
					Print(format + 1, Fargs...);
					return;
				}
				std::cout << *format;
			}
			std::cout << '\n';
		}

		void PrintLoggerName();

		void ChangeOutputColor(Logger::Colors color);
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
#define ZE_CORE_TRACE(...)    Log::GetCoreLogger()->Trace(__VA_ARGS__)
#define ZE_CORE_INFO(...)     Log::GetCoreLogger()->Info(__VA_ARGS__)
#define ZE_CORE_WARN(...)     Log::GetCoreLogger()->Warn(__VA_ARGS__)
#define ZE_CORE_ERROR(...)    Log::GetCoreLogger()->Error(__VA_ARGS__)
#define ZE_CORE_FATAL(...)    Log::GetCoreLogger()->Fatal(__VA_ARGS__)

// Client log macros
#define ZE_TRACE(...)         Log::GetClientLogger()->Trace(__VA_ARGS__)
#define ZE_INFO(...)          Log::GetClientLogger()->Info(__VA_ARGS__)
#define ZE_WARN(...)          Log::GetClientLogger()->Warn(__VA_ARGS__)
#define ZE_ERROR(...)         Log::GetClientLogger()->Error(__VA_ARGS__)
#define ZE_FATAL(...)         Log::GetClientLogger()->Fatal(__VA_ARGS__)
