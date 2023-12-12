#include "hlpch.h"
#include "Framebuffer.h"

#include "Holt/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace Holt {

	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    HL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLFramebuffer>(spec);
		}

		HL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}