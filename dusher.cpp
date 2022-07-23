#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float udpateTime;
    float runningTime;
};

bool isOnGround(AnimData data, int WindowHeight)
{
    return data.pos.y >= WindowHeight - data.rec.height;
}

AnimData updateAnimData(AnimData data, float deltaTime, int maxFrame)
{
    //update running time
    data.runningTime += deltaTime;
    if (data.runningTime >= data.udpateTime)
    {
        data.runningTime = 0.0;
        // update animation frame 
        data.rec.x = data.frame * data.rec.width;
        data.frame++;
        if (data.frame > maxFrame)
        {
            data.frame = 0;
        }   
    }
    return data;
}

int main()
{
    int windowDimensions[2]{1280,960};

    // initialize the window
    InitWindow(windowDimensions[0],windowDimensions[1], "Depper Dasher");

    // acceleration due to gravity (pixels/s)/s
    const int gravity{1'000};
    
    // nebula 
    Texture2D nebula = LoadTexture ("textures/12_nebula_spritesheet.png");

    // AnimData for nebula
    const int sizeOfNebulae{10};

    AnimData nebulae[sizeOfNebulae]{};
    for (int i = 0; i < sizeOfNebulae; i++)
    {
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width/8;
        nebulae[i].rec.height = nebula.height/8;
        nebulae[i].pos.y = windowDimensions[1] - nebula.height/8;
        nebulae[i].frame = 0;
        nebulae[i].udpateTime = 1.0/24.0;
        nebulae[i].runningTime = 0.0;

        nebulae[i].pos.x = windowDimensions [0] + i * 400;
    }
 
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

    Texture2D background = LoadTexture ("textures/far-buildings.png");
    float bgX{};

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {

        const float dT{GetFrameTime()};

        // start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        // draw the background
        // void DrawTextureEx(Texture2D texture, Vector2 position, float rotation, float scale, Color tint)
        Vector2 backPos{bgX, 0.0};
        DrawTextureEx(background, backPos, 0.0, 5.0, WHITE);

        bgX -= 20 * dT;
        
        // perform ground check
        if (isOnGround(scarfyData, windowDimensions[1]))
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
        for (int i = 0; i < sizeOfNebulae; i++)
        {
            nebulae[i].pos.x += nebulaVel * dT; 
        }
          
        // update position
        scarfyData.pos.y += velocity * dT;

        // update scurfy's animations frame
        if (!isInAir)
        {
           scarfyData = updateAnimData(scarfyData, dT, 5);
        }
        
        for (int i = 0; i < sizeOfNebulae; i++)
        {
            // nebula animations frame 
          nebulae[i] = updateAnimData(nebulae[i], dT, 7);   
        }
        
         // draw nebula 
        for (int i = 0; i < sizeOfNebulae; i++)
        {
            DrawTextureRec(nebula,nebulae[i].rec,nebulae[i].pos,WHITE);
        }
        // draw scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
        
        // stop drawing
        EndDrawing();
    }    
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}