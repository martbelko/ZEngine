#include "zpch.hpp"

#include "Core/Core.hpp"

int main()
{
	Log::Init();
	Log::GetCoreLogger()->info("ZEngine logger initialized");
	Log::GetClientLogger()->info("Client logger initialized");
	system("pause");
	return 0;
}