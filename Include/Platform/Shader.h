#pragma once

#include <string>
#include <glad/glad.h>

namespace HC {
    struct CompileStatus {
        int success;
        std::string infoLog;
    };
    class Shader {
    public:
        explicit Shader(GLenum shaderType);
        ~Shader();
        void SetSource(const char *source);
        void Compile();
        void GetCompileStatus(CompileStatus& compileStatus);
        GLuint GetId() const { return Id;}
    private:
        GLuint Id;
        GLenum ShaderType;


    };

} // HC

