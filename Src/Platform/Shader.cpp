//
// Created by hugom on 26/12/2023.
//

#include <fstream>
#include <sstream>
#include "Shader.h"

namespace HC {
    Shader::Shader(GLenum shaderType) {
        ShaderType = shaderType;
        Id = glCreateShader(shaderType);
    }

    Shader::~Shader() {

    }

    void Shader::SetSource(const char *source) {
        glShaderSource(Id, 1, &source, NULL);
    }

    void Shader::Compile() {
        glCompileShader(Id);
    }

    void Shader::GetCompileStatus(CompileStatus &compileStatus) {
        glGetShaderiv(Id, GL_COMPILE_STATUS, &compileStatus.success);
        if(!compileStatus.success) {
            char infoLog[512];
            glGetShaderInfoLog(Id, 512, nullptr, infoLog);
            compileStatus.infoLog = std::string(infoLog);
        }

    }




} // HC