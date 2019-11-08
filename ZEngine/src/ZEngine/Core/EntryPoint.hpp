#pragma once

extern ZEngine::Application* CreateApplication();

int main(int argc, char** argv)
{
	ZEngine::Application* app = CreateApplication();
	app->run();
	delete app;
	return 0;
}
