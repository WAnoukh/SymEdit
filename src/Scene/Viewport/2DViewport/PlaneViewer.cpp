#include "PlaneViewer.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../../../Rendering/shader_s.h"

#include "../../../Application/Application.h"

class Texture;

PlaneViewer::~PlaneViewer()
{
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
}

void PlaneViewer::Init()
{
    ViewPortBase::Init();
    float vertices[] = {
        // positions        // uv coord
        1.0f,  -1.0f, 0.0f, // top right
        1.0f, 1.0f, 0.0f, // bottom right
       -1.0f, 1.0f, 0.0f, // bottom left
       -1.0f, -1.0f, 0.0f  // top left 
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    shader = new Shader("src/Rendering/Shaders/ViewPort/PlaneViewer.vert", "src/Rendering/Shaders/ViewPort/PlaneViewer.frag");

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void PlaneViewer::RenderViewPort()
{
    ViewPort2D::RenderViewPort();
    glClearColor(1, 0.1843137254901961f, 0.26666666666666666, 1.00f);
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(VAO);
    //glActiveTexture(GL_TEXTURE0);
    //const Texture& texture = Application::GetInstance().GetActiveTexture();
    //glBindTexture(GL_TEXTURE_2D, texture.GetTextureId());
    if(shader == nullptr)
    {
        std::cerr << "Shader is null" << std::endl;
        return;
    }

    shader->use();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void PlaneViewer::RenderUI()
{
    ViewPort2D::RenderUI();
}

void PlaneViewer::Tick(float deltaTime)
{
    ViewPort2D::Tick(deltaTime);
}

bool PlaneViewer::ScreenToTexture(const float x, const float y, float& outX, float& outY)
{
    return true;
}
