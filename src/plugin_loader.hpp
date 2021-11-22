#pragma once

#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

#include "common.hpp"

class PluginHandler:public std::enable_shared_from_this<PluginHandler> {
public:
    typedef std::shared_ptr<PluginHandler> Ptr;
    PluginHandler(){}
    virtual ~PluginHandler(){}

    virtual void close() = 0;
};

using Handler = PluginHandler::Ptr;

template<class T>
class PluginLoader: public PluginHandler
{
public:

        typedef std::shared_ptr<PluginLoader<T>> Ptr;

        PluginLoader(std::string lib_name,std::string lib_dir = "./"){
            loadPlugIn(lib_name,lib_dir);
        }

        ~PluginLoader(){
            close();
        }

        void loadPlugIn(std::string filename,std::string lib_dir)
        {
            std::string libfile = "";
#ifdef _WIN32
#ifdef __MINGW32__
            libfile = lib_dir+"/lib"+filename+".dll";
#else
            libfile = lib_dir+"/"+filename+".dll";
#endif
            lib = LoadLibrary(TEXT(libfile.c_str()));
#else
            libfile = lib_dir+"/lib"+filename+".so";
            lib = dlopen((libfile).c_str(), RTLD_NOW | RTLD_LOCAL);

            if (!lib) {
                LOG_ERROR_STREAM("dlopen: "<<dlerror()<<LOG_END);
            }
#endif

            if(!lib){
                LOG_ERROR_STREAM("could not load library: "<<libfile<<LOG_END);
            }
        }

        void close(){
            if(!lib){
                return;
            }

#ifdef _WIN32
            FreeLibrary(lib);
#else
            dlclose(lib);
            lib = nullptr;
#endif
        }

        std::shared_ptr<T> createInstance(std::string target_class){
            if(!lib){
                return nullptr;
            }

            std::string factory_func_name = target_class+"Factory";

#ifdef _WIN32
            FARPROC factory_function = GetProcAddress(lib, TEXT(factory_func_name.c_str()));
#else
            void* factory_function = dlsym(lib, factory_func_name.c_str());
#endif
            if(factory_function != nullptr){
                return std::shared_ptr<T>(reinterpret_cast<PluginFactory>(factory_function)(shared_from_this()));
            }
            LOG_ERROR_STREAM("create error: "<<target_class<<" not found"<<LOG_END);
            return nullptr;
        }

    private:
        using PluginFactory = T*(*)(Handler);

#ifdef _WIN32
        HMODULE lib;
#else
        void* lib = nullptr;
#endif
};


template<class T>
typename PluginLoader<T>::Ptr createLoader(std::string lib_name,std::string lib_dir){
    return typename PluginLoader<T>::Ptr(new PluginLoader<T>(lib_name,lib_dir));
}
