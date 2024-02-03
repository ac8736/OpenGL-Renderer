#include "OpenGLRenderer/OpenGLRenderer.h"
#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Sandbox : public OpenGLRenderer::Application 
{
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

public:
    Sandbox()
        : m_Size(1280, 720),
        m_Model(glm::mat4(1.0f)),
        m_ViewportSize(1280, 720),
        m_Transform(glm::mat4(1.0f)),
        m_Renderer(new OpenGLRenderer::Renderer()),
        m_Camera(new OpenGLRenderer::PerspectiveCamera(45.0f, 800.0f / 600.0f, 0.1f, 100.0f)),
        m_Framebuffer(new OpenGLRenderer::Framebuffer(m_Window->GetWidth(), m_Window->GetHeight()))
    {
        float vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 1.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,

             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
        };

        OpenGLRenderer::BufferLayout layout = {
            { OpenGLRenderer::ShaderDataType::Float3, "a_Position" },
            { OpenGLRenderer::ShaderDataType::Float3, "a_Normal" },
            { OpenGLRenderer::ShaderDataType::Float2, "a_TexCoord" }
        };

        m_VertexBuffer.reset(new OpenGLRenderer::VertexBuffer(vertices, sizeof(vertices) / sizeof(float)));
        m_VertexBuffer->SetLayout(layout);

        m_VertexArrayMaterial.reset(new OpenGLRenderer::VertexArray());
        m_VertexArrayMaterial->AddVertexBuffer(m_VertexBuffer);

        m_VertexArrayLight.reset(new OpenGLRenderer::VertexArray());
        m_VertexArrayLight->AddVertexBuffer(m_VertexBuffer);

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

        m_VertexArrayMaterial->SetIndexBuffer(m_IndexBuffer);
        m_VertexArrayLight->SetIndexBuffer(m_IndexBuffer);

        m_ShaderMaterial.reset(new OpenGLRenderer::Shader(OpenGLRenderer::Shader::ParseShader("res/shaders/vertex/basic.glsl", "res/shaders/fragment/diffuse_maps.glsl")));
        m_ShaderLight.reset(new OpenGLRenderer::Shader(OpenGLRenderer::Shader::ParseShader("res/shaders/vertex/basic.glsl", "res/shaders/fragment/texture.glsl")));

        m_LightTexture.reset(new OpenGLRenderer::Texture("res/textures/glowstone.png"));
        m_MaterialTexture.reset(new OpenGLRenderer::Texture("res/textures/container.png"));
        m_MetalFrameTexture.reset(new OpenGLRenderer::Texture("res/textures/container_specular.png"));

        OpenGLRenderer::RenderCommands::EnableDepthTest();
    }
    
    ~Sandbox() override 
    {
    }

    void OnEvent(OpenGLRenderer::Event& e) override
    {
        OpenGLRenderer::EventDispatcher dispatcher(e);
        dispatcher.Dispatch<OpenGLRenderer::MouseButtonReleasedEvent>(BIND_EVENT_FN(Sandbox::OnMouseButtonRelease));
        dispatcher.Dispatch<OpenGLRenderer::MouseScrolledEvent>(BIND_EVENT_FN(Sandbox::OnMouseScroll));
    }

    bool OnMouseScroll(OpenGLRenderer::MouseScrolledEvent& e) const
    {
        std::dynamic_pointer_cast<OpenGLRenderer::PerspectiveCamera>(m_Camera)->MouseScrollZoom(e.GetYOffset(), m_DeltaTime);
        return true;
    }

    bool OnMouseButtonRelease(OpenGLRenderer::MouseButtonReleasedEvent& e) const
    {
        std::dynamic_pointer_cast<OpenGLRenderer::PerspectiveCamera>(m_Camera)->SetFirstMouse(true);
        return true;
    }

    void Update() override
    {
        if (SceneFocused)
        {
            const float cameraSpeed = 2.5f * m_DeltaTime;
            if (OpenGLRenderer::Input::IsKeyPressed(KEY_SPACE, m_Window->GetWindow()))
                std::dynamic_pointer_cast<OpenGLRenderer::PerspectiveCamera>(m_Camera)
                ->SetPosition(m_Camera->GetPosition() + cameraSpeed * std::dynamic_pointer_cast<OpenGLRenderer::PerspectiveCamera>(m_Camera)->GetCameraUp());

            if (OpenGLRenderer::Input::IsKeyPressed(KEY_LEFT_SHIFT, m_Window->GetWindow()))
                std::dynamic_pointer_cast<OpenGLRenderer::PerspectiveCamera>(m_Camera)
                ->SetPosition(m_Camera->GetPosition() - cameraSpeed * std::dynamic_pointer_cast<OpenGLRenderer::PerspectiveCamera>(m_Camera)->GetCameraUp());

            if (OpenGLRenderer::Input::IsKeyPressed(KEY_W, m_Window->GetWindow()))
                std::dynamic_pointer_cast<OpenGLRenderer::PerspectiveCamera>(m_Camera)
                ->SetPosition(m_Camera->GetPosition() + cameraSpeed * std::dynamic_pointer_cast<OpenGLRenderer::PerspectiveCamera>(m_Camera)->GetCameraFront());

            if (OpenGLRenderer::Input::IsKeyPressed(KEY_S, m_Window->GetWindow()))
                std::dynamic_pointer_cast<OpenGLRenderer::PerspectiveCamera>(m_Camera)
                ->SetPosition(m_Camera->GetPosition() - cameraSpeed * std::dynamic_pointer_cast<OpenGLRenderer::PerspectiveCamera>(m_Camera)->GetCameraFront());

            if (OpenGLRenderer::Input::IsKeyPressed(KEY_A, m_Window->GetWindow()))
                std::dynamic_pointer_cast<OpenGLRenderer::PerspectiveCamera>(m_Camera)
                ->SetPosition(m_Camera->GetPosition() - glm::normalize(glm::cross(std::dynamic_pointer_cast<OpenGLRenderer::PerspectiveCamera>(m_Camera)->GetCameraFront(),
                    std::dynamic_pointer_cast<OpenGLRenderer::PerspectiveCamera>(m_Camera)->GetCameraUp())) * cameraSpeed);

            if (OpenGLRenderer::Input::IsKeyPressed(KEY_D, m_Window->GetWindow()))
                std::dynamic_pointer_cast<OpenGLRenderer::PerspectiveCamera>(m_Camera)
                ->SetPosition(m_Camera->GetPosition() + glm::normalize(glm::cross(std::dynamic_pointer_cast<OpenGLRenderer::PerspectiveCamera>(m_Camera)->GetCameraFront(),
                    std::dynamic_pointer_cast<OpenGLRenderer::PerspectiveCamera>(m_Camera)->GetCameraUp())) * cameraSpeed);

            if (OpenGLRenderer::Input::IsMousePressed(MOUSE_BUTTON_1, m_Window->GetWindow()))
            {
                std::dynamic_pointer_cast<OpenGLRenderer::PerspectiveCamera>(m_Camera)
                    ->MouseMovement(OpenGLRenderer::Input::GetMousePosX(m_Window->GetWindow()), OpenGLRenderer::Input::GetMousePosY(m_Window->GetWindow()));
            }
        }

        OpenGLRenderer::RenderCommands::Clear();
        m_Framebuffer->Bind();

        m_Renderer->BeginScene(*m_Camera);

        m_Model = glm::mat4(1.0f);
        m_ShaderMaterial->Bind();
        m_ShaderMaterial->UploadUniformFloat3(glm::vec3(1.0f, 0.5f, 0.31f), "objectColor");
        m_ShaderMaterial->UploadUniformFloat3(glm::vec3(1.0f, 1.0f, 1.0f), "lightColor");

        m_ShaderMaterial->UploadUniformFloat3(glm::vec3(1.0f, 0.5f, 0.31f), "material.ambient");
        m_ShaderMaterial->UploadUniformInt1(0, "material.diffuse");
        m_ShaderMaterial->UploadUniformInt1(1, "material.specular");
        m_ShaderMaterial->UploadUniformInt1(2, "material.emission");
        m_ShaderMaterial->UploadUniformFloat3(glm::vec3(0.5f, 0.5f, 0.5f), "material.specular");
        m_ShaderMaterial->UploadUniformFloat1(32.0f, "material.shininess");

        m_ShaderMaterial->UploadUniformFloat3(glm::vec3(0.2f, 0.2f, 0.2f), "light.ambient");
        m_ShaderMaterial->UploadUniformFloat3(glm::vec3(0.5f, 0.5f, 0.5f), "light.diffuse"); // darken diffuse light a bit
        m_ShaderMaterial->UploadUniformFloat3(glm::vec3(1.0f, 1.0f, 1.0f), "light.specular");

        m_ShaderMaterial->UploadUniformMat4(m_Model, "u_Model");
        m_ShaderMaterial->UploadUniformFloat3(lightPos, "lightPos");
        m_ShaderMaterial->UploadUniformFloat3(m_Camera->GetPosition(), "viewPos");
        m_MaterialTexture->Bind(0);
        m_MetalFrameTexture->Bind(1);
        m_Renderer->Draw(m_VertexArrayMaterial, m_ShaderMaterial);
        m_MaterialTexture->Unbind();
        m_MetalFrameTexture->Unbind();
        
        m_Model = glm::translate(m_Model, lightPos);
        m_Model = glm::scale(m_Model, glm::vec3(0.2f));
        m_ShaderLight->Bind();
        m_LightTexture->Bind();
        m_ShaderLight->UploadUniformMat4(m_Model, "u_Model");
        m_Renderer->Draw(m_VertexArrayLight, m_ShaderLight);
        m_LightTexture->Unbind();

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
        SceneFocused = ImGui::IsWindowFocused();
        ImGui::End();
        
        static bool triangleDraw = false;

        ImGui::Begin("Properties");

        if (ImGui::CollapsingHeader("Light Source"))
        {
            ImGui::SliderFloat("Position X", &lightPos.x, -2.0f, 2.0);
            ImGui::SliderFloat("Position Y", &lightPos.y, -2.0f, 2.0);
            ImGui::SliderFloat("Position Z", &lightPos.z, -2.0f, 2.0);
        }

        ImGui::End();
    }
