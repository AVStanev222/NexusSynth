#include "argumentEditor.h"
#include <sstream>
#include <cstring>

void DrawCenteredText(const char* text, int fontSize, float centerX, float centerY, Color color) {
    Vector2 textSize = MeasureTextEx(GetFontDefault(), text, static_cast<float>(fontSize), 2.0f);
    float textX = centerX - textSize.x / 2.0f;
    float textY = centerY - textSize.y / 2.0f;
    DrawText(text, static_cast<int>(textX), static_cast<int>(textY), fontSize, color);
}

void DisplayArguments(const std::vector<Argument>& arguments) {
    float startY = 100.0f;
    float lineHeight = 30.0f;

    if (arguments.empty()) {
        DrawText("No arguments saved yet.", 100, startY, 20, GRAY);
        return;
    }

    for (size_t i = 0; i < arguments.size(); i++) {
        const Argument& arg = arguments[i];

        // Display main question
        DrawText(("Question: " + arg.mainQuestion).c_str(), 100, startY, 20, BLACK);
        startY += lineHeight;

        // Display Yes arguments
        DrawText("Yes Arguments:", 120, startY, 20, DARKGREEN);
        startY += lineHeight;
        for (const auto& yesArg : arg.yesArguments) {
            if (!yesArg.empty()) {
                DrawText(("- " + yesArg).c_str(), 140, startY, 20, DARKGREEN);
                startY += lineHeight;
            }
        }

        // Display No arguments
        DrawText("No Arguments:", 120, startY, 20, RED);
        startY += lineHeight;
        for (const auto& noArg : arg.noArguments) {
            if (!noArg.empty()) {
                DrawText(("- " + noArg).c_str(), 140, startY, 20, RED);
                startY += lineHeight;
            }
        }

        startY += lineHeight; // Add space between different arguments
    }
}

void HandleInputField(Rectangle inputBox, char* text, int maxLength, const char* placeholder) {
    DrawRectangleRec(inputBox, WHITE);
    DrawRectangleLinesEx(inputBox, 2, DARKGRAY);

    const int padding = 5;
    const int fontSize = 20;

    if (strlen(text) == 0) {
        DrawText(placeholder, static_cast<int>(inputBox.x + padding),
            static_cast<int>(inputBox.y + (inputBox.height - fontSize) / 2.0f),
            fontSize, GRAY);
    }
    else {
        DrawText(text, static_cast<int>(inputBox.x + padding),
            static_cast<int>(inputBox.y + (inputBox.height - fontSize) / 2.0f),
            fontSize, BLACK);
    }

    // Handle text input
    int key = GetCharPressed();
   /* while (key > 0) {
        size_t len = strlen(text);
        if (len < static_cast<size_t>(maxLength - 1) && key >= 32 && key <= 126) {
            text[len] = static_cast<char>(key);
            text[len + 1] = '\0';
        }
        key = GetCharPressed();
    }*/
    for(int i = 0; i <=170;i++)
    if (strlen(text) <= 22 && key >= 32 && key <= 126)
    {
        if (IsKeyPressed(i))
        {
            text[strlen(text)] = static_cast<char>(i);
            text[strlen(text) + 1] = '\0';
        }
    }

   
}