#include "raylib.h"
#include "gui.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_INPUT_CHARS 20
#define INPUT_COUNT 8

static const Color BG_COLOR         = {245, 247, 250, 255};
static const Color CARD_COLOR       = {252, 252, 252, 255};
static const Color PRIMARY_BLUE     = {25, 90, 180, 255};
static const Color PRIMARY_BLUE_HOV = {35, 110, 210, 255};
static const Color SECONDARY_BLUE   = {45, 95, 160, 255};
static const Color TEXT_DARK        = {35, 35, 35, 255};
static const Color TEXT_MUTED       = {95, 95, 95, 255};
static const Color BORDER_SOFT      = {210, 215, 220, 255};
static const Color INPUT_FILL       = {248, 249, 251, 255};
static const Color INPUT_ACTIVE     = {232, 240, 255, 255};
static const Color SUCCESS_GREEN    = {25, 120, 70, 255};

typedef enum {
    SCREEN_MENU = 0,
    SCREEN_ANALYSIS,
    SCREEN_ABOUT
} AppScreen;

typedef struct {
    Rectangle bounds;
    char text[MAX_INPUT_CHARS];
    int letterCount;
    bool active;
    const char *placeholder;
} InputBox;

static bool DrawButton(Rectangle rect, const char *text, Font font)
{
    Vector2 mouse = GetMousePosition();
    bool hover = CheckCollisionPointRec(mouse, rect);

    bool isBackButton = (strcmp(text, "VOLTAR") == 0);

    Color fillColor;
    Color borderColor;

    if (isBackButton) {
        fillColor = hover ? (Color){60, 110, 180, 255} : SECONDARY_BLUE;
        borderColor = hover ? (Color){120, 170, 230, 255} : SECONDARY_BLUE;
    } else {
        fillColor = hover ? PRIMARY_BLUE_HOV : PRIMARY_BLUE;
        borderColor = hover ? (Color){120, 170, 230, 255} : PRIMARY_BLUE;
    }

    DrawRectangleRounded(rect, 0.18f, 10, fillColor);
    DrawRectangleRoundedLinesEx(rect, 0.18f, 10, 2.0f, borderColor);

    float fontSize = 22;
    float spacing = 1;

    Vector2 textSize = MeasureTextEx(font, text, fontSize, spacing);
    Vector2 textPos = {
        rect.x + (rect.width - textSize.x) / 2.0f,
        rect.y + (rect.height - textSize.y) / 2.0f
    };

    DrawTextEx(font, text, textPos, fontSize, spacing, RAYWHITE);

    return hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

static void UpdateActiveInput(InputBox inputs[], int count)
{
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mouse = GetMousePosition();
        bool clickedAny = false;

        for (int i = 0; i < count; i++) {
            if (CheckCollisionPointRec(mouse, inputs[i].bounds)) {
                clickedAny = true;

                for (int j = 0; j < count; j++) {
                    inputs[j].active = false;
                }

                inputs[i].active = true;
                break;
            }
        }

        if (!clickedAny) {
            for (int i = 0; i < count; i++) {
                inputs[i].active = false;
            }
        }
    }
}

static bool InputHasDot(const InputBox *box)
{
    for (int i = 0; i < box->letterCount; i++) {
        if (box->text[i] == '.') return true;
    }
    return false;
}

static void HandleSingleInput(InputBox *box)
{
    if (!box->active) return;

    int key = GetCharPressed();

    while (key > 0) {
        bool isDigit = (key >= '0' && key <= '9');
        bool isDot = (key == '.');

        if (isDigit) {
            if (box->letterCount < MAX_INPUT_CHARS - 1) {
                box->text[box->letterCount] = (char)key;
                box->letterCount++;
                box->text[box->letterCount] = '\0';
            }
        } else if (isDot) {
            if (!InputHasDot(box) && box->letterCount > 0 && box->letterCount < MAX_INPUT_CHARS - 1) {
                box->text[box->letterCount] = '.';
                box->letterCount++;
                box->text[box->letterCount] = '\0';
            }
        }

        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE)) {
        if (box->letterCount > 0) {
            box->letterCount--;
            box->text[box->letterCount] = '\0';
        }
    }
}

static void HandleAllInputs(InputBox inputs[], int count)
{
    UpdateActiveInput(inputs, count);

    for (int i = 0; i < count; i++) {
        HandleSingleInput(&inputs[i]);
    }
}

