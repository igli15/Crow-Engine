#pragma once

#ifdef CR_PLATFORM_WINDOWS

extern Crow::Application* Crow::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Crow::CreateApplication();
	app->Run();
	delete app;
}

#endif