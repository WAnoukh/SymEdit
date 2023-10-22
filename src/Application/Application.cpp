#include "Application.h"

#include <string>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_opengl3_loader.h"
#include "imgui_internal.h"

void Application::Init() {
	if (Window.init() == -1) {
		std::cerr << "Application : Window.init() Failed." << std::endl;
	}
	glEnable(GL_DEPTH_TEST);
}

void Application::Render()
{
	Window.PreRender();
	
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
	ImGuiID dockspace_id = ImGui::DockSpaceOverViewport(viewport,dockspace_flags);
	if(LayoutNeedRefresh)
	{
		if (dockspace_id)
		{
			if(viewport->Size.x != 0 && viewport->Size.y != 0)
			{
				ImGui::DockBuilderAddNode(dockspace_id, dockspace_flags | ImGuiDockNodeFlags_DockSpace);
				ImGui::DockBuilderSetNodeSize(dockspace_id, viewport->Size);

				auto dock_id_top = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Left, 0.1f, nullptr, &dockspace_id);
				ImGui::DockBuilderDockWindow("Tools", dock_id_top);
				ImGui::DockBuilderDockWindow("Viewport", dockspace_id);
			}
		}
		LayoutNeedRefresh = false;
	}	
	ImGui::Begin("Tools");
	ImGui::Text("This is some useful text.");
	ImGui::End();
	
	ViewPort.RenderUI();
	pen.RenderUI();
	
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	
	Window.PostRender();
}

void Application::Tick(float deltaTime)
{
	if (ViewPort.IsWindowHovered() && mouseRightPressed)
	{
		pen.Apply(ViewPort.GetTexture(), ViewPort, static_cast<float>(lastX), static_cast<float>(lastY));
		pen.SetInterpolate(true);
		ImGui::SetWindowFocus(ViewPort.GetGuiName());
	}
	ViewPort.Tick(deltaTime);
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
	float lastFrame = 0.0f;
	
	// render loop
	// -----------
	while (!Window.shouldClose())
	{
		const auto currentFrame = static_cast<float>(glfwGetTime());
		const float deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		
		Tick(deltaTime);
		Render();
		
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

void Application::MouseButtonCallBackEvent(GLFWwindow* window, bool guiWantToCapture, int button, int action, int mods)
{
	if(button == GLFW_MOUSE_BUTTON_MIDDLE)
	{
		if(action == GLFW_PRESS)
		{
			if (ViewPort.IsWindowHovered() && !ViewPort.IsPanning())
			{
				ViewPort.StartPanning(static_cast<float>(lastX), static_cast<float>(lastY));
				ImGui::SetWindowFocus(ViewPort.GetGuiName());
			}
		}
		else if(action == GLFW_RELEASE)
		{
			if(ViewPort.IsPanning())
			{
				ViewPort.StopPanning();
			}
		}
		return;
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		if(action == GLFW_PRESS)
		{
			mouseRightPressed = true;
		}
		if(action == GLFW_RELEASE)
		{
			mouseRightPressed = false;
			pen.SetInterpolate(false);
		}
	}
}

void Application::MousePositionCallBackEvent(GLFWwindow* window, bool guiWantToCapture, double xPos, double yPos)
{
	//TODO: Replace that with Imgui::MousePos
	lastX = xPos;
	lastY = yPos;
	if(ViewPort.IsPanning())
	{
		ViewPort.SetPanOffset(static_cast<float>(lastX), static_cast<float>(lastY));
		ImGui::SetWindowFocus(ViewPort.GetGuiName());
	}
}
