#include "OpenGLRenderer/OpenGLRenderer.h"

class Sandbox : public OpenGLRenderer::Application 
{
public:
    Sandbox() 
    {

    }

    ~Sandbox() 
    {

    }
};

OpenGLRenderer::Application* OpenGLRenderer::CreateApplication() 
{
    return new Sandbox();
}
