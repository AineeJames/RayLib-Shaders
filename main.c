#include <stdio.h>
#include "raylib.h"

#define PRINT_VEC2(var) printf("%s = {%f, %f}\n", #var, var.x, var.y);

int main(void) {

  const int window_width = 800;
  const int window_height = 600;
  InitWindow(window_width, window_height, "Shaders");
  // SetTargetFPS(60);

  RenderTexture2D target = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());

  Shader shader = LoadShader(NULL, "./shader.fs");
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
