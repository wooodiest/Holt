#pragma once

#ifdef HL_PLATFORM_WINDOWS
	
extern Holt::Application* Holt::CreateApplication();

int main(int argc, char** argv)
{
	Holt::Log::Init();

	auto app = Holt::CreateApplication();
	app->Run();
	delete app;
}
	
#endif