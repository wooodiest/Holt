#pragma once

#include "Holt/Core/Core.h"
#include "Holt/Core/MouseButtonCodes.h"
#include "Holt/Core/KeyCodes.h"

namespace Holt {

	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();

	};
}