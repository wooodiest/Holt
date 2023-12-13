#pragma once

#include "entt.hpp"

#include "Holt/Core/Timestep.h"

namespace Holt {

	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& = std::string());

		void OnUpdate(Timestep ts);

	private:
		entt::registry m_Registry;

		friend class Entity;
	};

}