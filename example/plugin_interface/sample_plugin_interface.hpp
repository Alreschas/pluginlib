#pragma once

#include "plugin_loader.hpp"

class SamplePluginInterface{
public:
    typedef std::shared_ptr<SamplePluginInterface> Ptr;

    SamplePluginInterface(Handler handler = nullptr):handler(handler){
    }

    virtual ~SamplePluginInterface(){}

    Handler getHandler(){
        return handler;
    }

    virtual void init(){};

    virtual void exec() = 0;

private:
    Handler handler;

};
