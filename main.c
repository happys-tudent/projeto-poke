#include <stdio.h>
#include <raylib.h>
#include <math.h>  // Necessário para usar sinf

typedef enum GameScreen {TELA_INICIAL, MENU} GameScreen;

int fadeAlphaMenu = 255;
bool fadeInMenu = true;

Font subtitle;
Font enter;
Font text;
Texture arrow;
Texture red;
Music person;

bool mostrarTexto = true;
float redJumpTimer = 0.0f;  // Timer para o pulo do Red

void DesenhaMenu(int fadeAlpha, int framesCounter);

int main(void) {
    InitWindow(1050, 540, "Pokemon");
    InitAudioDevice();
    SetTargetFPS(60);

    GameScreen telaAtual = TELA_INICIAL;

    int framesCounter = 0;
    int fadeAlpha = 0;
    bool fadeOut = false;
    bool recursosDescarregados = false;
    bool musicaMenuTocando = false;

    Texture background = LoadTexture("sprites/background.jpg");
    Texture titulo = LoadTexture("sprites/title.png");
    subtitle = LoadFont("fonts/Ketchum.otf");
    enter = LoadFont("fonts/BarberChop.otf");
    text = LoadFont("fonts/Pokemon X and Y.ttf");
    Texture Charizard = LoadTexture("sprites/charizard.gif");
    Music menuMusic = LoadMusicStream("audios/menu.mp3");
    Sound start = LoadSound("audios/enter.mp3");
    arrow = LoadTexture("sprites/Arrow.png");
    person = LoadMusicStream("audios/select.mp3");
    red = LoadTexture("sprites/red.png");

    PlayMusicStream(menuMusic);

    while (!WindowShouldClose()) {
        redJumpTimer += GetFrameTime();  // Atualiza o tempo do pulo

        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch (telaAtual) {
            case TELA_INICIAL:
                UpdateMusicStream(menuMusic);

                if (IsKeyPressed(KEY_ENTER)) fadeOut = true;

                if (fadeOut && !recursosDescarregados) {
                    StopMusicStream(menuMusic);
                    PlaySound(start);
                    recursosDescarregados = true;
                }

                if (fadeOut && fadeAlpha < 255) {
                    fadeAlpha += 3;
                    if (fadeAlpha >= 255) {
                        telaAtual = MENU;
                        if (!musicaMenuTocando) {
                            PlayMusicStream(person);
                            musicaMenuTocando = true;
                        }
                    }
                }

                DrawTexture(background, 0, 0, WHITE);
                DrawRectangle(0, 0, 1050, 150, BLACK);
                DrawRectangle(0, 0, 1050, 25, ORANGE);
                DrawRectangle(0, 390, 1050, 150, BLACK);
                DrawRectangle(0, 515, 1050, 25, ORANGE);
                DrawTextureEx(titulo, (Vector2){60, 10}, 0, 0.25, BLACK);
                DrawTextureEx(titulo, (Vector2){50, 0}, 0, 0.25, WHITE);
                DrawTextEx(subtitle, "Projeto APPC", (Vector2){135, 255}, 65, 0.25, BLACK);
                DrawTextEx(subtitle, "Projeto APPC", (Vector2){130, 250}, 65, 0.25, WHITE);
                DrawTextureEx(Charizard, (Vector2){570, 35}, 0, 5.0, WHITE);

                if ((framesCounter / 30) % 2 == 0) {
                    DrawTextEx(enter, "PRESSIONE ENTER", (Vector2){150, 425}, 55, 0.25, WHITE);
                }

                if (fadeOut) {
                    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), (Color){255, 255, 255, fadeAlpha});
                }

                break;

            case MENU:
                UpdateMusicStream(person);

                if (fadeInMenu && fadeAlphaMenu > 0) {
                    fadeAlphaMenu -= 3;
                    if (fadeAlphaMenu <= 0) {
                        fadeAlphaMenu = 0;
                        fadeInMenu = false;
                    }
                }

                if (IsKeyPressed(KEY_RIGHT)) {
                    mostrarTexto = false;
                }

                DesenhaMenu(fadeAlphaMenu, framesCounter);
                break;
        }

        EndDrawing();
        framesCounter++;
    }

    // Descarregar recursos
    UnloadTexture(background);
    UnloadTexture(titulo);
    UnloadFont(subtitle);
    UnloadFont(enter);
    UnloadFont(text);
    UnloadTexture(Charizard);
    UnloadMusicStream(menuMusic);
    UnloadMusicStream(person);
    UnloadSound(start);
    UnloadTexture(arrow);
    UnloadTexture(red);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}

void DesenhaMenu(int fadeAlpha, int framesCounter) {
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLUE); // background do menu

    if (mostrarTexto) {
        DrawTextEx(text, "COMO JOGAR", (Vector2){10, 2}, 60, 2, WHITE);
        DrawTextEx(text, "Este eh um jogo de batalha entre 2 jogadores. Cada jogador escolhe um Pokemon e os \ndois se enfrentam em um combate. Vence aquele que conseguir derrotar o Pokemon ad-\nversario. \n\nPrepare sua estrategia, escolha com sabedoria e que venca o melhor treinador!", (Vector2){10, 100}, 35, 2, WHITE);

        if ((framesCounter / 30) % 2 == 0) {
            DrawTextureEx(arrow, (Vector2){1050, 335}, 90, 0.35, WHITE);
        }
    } else {
        // pulo suave usando senóide
        float jumpOffset = sinf(redJumpTimer * 3.0f) * 5.0f;
        DrawEllipse(210, 450 + jumpOffset, 175, 25, SKYBLUE); // sombra do Red
        DrawTextureEx(red, (Vector2){0, 70 + jumpOffset}, 0.0, 5.0, WHITE);

        if ((framesCounter / 30) % 2 == 0) {
            DrawTextureEx(arrow, (Vector2){1050, 335}, 90, 0.35, WHITE);
        }
    }

    if (fadeAlpha > 0) {
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), (Color){255, 255, 255, fadeAlpha});
    }
}
