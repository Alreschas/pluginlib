#pragma once

#include "../plugin_interface/sample_plugin_interface.hpp"
#include "common.hpp"
#include "plugin_exporter.hpp"

class SamplePlugin: public SamplePluginInterface {
public:
    SamplePlugin(Handler handler) :
            SamplePluginInterface(handler) {
    }

    ~SamplePlugin() {
    }


    void exec(){
        std::cout<<"Hello World."<<std::endl;
    }

};

PLUGIN_EXPORT_CLASS(SamplePlugin, SamplePluginInterface);
