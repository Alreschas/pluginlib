#include "plugin_exporter.hpp"

#ifdef _WIN32
// Windowsは、DLLエントリポイントが必要
#include <windows.h>
BOOL APIENTRY DllMain(HANDLE, DWORD, LPVOID){
    return TRUE;
}
#endif
