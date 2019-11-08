#pragma once

extern ZEngine::Application* CreateApplication();

int main(int argc, char** argv)
{
	ZEngine::Application* app = CreateApplication();
	app->run();
	return 0;
}
