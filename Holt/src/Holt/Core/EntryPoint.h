#pragma once

#ifdef HL_PLATFORM_WINDOWS
	
extern Holt::Application* Holt::CreateApplication();

int main(int argc, char** argv)
{
	Holt::Log::Init();

	HL_PROFILE_BEGIN_SESSION("Startup", "Holt-Profile-Startup.json");
	auto app = Holt::CreateApplication();
	HL_PROFILE_END_SESSION();

	HL_PROFILE_BEGIN_SESSION("Runtime", "Holt-Profile-Runtime.json");
	app->Run();
	HL_PROFILE_END_SESSION();

	HL_PROFILE_BEGIN_SESSION("Shutdown", "Holt-Profile-Shutdown.json");
	delete app;
	HL_PROFILE_END_SESSION();
}
	
#endif