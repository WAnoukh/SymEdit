#pragma once

#include <list>

#include "Window.h"
#include "../Scene/Viewport/2DViewPort/TextureEditor.h"
#include "../Rendering/Textures/TextureDrawers/Pen.h"
#include "../Scene/Viewport/2DViewport/PlaneViewer.h"


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

	//Texture Editing
	Texture& GetActiveTexture() { return activeTexture; }
	
private:
	const unsigned int INITIAL_SCR_WIDTH = 1000;
	const unsigned int INITIAL_SCR_HEIGHT = 1000;
	const unsigned int TEXTURE_W = 2048;
	const unsigned int TEXTURE_H = 1024;
	int swapInterval = 0;
	bool LayoutNeedRefresh = true;
	bool mouseRightPressed = false;
	Window Window;
	std::list<ViewPortBase*> viewPorts;
	TextureEditor textureEditor;
	PlaneViewer planeViewer;
	Pen pen;

	double lastX = 0.0f;
	double lastY = 0.0f;

	void Init();

	void Render();

	void Tick(float deltaTime);

	//Texture Editing
	Texture activeTexture;
};

