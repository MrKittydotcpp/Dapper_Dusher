#include "raylib.h"
// some changes

int main()
{
    // window dimensions
    int window_Weight{1280};
    int window_Height{820};

    // initialize the window
    InitWindow(window_Weight,window_Height, "Depper Dasher");

    // acceleration due to gravity (pixels/s)/s
    const int gravity{1'000};
    
    // nebula 

    Texture2D nebula = LoadTexture ("textures/12_nebula_spritesheet.png");
    Rectangle nebulaRec;
    nebulaRec.width = nebula.width/9;
    nebulaRec.height = nebula.height/9;
    

    // Scarfy
    Texture2D scarfy = LoadTexture ("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0; 
    Vector2 scarfyPos;
    scarfyPos.x = window_Weight/2 - scarfyRec.width/2;
    scarfyPos.y = window_Height - scarfyRec.height;

    // is the rectangle in the air? (default value false)
    bool isInAir{};
    // jump velocity(pixels/second)
    const int jumpVel{-600};
    
    int velocity{0};

    // animation frame
    int frame{};
    // amount of the time before we update the animations
    const float updateTime{1.0/12.0};
    float runningTime{};

    SetTargetFPS(120);

    while (!WindowShouldClose())
    {   
        // start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        const float dT{ GetFrameTime()};

        // perform ground check
        if (scarfyPos.y >= window_Height - scarfyRec.height )
        {
            // rectangle is on the ground
            velocity = 0;
            isInAir = false;
        }
        else
        {
            // rectangle is in the air
            // apply gravity
            velocity += gravity * dT;
            isInAir = true;

        }
        

        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVel;
        }

         
        // update position
        scarfyPos.y += velocity * dT;

        // update running time
        runningTime += dT;
        if (runningTime >= updateTime)
        {
            runningTime = 0.0;
             // update animation frame
            scarfyRec.x = frame * scarfyRec.width;
            frame++;
            if (frame > 5)
            {
                frame = 0;
            }
            
        }
        
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);
        
        // stop drawing
        EndDrawing();
    }    
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}