#pragma once

extern OpenGLRenderer::Application* OpenGLRenderer::CreateApplication();

int main(int argc, char** argv) {
	OpenGLRenderer::Log::Init();
	CORE_INFO("Logging in library works!");
	CLIENT_INFO("Logging in client works!");
	OpenGLRenderer::Application* app = OpenGLRenderer::CreateApplication();
	app->Run();
	delete app;
}