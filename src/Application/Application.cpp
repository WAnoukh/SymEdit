#include "Application.h"

#include <string>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"

bool firstMouse = false, SwapInterval = true;
float lastX, lastY, deltaTime, lastFrame, timeDiff = 0.0f;
unsigned int counter;


void Application::Init() {
	if (Window.init() == -1) {
		std::cerr << "Application : Window.init() Failed." << std::endl;
	}
	glEnable(GL_DEPTH_TEST);
}

Application& Application::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new Application();
	}
	return *instance;
}

int Application::Run() {
	ViewPort.Init();
	// render loop
	// -----------
	while (!Window.shouldClose())
	{
		Window.PreRender();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		//ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
		//ImGui::End();
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
		ImGuiID dockspace_id = ImGui::DockSpaceOverViewport(viewport,dockspace_flags);
		if(LayoutNeedRefresh)
		{
			//ViewPort.Render();
			if (dockspace_id)
			{
				ImGui::DockBuilderAddNode(dockspace_id, dockspace_flags | ImGuiDockNodeFlags_DockSpace);
				ImGui::DockBuilderSetNodeSize(dockspace_id, viewport->Size);

				auto dock_id_top = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Left, 0.1f, nullptr, &dockspace_id);
				ImGui::DockBuilderDockWindow("Tools", dock_id_top);
				ImGui::DockBuilderDockWindow("Viewport", dockspace_id);
			}
			LayoutNeedRefresh = false;
		}
		ImGui::Begin("Tools");
		ImGui::Text("This is some useful text.");
		ImGui::End();
		ViewPort.RenderUI();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		
		Window.PostRender();
		glfwPollEvents();
	}
	Window.terminate();
	return 0;
}

void Application::framebufferSizeEvent()
{
	LayoutNeedRefresh = true;
}

void Application::AskForLayoutRefresh()
{
	LayoutNeedRefresh = true;
}

void Application::ScrollCallBackEvent(GLFWwindow* window, bool guiWantToCapture, double xoffset, double yoffset)
{
	if (ViewPort.IsWindowHovered())
	{
		ViewPort.SetZoom(ViewPort.GetZoom()*(1 + yoffset*0.1));
		ImGui::SetWindowFocus(ViewPort.GetGuiName());
	}
}