private:
    glm::vec2 m_Size, m_ViewportSize;
    glm::mat4 m_Transform;
    glm::mat4 m_Model;

    glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);


    std::unique_ptr<OpenGLRenderer::Renderer> m_Renderer;
    std::unique_ptr<OpenGLRenderer::Framebuffer> m_Framebuffer;

    std::shared_ptr<OpenGLRenderer::VertexArray> m_VertexArrayMaterial;
    std::shared_ptr<OpenGLRenderer::VertexArray> m_VertexArrayLight;

    std::shared_ptr<OpenGLRenderer::Texture> m_LightTexture;
    std::shared_ptr<OpenGLRenderer::Texture> m_MaterialTexture;
    std::shared_ptr<OpenGLRenderer::Texture> m_MetalFrameTexture;

    std::shared_ptr<OpenGLRenderer::VertexBuffer> m_VertexBuffer;
    std::shared_ptr<OpenGLRenderer::IndexBuffer> m_IndexBuffer;

    std::shared_ptr<OpenGLRenderer::Shader> m_ShaderMaterial;
    std::shared_ptr<OpenGLRenderer::Shader> m_ShaderLight;

    std::shared_ptr<OpenGLRenderer::Camera> m_Camera;

    bool SceneFocused = false;
};

OpenGLRenderer::Application* OpenGLRenderer::CreateApplication() { return new Sandbox(); }

int main(int argc, char** argv)
{
    OpenGLRenderer::Log::Init();
    OpenGLRenderer::Application* app = OpenGLRenderer::CreateApplication();
    app->Run();
    delete app;
}
