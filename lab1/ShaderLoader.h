#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H

#include <GL/glew.h>
#include <string>

class ShaderLoader {
public:
    static GLuint LoadShader(const char* vertexPath, const char* fragmentPath);

    static void SetUniform(GLuint shaderProgram, const std::string& name, float v1);
    static void SetUniform(GLuint shaderProgram, const std::string& name, float v1, float v2);
    static void SetUniform(GLuint shaderProgram, const std::string& name, float v1, float v2, float v3);
    static void SetUniform(GLuint shaderProgram, const std::string& name, float v1, float v2, float v3, float v4);

    static void SetUniform(GLuint shaderProgram, const std::string& name, int v1);
    static void SetUniform(GLuint shaderProgram, const std::string& name, int v1, int v2);
    static void SetUniform(GLuint shaderProgram, const std::string& name, int v1, int v2, int v3);
    static void SetUniform(GLuint shaderProgram, const std::string& name, int v1, int v2, int v3, int v4);

    static void SetUniformMatrix4(GLuint shaderProgram, const std::string& name, const float* matrix);
};

#endif 
