#include "hlpch.h"
#include "Holt/Scene/Entity.h"

namespace Holt {

	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_Scene(scene)
	{

	}

}