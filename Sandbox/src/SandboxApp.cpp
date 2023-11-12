#include <Holt.h>

class Sandbox : public Holt::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}

};

Holt::Application* Holt::CreateApplication()
{
	return new Sandbox();
}