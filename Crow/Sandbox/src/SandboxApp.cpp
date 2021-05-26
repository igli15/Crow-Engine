
#include <Crow.h>

class Sandbox : public Crow::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}

};

Crow::Application* Crow::CreateApplication()
{
	return new Sandbox();
}