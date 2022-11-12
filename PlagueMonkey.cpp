#include "raylib.h"
//Plague Doctor FTW

int main()

{
   const int screenWidth {1200};
   const int screenHeight {750};
   char WindowName[] = "Plague Doctor";
   
InitWindow(screenWidth, screenHeight, WindowName);
  const char msg[] = "Merrie Olde England 1349...";
   Font font = LoadFont("resources/fonts/alagard.png");   
   Vector2 fontPosition = { screenWidth/4.0f - MeasureTextEx
   (font, msg, (float)font.baseSize*2.0f, 10).x/10,screenHeight/4.0f - font.baseSize};

   Texture2D background = LoadTexture("resources/textures/england_background.png");
    Texture2D midground = LoadTexture("resources/textures/england_midground.png");
    Texture2D foreground = LoadTexture("resources/textures/england_foreground.png");

    float scrollingBack = 0.0f;
    float scrollingMid = 0.0f;
    float scrollingFore = 0.0f;

SetTargetFPS(60);

while(!WindowShouldClose())


{

 scrollingBack -= 0.1f;
        scrollingMid -= 0.5f;
        scrollingFore -= 1.0f;

        // NOTE: Texture is scaled twice its size, so it sould be considered on scrolling
        if (scrollingBack <= -background.width*2) scrollingBack = 0;
        if (scrollingMid <= -midground.width*2) scrollingMid = 0;
        if (scrollingFore <= -foreground.width*2) scrollingFore = 0;


BeginDrawing();
   ClearBackground(WHITE);
   
DrawTextureEx(background, (Vector2){ scrollingBack, 20 }, 0.0f, 2.0f, WHITE);
            DrawTextureEx(background, (Vector2){ background.width*2 + scrollingBack, 20 }, 0.0f, 2.0f, WHITE);

            // Draw midground image twice
            DrawTextureEx(midground, (Vector2){ scrollingMid, 30 }, 0.0f, 2.0f, WHITE);
            DrawTextureEx(midground, (Vector2){ midground.width*2 + scrollingMid, 20 }, 0.0f, 2.0f, WHITE);

            // Draw foreground image twice
            DrawTextureEx(foreground, (Vector2){ scrollingFore, 70 }, 0.0f, 2.0f, WHITE);
            DrawTextureEx(foreground, (Vector2){ foreground.width*2 + scrollingFore, 70 }, 0.0f, 2.0f, WHITE);

DrawTextEx(font, msg, fontPosition, (float)font.baseSize*2.0f, 10, RED);


EndDrawing();
} 
UnloadFont(font);
CloseWindow();
return 0;
}



