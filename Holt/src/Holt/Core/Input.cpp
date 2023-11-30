#pragma once
#include "hlpch.h"
#include "Input.h"

#ifdef HL_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsInput.h"
#endif

namespace Holt {

	Scope<Input> Input::s_Instance;

	Scope<Input> Input::Create()
	{
#ifdef HL_PLATFORM_WINDOWS
		return CreateScope<WindowsInput>();
#else
		HL_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif
	}

	void Input::Init()
	{
		s_Instance = Input::Create();
	}

}