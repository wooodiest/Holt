#pragma once

#include "entt.hpp"

#include "Holt/Core/Timestep.h"

namespace Holt {

	class Scene
	{
	public:
		Scene();
		~Scene();

		entt::entity CreateEntity();
		entt::registry& Reg() { return m_Registry; }
		void OnUpdate(Timestep ts);

	private:
		entt::registry m_Registry;

	};

}