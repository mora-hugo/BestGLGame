#pragma once

#include <string>
#include <cstdint>
#include <memory>
#include <map>
#include <vector>
#include <FileIO.h>
#include <Singleton.h>
#include <Shader.h>
#include <Assertion.h>
#include <format>

namespace HC {
    class IResource {
    public:
        explicit IResource(const std::string& filepath) : filepath(filepath) { }
        virtual ~IResource() = default;
        virtual bool Load() = 0;
        virtual bool Save() = 0;

        std::string GetFilePath() const {
            return filepath;
        }

    protected:
        std::string filepath;
    };

    template<typename T>
    class Resource : public IResource {
    public:
        explicit Resource(const std::string& filepath) : IResource(filepath) { }
        bool Load() override = 0;
        bool Save() override = 0;
    };

    class FileResource : public Resource<FileResource> {
    public:
        FileResource(const std::string& filepath) : Resource(filepath), reader(filepath), writer(filepath) {

        }


        bool Load() override {
            if(!reader.OpenFile()) {
                return false;
            }
            bytes.resize(reader.GetFileContentSize());
            reader.Read(bytes.data(), reader.GetFileContentSize());
            return reader.CloseFile();

        }

        bool Save() override {
            writer.OpenFile();
            writer.Write(bytes.data(), bytes.size());
            return writer.CloseFile();

        }
    public:
        std::vector<uint8_t> bytes;
    private:
        FileWriter writer;
        FileReader reader;


    };

    class ShaderResource : public FileResource {
    public:
        ShaderResource(const std::string& filepath, GLenum shaderType) : FileResource(filepath), shader(shaderType) {

        }

        Shader& GetShader() {
            return shader;
        }

        bool Load() override {
            bool bSuccess = FileResource::Load();
            if (!bSuccess) {
                return false;
            }
            shader.SetSource(reinterpret_cast<const char*>(bytes.data()));
            shader.Compile();
            CompileStatus compileStatus;
            shader.GetCompileStatus(compileStatus);
            Assertion(compileStatus.success, std::format("Shader compiling error: {0}", compileStatus.infoLog));
            return bSuccess;

        }


        Shader shader;

    };


    class ResourceManager : public Singleton<ResourceManager> {
    public:
        template<typename T, typename... Args>
        std::shared_ptr<T> Load(const std::string& filepath, Args... args) {
            std::shared_ptr<T> resource;
            auto it = resources.find(filepath);
            if (it != resources.end()) {
                resource = std::dynamic_pointer_cast<T>(it->second);
            }

            if (!resource) {
                resource = std::make_shared<T>(filepath, args...);
                // if the loading is not successful, we reset the newly created ptr
                if (!resource->Load()) {
                    resource.reset();
                    return nullptr;
                }
                resources[filepath] = std::static_pointer_cast<IResource>(resource);
            }
            return resource;
        }

        bool Unload(const std::string& filepath) {
            auto it = resources.find(filepath);
            if (it != resources.end()) {
                it->second.reset();
                resources.erase(it);
                return true;
            }
            return false;
        }

    private:
        std::map<std::string, std::shared_ptr<IResource>> resources;
    };

}