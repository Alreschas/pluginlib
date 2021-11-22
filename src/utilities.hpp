#pragma once

#include "common.hpp"

std::vector<std::string> getFileNames(std::string folderPath, std::string extension, std::string prefix = "") ;



template<class T1,class T2>
std::vector<T2> mapToVec(const std::map<T1,T2>& map){
    std::vector<T2> ret;
    for(auto &m:map){
        ret.push_back(m.second);
    }
    return ret;
}
