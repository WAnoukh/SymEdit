#pragma once

#include "Window.h"
#include "../Scene/ViewPort.h"


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

	void ScrollCallBackEvent(GLFWwindow* window, bool guiWantToCapture, double xoffset, double yoffset);

private:
	const unsigned int INITIAL_SCR_WIDTH = 1000;
	const unsigned int INITIAL_SCR_HEIGHT = 1000;
	int SwapInterval = 0;
	bool LayoutNeedRefresh = true;
	Window Window;
	ViewPort ViewPort;

	void Init();
};

