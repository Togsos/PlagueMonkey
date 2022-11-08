#include "raylib.h"


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

SetTargetFPS(60);

while(!WindowShouldClose())

{
BeginDrawing();
   ClearBackground(WHITE);
   DrawTextEx(font, msg, fontPosition, (float)font.baseSize*2.0f, 10, RED);
EndDrawing();
} 
UnloadFont(font);
CloseWindow();
return 0;
}



