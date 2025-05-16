#include <stdio.h>
#include <raylib.h>

int main(void) {
    InitWindow(1050, 540, "Pokemon"); //inicializa a janela do jogo
    InitAudioDevice();
    SetTargetFPS(1000); //sla kkk

    int framesCounter = 0;
    int fadeAlpha = 0;
    bool fadeOut = false;
    bool menuDescarregado = false;

    Texture background = LoadTexture("sprites/background.jpg");
    Texture titulo = LoadTexture("sprites/title.png");
    Font subtitle = LoadFont("fonts/Ketchum.otf");
    Font enter = LoadFont("fonts/BarberChop.otf");
    Texture Charizard = LoadTexture("sprites/charizard.gif");
    Music menu = LoadMusicStream("audios/menu.mp3");
    Sound start = LoadSound("audios/enter.mp3");

    PlayMusicStream(menu);

    while (!WindowShouldClose()) {
        UpdateMusicStream(menu);

        if (IsKeyPressed(KEY_ENTER)) {
            fadeOut = true;
        }

        if (fadeOut && !menuDescarregado) {
            UnloadMusicStream(menu);
            PlaySound(start);
            menuDescarregado = true;
        }

        if (fadeOut && fadeAlpha < 255) {
            fadeAlpha += 1;
        }

        framesCounter++;

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTexture(background, 0, 0, WHITE); //background do menu

        DrawRectangle(0, 0, 1050, 150, BLACK); //barras pretas
        DrawRectangle(0, 0, 1050, 25, ORANGE);
        DrawRectangle(0, 390, 1050, 150, BLACK);
        DrawRectangle(0, 515, 1050, 25, ORANGE);

        DrawTextureEx(titulo, (Vector2){60, 10}, 0, 0.25, BLACK); //titulo "pokemon"
        DrawTextureEx(titulo, (Vector2){50, 0}, 0, 0.25, WHITE);

        DrawTextEx(subtitle, "Projeto APPC", (Vector2){135, 255}, 65, 0.25, BLACK); //subtitulo "Projeto APPC"
        DrawTextEx(subtitle, "Projeto APPC", (Vector2){130, 250}, 65, 0.25, WHITE);

        DrawTextureEx(Charizard, (Vector2){570, 35}, 0, 5.0, WHITE); //charizard do menu

        if ((framesCounter / 500) % 2 == 0) {
            DrawTextEx(enter, "PRESSIONE ENTER", (Vector2){150, 425}, 55, 0.25, WHITE);
        }

        if (fadeOut) {
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), (Color){255, 255, 255, fadeAlpha});
        }

        EndDrawing();
    }

    CloseAudioDevice();
    return 0;
}
