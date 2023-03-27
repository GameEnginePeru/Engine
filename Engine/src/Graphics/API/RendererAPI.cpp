#include "Graphics/API/RendererAPI.h"

#include "GraphicInterfaces/OpenGL/API/OpenGLRendererAPI.h"

namespace ENGINE_NAMESPACE
{
    RendererAPI::API RendererAPI::s_API = RendererAPI::API::NONE;

    Ref<RendererAPI> RendererAPI::Create()
    {
        switch (s_API)
        {
        case Engine::RendererAPI::API::NONE:
            return nullptr;
        case Engine::RendererAPI::API::OPENGL:
            return CreateRef<OpenGLRendererAPI>();
        default:
            return nullptr;
        }
    }
}
