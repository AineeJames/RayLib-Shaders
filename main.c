#include <stdio.h>
#include "raylib.h"
#include "rlgl.h"

#define PRINT_VEC2(var) printf("%s = {%f, %f}\n", #var, var.x, var.y);

int main(void) {

  const int window_width = 600;
  const int window_height = 600;
  InitWindow(window_width, window_height, "Shaders");
  // SetTargetFPS(60);

  RenderTexture2D target = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());

  const char *fragShaderFileName = "./shader.fs";
  long fragShaderFileModTime = GetFileModTime(fragShaderFileName);
  Shader shader = LoadShader(NULL, fragShaderFileName);
  bool shaderAutoReloading = true;


  int resolutionLoc = GetShaderLocation(shader, "resolution");
  int mouseposLoc = GetShaderLocation(shader, "mousepos");
  int timeLoc = GetShaderLocation(shader, "time");
  Vector2 resolution = {window_width, window_height};
  PRINT_VEC2(resolution);
  SetShaderValue(shader, resolutionLoc, &resolution, SHADER_UNIFORM_VEC2);

  while (!WindowShouldClose()) {

    Vector2 mousepos = GetMousePosition();
    SetShaderValue(shader, mouseposLoc, &mousepos, SHADER_UNIFORM_VEC2);
    float time = (float)GetTime();
    SetShaderValue(shader, timeLoc, &time, SHADER_UNIFORM_FLOAT);

    if (shaderAutoReloading){
	    long currentFragShaderModTime = GetFileModTime(fragShaderFileName);
	    if(currentFragShaderModTime != fragShaderFileModTime)
            {
		Shader updatedShader = LoadShader(NULL,fragShaderFileName);
		if(updatedShader.id != rlGetShaderIdDefault()){
			UnloadShader(shader);
			shader = updatedShader;
		
			resolutionLoc = GetShaderLocation(shader, "resolution");
			mouseposLoc = GetShaderLocation(shader, "mousepos");
			timeLoc = GetShaderLocation(shader, "time");
			SetShaderValue(shader,resolutionLoc, &resolution, SHADER_UNIFORM_VEC2);
		}
		fragShaderFileModTime = currentFragShaderModTime;
            }
    }

    BeginTextureMode(target);       // Enable drawing to texture
      ClearBackground(BLACK);     // Clear the render texture
      DrawRectangle(0, 0, window_width, window_height, BLACK);
    EndTextureMode();

    BeginDrawing();
    BeginShaderMode(shader);
      DrawTextureEx(target.texture, (Vector2){0, 0}, 0, 1, WHITE);
    EndShaderMode();
    DrawFPS(0, 0);
    EndDrawing();

  }

  UnloadShader(shader);
  CloseWindow();
}
