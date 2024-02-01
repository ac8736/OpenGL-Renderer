#include "OpenGLRenderer/OpenGLRenderer.h"
#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Sandbox : public OpenGLRenderer::Application 
{
public:
    Sandbox()
        : m_Size(1280, 720),
        m_ViewportSize(1280, 720),
        m_Transform(glm::mat4(1.0f)),
        m_Renderer(new OpenGLRenderer::Renderer()),
        m_Camera(new OpenGLRenderer::PerspectiveCamera(45.0f, 800.0f / 600.0f, 0.1f, 100.0f)),
        m_Framebuffer(new OpenGLRenderer::Framebuffer(m_Window->GetWidth(), m_Window->GetHeight()))
    {
        float positions[] = {
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // 0
             0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // 4
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // 8
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

             0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // 12
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // 16
             0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // 20
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        };

        OpenGLRenderer::BufferLayout layout = {
            { OpenGLRenderer::ShaderDataType::Float3, "a_Position" },
            { OpenGLRenderer::ShaderDataType::Float2, "a_TexCoord"}
        };

        m_VertexBuffer.reset(new OpenGLRenderer::VertexBuffer(positions, sizeof(positions) / sizeof(float)));
        m_VertexBuffer->SetLayout(layout);

        m_VertexArray.reset(new OpenGLRenderer::VertexArray());
        m_VertexArray->AddVertexBuffer(m_VertexBuffer);

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0,

            4, 5, 6,
            6, 7, 4,

            8, 9, 10,
            10, 11, 8,

            12, 13, 14,
            14, 15, 12,

            16, 17, 18,
            18, 19, 16,

            20, 21, 22,
            22, 23, 20
        };

        m_IndexBuffer.reset(new OpenGLRenderer::IndexBuffer(indices, sizeof(indices) / sizeof(float)));
        m_VertexArray->SetIndexBuffer(m_IndexBuffer);

        m_Shader.reset(new OpenGLRenderer::Shader(OpenGLRenderer::Shader::ParseShader("res/shaders/Basic.shader")));
        m_Shader->Bind();
        m_Shader->UploadUniformFloat3(glm::vec3(1.0f, 1.0f, 1.0f), "u_Color");

        m_Texture.reset(new OpenGLRenderer::Texture("res/textures/texture_test.png"));

        OpenGLRenderer::RenderCommands::EnableDepthTest();
    }
    
    ~Sandbox() override 
    {
    }

    void Update() override
    {
        glm::vec3 cubePositions[] = {
            glm::vec3(0.0f,  0.0f,  0.0f),
            glm::vec3(2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3(2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3(1.3f, -2.0f, -2.5f),
            glm::vec3(1.5f,  2.0f, -2.5f),
            glm::vec3(1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
        };

        const float cameraSpeed = 2.5f * m_DeltaTime;
        if (OpenGLRenderer::Input::IsKeyPressed(int('W'), m_Window->GetWindow()))
            std::dynamic_pointer_cast<OpenGLRenderer::PerspectiveCamera>(m_Camera)
                ->SetPosition(m_Camera->GetPosition() + cameraSpeed * std::dynamic_pointer_cast<OpenGLRenderer::PerspectiveCamera>(m_Camera)->GetCameraFront());

        if (OpenGLRenderer::Input::IsKeyPressed(int('S'), m_Window->GetWindow()))
            std::dynamic_pointer_cast<OpenGLRenderer::PerspectiveCamera>(m_Camera)
                ->SetPosition(m_Camera->GetPosition() - cameraSpeed * std::dynamic_pointer_cast<OpenGLRenderer::PerspectiveCamera>(m_Camera)->GetCameraFront());

        if (OpenGLRenderer::Input::IsKeyPressed(int('A'), m_Window->GetWindow()))
            std::dynamic_pointer_cast<OpenGLRenderer::PerspectiveCamera>(m_Camera)
                ->SetPosition(m_Camera->GetPosition() - glm::normalize(glm::cross(std::dynamic_pointer_cast<OpenGLRenderer::PerspectiveCamera>(m_Camera)->GetCameraFront(),
                    std::dynamic_pointer_cast<OpenGLRenderer::PerspectiveCamera>(m_Camera)->GetCameraUp())) * cameraSpeed);

        if (OpenGLRenderer::Input::IsKeyPressed(int('D'), m_Window->GetWindow()))
            std::dynamic_pointer_cast<OpenGLRenderer::PerspectiveCamera>(m_Camera)
                ->SetPosition(m_Camera->GetPosition() + glm::normalize(glm::cross(std::dynamic_pointer_cast<OpenGLRenderer::PerspectiveCamera>(m_Camera)->GetCameraFront(), 
                    std::dynamic_pointer_cast<OpenGLRenderer::PerspectiveCamera>(m_Camera)->GetCameraUp())) * cameraSpeed);

        if (OpenGLRenderer::Input::IsMousePressed(0, m_Window->GetWindow()))
        {
            std::dynamic_pointer_cast<OpenGLRenderer::PerspectiveCamera>(m_Camera)
                ->MouseMovement(OpenGLRenderer::Input::GetMousePosX(m_Window->GetWindow()), OpenGLRenderer::Input::GetMousePosY(m_Window->GetWindow()));
        }
        else
        {
            std::dynamic_pointer_cast<OpenGLRenderer::PerspectiveCamera>(m_Camera)->SetFirstMouse(true);
        }

        OpenGLRenderer::RenderCommands::Clear();
        m_Framebuffer->Bind();

        m_Renderer->BeginScene(*m_Camera);
        m_Texture->Bind();
        m_Texture->EnableBlend();

        m_Shader->UploadUniformInt1(0, "u_Texture");
        m_Shader->UploadUniformMat4(m_Transform, "u_Transform");

        for (size_t i = 0; i < sizeof(cubePositions) / sizeof(glm::vec3); ++i)
        {
            m_Model = glm::mat4(1.0f);
            m_Model = glm::translate(m_Model, cubePositions[i]);
            float angle = 50.0f * m_LastFrameTime;
            if (i % 2 == 0)
                angle *= -1;

            m_Model = glm::rotate(m_Model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            m_Shader->UploadUniformMat4(m_Model, "u_Model");

            m_Renderer->Draw(m_VertexArray, m_Shader);
        }
 
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

        ImGui::End();
    }
private:
    glm::vec2 m_Size, m_ViewportSize;
    glm::mat4 m_Transform;
    glm::mat4 m_Model;

    std::unique_ptr<OpenGLRenderer::Renderer> m_Renderer;
    std::unique_ptr<OpenGLRenderer::Framebuffer> m_Framebuffer;

    std::shared_ptr<OpenGLRenderer::VertexArray> m_VertexArray;
    std::shared_ptr<OpenGLRenderer::Texture> m_Texture;
    std::shared_ptr<OpenGLRenderer::VertexBuffer> m_VertexBuffer;
    std::shared_ptr<OpenGLRenderer::IndexBuffer> m_IndexBuffer;
    std::shared_ptr<OpenGLRenderer::Shader> m_Shader;

    std::shared_ptr<OpenGLRenderer::Camera> m_Camera;
};

OpenGLRenderer::Application* OpenGLRenderer::CreateApplication() { return new Sandbox(); }

int main(int argc, char** argv)
{
    OpenGLRenderer::Log::Init();
    OpenGLRenderer::Application* app = OpenGLRenderer::CreateApplication();
    app->Run();
    delete app;
}
