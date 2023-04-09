#include <string>
#include <fstream>
#include <filesystem>

#include "core/logger/Log.h"

std::string ReadFileContent(const std::string& path)
{
    std::string output{};
    std::ifstream input{path};

    std::filesystem::path cwd = std::filesystem::current_path();

    if (input.is_open())
    {
        output.assign(
            std::istreambuf_iterator<char>(input),
            std::istreambuf_iterator<char>()
        );

        return output;
    }
    else
    {
        F_LOG_CORE_ERROR("Failed to open file {}", path);
    }

    return std::string{};
}