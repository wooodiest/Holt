#pragma once

#ifdef HL_PLATFORM_WINDOWS
	
int main(int argc, char** argv)
{
	auto app = Holt::CreateApplication();
	app->Run();
	delete app;
}
	
#endif