#pragma once

#include "Window.h"
#include "../Scene/ViewPort.h"
#include "../Rendering/Textures/TextureDrawers/Pen.h"


class Application
{
public:
	
	Application(): Window(*this) {Init();}

	static inline  Application* instance = nullptr;

	static Application& GetInstance();

	int Run();

	unsigned int GetInitialScreenWidth() const { return INITIAL_SCR_WIDTH; };
	unsigned int GetInitialScreenHeight() const { return INITIAL_SCR_HEIGHT; };

	void framebufferSizeEvent();

	void AskForLayoutRefresh();

	void ScrollCallBackEvent(GLFWwindow* window, bool guiWantToCapture, double xOffset, double yOffset);

	void MouseButtonCallBackEvent(GLFWwindow* window, bool guiWantToCapture, int button, int action, int mods);

	void MousePositionCallBackEvent(GLFWwindow* window, bool guiWantToCapture, double xPos, double yPos);

private:
	const unsigned int INITIAL_SCR_WIDTH = 1000;
	const unsigned int INITIAL_SCR_HEIGHT = 1000;
	int swapInterval = 0;
	bool LayoutNeedRefresh = true;
	bool mouseRightPressed = false;
	Window Window;
	ViewPort ViewPort;
	Pen pen;

	double lastX = 0.0f;
	double lastY = 0.0f;

	void Init();

	void Render();

	void Tick(float deltaTime);
};

