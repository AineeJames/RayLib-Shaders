#include "raylib.h"
#include <stdio.h>

#define PRINT_VEC2(var) printf("%s = {%f, %f}\n", #var, var.x, var.y);

int main(void) {

  const int window_width = 600;
  const int window_height = 600;
  InitWindow(window_width, window_height, "Shaders");
  // SetTargetFPS(60);

  RenderTexture2D target =
      LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
  Mesh cube = GenMeshCube(1, 1, 1);
  Material defaultmat = LoadMaterialDefault();
  Model cube_model = LoadModelFromMesh(cube);
  Vector3 cube_position = {0.0f, 0.0f, 0.0f}; // Set model position

  Camera camera = {0};
  camera.position = (Vector3){2.0f, 3.0f, 2.0f}; // Camera position
  camera.target = (Vector3){0.0f, 1.0f, 0.0f};   // Camera looking at point
  camera.up =
      (Vector3){0.0f, 1.0f, 0.0f}; // Camera up vector (rotation towards target)
  camera.fovy = 45.0f;             // Camera field-of-view Y
  camera.projection = CAMERA_PERSPECTIVE; // Camera projection type

  const char *fragShaderFileName = "./shader.fs";
  long fragShaderFileModTime = GetFileModTime(fragShaderFileName);
  Shader shader = LoadShader(NULL, fragShaderFileName);
  bool shaderAutoReloading = true;

  cube_model.materials[0].shader = shader;

  int resolutionLoc = GetShaderLocation(shader, "resolution");
  int mouseposLoc = GetShaderLocation(shader, "mousepos");
  int timeLoc = GetShaderLocation(shader, "time");
  Vector2 resolution = {window_width, window_height};
  PRINT_VEC2(resolution);
  SetShaderValue(shader, resolutionLoc, &resolution, SHADER_UNIFORM_VEC2);

  while (!WindowShouldClose()) {
    UpdateCamera(&camera, CAMERA_ORBITAL);
    Vector2 mousepos = GetMousePosition();
    SetShaderValue(shader, mouseposLoc, &mousepos, SHADER_UNIFORM_VEC2);
    float time = (float)GetTime();
    SetShaderValue(shader, timeLoc, &time, SHADER_UNIFORM_FLOAT);

    if (shaderAutoReloading) {
      long currentFragShaderModTime = GetFileModTime(fragShaderFileName);
      if (currentFragShaderModTime != fragShaderFileModTime) {
        Shader updatedShader = LoadShader(NULL, fragShaderFileName);
        if (updatedShader.id != rlGetShaderIdDefault()) {
          UnloadShader(shader);
          shader = updatedShader;

          resolutionLoc = GetShaderLocation(shader, "resolution");
          mouseposLoc = GetShaderLocation(shader, "mousepos");
          timeLoc = GetShaderLocation(shader, "time");
          SetShaderValue(shader, resolutionLoc, &resolution,
                         SHADER_UNIFORM_VEC2);
          cube_model.materials[0].shader = shader;
        }
        fragShaderFileModTime = currentFragShaderModTime;
      }
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawFPS(0, 0);
    BeginMode3D(camera);
    DrawModel(cube_model, cube_position, 1.0f, WHITE);
    DrawGrid(10, 1.0f);
    EndMode3D();
    EndDrawing();
  }

  UnloadShader(shader);
  CloseWindow();
}
