#pragma once

#ifdef CR_PLATFORM_WINDOWS

extern Crow::Application* Crow::CreateApplication();

int main(int argc, char** argv)
{
	Crow::Log::Init();
	
	ENGINE_LOG_INFO("Info test");
	ENGINE_LOG_WARNING("Warning test");
	ENGINE_LOG_ERROR("Error test");
	ENGINE_LOG("Trace test");


	APP_LOG_INFO("Info test");
	APP_LOG_WARNING("Warning test");
	APP_LOG_ERROR("Error test");
	APP_LOG("Trace test");

	auto app = Crow::CreateApplication();
	app->Run();
	delete app;
}


#endif