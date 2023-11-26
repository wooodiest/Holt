#include <Holt.h>
#include <Holt/Core/EntryPoint.h>

#include "ExampleLayer.h"
#include "Sandbox2D.h"

class Sandbox : public Holt::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{

	}

};

Holt::Application* Holt::CreateApplication()
{
	return new Sandbox();
}