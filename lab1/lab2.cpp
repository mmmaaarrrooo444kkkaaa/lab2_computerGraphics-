#define GLEW_DLL
#define GLFW_DLL

#include "ShaderLoader.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <cmath>

float pointer[] = {
    -0.5f,  0.5f,  
     0.5f,  0.5f,  
     0.5f, -0.5f,  
    -0.5f, -0.5f  
};
GLuint index[] = { 0, 1, 2, 3 };

int main() {
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW.\n");
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(512, 512, "Mainwindow", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "ERROR: Failed to initialize GLEW.\n");
        return 1;
    }

    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pointer), pointer, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    GLuint shaderProgram = ShaderLoader::LoadShader("vertex_shader.glsl", "fragment_shader.glsl");

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        float timeValue = glfwGetTime();
        float speed = 2.0f;
        float r = (cos(timeValue * speed) / 2.0f) + 0.5f;
        float g = (sin(timeValue * speed) / 2.0f) + 0.5f;
        float b = 0.5f;

        ShaderLoader::SetUniform(shaderProgram, "ourColor", r, g, b, 1.0f);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
