#pragma once
#include <memory>
#include <string>
#include <vector>

#include "kat/engine.hpp"

#include <glm/gtc/type_ptr.hpp>

namespace kat {

    enum class ShaderType : GLenum {
        Vertex = GL_VERTEX_SHADER,
        Fragment = GL_FRAGMENT_SHADER,
        Geometry = GL_GEOMETRY_SHADER,
        TessControl = GL_TESS_CONTROL_SHADER,
        TessEval = GL_TESS_EVALUATION_SHADER,
        Compute = GL_COMPUTE_SHADER,
    };

    class ShaderModule {
      public:

        ~ShaderModule();

        static std::shared_ptr<ShaderModule> load(const std::string& path, ShaderType type);
        static std::shared_ptr<ShaderModule> create(const std::string& source, ShaderType type);

        inline unsigned int get_handle() const noexcept { return m_shader; };

    private:
        ShaderModule(const std::string& source, ShaderType type);

        unsigned int m_shader;
    };

    class Shader {
      public:

        static std::shared_ptr<Shader> load(const std::string &vertex, const std::string &fragment);
        static std::shared_ptr<Shader> load(const std::vector<std::pair<std::string, ShaderType>> &modules);

        static std::shared_ptr<Shader> create(const std::vector<std::shared_ptr<ShaderModule>> &modules);
        static std::shared_ptr<Shader> create(const std::vector<std::pair<std::string, ShaderType>> &modules);


        ~Shader();

        void bind() const;

        int get_uniform_location(const std::string& name) const;

        // Vector : float | glm::vec
        inline void uniform1f(const std::string &uniform_name, float x) const {
            glProgramUniform1f(m_program, get_uniform_location(uniform_name), x);
        };

        inline void uniform1f(const std::string &uniform_name, const glm::vec1 &v) const {
            glProgramUniform1fv(m_program, get_uniform_location(uniform_name), 1, glm::value_ptr(v));
        };

        inline void uniform2f(const std::string &uniform_name, float x, float y) const {
            glProgramUniform2f(m_program, get_uniform_location(uniform_name), x, y);
        };

        inline void uniform2f(const std::string &uniform_name, const glm::vec2 &v) const {
            glProgramUniform2fv(m_program, get_uniform_location(uniform_name), 1, glm::value_ptr(v));
        };

        inline void uniform3f(const std::string &uniform_name, float x, float y, float z) const {
            glProgramUniform3f(m_program, get_uniform_location(uniform_name), x, y, z);
        };

        inline void uniform3f(const std::string &uniform_name, const glm::vec3 &v) const {
            glProgramUniform3fv(m_program, get_uniform_location(uniform_name), 1, glm::value_ptr(v));
        };

        inline void uniform4f(const std::string &uniform_name, float x, float y, float z, float w) const {
            glProgramUniform4f(m_program, get_uniform_location(uniform_name), x, y, z, w);
        };

        inline void uniform4f(const std::string &uniform_name, const glm::vec4 &v) const {
            glProgramUniform4fv(m_program, get_uniform_location(uniform_name), 1, glm::value_ptr(v));
        };

        // Vector : double | glm::dvec
        inline void uniform1d(const std::string &uniform_name, double x) const {
            glProgramUniform1d(m_program, get_uniform_location(uniform_name), x);
        };

        inline void uniform1d(const std::string &uniform_name, const glm::dvec1 &v) const {
            glProgramUniform1dv(m_program, get_uniform_location(uniform_name), 1, glm::value_ptr(v));
        };

        inline void uniform2d(const std::string &uniform_name, double x, double y) const {
            glProgramUniform2d(m_program, get_uniform_location(uniform_name), x, y);
        };

        inline void uniform2d(const std::string &uniform_name, const glm::dvec2 &v) const {
            glProgramUniform2dv(m_program, get_uniform_location(uniform_name), 1, glm::value_ptr(v));
        };

        inline void uniform3d(const std::string &uniform_name, double x, double y, double z) const {
            glProgramUniform3d(m_program, get_uniform_location(uniform_name), x, y, z);
        };

        inline void uniform3d(const std::string &uniform_name, const glm::dvec3 &v) const {
            glProgramUniform3dv(m_program, get_uniform_location(uniform_name), 1, glm::value_ptr(v));
        };

        inline void uniform4d(const std::string &uniform_name, double x, double y, double z, double w) const {
            glProgramUniform4d(m_program, get_uniform_location(uniform_name), x, y, z, w);
        };

        inline void uniform4d(const std::string &uniform_name, const glm::dvec4 &v) const {
            glProgramUniform4dv(m_program, get_uniform_location(uniform_name), 1, glm::value_ptr(v));
        };

        // Vector : int | glm::ivec
        inline void uniform1i(const std::string &uniform_name, int x) const {
            glProgramUniform1i(m_program, get_uniform_location(uniform_name), x);
        };

