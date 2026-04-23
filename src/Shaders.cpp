#include "Shaders.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

std::string Shader::readFile(const std::string& path)
{
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Could not open shader file: " << path << "\n";
        return "";
    }
    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

GLuint Shader::compileShader(GLenum type, const std::string& src)
{
    GLuint shader = glCreateShader(type);
    const char* cstr = src.c_str();
    glShaderSource(shader, 1, &cstr, nullptr);
    glCompileShader(shader);

    // Check for compile errors
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char log[512];
        glGetShaderInfoLog(shader, 512, nullptr, log);
        std::cerr << "Shader compile error:\n" << log << "\n";
    }
    return shader;
}

bool Shader::load(const std::string& vertPath, const std::string& fragPath)
{
    GLuint vert = compileShader(GL_VERTEX_SHADER, readFile(vertPath));
    GLuint frag = compileShader(GL_FRAGMENT_SHADER, readFile(fragPath));

    m_program = glCreateProgram();
    glAttachShader(m_program, vert);
    glAttachShader(m_program, frag);
    glLinkProgram(m_program);

    // Check for link errors
    int success;
    glGetProgramiv(m_program, GL_LINK_STATUS, &success);
    if (!success) {
        char log[512];
        glGetProgramInfoLog(m_program, 512, nullptr, log);
        std::cerr << "Shader link error:\n" << log << "\n";
        return false;
    }

    // Once linked, the individual shaders are no longer needed
    glDeleteShader(vert);
    glDeleteShader(frag);
    return true;
}

void Shader::use()     const { glUseProgram(m_program); }
void Shader::shutdown() { glDeleteProgram(m_program); }

void Shader::setMat4(const std::string& name, const glm::mat4& mat) const
{
    GLint loc = glGetUniformLocation(m_program, name.c_str());
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
}
