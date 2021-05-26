#pragma once

#include "Core.h"

namespace Crow
{
	class CROW_API Application
	{
	public:
		Application();
		~Application();

		void Run();
	};

	//This is defined by the client!
	Application* CreateApplication();
}

