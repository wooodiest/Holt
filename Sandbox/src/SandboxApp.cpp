#include <Holt.h>

class ExampleLayer : public Holt::Layer
{
public:
	ExampleLayer()
		: Layer("Example") {}

	virtual void OnUpdate() override
	{
		//HL_TRACE("{0} {1}", Holt::Input::GetMouseX(), Holt::Input::GetMouseX());
	}

	virtual void OnImGuiRender() override
	{

	}

	virtual void OnEvent(Holt::Event& event) override
	{
		if (event.GetEventType() == Holt::EventType::KeyPressed)
		{
			Holt::KeyPressedEvent& e = (Holt::KeyPressedEvent&)event;
			HL_TRACE("{0}", (char)e.GetKeyCode());
		}
	}

};

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