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

	Logger::~Logger()
	{
		SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	}

	void Logger::PrintLoggerName()
	{
		std::cout << '[' << m_strName << "] : ";
	}

	void Logger::ChangeOutputColor(Colors color)
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
			Print("% logger error: Unknown color\n");
			break;
		}
	}

}