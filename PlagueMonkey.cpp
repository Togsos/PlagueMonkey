#include "raylib.h"
//Plague Doctor FTW

int main()

{
   const int windowWidth {1200};
   const int windowHeight {750};
   char WindowName[] = "Plague Doctor";

   const int jumpHeight{100};
    const int MOVING_UP{-1};
    const int CHANGE_DIRECTION{-1};
    const int JUMP_INCREMENT{10};

    bool isJumping{false};
    int jumpDirection{MOVING_UP}, plagueDoctorFacing{1};

   
InitWindow(windowWidth, windowHeight, WindowName);
  const char msg[] = "Merrie Olde England 1349...";
   Font font = LoadFont("resources/fonts/alagard.png");   
   Vector2 fontPosition = { windowWidth/4.0f - MeasureTextEx
   (font, msg, (float)font.baseSize*2.0f, 10).x/10,windowHeight/4.0f - font.baseSize};


   int frame{0};
    Texture2D plagueDoctor = LoadTexture("resources/textures/plagueDoctor.png");
    Rectangle plagueDoctorRec = {float((plagueDoctor.width / 6) * frame), 0, 128, 128};
    const float TOP_OF_JUMP{windowHeight - plagueDoctorRec.height - jumpHeight};
    const float BOTTOM_OF_JUMP{windowHeight - plagueDoctorRec.height};
    Vector2 plagueDoctorPos = {windowWidth / 2 - plagueDoctorRec.width / 2, BOTTOM_OF_JUMP};

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

        // Texture is scaled twice its size, so it sould be considered on scrolling
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

  DrawTextureRec(plagueDoctor, plagueDoctorRec, plagueDoctorPos, WHITE);

        if (IsKeyPressed(KEY_SPACE) && !isJumping)
        {
            isJumping = true;
        }

        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
        {
            plagueDoctorFacing = -1;
            plagueDoctorPos.x -= 10;
        }
        else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
        {
            plagueDoctorFacing = 1;
            plagueDoctorPos.x += 10;
        }
        plagueDoctorRec.width = 128 * plagueDoctorFacing;

        if (isJumping)
        {
            if (plagueDoctorPos.y >= TOP_OF_JUMP && plagueDoctorPos.y <= BOTTOM_OF_JUMP)
            {
                plagueDoctorPos.y += (JUMP_INCREMENT * jumpDirection);
            }

            if (plagueDoctorPos.y <= (TOP_OF_JUMP))
            {
                jumpDirection *= CHANGE_DIRECTION;
            }
            else if (plagueDoctorPos.y >= BOTTOM_OF_JUMP)
            {
                plagueDoctorPos.y = BOTTOM_OF_JUMP;
                isJumping = !isJumping;
                jumpDirection = MOVING_UP;
            }
        }

   ClearBackground(WHITE);
EndDrawing();
} 
UnloadFont(font);
UnloadTexture(plagueDoctor);
CloseWindow();
return 0;
}



