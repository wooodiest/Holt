#pragma once

#ifdef HL_PLATFORM_WINDOWS
	
int main(int argc, char** argv)
{
	Holt::Log::Init();
	HL_INFO("App is running");

	auto app = Holt::CreateApplication();
	app->Run();
	delete app;
}
	
#endif