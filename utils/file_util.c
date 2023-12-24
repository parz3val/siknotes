#include "file_util.h"

const char* getHomeDir() {
    #ifdef _WIN32
        return getenv("USERPROFILE");
    #else
        return getenv("HOME");
    #endif
}
