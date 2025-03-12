#include "ShaderLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::string ReadFile(const char* filePath) {
    std::ifstream file(filePath);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void CheckCompileErrors(GLuint shader, std::string type) {
    GLint success;
    GLchar infoLog[1024];

    if (type == "SHADER") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "ERROR: Shader Compilation Failed\n" << infoLog << std::endl;
        }
    }
    else if (type == "PROGRAM") {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "ERROR: Program Linking Failed\n" << infoLog << std::endl;
        }
    }
}

GLuint ShaderLoader::LoadShader(const char* vertexPath, const char* fragmentPath) {
    std::string vertexFile = ReadFile(vertexPath);
    std::string fragmentFile = ReadFile(fragmentPath);
    const char* vShaderCode = vertexFile.c_str();
    const char* fShaderCode = fragmentFile.c_str();

    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);
    CheckCompileErrors(vertex, "SHADER");

    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);
    CheckCompileErrors(fragment, "SHADER");

    GLuint program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);
    CheckCompileErrors(program, "PROGRAM");

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return program;
}

void ShaderLoader::SetUniform(GLuint shaderProgram, const std::string& name, float v1, float v2, float v3, float v4) {
    glUseProgram(shaderProgram);
    GLint location = glGetUniformLocation(shaderProgram, name.c_str());
    if (location == -1) {
        std::cerr << "WARNING: Uniform '" << name << "' not found!" << std::endl;
    }
    else {
        glUniform4f(location, v1, v2, v3, v4);
    }
}

void ShaderLoader::SetUniform(GLuint shaderProgram, const std::string& name, float v1) {
    glUseProgram(shaderProgram);
    GLint location = glGetUniformLocation(shaderProgram, name.c_str());
    if (location != -1) glUniform1f(location, v1);
}

void ShaderLoader::SetUniform(GLuint shaderProgram, const std::string& name, float v1, float v2) {
    glUseProgram(shaderProgram);
    GLint location = glGetUniformLocation(shaderProgram, name.c_str());
    if (location != -1) glUniform2f(location, v1, v2);
}

void ShaderLoader::SetUniform(GLuint shaderProgram, const std::string& name, float v1, float v2, float v3) {
    glUseProgram(shaderProgram);
    GLint location = glGetUniformLocation(shaderProgram, name.c_str());
    if (location != -1) glUniform3f(location, v1, v2, v3);
}

void ShaderLoader::SetUniform(GLuint shaderProgram, const std::string& name, int v1) {
    glUseProgram(shaderProgram);
    GLint location = glGetUniformLocation(shaderProgram, name.c_str());
    if (location != -1) glUniform1i(location, v1);
}

void ShaderLoader::SetUniform(GLuint shaderProgram, const std::string& name, int v1, int v2) {
    glUseProgram(shaderProgram);
    GLint location = glGetUniformLocation(shaderProgram, name.c_str());
    if (location != -1) glUniform2i(location, v1, v2);
}

void ShaderLoader::SetUniform(GLuint shaderProgram, const std::string& name, int v1, int v2, int v3) {
    glUseProgram(shaderProgram);
    GLint location = glGetUniformLocation(shaderProgram, name.c_str());
    if (location != -1) glUniform3i(location, v1, v2, v3);
}

void ShaderLoader::SetUniformMatrix4(GLuint shaderProgram, const std::string& name, const float* matrix) {
    glUseProgram(shaderProgram);
    GLint location = glGetUniformLocation(shaderProgram, name.c_str());
    if (location != -1) glUniformMatrix4fv(location, 1, GL_FALSE, matrix);
}
