#include "Graphics/API/RendererAPI.h"

namespace ENGINE_NAMESPACE
{
    RendererAPI::API RendererAPI::s_API = RendererAPI::API::OPENGL;

    Ref<RendererAPI> RendererAPI::Create()
    {
        switch (s_API)
        {
        case Engine::RendererAPI::API::NONE:
            return nullptr;
        case Engine::RendererAPI::API::OPENGL:
            return nullptr;
        default:
            return nullptr;
        }
    }
}
