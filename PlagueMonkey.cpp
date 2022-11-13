#include "raylib.h"

struct Anim
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

int main()
{
    const int windowWidth{1200};         // defines the window width
    const int windowHeight{750};         // defines the window heights
    char WindowName[] = "Plague Doctor"; // names the pop up winddow "Plague Doctor"
    InitWindow(windowWidth, windowHeight, WindowName);

    const int jumpHeight{200}; // sets the maximum jump height
    const int MOVING_UP{-1};   // control the jump speed
    const int DIRECTION{-1};
    const int JUMP_INCREMENT{10}; // control the jump increment

    bool isJumping{false};
    int jumpDirection{MOVING_UP}, plagueDoctorFacing{1};

    int ratVel{-10}; // speed of rat across the screen

    // onscreen text
    const char msg[] = "Merrie Olde England 1349...";                                                                                                    // unchanging message
    Font font = LoadFont("resources/fonts/alagard.png");                                                                                                 // loading the alagard.png font
    Vector2 fontPosition = {windowWidth / 3.0f - MeasureTextEx(font, msg, (float)font.baseSize * 2.0f, 10).x / 10, windowHeight / 4.0f - font.baseSize}; // positioning the font based of halves and quarters of the width of the screen

    // plagueDoctor sprite
    int frame{0};
    Texture2D plagueDoctor = LoadTexture("resources/textures/plagueDoctor.png");             // loading in the sprite
    Rectangle plagueDoctorRec = {float((plagueDoctor.width / 6) * frame), 0, 128, 128};      // there are 6 conditions of the sprite to be used, it is framed out in a 128x128 box
    const float TOP_OF_JUMP{windowHeight - plagueDoctorRec.height - jumpHeight};             // extent of jump
    const float BOTTOM_OF_JUMP{windowHeight - 20 - plagueDoctorRec.height};                  //  -20 to raise PlagueDoctor off the ground
    Vector2 plagueDoctorPos = {windowWidth / 6 - plagueDoctorRec.width / 6, BOTTOM_OF_JUMP}; // initial postioning of the sprite

    int currentFrame = 0;
    int runningTime = 0;
    int runningSpeed = 8;

    // Rat collision object
    Texture2D rat = LoadTexture("resources/textures/rat.png");
    Rectangle ratRec = {float(rat.width), 0, 105, 50};
    Vector2 ratPos = {ratPos.x = windowWidth - ratRec.width, ratPos.y = windowHeight - 20 - ratRec.height};

    Anim plagueDoctorAnim;
    // plagueDoctorAnim.rec.width = plagueDoctor.width/6;
    // plagueDoctorAnim.rec.height = plagueDoctor.height;
    // plagueDoctorAnim.rec.x = 0;
    // plagueDoctorAnim.rec.y = 0;
    plagueDoctorAnim.rec = plagueDoctorRec;

    // plagueDoctorAnim.pos.x = windowWidth / 2 - plagueDoctorAnim.rec.width / 2;
    // plagueDoctorAnim.pos.y = windowHeight - plagueDoctorAnim.rec.height;
    plagueDoctorAnim.pos = plagueDoctorPos;
    plagueDoctorAnim.frame = 0;
    plagueDoctorAnim.updateTime = 1.0 / 12.0;
    plagueDoctorAnim.runningTime = 0.0;

    // Rectangle ratRec; // already declared on Line 48, you can still change the values like yor are doing on 66 to 69
    ratRec.width = rat.width;
    ratRec.height = rat.height;
    ratRec.x = 0;
    ratRec.y = 0;
    // Vector2 ratPos; // already declared on line 49, you can still change the values like you are on line 71, and 72
    ratPos.x = windowWidth - ratRec.width;
    ratPos.y = windowHeight - ratRec.height;

    // background
    Texture2D background = LoadTexture("resources/textures/england_background.png");
    Texture2D midground = LoadTexture("resources/textures/england_midground.png");
    Texture2D foreground = LoadTexture("resources/textures/england_foreground.png");

    float scrollingBack = 0.0f;
    float scrollingMid = 0.0f;
    float scrollingFore = 0.0f;

    bool collision{};

    SetTargetFPS(60); // refresh rate

    while (!WindowShouldClose()) // as long as the window is not closed do the actions contained within curly bracers

    {

        // Rectangle ratRec{
        //     ratPos.x,
        //     ratPos.y,
        //     ratRec.height,
        //     ratRec.width,
        // };

        // Rectangle plagueDoctorRec{
        //     plagueDoctorAnim.pos.x,
        //     plagueDoctorAnim.pos.y,
        //     plagueDoctorAnim.rec.height,
        //     plagueDoctorAnim.rec.width,
        // };
        if (CheckCollisionRecs(plagueDoctorRec, ratRec))
        {
            collision = true;
        }

        // redundant took out gravity const float deltaTime{GetFrameTime()}

        runningTime++;

        if (runningTime >= (60 / runningSpeed))
        {
            runningTime = 0.0;
            currentFrame++;

            if (currentFrame > 5)
                currentFrame = 0;

            plagueDoctorRec.x = (float)currentFrame * (float)plagueDoctor.width / 6;
        }

        // scrolling speeds
        scrollingBack -= 0.1f;
        scrollingMid -= 0.5f;
        scrollingFore -= 1.0f;

        // Texture is scaled twice its size, so it sould be considered on scrolling
        if (scrollingBack <= -background.width * 2)
            scrollingBack = 0;
        if (scrollingMid <= -midground.width * 2)
            scrollingMid = 0;
        if (scrollingFore <= -foreground.width * 2)
            scrollingFore = 0;

        BeginDrawing();
        ClearBackground(WHITE);

        DrawTextureEx(background, (Vector2){scrollingBack, 20}, 0.0f, 2.0f, WHITE);
        DrawTextureEx(background, (Vector2){background.width * 2 + scrollingBack, 20}, 0.0f, 2.0f, WHITE);

        // Draw midground image twice
        DrawTextureEx(midground, (Vector2){scrollingMid, 30}, 0.0f, 2.0f, WHITE);
        DrawTextureEx(midground, (Vector2){midground.width * 2 + scrollingMid, 20}, 0.0f, 2.0f, WHITE);

        // Draw foreground image twice
        DrawTextureEx(foreground, (Vector2){scrollingFore, 70}, 0.0f, 2.0f, WHITE); // scrolling speed
        DrawTextureEx(foreground, (Vector2){foreground.width * 2 + scrollingFore, 70}, 0.0f, 2.0f, WHITE);

        DrawTextEx(font, msg, fontPosition, (float)font.baseSize * 2.0f, 10, RED);

        DrawTextureRec(plagueDoctor, plagueDoctorRec, plagueDoctorPos, WHITE);

        DrawTextureRec(rat, ratRec, ratPos, WHITE);

        // obselete on hold for testing ---> plagueDoctorRec_posX += direction; if (plagueDoctorRec_posX<0||plagueDoctorRec_posX>1200){direction *=-1;}
        // if(plagueDoctor.X<0){PlagueDoctor.X=0}

        if (IsKeyPressed(KEY_UP) && !isJumping)
        {
            isJumping = true;
        }

        if (IsKeyDown(KEY_LEFT))
        {
            plagueDoctorFacing = -1; // facing left
            plagueDoctorPos.x -= 10; // use a compond assignment for pos.x
        }
        else if (IsKeyDown(KEY_RIGHT))
        {
            plagueDoctorFacing = 1;  // facing right
            plagueDoctorPos.x += 10; // use a compond assignment for pos.x moving it by 10
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
                jumpDirection *= DIRECTION;
            }
            else if (plagueDoctorPos.y >= BOTTOM_OF_JUMP)
            {
                plagueDoctorPos.y = BOTTOM_OF_JUMP;
                isJumping = !isJumping;
                jumpDirection = MOVING_UP;
            }
        }

        ratPos.x += ratVel; // rat Position += Rat velocity;

        // rat does a repeat run once it goes off the screen
        if (ratPos.x < -rat.width)
        {
            ratPos.x = windowWidth + 100;
        }

        // ClearBackground(WHITE); // this wipes the screen, you need to do it before drawing to the screen, and you already are on line 138

        if (collision)
        {
        }
        else
        {
            DrawTextureRec(plagueDoctor, plagueDoctorAnim.rec, plagueDoctorAnim.pos, WHITE);
            DrawTextureRec(rat, ratRec, ratPos, WHITE);
        }

        EndDrawing();
    }

    UnloadFont(font);
    UnloadTexture(plagueDoctor);
    UnloadTexture(rat);
    UnloadTexture(background);
    UnloadTexture(midground);
    UnloadTexture(foreground);

    CloseWindow();
}
