#include "utilities.hpp"

std::vector<std::string> getFileNames(std::string folderPath, std::string extension, std::string prefix) {

    std::vector < std::string > file_names;
    std::filesystem::path path(folderPath);
    if (std::filesystem::is_directory(path)) {
        auto dir_it = std::filesystem::directory_iterator(path);
        for (auto &file : dir_it) {

            if (file.path().extension() == extension) {
                auto fname = file.path().filename().string();
                if (prefix.empty() || std::equal(std::begin(prefix), std::end(prefix), std::begin(fname)))
                    file_names.push_back(file.path().string());
            }
        }
    }

    return file_names;
}

