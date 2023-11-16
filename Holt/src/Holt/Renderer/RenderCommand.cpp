#include "hlpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Holt {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}