#include <Holt.h>
#include <Holt/Core/EntryPoint.h>

#include "ExampleLayer.h"


class Sandbox : public Holt::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}

};

Holt::Application* Holt::CreateApplication()
{
	return new Sandbox();
}