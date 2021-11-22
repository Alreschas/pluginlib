#pragma once

#include<cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <algorithm>
#include <string>
#include <thread>
#include <chrono>
#include <regex>
#include <memory>
#include <mutex>
#include <map>
#include <unordered_map>
#include <typeinfo>
#include <queue>
#include <condition_variable>
#include <typeindex>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
#include <cstdlib>
#include <cstring>
#include <filesystem>



#define LOG_ERROR_STREAM(str) std::cout<<"\033[31m[ERROR][func:"<<__FUNCTION__<<"] "<< str
#define LOG_INFO_STREAM(str) std::cout<<"\x1b[36m[INFO][func:"<<__FUNCTION__<<"] "<< str
#define LOG_DEBUG_STREAM(str) std::cout<<"\x1b[36m[INFO][func:"<<__FUNCTION__<<"] "<< str
#define LOG_STREAM_CONTINUE(str) std::cout<<str
#define LOG_END std::dec<<"\033[m"<<std::endl
