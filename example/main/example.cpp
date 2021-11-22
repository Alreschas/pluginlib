#include <iostream>
#include <memory>

#include "sample_plugin_interface.hpp"
#include "plugin_list_loader.hpp"


//関数群
using SamplePluginInterfaceList = PluginList<SamplePluginInterface>;
void loadPlugins(std::string plugin_dir,SamplePluginInterfaceList::Ptr panels);


void loadPlugins(std::string plugin_dir,SamplePluginInterfaceList::Ptr panels){
    //設定jsonファイルの、base_classが、SamplePluginInterfaceのものを読み込む
    loadPlugins<SamplePluginInterface>(plugin_dir,"SamplePluginInterface", panels);
}


int main(){
    SamplePluginInterfaceList::Ptr pluginList;
    pluginList = std::make_shared<SamplePluginInterfaceList>();
    loadPlugins("./", pluginList);
    for(auto plugin:pluginList->getPlugins()){
        plugin->exec();
    }

    return 0;
}
