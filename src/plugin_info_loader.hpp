#pragma once

#include "common.hpp"
#include "utilities.hpp"
#include "picojson.h"

struct PluginInfo{
    std::string name;
    std::string plugin_class;
    std::string base_class;
};

class PluginInfoLoader{
public:

    PluginInfoLoader(std::string plugin_dir){
        std::vector<std::string> file_names;
        file_names = getFileNames(plugin_dir, ".json");

        for(auto file_name:file_names){
            std::ifstream fs;
            fs.open(file_name, std::ios::binary);
            picojson::value val;
            fs >> val;
            fs.close();

            // Playerの名前を取得
          std::string name = val.get<picojson::object>()
                              ["name"].get<std::string>();
          std::string plugin_class = val.get<picojson::object>()
                              ["class"].get<std::string>();
          std::string base_class = val.get<picojson::object>()
                              ["base_class"].get<std::string>();


          //重複チェック
          bool duplicated = false;
          for (auto it = infos.begin(); it != infos.end(); ++it) {
              if(it->name == name){
                  duplicated = true;
                  LOG_ERROR_STREAM("plugin name duplicated: "<<name<<LOG_END);
              }
          }

          if(!duplicated){
              PluginInfo info{
                  name,
                  plugin_class,
                  base_class
              };
              infos.push_back(info);
          }

        }
    }

    std::vector<PluginInfo> getInfos(){
        return infos;
    }

    std::vector<PluginInfo> infos;


};
