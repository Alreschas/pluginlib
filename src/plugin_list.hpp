#pragma once

#include "common.hpp"

//関数群
template<class T>
class PluginList {
    public:
    std::string id;
        typedef std::shared_ptr<PluginList<T>> Ptr;

        PluginList(std::string id = ""):id(id){
        };

        ~PluginList(){
            LOG_INFO_STREAM("closed : "<<id<<LOG_END);

            for(auto itr = plugin_list.begin();itr != plugin_list.end();){

                auto handler = itr->second->getHandler();
                itr = plugin_list.erase(itr);

                if(handler){
                    handler->close();
                }
            }
        }

        //重複した場合は弾く
        void insert(std::string name, std::shared_ptr<T> plugin) {
                plugin_list.insert(std::make_pair(name, plugin));
        }

        std::vector<std::string> getPluginNames(){
            std::vector <std::string> ret;
            for (auto itr = plugin_list.begin(); itr != plugin_list.end(); ++itr) {
                ret.push_back(itr->first);
            }
            return ret;
        }

        std::shared_ptr<T> getPlugin(std::string plugin_name){
            if(plugin_list.count(plugin_name)==0){
                return nullptr;
            }

            return plugin_list[plugin_name];
        }

        std::vector<std::shared_ptr<T>> getPlugins(){
            return mapToVec(plugin_list);
        }


    private:
        std::map<std::string, std::shared_ptr<T>> plugin_list;
};
