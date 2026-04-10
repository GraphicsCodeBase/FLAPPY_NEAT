#pragma once
#include <glad/glad.h>
#include <string>

class Shader {
public:
    bool load(const std::string& vertPath, const std::string& fragPath);
    void use()     const;
    void shutdown();

    GLuint id() const { return m_program; }

private:
    GLuint m_program = 0;

    static GLuint compileShader(GLenum type, const std::string& src);
    static std::string readFile(const std::string& path);
};