static void DrawInputBox(InputBox box, Font font)
{
    Color fillColor = box.active ? INPUT_ACTIVE : INPUT_FILL;
    Color borderColor = box.active ? PRIMARY_BLUE : BORDER_SOFT;

    DrawRectangleRounded(box.bounds, 0.10f, 8, fillColor);
    DrawRectangleRoundedLinesEx(box.bounds, 0.10f, 8, 2.0f, borderColor);

    Vector2 textPos = {
        box.bounds.x + 12,
        box.bounds.y + 10
    };

    if (box.letterCount == 0) {
        DrawTextEx(font, box.placeholder, textPos, 20, 1, TEXT_MUTED);
    } else {
        DrawTextEx(font, box.text, textPos, 20, 1, TEXT_DARK);
    }

    if (box.active) {
        float textWidth = MeasureTextEx(font, box.text, 20, 1).x;
        int cursorX = (int)(box.bounds.x + 12 + textWidth + 2);
        int cursorY = (int)box.bounds.y + 8;

        if (((int)(GetTime() * 2) % 2) == 0) {
            DrawRectangle(cursorX, cursorY, 2, 24, PRIMARY_BLUE);
        }
    }
}

void start_gui(void)
{
    const int screenWidth = 1366;
    const int screenHeight = 1040;

    InitWindow(screenWidth, screenHeight, "MED IA - Analise de Hemograma");
    SetTargetFPS(60);

    Font fontTitle = LoadFontEx("assets/fonts/Roboto-Bold.ttf", 42, 0, 0);
    Font fontSubtitle = LoadFontEx("assets/fonts/Roboto-Bold.ttf", 30, 0, 0);
    Font fontText = LoadFontEx("assets/fonts/Roboto-Regular.ttf", 22, 0, 0);
    Font fontButton = LoadFontEx("assets/fonts/Roboto-Bold.ttf", 22, 0, 0);

    AppScreen currentScreen = SCREEN_MENU;

    int formX = 250;
    int formY = 170;
    int formWidth = 860;
    int formHeight = 860;

    int labelX = 330;
    int inputX = 720;
    int inputWidth = 240;
    int inputHeight = 42;

    InputBox inputs[INPUT_COUNT] = {
        {{inputX, 245, inputWidth, inputHeight}, "", 0, false, "Ex: 4.80"},
        {{inputX, 300, inputWidth, inputHeight}, "", 0, false, "Ex: 13.50"},
        {{inputX, 355, inputWidth, inputHeight}, "", 0, false, "Ex: 40.00"},
        {{inputX, 410, inputWidth, inputHeight}, "", 0, false, "Ex: 90.00"},
        {{inputX, 465, inputWidth, inputHeight}, "", 0, false, "Ex: 30.00"},
        {{inputX, 520, inputWidth, inputHeight}, "", 0, false, "Ex: 34.00"},
        {{inputX, 640, inputWidth, inputHeight}, "", 0, false, "Ex: 7000"},
        {{inputX, 760, inputWidth, inputHeight}, "", 0, false, "Ex: 250000"}
    };

    char resultado[256] = "";
    bool showResult = false;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BG_COLOR);

        DrawTextEx(
            fontTitle,
            "SISTEMA MED IA",
            (Vector2){
                screenWidth / 2.0f - MeasureTextEx(fontTitle, "SISTEMA MED IA", 42, 2).x / 2.0f,
                45
            },
            42,
            2,
            PRIMARY_BLUE
        );

        DrawLine(200, 110, screenWidth - 200, 110, BORDER_SOFT);

        if (currentScreen == SCREEN_MENU) {
            const char *menuTitle = "MENU PRINCIPAL";
            Vector2 menuTitlePos = {
                screenWidth / 2.0f - MeasureTextEx(fontSubtitle, menuTitle, 30, 2).x / 2.0f,
                150
            };

            DrawTextEx(fontSubtitle, menuTitle, menuTitlePos, 30, 2, TEXT_DARK);

            Rectangle btnAnalysis = {365, 270, 550, 70};
            Rectangle btnAbout    = {365, 370, 550, 70};
            Rectangle btnExit     = {365, 470, 550, 70};

            if (DrawButton(btnAnalysis, "1. Inserir novo hemograma para analise", fontButton)) {
                currentScreen = SCREEN_ANALYSIS;
            }

            if (DrawButton(btnAbout, "2. Sobre o sistema", fontButton)) {
                currentScreen = SCREEN_ABOUT;
            }

            if (DrawButton(btnExit, "3. Sair", fontButton)) {
                break;
            }
        }
        else if (currentScreen == SCREEN_ANALYSIS) {
            HandleAllInputs(inputs, INPUT_COUNT);

            DrawRectangleRounded((Rectangle){formX, formY, formWidth, formHeight}, 0.03f, 8, CARD_COLOR);
            DrawRectangleRoundedLinesEx((Rectangle){formX, formY, formWidth, formHeight}, 0.03f, 8, 2.0f, BORDER_SOFT);

            const char *analysisTitle = "ANALISE DE HEMOGRAMA";
            Vector2 analysisTitlePos = {
                screenWidth / 2.0f - MeasureTextEx(fontSubtitle, analysisTitle, 30, 2).x / 2.0f,
                120
            };

            DrawTextEx(fontSubtitle, analysisTitle, analysisTitlePos, 30, 2, TEXT_DARK);

            DrawTextEx(fontSubtitle, "SERIE VERMELHA", (Vector2){labelX, 205}, 26, 1.5f, TEXT_DARK);
            DrawTextEx(fontText, "Hemacias (RBC)",    (Vector2){labelX, 255}, 24, 1.0f, TEXT_DARK);
            DrawTextEx(fontText, "Hemoglobina (HGB)", (Vector2){labelX, 310}, 24, 1.0f, TEXT_DARK);
            DrawTextEx(fontText, "Hematocrito (HCT)", (Vector2){labelX, 365}, 24, 1.0f, TEXT_DARK);
            DrawTextEx(fontText, "VCM",               (Vector2){labelX, 420}, 24, 1.0f, TEXT_DARK);
            DrawTextEx(fontText, "HCM",               (Vector2){labelX, 475}, 24, 1.0f, TEXT_DARK);
            DrawTextEx(fontText, "CHCM",              (Vector2){labelX, 530}, 24, 1.0f, TEXT_DARK);

            DrawTextEx(fontSubtitle, "SERIE BRANCA", (Vector2){labelX, 600}, 26, 1.5f, TEXT_DARK);
            DrawTextEx(fontText, "Leucocitos (WBC)", (Vector2){labelX, 650}, 24, 1.0f, TEXT_DARK);

            DrawTextEx(fontSubtitle, "PLAQUETAS", (Vector2){labelX, 720}, 26, 1.5f, TEXT_DARK);
            DrawTextEx(fontText, "PLT",           (Vector2){labelX, 770}, 24, 1.0f, TEXT_DARK);

            for (int i = 0; i < INPUT_COUNT; i++) {
                DrawInputBox(inputs[i], fontText);
            }

            Rectangle btnAnalyze = {580, 855, 200, 50};
            Rectangle btnBack    = {580, 920, 200, 50};

            if (DrawButton(btnAnalyze, "ANALISAR", fontButton)) {
                snprintf(
                    resultado,
                    sizeof(resultado),
                    "RBC: %s | HGB: %s | HCT: %s | WBC: %s | PLT: %s",
                    inputs[0].text, inputs[1].text, inputs[2].text, inputs[6].text, inputs[7].text
                );
                showResult = true;
            }

            if (DrawButton(btnBack, "VOLTAR", fontButton)) {
                for (int i = 0; i < INPUT_COUNT; i++) {
                    inputs[i].active = false;
                }
                currentScreen = SCREEN_MENU;
            }

            if (showResult) {
                DrawTextEx(fontText, "Resultado da analise:", (Vector2){160, 820}, 22, 1, TEXT_MUTED);
                DrawTextEx(fontText, resultado, (Vector2){160, 850}, 20, 1, SUCCESS_GREEN);
            }
        }
        else if (currentScreen == SCREEN_ABOUT) {
            const char *aboutTitle = "SOBRE O SISTEMA";

            Vector2 aboutTitlePos = {
                screenWidth / 2.0f - MeasureTextEx(fontSubtitle, aboutTitle, 30, 2).x / 2.0f,
                140
            };

            DrawTextEx(fontSubtitle, aboutTitle, aboutTitlePos, 30, 2, TEXT_DARK);

            DrawTextEx(fontText,
                "Sistema MED IA - Analise de Hemograma com Machine Learning",
                (Vector2){140, 250}, 24, 1, TEXT_DARK);

            DrawTextEx(fontText,
                "Este sistema utiliza inteligencia artificial para auxiliar",
                (Vector2){140, 310}, 24, 1, TEXT_MUTED);

            DrawTextEx(fontText,
                "na analise de exames de hemograma completo.",
                (Vector2){140, 350}, 24, 1, TEXT_MUTED);

            DrawTextEx(fontText,
                "IMPORTANTE: este sistema e apenas para fins educacionais",
                (Vector2){140, 450}, 24, 1, MAROON);

            DrawTextEx(fontText,
                "e de pesquisa. Nao substitui o diagnostico medico.",
                (Vector2){140, 490}, 24, 1, MAROON);

            DrawTextEx(fontText,
                "Frontend: C",
                (Vector2){140, 590}, 24, 1, TEXT_DARK);

            DrawTextEx(fontText,
                "Backend: Python (Machine Learning)",
                (Vector2){140, 630}, 24, 1, TEXT_DARK);

            DrawTextEx(fontText,
                "Comunicacao: Socket TCP/IP",
                (Vector2){140, 670}, 24, 1, TEXT_DARK);

            Rectangle btnBack = {530, 790, 220, 55};

            if (DrawButton(btnBack, "VOLTAR", fontButton)) {
                currentScreen = SCREEN_MENU;
            }
        }

        EndDrawing();
    }

    UnloadFont(fontTitle);
    UnloadFont(fontSubtitle);
    UnloadFont(fontText);
    UnloadFont(fontButton);
    CloseWindow();
}