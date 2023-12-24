#include "main.h"

int main() {

  // Font customFnt =
  // LoadFontEx("./rayfonts/mplus-1m-bold.ttf", 256, NULL, 1024);

  int screenWidth = 800;
  int screenHeight = 400;
  int loggedIn = 0;

  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
  // Init window
  InitWindow(screenWidth, screenHeight, "Siknotes: Secret Notes");

  // Load Image
  Image iconImage = LoadImage("./OIG.png");
  ImageResize(&iconImage, 200, 200);

  // Get the texture from the image
  Texture2D iconTexture = LoadTextureFromImage(iconImage);

  // We can unload the image after its been conveted into texture
  UnloadImage(iconImage);
  // Note :: Can only load the fonts after initializing the window

  const char *pageTitle = "SIKNOTES";
  const char *subTitle = "No fuss secure notes with git backend!";
  const char *loginButtonText = "Login";

  char repoNameInputText[1024] = "repo url";
  char encryptionBoxInputText[1024] = "encryption key";
  char encryptionText[1024] = "";

  bool repoNameInputEditMode = false;
  int repoNameInputValue = 0;
  bool encryptionBoxInputEditMode = false;
  int encryptionBoxInputValue = 0;

  // FONT AND TEXTURE  LOADING

  Font buttonFont = LoadFontEx("./rayfonts/mplus-1m-light.ttf", 64, 0, 0);
  Font customFnt =
      LoadFontEx("./rayfonts/CaskaydiaCoveNerdFont-Bold.ttf", 64, 0, 0);
  Font subFont = LoadFontEx("./rayfonts/mplus-1m-bold.ttf", 64, 0, 0);
  Font bodyFont = LoadFontEx("./rayfonts/mplus-1m-regular.ttf", 64, 0, 0);
  SetTargetFPS(60);
  // Main loop
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (IsWindowResized() && !IsWindowFullscreen()) {
      screenHeight = GetScreenHeight();
      screenWidth = GetScreenWidth();
    }
    // DrawRectangleGradientV(0, 0, screenWidth, screenHeight,  WHITE, BLUE);
    Color color1 = (Color){1, 3, 50, 255};   // Cetacean Blue
    Color color2 = (Color){0, 109, 91, 255}; // Teal green

    // Color color1 = GetColor(0xc2004592);
    // Color color2 = GetColor(0xf1005f79);
    DrawRectangleGradientV(0, 0, screenWidth, screenHeight, color2, color1);
    // This is how to use hex colors
    // Color c = {0xff, 0xff, 0xff, 0xff};
    // Color c = GetColor(0xff00ffff);

    // DrawCircleGradient(int centerX, int centerY, float radius, Color color1,
    //                   Color color2); // Draw a gradient-filled circle

    // Draw a gradient background
    // draw the Title

    // #B24592
    // #F15F79
    if (!loggedIn || loggedIn == 2) {

      int gap = 60;
      int const heightModifier = 4;
      // Drawing the Image Icon

      int iconY = screenHeight / heightModifier - gap * 2;
      int iconX = screenWidth / 2 - iconTexture.width / 2;
      DrawTexture(iconTexture, iconX, iconY, WHITE);

      // Drawing the title
      int titleY = iconY + iconTexture.height + gap;
      int titleX = screenWidth / 2 - (MeasureText(pageTitle, 64) / 2) + 45;
      SetTextLineSpacing(48);
      GuiSetFont(customFnt);
      // set the style
      GuiSetStyle(DEFAULT, TEXT_SIZE, 64);

      // set the font color to the white
      GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, 0xFFFFFFFF);
      // GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, 0x00000000);
      GuiLabel((Rectangle){titleX, titleY, MeasureText(pageTitle, 64), 24},
               pageTitle);
      // End of title drawing

      int commonYLen = (MeasureText(subTitle, 24) / 2) - 45;

      // Draw subtitle
      SetTextLineSpacing(48);
      GuiSetFont(subFont);
      GuiSetStyle(DEFAULT, TEXT_SIZE, 32);

      int subY = titleY + gap;
      int subX = screenWidth / 2 - (MeasureText(subTitle, 32) / 2) + 45;
      GuiLabel((Rectangle){subX, subY, MeasureText(subTitle, 32), 24},
               subTitle);

      // Body font and style

      SetTextLineSpacing(48);
      GuiSetFont(bodyFont);
      GuiSetStyle(DEFAULT, TEXT_SIZE, 24);

      // Draw the repo name input box
      int repoY = subY + gap * 2 - 20;
      int repoX = screenWidth / 2 - commonYLen;
      if (GuiTextBox((Rectangle){repoX, repoY, 400, 40}, repoNameInputText,
                     1024, repoNameInputEditMode))
        repoNameInputEditMode = !repoNameInputEditMode;
      // END DRAWING repo input box

      // gap = gap + 20;
      // start encryption box drawing
      int encryptY = repoY + gap;
      int encryptX = screenWidth / 2 - commonYLen;
      if (GuiTextBox((Rectangle){encryptX, encryptY, 400, 40},
                     encryptionBoxInputText, 1024, encryptionBoxInputEditMode))
        encryptionBoxInputEditMode = !encryptionBoxInputEditMode;
      // End encryption key box

      SetTextLineSpacing(48);
      GuiSetFont(buttonFont);
      GuiSetStyle(DEFAULT, TEXT_SIZE, 48);
      // set the color to the black

      GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, 0x000000FF);
      int buttonY = encryptY + gap;
      int buttonX = screenWidth / 2 - MeasureText(loginButtonText, 48) * 2 + 15;
      if (GuiButton((Rectangle){buttonX, buttonY,
                                MeasureText(loginButtonText, 48) * 4, 48},
                    loginButtonText))
        LoginButton(&loggedIn, repoNameInputText, encryptionBoxInputText);
    } else {
      int const gap = 60;
      int const heightModifier = 6;
      char *homePageTitle = "SikNotes: HomePage";

      int relativeFontSize = GetScreenWidth() / 40;
      int titleY = GetScreenHeight() / heightModifier - gap;
      int titleX = GetScreenWidth() / 2 -
                   (MeasureText(homePageTitle, relativeFontSize) / 2);
      SetTextLineSpacing(48);
      GuiSetFont(customFnt);
      // printf("Relative font size if %d", relativeFontSize);
      //  set the style
      GuiSetStyle(DEFAULT, TEXT_SIZE, relativeFontSize);
      GuiLabel((Rectangle){titleX, titleY,
                           MeasureText(homePageTitle, relativeFontSize), 24},
               homePageTitle);
      ClearBackground(RAYWHITE);
    }

    EndDrawing();
  }
  CloseWindow();
  return 0;
}

static void LoginButton(int *loggedIn, const char *repoUrl,
                        const char *encryptionKey) {
  const char *homeDir = getHomeDir();
  printf("The home directory of the user is %s\n", homeDir);
  printf("Button CLICKED\n");
  printf("repo url is :: -> %s | encryption code is %s\n", repoUrl,
         encryptionKey);
  // clear screen
  // clear the old drawings from the screen with ray lib clear background
  if (strcmp(encryptionKey, "1234") != 0) {
    printf("Matched the password!");
    *loggedIn = 1;
  } else {
    *loggedIn = 2;
  }
  // ClearWindowState(0);
}
