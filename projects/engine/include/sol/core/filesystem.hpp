#ifndef _SOL_FILESYSTEM_HPP__
#define _SOL_FILESYSTEM_HPP__

#include <filesystem>
#include <fstream>
#include <vector>

namespace sol::core
{
	using Path = std::filesystem::path;

	enum class ESaveMode : uint8_t
    {
        Append,
        Truncate
    };

	class FileSystem
	{
      public:
        static bool exists(const Path& path);
        static bool is_file(const Path& path);
        static bool is_directory(const Path& path);

		static bool create_directory(const Path& path);

        static const std::vector<Path> get_file_paths(const Path& directory, bool recursive);
        static const std::vector<Path> get_file_paths(const Path& directory, bool recursive,
                                                      const std::string& searchPattern);

		static std::fstream load_to_stream(const Path& path);
        static std::string load_to_string(const Path& path);

		template<typename Type>
        static const std::vector<Type> load_as(const Path& path);

        static bool save_to_file(const Path& path, const std::string& data, ESaveMode saveMode, bool binary = false);

        template<typename Type>
        static bool save_to_file(const Path& path, const std::vector<Type>& data, ESaveMode saveMode);
	};

    template <typename Type>
    inline const std::vector<Type> FileSystem::load_as(const Path& path)
    {
        if (!exists(path))
        {
            throw new std::exception(std::string(("File does not exist (") + path.string() + ")").c_str());
        }

        std::ifstream file(path.c_str());
        return std::vector<Type>((std::istream_iterator<Type>(file)),
                                 std::istream_iterator<Type>());
    }

    template <typename Type>
    inline bool FileSystem::save_to_file(const Path& path, const std::vector<Type>& data, ESaveMode saveMode)
    {
        if (!exists(path))
        {
            Path directory = path;
            directory.remove_filename();

            if (!exists(directory))
            {
                create_directory(directory);
            }
        }

        int32_t openMode = std::ios::out | std::ios::binary;

        switch (saveMode)
        {
        case ESaveMode::Append:
            openMode |= std::ios::app;
            break;

        case ESaveMode::Truncate:
            openMode |= std::ios::trunc;
            break;
        }

        std::ofstream file(path, static_cast<std::_Iosb<int32_t>::_Openmode>(openMode));
        file << data.data();
        file.close();

        return true;
    }
} // namespace sol::core

#endif // _SOL_FILESYSTEM_HPP__