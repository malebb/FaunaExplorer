#include <iostream>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "VBO.h"
#include "VAO.h"


unsigned int winWidth = 800;
unsigned int winHeight = 600;

float rectangle[] = {
    -0.5f, 0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    0.5f, 0.5f, 0.0f,
    0.5f, 0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f
};

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(winWidth, winHeight, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        return -1;
    }

    glViewport(0, 0, winWidth, winHeight);

    Shader shader("./shaders/default.vertex", "./shaders/default.fragment");

    VAO vao1;
    vao1.bind();

    VBO vbo1(rectangle, sizeof(rectangle));
    vao1.linkVBO(vbo1);

    vao1.unbind();
    vbo1.unbind();

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        vao1.bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    vao1.deleteBuf();
    vbo1.deleteBuf();
    shader.deleteProgram();

    glfwTerminate();
    return 0;
}