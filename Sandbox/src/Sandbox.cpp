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
        m_Framebuffer(new OpenGLRenderer::Framebuffer(m_Window->GetWidth(), m_Window->GetHeight())) {}
    
    ~Sandbox() override 
    {
        delete m_Renderer;
        m_Renderer = nullptr;
        delete m_Camera;
        m_Camera = nullptr;
    }

    void Update() override
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

        std::shared_ptr<OpenGLRenderer::VertexBuffer> vertexBuffer;
        vertexBuffer.reset(new OpenGLRenderer::VertexBuffer(positions, 16));

        vertexBuffer->SetLayout(layout);

        OpenGLRenderer::VertexArray vertexArray = OpenGLRenderer::VertexArray();
        vertexArray.AddVertexBuffer(vertexBuffer);

        unsigned int indices[] = {
        	0, 1, 2,
        	2, 3, 0,
        };

        OpenGLRenderer::IndexBuffer indexBuffer(indices, 6);

        vertexArray.SetIndexBuffer(indexBuffer);

        OpenGLRenderer::Shader shader = OpenGLRenderer::Shader(OpenGLRenderer::Shader::ParseShader("res/shaders/Basic.shader"));
        shader.Bind();
        shader.UploadUniformFloat3(glm::vec3(1.0f, 1.0f, 1.0f), "u_Color");

        OpenGLRenderer::Texture texture("res/textures/texture_test.png");
        texture.EnableBlend();
        texture.Bind();
        shader.UploadUniformInt1(0, "u_Texture");

        m_Framebuffer->Bind();

        m_Renderer->BeginScene(*m_Camera);

        m_Renderer->Draw(vertexArray, shader);

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

    OpenGLRenderer::Renderer* m_Renderer;
    OpenGLRenderer::Camera* m_Camera;
    OpenGLRenderer::Framebuffer* m_Framebuffer;
};

OpenGLRenderer::Application* OpenGLRenderer::CreateApplication() { return new Sandbox(); }

int main(int argc, char** argv)
{
    OpenGLRenderer::Log::Init();
    OpenGLRenderer::Application* app = OpenGLRenderer::CreateApplication();
    app->Run();
    delete app;
}
