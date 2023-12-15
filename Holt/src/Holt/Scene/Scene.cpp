#include "hlpch.h"
#include "Holt/Scene/Scene.h"

#include "Holt/Renderer/Renderer2D.h"

#include "Components.h"
#include "Entity.h"

namespace Holt {

	Scene::Scene()
	{

	}

	Scene::~Scene()
	{
		
	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity" : name;

		return entity;
	}

	void Scene::OnUpdate(Timestep ts)
	{

		// Update scripts
		{
			m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
				{
					//TODO: Move to Scene::OnPlay
					if (!nsc.Instance)
					{
						nsc.Instance = nsc.InstantiateScript();
						nsc.Instance->m_Entity = Entity{ entity, this };
						nsc.Instance->OnCreate();
					}

					nsc.Instance->OnUpdate(ts);
				});
		}
		// Render 2D
		Camera* mainCamera = nullptr;
		glm::mat4* mainCameraTransform = nullptr;
		{
			auto view = m_Registry.view<TransformComponent, CameraComponent>();
			for (auto entity : view)
			{
				auto& [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);

				if (camera.Primary)
				{
					mainCamera = &camera.Camera;
					mainCameraTransform = &transform.GetTransform();
					break;
				}
			}
		}
		
		if (mainCamera)
		{
			Renderer2D::BeginScene(*mainCamera, *mainCameraTransform);

			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (auto entity : group)
			{
				auto [transform, sprite] = group.get< TransformComponent, SpriteRendererComponent>(entity);

				if (sprite.Texture == nullptr)
					Renderer2D::DrawQuad(transform.GetTransform(), sprite.Color);
				else
					Renderer2D::DrawQuad(transform.GetTransform(), sprite.Texture, sprite.TilingFactor, sprite.Color);
			}

			Renderer2D::EndScene();
		}
		
	}

	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		m_ViewportWidth = width;
		m_ViewportHeight = height;

		// Resize our non-FixedAspectRatio cameras
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			auto& cameraComponent = view.get<CameraComponent>(entity);
			if (!cameraComponent.FixedAspectRatio)
				cameraComponent.Camera.SetViewportSize(width, height);
		}

	}

	void Scene::SetPrimaryCamera(Entity entity)
	{
		auto view = m_Registry.view<CameraComponent>();
		for (auto ent : view)
		{
			if (entity.m_EntityHandle != ent)
			{
				auto& cameraComponent = view.get<CameraComponent>(ent);
				cameraComponent.Primary = false;
			}
			else
			{
				auto& cameraComponent = view.get<CameraComponent>(ent);
				cameraComponent.Primary = true;
			}

		}
	}

}