        inline void uniform1i(const std::string &uniform_name, const glm::ivec1 &v) const {
            glProgramUniform1iv(m_program, get_uniform_location(uniform_name), 1, glm::value_ptr(v));
        };

        inline void uniform2i(const std::string &uniform_name, int x, int y) const {
            glProgramUniform2i(m_program, get_uniform_location(uniform_name), x, y);
        };

        inline void uniform2i(const std::string &uniform_name, const glm::ivec2 &v) const {
            glProgramUniform2iv(m_program, get_uniform_location(uniform_name), 1, glm::value_ptr(v));
        };

        inline void uniform3i(const std::string &uniform_name, int x, int y, int z) const {
            glProgramUniform3i(m_program, get_uniform_location(uniform_name), x, y, z);
        };

        inline void uniform3i(const std::string &uniform_name, const glm::ivec3 &v) const {
            glProgramUniform3iv(m_program, get_uniform_location(uniform_name), 1, glm::value_ptr(v));
        };

        inline void uniform4i(const std::string &uniform_name, int x, int y, int z, int w) const {
            glProgramUniform4i(m_program, get_uniform_location(uniform_name), x, y, z, w);
        };

        inline void uniform4i(const std::string &uniform_name, const glm::ivec4 &v) const {
            glProgramUniform4iv(m_program, get_uniform_location(uniform_name), 1, glm::value_ptr(v));
        };

        // Vector : unsigned int | glm::uvec
        inline void uniform1ui(const std::string &uniform_name, unsigned int x) const {
            glProgramUniform1ui(m_program, get_uniform_location(uniform_name), x);
        };

        inline void uniform1ui(const std::string &uniform_name, const glm::uvec1 &v) const {
            glProgramUniform1uiv(m_program, get_uniform_location(uniform_name), 1, glm::value_ptr(v));
        };

        inline void uniform2ui(const std::string &uniform_name, unsigned int x, unsigned int y) const {
            glProgramUniform2ui(m_program, get_uniform_location(uniform_name), x, y);
        };

        inline void uniform2ui(const std::string &uniform_name, const glm::uvec2 &v) const {
            glProgramUniform2uiv(m_program, get_uniform_location(uniform_name), 1, glm::value_ptr(v));
        };

        inline void uniform3ui(const std::string &uniform_name, unsigned int x, unsigned int y, unsigned int z) const {
            glProgramUniform3ui(m_program, get_uniform_location(uniform_name), x, y, z);
        };

        inline void uniform3ui(const std::string &uniform_name, const glm::uvec3 &v) const {
            glProgramUniform3uiv(m_program, get_uniform_location(uniform_name), 1, glm::value_ptr(v));
        };

        inline void uniform4ui(const std::string &uniform_name, unsigned int x, unsigned int y, unsigned int z,
                               unsigned int w) const {
            glProgramUniform4ui(m_program, get_uniform_location(uniform_name), x, y, z, w);
        };

        inline void uniform4ui(const std::string &uniform_name, const glm::uvec4 &v) const {
            glProgramUniform4uiv(m_program, get_uniform_location(uniform_name), 1, glm::value_ptr(v));
        };

        // Matrix : float | glm::mat
        inline void uniform_matrix2f(const std::string &uniform_name, const glm::mat2 &v) const {
            glProgramUniformMatrix2fv(m_program, get_uniform_location(uniform_name), 1, false, glm::value_ptr(v));
        };

        inline void uniform_matrix3f(const std::string &uniform_name, const glm::mat3 &v) const {
            glProgramUniformMatrix3fv(m_program, get_uniform_location(uniform_name), 1, false, glm::value_ptr(v));
        };

        inline void uniform_matrix4f(const std::string &uniform_name, const glm::mat4 &v) const {
            glProgramUniformMatrix4fv(m_program, get_uniform_location(uniform_name), 1, false, glm::value_ptr(v));
        };

        // Matrix : double | glm::dmat
        inline void uniform_matrix2d(const std::string &uniform_name, const glm::dmat2 &v) const {
            glProgramUniformMatrix2dv(m_program, get_uniform_location(uniform_name), 1, false, glm::value_ptr(v));
        };

        inline void uniform_matrix3d(const std::string &uniform_name, const glm::dmat3 &v) const {
            glProgramUniformMatrix3dv(m_program, get_uniform_location(uniform_name), 1, false, glm::value_ptr(v));
        };

        inline void uniform_matrix4d(const std::string &uniform_name, const glm::dmat4 &v) const {
            glProgramUniformMatrix4dv(m_program, get_uniform_location(uniform_name), 1, false, glm::value_ptr(v));
        };


      private:
        Shader(const std::vector<std::shared_ptr<ShaderModule>> &modules);

        unsigned int m_program;
    };

} // namespace kat
