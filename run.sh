# mv src/raygui.h src/raygui.c
#gcc -o raygui.so src/raygui.c -shared -fpic -DRAYGUI_IMPLEMENTATION -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
gcc main.c utils/file_util.c -o app -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
./app
rm -rf app
