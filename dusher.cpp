#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float udpateTime;
    float runningTime;
};

int main()
{
    int windowDimensions[2]{1280,820};

    // initialize the window
    InitWindow(windowDimensions[0],windowDimensions[1], "Depper Dasher");

    // acceleration due to gravity (pixels/s)/s
    const int gravity{1'000};
    
    // nebula 
    Texture2D nebula = LoadTexture ("textures/12_nebula_spritesheet.png");

    // AnimData for nebula
    AnimData nebulaData{
        {0.0, 0.0, nebula.width/8, nebula.height/8}, // Rectabgel rec
        {windowDimensions[0], windowDimensions[1] - nebulaData.rec.height}, // Vector2 pos
        0, // int frame 
        1.0/24.0, // float updateTIme
        0.0 // float runningTime
    }; 

     AnimData nebula2Data{
        {0.0, 0.0, nebula.width/8, nebula.height/8}, // Rectabgel rec
        {windowDimensions[0] + 600, windowDimensions[1] - nebulaData.rec.height}, // Vector2 pos
        0, // int frame 
        1.0/22.0, // float updateTIme
        0.0// float runningTime
    }; 

    AnimData nebulae[3]{};

    for (int i = 0; i < 3; i++)
    {
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width/8;
        nebulae[i].rec.height = nebula.height/8;
        nebulae[i].pos.y =windowDimensions[1] - nebula.height;
        nebulae[i].frame = 0;
        nebulae[i].udpateTime = 0.0;
        nebulae[i].runningTime = 0.0;
    }

    nebulae[0].pos.x = windowDimensions[0];
    nebulae[1].pos.x = windowDimensions [0] + 300;
    nebulae[2].pos.x = windowDimensions [0] + 600;
    

    int nebulaVel{-300};

    // Scarfy
    Texture2D scarfy = LoadTexture ("textures/scarfy.png");
    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width/6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = windowDimensions[0]/2 - scarfyData.rec.width/2;
    scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.udpateTime = 1.0/12.0;
    scarfyData.runningTime = 0.0;
    
    // is the rectangle in the air? (default value false)
    bool isInAir{};
    // jump velocity(pixels/second)
    const int jumpVel{-600};
    
    int velocity{0};

    SetTargetFPS(120);

    while (!WindowShouldClose())
    {   
        // start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        const float dT{ GetFrameTime()};

        // perform ground check
        if (scarfyData.pos.y >= windowDimensions[1] - scarfyData.rec.height)
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
        
        // jump check
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVel;
        }

        // update nebula position
        nebulae[0].pos.x += nebulaVel * dT;

        // update the second nebula's position
        nebulae[1].pos.x += nebulaVel * dT;
         
        // update position
        scarfyData.pos.y += velocity * dT;

        // update scurfy's animations frame
        if (!isInAir)
        {
            // update running time
            scarfyData.runningTime += dT;
            if (scarfyData.runningTime >= scarfyData.udpateTime)
            {
                scarfyData.runningTime = 0.0;
                // update animation frame
                scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
                scarfyData.frame++;
                if (scarfyData.frame > 5)
                {
                    scarfyData.frame = 0;
                }   
            }
        }
        
        // nebula animations frame 
        nebulae[0].runningTime += dT;
        if (nebulae[0].runningTime >= nebulae[0].udpateTime)
        {
            nebulae[0].runningTime = 0.0;
            nebulae[0].rec.x = nebulae[0].frame * nebulae[0].rec.width;
            nebulae[0].frame++;
            if (nebulae[0].frame > 7)
            {
                nebulae[0].frame = 0;
            }
        }

        nebulae[1].runningTime += dT;
        if (nebulae[1].runningTime >= nebulae[1].udpateTime)
        {
            nebulae[1].runningTime = 0.0;
            nebulae[1].rec.x = nebulae[1].frame * nebulae[1].rec.width;
            nebulae[1].frame++;
            if (nebulae[1].frame > 7)
            {
                nebulae[1].frame = 0;
            }
        }
        
        // draw nebula 
        DrawTextureRec(nebula,nebulae[0].rec,nebulae[0].pos, WHITE);
        // draw the second nebula
        DrawTextureRec(nebula,nebulae[1].rec,nebulae[1].pos, WHITE);
        // draw scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
        
        // stop drawing
        EndDrawing();
    }    
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}