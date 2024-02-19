#include <sol/core/filesystem.hpp>
#include <sol/log/logger.hpp>

namespace sol::core
{
	bool FileSystem::exists(const Path& path)
	{
        return std::filesystem::exists(path);
	}

	bool FileSystem::is_file(const Path& path)
	{
        return exists(path) && std::filesystem::is_regular_file(path);
	}

	bool FileSystem::is_directory(const Path& path)
	{
        return exists(path) && std::filesystem::is_directory(path);
	}

	bool FileSystem::create_directory(const Path& path)
	{
        return std::filesystem::create_directory(path);
    }

    const std::vector<Path> FileSystem::get_file_paths(const Path& directory, bool recursive)
    {
        std::vector<Path> results;

        if (exists(directory))
        {
            if (recursive)
            {
                for (auto const& dirEntry : std::filesystem::recursive_directory_iterator{ directory })
                {
                    results.push_back(dirEntry.path());
                }
            }
            else
            {
                for (auto const& dirEntry : std::filesystem::directory_iterator{ directory })
                {
                    results.push_back(dirEntry.path());
                }
            }
        }
        else
        {
            throw new std::exception(std::string("Directory not found (" + directory.string() + ")").c_str());
        }

        return results;
    }

    const std::vector<Path> FileSystem::get_file_paths(const Path& directory, bool recursive,
                                                       const std::string& searchPattern)
    {
        return get_file_paths(directory, recursive);
    }

    std::fstream FileSystem::load_to_stream(const Path& path)
    {
		if (!exists(path))
		{
            throw new std::exception(std::string(("File does not exist (") + path.string() + ")").c_str());
		}

		return std::fstream(path.c_str());
    }

    std::string FileSystem::load_to_string(const Path& path)
    {
        if (!exists(path))
        {
            throw new std::exception(std::string(("File does not exist (") + path.string() + ")").c_str());
        }

        std::ifstream file(path.c_str());
        const std::string data((std::istreambuf_iterator(file)), std::istreambuf_iterator<char>());

        return data;
    }

    bool FileSystem::save_to_file(const Path& path, const std::string& data, ESaveMode saveMode, bool binary)
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

        int32_t openMode = std::ios::out;

        switch (saveMode)
        {
        case ESaveMode::Append:
            openMode |= std::ios::app;
            break;

        case ESaveMode::Truncate:
            openMode |= std::ios::trunc;
            break;
        }

        if (binary)
        {
            openMode |= std::ios::binary;
        }

        std::ofstream file(path, static_cast<std::_Iosb<int32_t>::_Openmode>(openMode));
        file << data.data();
        file.close();

        return true;
    }
}