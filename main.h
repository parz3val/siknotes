#ifndef __main_h
#define __main_h
#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "./vendor/raygui/src/raygui.h"
#include "utils/file_util.h"

static void LoginButton(int *loggedIn, const char *repoUrl, const char *encryptionKey);
#endif
