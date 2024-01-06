#pragma once
#include <memory>
#include <string>
#include <vector>

namespace kat {

    class ShaderModule {
      public:
        ShaderModule();

        ~ShaderModule();
    };

    class Shader {
      public:
        Shader(const std::vector<std::shared_ptr<ShaderModule>> &modules);

        static std::shared_ptr<Shader> load(const std::string &vertex, const std::string &fragment);
        static std::shared_ptr<Shader> create(const std::vector<std::shared_ptr<ShaderModule>> &modules);


        ~Shader();

        void bind();


      private:
    };

} // namespace kat
