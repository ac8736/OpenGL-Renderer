#include "OpenGLRenderer/OpenGLRenderer.h"
#include <imgui.h>

static void ImGui_DrawTriangleMode(bool draw)
{
    if (!draw) return;
}

class Sandbox : public OpenGLRenderer::Application 
{
public:
    Sandbox()
        : m_Size(1280, 720),
        m_ViewportSize(1280, 720),
        m_Renderer(new OpenGLRenderer::Renderer()),
        m_Camera(new OpenGLRenderer::OrthographicCamera(-1.0f, 1.0f, 1.0f, -1.0f)),
        m_Framebuffer(new OpenGLRenderer::Framebuffer(m_Window->GetWidth(), m_Window->GetHeight()))
    {
        float positions[4 * 4] = {
            -0.5f, -0.5f, 0.0f, 0.0f,
             0.5f, -0.5f, 1.0f, 0.0f,
             0.5f,  0.5f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 1.0f
        };

        OpenGLRenderer::BufferLayout layout = {
            { OpenGLRenderer::ShaderDataType::Float2, "a_Position" },
            { OpenGLRenderer::ShaderDataType::Float2, "a_TexCoord"}
        };

        m_VertexBuffer.reset(new OpenGLRenderer::VertexBuffer(positions, 16));
        m_VertexBuffer->SetLayout(layout);

        m_VertexArray.reset(new OpenGLRenderer::VertexArray());
        m_VertexArray->AddVertexBuffer(m_VertexBuffer);

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0,
        };

        m_IndexBuffer.reset(new OpenGLRenderer::IndexBuffer(indices, sizeof(indices) / sizeof(float)));
        m_VertexArray->SetIndexBuffer(m_IndexBuffer);

        m_Shader.reset(new OpenGLRenderer::Shader(OpenGLRenderer::Shader::ParseShader("res/shaders/Basic.shader")));
        m_Shader->Bind();
        m_Shader->UploadUniformFloat3(glm::vec3(1.0f, 1.0f, 1.0f), "u_Color");

        m_Texture.reset(new OpenGLRenderer::Texture("res/textures/texture_test.png"));
    }
    
    ~Sandbox() override 
    {
    }

    void Update() override
    {
        OpenGLRenderer::RenderCommands::Clear();
        m_Framebuffer->Bind();

        m_Renderer->BeginScene(*m_Camera);
        m_Texture->Bind();
        m_Texture->EnableBlend();
        m_Shader->UploadUniformInt1(0, "u_Texture");
        m_Renderer->Draw(m_VertexArray, m_Shader);

        m_Renderer->EndScene();
        m_Framebuffer->Unbind();
    }

    void ImGuiUpdate() override
    {
        ImGui::Begin("Scene");
        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

        if (m_ViewportSize != *((glm::vec2*)&viewportPanelSize))
        {
            m_Framebuffer->UpdateDimensions((int)viewportPanelSize.x, (int)viewportPanelSize.y);
            OpenGLRenderer::RenderCommands::SetViewport(0, 0, (int)viewportPanelSize.x, (int)viewportPanelSize.y);
            m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
        }
        uint32_t textureID = m_Framebuffer->GetTextureColorID();
        ImGui::Image((void*)textureID, ImVec2{ viewportPanelSize.x, viewportPanelSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
        ImGui::End();
        
        static bool triangleDraw = false;

        ImGui::Begin("Properties");

        if (ImGui::CollapsingHeader("Draw Mode"))
        {
            ImGui::Checkbox("Triangles", &triangleDraw);
        }
        ImGui_DrawTriangleMode(triangleDraw);

        ImGui::End();
    }
private:
    glm::vec2 m_Size, m_ViewportSize;

    std::unique_ptr<OpenGLRenderer::Renderer> m_Renderer;
    std::unique_ptr<OpenGLRenderer::Camera> m_Camera;
    std::unique_ptr<OpenGLRenderer::Framebuffer> m_Framebuffer;

    std::shared_ptr<OpenGLRenderer::VertexArray> m_VertexArray;
    std::shared_ptr<OpenGLRenderer::Texture> m_Texture;
    std::shared_ptr<OpenGLRenderer::VertexBuffer> m_VertexBuffer;
    std::shared_ptr<OpenGLRenderer::IndexBuffer> m_IndexBuffer;
    std::shared_ptr<OpenGLRenderer::Shader> m_Shader;
};

OpenGLRenderer::Application* OpenGLRenderer::CreateApplication() { return new Sandbox(); }

int main(int argc, char** argv)
{
    OpenGLRenderer::Log::Init();
    OpenGLRenderer::Application* app = OpenGLRenderer::CreateApplication();
    app->Run();
    delete app;
}
