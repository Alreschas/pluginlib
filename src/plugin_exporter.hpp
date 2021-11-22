#pragma once

//マングリングを解除する

#ifdef _WIN32
#define PLUGIN_EXPORT extern "C" __declspec(dllexport)
#define PLUGIN_EXPORT_CLASS(TARGET,BASE) \
    PLUGIN_EXPORT BASE* TARGET##Factory(){\
        return new TARGET; \
    }
#else
#define PLUGIN_EXPORT extern "C"
#define PLUGIN_EXPORT_CLASS(TARGET,BASE) \
    PLUGIN_EXPORT BASE* TARGET##Factory(Handler handler){\
        return new TARGET(handler); \
    }
#endif

