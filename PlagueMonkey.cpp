#include "raylib.h"
//Plague Doctor FTW



int main()

{
   const int windowWidth {1200}; //defines the window width
   const int windowHeight {750};  //defines the window heights
   char WindowName[] = "Plague Doctor"; //names the pop up winddow "Plague Doctor"

   const int jumpHeight{150};//sets the maximum jump height
    const int MOVING_UP{-1}; //control the jump speed
    const int CHANGE_DIRECTION{-1};
    const int JUMP_INCREMENT{10}; //control the jump increment

    bool isJumping{false}; 
    int jumpDirection{MOVING_UP}, plagueDoctorFacing{1};

   
InitWindow(windowWidth, windowHeight, WindowName);

   //onscreen text
  const char msg[] = "Merrie Olde England 1349..."; // unchanging message  
   Font font = LoadFont("resources/fonts/alagard.png");  // loading the alagard.png font 
   Vector2 fontPosition = { windowWidth/3.0f - MeasureTextEx
   (font, msg, (float)font.baseSize*2.0f, 10).x/10,windowHeight/4.0f - font.baseSize}; //positioning the font based of halves and quarters of the width of the screen

   //sprite
   int frame{0};
    Texture2D plagueDoctor = LoadTexture("resources/textures/plagueDoctor.png"); //loading in the sprite
    Rectangle plagueDoctorRec = {float((plagueDoctor.width /6) * frame), 0, 128, 128}; //there are 6 conditions of the sprite to be used
    const float TOP_OF_JUMP{windowHeight - plagueDoctorRec.height - jumpHeight};
    const float BOTTOM_OF_JUMP{windowHeight - plagueDoctorRec.height};
    Vector2 plagueDoctorPos = {windowWidth / 6 - plagueDoctorRec.width / 6, BOTTOM_OF_JUMP}; //initial postioning of the sprite


    int currentFrame = 0;


    int framesCounter = 0;
    int framesSpeed = 8;    






   //background
   Texture2D background = LoadTexture("resources/textures/england_background.png");
    Texture2D midground = LoadTexture("resources/textures/england_midground.png");
    Texture2D foreground = LoadTexture("resources/textures/england_foreground.png");

    float scrollingBack = 0.0f;
    float scrollingMid = 0.0f;
    float scrollingFore = 0.0f;


SetTargetFPS(60); //refresh rate



while(!WindowShouldClose()) //as long as the window is not closed do the actions contained within curly bracers


{

    framesCounter++;

        if (framesCounter >= (60/framesSpeed))
        {
            framesCounter = 0;
            currentFrame++;

            if (currentFrame > 5) currentFrame = 0;

            plagueDoctorRec.x = (float)currentFrame*(float)plagueDoctor.width/6;
        }





//scrolling speeds
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

DrawTextureRec(plagueDoctor, plagueDoctorRec, plagueDoctorPos, WHITE);  // Draw part of the texture


        // obselete on hold for testing ---> plagueDoctorRec_posX += direction; if (plagueDoctorRec_posX<0||plagueDoctorRec_posX>1200){direction *=-1;}
         // if(plagueDoctor.X<0){PlagueDoctor.X=0}

        if (IsKeyPressed(KEY_UP) && !isJumping)
        {
            isJumping = true;
        }

        if (IsKeyDown(KEY_LEFT))
        {
            plagueDoctorFacing = -1; // facing left
            plagueDoctorPos.x -= 10; //use a compond assignment for pos.x
        }
        else if (IsKeyDown(KEY_RIGHT))
        {
            plagueDoctorFacing = 1; //facing right
            plagueDoctorPos.x += 10;//use a compond assignment for pos.x moving it by 10
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
UnloadTexture(background);
UnloadTexture(midground);
UnloadTexture(foreground);

CloseWindow();

}



