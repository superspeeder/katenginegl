#include "shader.hpp"


#include <fstream>
#include <iostream>

namespace kat {

    ShaderModule::ShaderModule(const std::string &source, ShaderType type) {
        m_shader             = glCreateShader(static_cast<GLenum>(type));
        const char *cstr_src = source.c_str();
        glShaderSource(m_shader, 1, &cstr_src, nullptr);
        glCompileShader(m_shader);

        int status;
        glGetShaderiv(m_shader, GL_COMPILE_STATUS, &status);
        if (status != GL_TRUE) {
            glGetShaderiv(m_shader, GL_INFO_LOG_LENGTH, &status);
            char *buf = new char[status];
            glGetShaderInfoLog(m_shader, status, nullptr, buf);
            std::cerr << "Shader Compilation Error: " << buf << std::endl;
            delete[] buf;
        }
    }

    std::shared_ptr<ShaderModule> ShaderModule::load(const std::string &path, ShaderType type) {
        return create(read_file(path), type);
    }

    std::shared_ptr<ShaderModule> ShaderModule::create(const std::string &source, ShaderType type) {
        return std::shared_ptr<ShaderModule>(new ShaderModule(source, type));
    }

    ShaderModule::~ShaderModule() {
        glDeleteShader(m_shader);
    }

    Shader::Shader(const std::vector<std::shared_ptr<ShaderModule>> &modules) {
        m_program = glCreateProgram();

        for (const auto& module : modules) {
            glAttachShader(m_program, module->get_handle());
        }

        glLinkProgram(m_program);

        int status;
        glGetProgramiv(m_program, GL_LINK_STATUS, &status);
        if (status != GL_TRUE) {
            glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &status);
            char *buf = new char[status];
            glGetProgramInfoLog(m_program, status, nullptr, buf);
            std::cerr << "Shader Program Linker Error: " << buf << std::endl;
            delete[] buf;
        }
    }

    std::shared_ptr<Shader> Shader::load(const std::string &vertex, const std::string &fragment) {
        return load({{vertex, ShaderType::Vertex},{fragment, ShaderType::Fragment}});
    }

    std::shared_ptr<Shader> Shader::load(const std::vector<std::pair<std::string, ShaderType>> &modules) {
        std::vector<std::shared_ptr<ShaderModule>> mods;
        for (const auto &m : modules) {
            mods.push_back(ShaderModule::load(m.first, m.second));
        }
        return create(mods);
    }

    std::shared_ptr<Shader> Shader::create(const std::vector<std::shared_ptr<ShaderModule>> &modules) {
        return std::shared_ptr<Shader>(new Shader(modules));
    }

    std::shared_ptr<Shader> Shader::create(const std::vector<std::pair<std::string, ShaderType>> &modules) {
        std::vector<std::shared_ptr<ShaderModule>> mods;
        for (const auto &m : modules) {
            mods.push_back(ShaderModule::create(m.first, m.second));
        }
        return create(mods);
    }

    Shader::~Shader() {
        glDeleteProgram(m_program);
    }

    void Shader::bind() const {
        glUseProgram(m_program);
    }

    int Shader::get_uniform_location(const std::string &name) const {
        return glGetUniformLocation(m_program, name.c_str());
    }
} // namespace kat
