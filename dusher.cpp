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
    // window dimensions
    int window_Weight{1280};
    int window_Height{820};

    // initialize the window
    InitWindow(window_Weight,window_Height, "Depper Dasher");

    // acceleration due to gravity (pixels/s)/s
    const int gravity{1'000};
    
    // nebula 
    Texture2D nebula = LoadTexture ("textures/12_nebula_spritesheet.png");

    // AnimData for nebula
    AnimData nebulaData{
        {0.0, 0.0, nebula.width/8, nebula.height/8}, // Rectabgel rec
        {window_Weight, window_Height - nebulaData.rec.height/8}, // Vector2 pos
        0, // int frame 
        1.0/24.0, // float updateTIme
        0 // float runningTime
    }; 

     AnimData nebula2Data{
        {0.0, 0.0, nebula.width/8, nebula.height/8}, // Rectabgel rec
        {window_Weight, window_Height + 600 - nebulaData.rec.height/8}, // Vector2 pos
        0, // int frame 
        1.0/22.0, // float updateTIme
        0 // float runningTime
    }; 


    Rectangle nebulaRec{0.0,0.0,nebula.width/8,nebula.height/8};
    Vector2 nebulaPos{window_Weight, window_Height - nebulaRec.height};

    Rectangle nebula2Rec{0.0,0.0,nebula.width/8,nebula.height/8};
    Vector2 nebula2Pos{window_Weight + 600, window_Height - nebulaRec.height};
 
     // animation nebula
    int nebula_frame{};
    // amount of the time before we update the animations
    const float nebula_updateTime{1.0/24.0};
    float nebula_runningTime{};

    int nebula2_frame{};
    const float nebula2_updateTime{1.0/28.0};
    float nebula2_runningTime{};

    int nebulaVel{-300};

    // Scarfy
    Texture2D scarfy = LoadTexture ("textures/scarfy.png");
    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width/6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = window_Weight/2 - scarfyData.rec.width/2;
    scarfyData.pos.y = window_Height = scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.udpateTime = 1.0/12.0;
    scarfyData.runningTime = 0.0;

    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0; 
    Vector2 scarfyPos;
    scarfyPos.x = window_Weight/2 - scarfyRec.width/2;
    scarfyPos.y = window_Height - scarfyRec.height;

     // animation frame scarfy
    int frame{};
    // amount of the time before we update the animations
    const float updateTime{1.0/12.0};
    float runningTime{};

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
        
        // jump check
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVel;
        }

        // update nebula position
        nebulaPos.x += nebulaVel * dT;

        // update the second nebula's position
        nebula2Pos.x += nebulaVel * dT;
         
        // update position
        scarfyPos.y += velocity * dT;

        // update scurfy's animations frame
        if (!isInAir)
        {
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
        }
        
        // nebula animations frame 
        nebula_runningTime += dT;
        if (nebula_runningTime >= nebula_updateTime)
        {
            nebula_runningTime = 0.0;
            nebulaRec.x = nebula_frame * nebulaRec.width;
            nebula_frame++;
            if (frame > 7)
            {
                frame = 0;
            }
            
        }
    
        nebula2_runningTime += dT;
        if (nebula2_runningTime >= nebula2_updateTime)
        {
            nebula2_runningTime = 0.0;
            nebula2Rec.x = nebula2_frame * nebula2Rec.width;
            nebula2_frame++;
            if (frame > 7)
            {
                frame = 0;
            }
            
        }
        
        // draw nebula 
        DrawTextureRec(nebula,nebulaRec,nebulaPos, WHITE);
        // draw the second nebula
        DrawTextureRec(nebula,nebula2Rec,nebula2Pos,WHITE);
        // draw scarfy
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);
        
        // stop drawing
        EndDrawing();
    }    
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}