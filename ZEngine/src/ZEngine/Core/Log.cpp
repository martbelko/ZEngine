#include "zpch.hpp"
#include "Log.hpp"

namespace ZEngine {

	std::shared_ptr<Logger> Log::s_EngineLogger = nullptr;
	std::shared_ptr<Logger> Log::s_ClientLogger = nullptr;

	Logger::Logger(const std::string& name)
		: m_strName(name)
	{
		hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	void Logger::trace(const char* format)
	{
		changeOutputColor(Colors::GREEN);
		printLoggerName();
		print(format);
	}

	void Logger::info(const char* format)
	{
		changeOutputColor(Colors::CYAN);
		printLoggerName();
		print(format);
	}

	void Logger::warn(const char* format)
	{
		changeOutputColor(Colors::WHITE);
		printLoggerName();
		print(format);
	}

	void Logger::error(const char* format)
	{
		changeOutputColor(Colors::YELLOW);
		printLoggerName();
		print(format);
	}

	void Logger::fatal(const char* format)
	{
		changeOutputColor(Colors::RED);
		printLoggerName();
		print(format);
	}

	void Logger::print(const char* format)
	{
		std::cout << format << '\n';
	}

	void Logger::printLoggerName()
	{
		std::cout << '[' << m_strName << "] : ";
	}

	void Logger::changeOutputColor(Colors color)
	{
		// TODO: Sort by RGB
		switch (color)
		{
		case Colors::RED:
			SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_INTENSITY);
			break;
		case Colors::BLUE:
			SetConsoleTextAttribute(hStdout, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			break;
		case Colors::GREEN:
			SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			break;
		case Colors::WHITE:
			SetConsoleTextAttribute(hStdout, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
			break;
		case Colors::PURPLE:
			SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			break;
		case Colors::CYAN:
			SetConsoleTextAttribute(hStdout, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			break;
		case Colors::YELLOW:
			SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
			break;
		default:
			print("% logger error: Unknown color\n");
			break;
		}
	}

}