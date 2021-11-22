#pragma once

#include "plugin_loader.hpp"
#include "plugin_info_loader.hpp"
#include "plugin_list.hpp"

template<class T>
void loadPlugins(const std::string plugin_dir,const std::string base_class,typename PluginList<T>::Ptr plugin_list){
    using pluginLoaderHandler = std::map<std::string,typename PluginLoader<T>::Ptr>;

    pluginLoaderHandler handler;
    PluginInfoLoader* infoLoader = new PluginInfoLoader(plugin_dir);
    auto infos = infoLoader->getInfos();
    delete infoLoader;
    for(auto &info:infos){
        if (info.base_class == base_class) {

            typename PluginLoader<T>::Ptr loader = nullptr;
            auto itr = handler.find(info.name);
            if (itr != handler.end()) {
                loader = itr->second;
            } else {
                loader = createLoader<T>(info.name,plugin_dir);
                handler[info.name] = loader;
            }
            if (loader) {
                auto instance = loader->createInstance(info.plugin_class);
                if (instance) {
                    instance->init();
                    plugin_list->insert(info.plugin_class, instance);
                }
            }
        }
    }
};
