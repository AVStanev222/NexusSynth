#include <raylib.h>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include "argumentEditor.h"

using namespace std;

int main() {
    InitWindow(1200, 800, "Argument Editor");
    SetTargetFPS(60);

    bool displayTree = false;
    bool displayMapper = false;
    bool showExtraFieldsYes = false;
    bool showExtraFieldsNo = false;
    int activeField = -1;  // -1 for main field, 0-2 for yes fields, 3-4 for no fields
    vector<Argument> savedArguments;

    char inputText[256] = "";
    char extraTextsYes[3][256] = { "", "", "" };
    char extraTextsNo[2][256] = { "", "" };
    Rectangle inputBox = { (1200.0f - 300.0f) / 2.0f, 100.0f, 300.0f, 40.0f };

    // Yes argument fields
    Rectangle extraFieldsYes[3] = {
        { (1200.0f - 300.0f) / 2.0f, 250.0f, 300.0f, 40.0f },
        { (1200.0f - 300.0f) / 2.0f, 310.0f, 300.0f, 40.0f },
        { (1200.0f - 300.0f) / 2.0f, 370.0f, 300.0f, 40.0f }
    };

    // No argument fields
    Rectangle extraFieldsNo[2] = {
        { (1200.0f - 300.0f) / 2.0f, 250.0f, 300.0f, 40.0f },
        { (1200.0f - 300.0f) / 2.0f, 310.0f, 300.0f, 40.0f }
    };

    // Arrow buttons for Yes fields
    Rectangle arrowButtonsYes[3] = {
        { (1200.0f + 300.0f) / 2.0f + 10.0f, 250.0f, 40.0f, 40.0f },
        { (1200.0f + 300.0f) / 2.0f + 10.0f, 310.0f, 40.0f, 40.0f },
        { (1200.0f + 300.0f) / 2.0f + 10.0f, 370.0f, 40.0f, 40.0f }
    };

    // Arrow buttons for No fields
    Rectangle arrowButtonsNo[2] = {
        { (1200.0f + 300.0f) / 2.0f + 10.0f, 250.0f, 40.0f, 40.0f },
        { (1200.0f + 300.0f) / 2.0f + 10.0f, 310.0f, 40.0f, 40.0f }
    };

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(LIGHTGRAY);

        if (!displayTree && !displayMapper) {
            DrawCenteredText("Welcome to Argument Editor!", 40, 1200/2, 800/2, BLACK);

            Rectangle startButton = { 400.0f, 400.0f + 50.f, 200.0f, 50.0f };
            Color startButtonColor = DARKGRAY;
            if (CheckCollisionPointRec(GetMousePosition(), startButton) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                startButtonColor = GREEN;
            }
            DrawRectangleRec(startButton, startButtonColor);
            DrawCenteredText("Start", 20, startButton.x + startButton.width / 2.0f,
                475.f, WHITE);

            Rectangle mapperButton = { 700.0f, 450.0f, 200.0f, 50.0f };
            Color mapperButtonColor = DARKGRAY;
            if (CheckCollisionPointRec(GetMousePosition(), mapperButton) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                mapperButtonColor = GREEN;
            }
            DrawRectangleRec(mapperButton, mapperButtonColor);
            DrawCenteredText("Argument Mapper", 20, mapperButton.x + mapperButton.width / 2.0f,
                mapperButton.y + mapperButton.height / 2.0f, WHITE);

            if (CheckCollisionPointRec(GetMousePosition(), startButton) &&
                IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                displayTree = true;
            }
            else if (CheckCollisionPointRec(GetMousePosition(), mapperButton) &&
                IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                displayMapper = true;
            }
        }
        else if (displayTree) {
            // Main input field handling
            if (activeField == -1) {
                HandleInputField(inputBox, inputText, 255, "Question...");
            }
            else {
                DrawRectangleRec(inputBox, WHITE);
                DrawRectangleLinesEx(inputBox, 2, DARKGRAY);
                if (strlen(inputText) > 0) {
                    DrawText(inputText, static_cast<int>(inputBox.x + 5),
                        static_cast<int>(inputBox.y + inputBox.height / 2 - 10),
                        20, BLACK);
                }
                else {
                    DrawText("Question...", static_cast<int>(inputBox.x + 5),
                        static_cast<int>(inputBox.y + inputBox.height / 2 - 10),
                        20, GRAY);
                }
            }

            // Yes/No buttons
            float buttonY = inputBox.y + inputBox.height + 20.0f;
            float buttonWidth = 60.0f;
            float buttonHeight = 30.0f;
            float buttonGap = 20.0f;
            float totalWidth = (buttonWidth * 2) + buttonGap;
            float startX = (1200.0f - totalWidth) / 2.0f;

            Rectangle yesButton = { startX, buttonY, buttonWidth, buttonHeight };
            Color yesButtonColor = DARKGRAY;
            if (CheckCollisionPointRec(GetMousePosition(), yesButton) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                yesButtonColor = GREEN;
            }
            DrawRectangleRec(yesButton, yesButtonColor);
            DrawCenteredText("Yes", 20, yesButton.x + yesButton.width / 2.0f,
                yesButton.y + yesButton.height / 2.0f, WHITE);

            Rectangle noButton = { startX + buttonWidth + buttonGap, buttonY, buttonWidth, buttonHeight };
            Color noButtonColor = DARKGRAY;
            if (CheckCollisionPointRec(GetMousePosition(), noButton) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                noButtonColor = GREEN;
            }
            DrawRectangleRec(noButton, noButtonColor);
            DrawCenteredText("No", 20, noButton.x + noButton.width / 2.0f,
                noButton.y + noButton.height / 2.0f, WHITE);

            // Handle Yes/No button clicks
            if (CheckCollisionPointRec(GetMousePosition(), yesButton) &&
                IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                showExtraFieldsYes = true;
                showExtraFieldsNo = false;
                activeField = 0;
                for (int i = 0; i < 2; i++) {
                    extraTextsNo[i][0] = '\0';
                }
            }
            if (CheckCollisionPointRec(GetMousePosition(), noButton) &&
                IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                showExtraFieldsNo = true;
                showExtraFieldsYes = false;
                activeField = 3;
                for (int i = 0; i < 3; i++) {
                    extraTextsYes[i][0] = '\0';
                }
            }

            // Draw Yes/No argument fields
            if (showExtraFieldsYes) {
                // Draw Yes fields
                for (int i = 0; i < 3; i++) {
                    if (i == activeField) {
                        HandleInputField(extraFieldsYes[i], extraTextsYes[i], 255, "Argument for yes...");
                    }
                    else {
                        DrawRectangleRec(extraFieldsYes[i], WHITE);
                        DrawRectangleLinesEx(extraFieldsYes[i], 2, DARKGRAY);
                        if (strlen(extraTextsYes[i]) > 0) {
                            DrawText(extraTextsYes[i], static_cast<int>(extraFieldsYes[i].x + 5),
                                static_cast<int>(extraFieldsYes[i].y + extraFieldsYes[i].height / 2 - 10),
                                20, BLACK);
                        }
                        else {
                            DrawText("Argument for yes...", static_cast<int>(extraFieldsYes[i].x + 5),
                                static_cast<int>(extraFieldsYes[i].y + extraFieldsYes[i].height / 2 - 10),
                                20, GRAY);
                        }
                    }

                    // Draw arrow buttons
                    Color arrowColor = DARKGRAY;
                    if (CheckCollisionPointRec(GetMousePosition(), arrowButtonsYes[i]) &&
                        IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                        arrowColor = GREEN;
                    }
                    DrawRectangleRec(arrowButtonsYes[i], arrowColor);
                    DrawCenteredText("<", 20, arrowButtonsYes[i].x + arrowButtonsYes[i].width / 2.0f,
                        arrowButtonsYes[i].y + arrowButtonsYes[i].height / 2.0f, WHITE);

                    if (CheckCollisionPointRec(GetMousePosition(), arrowButtonsYes[i]) &&
                        IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && i < 2) {
                        activeField = i + 1;
                    }
                }
            }

            if (showExtraFieldsNo) {
                // Draw No fields
                for (int i = 0; i < 2; i++) {
                    if (i + 3 == activeField) {
                        HandleInputField(extraFieldsNo[i], extraTextsNo[i], 255, "Argument for no...");
                    }
                    else {
                        DrawRectangleRec(extraFieldsNo[i], WHITE);
                        DrawRectangleLinesEx(extraFieldsNo[i], 2, DARKGRAY);
                        if (strlen(extraTextsNo[i]) > 0) {
                            DrawText(extraTextsNo[i], static_cast<int>(extraFieldsNo[i].x + 5),
                                static_cast<int>(extraFieldsNo[i].y + extraFieldsNo[i].height / 2 - 10),
                                20, BLACK);
                        }
                        else {
                            DrawText("Argument for no...", static_cast<int>(extraFieldsNo[i].x + 5),
                                static_cast<int>(extraFieldsNo[i].y + extraFieldsNo[i].height / 2 - 10),
                                20, GRAY);
                        }
                    }

                    Color arrowColor = DARKGRAY;
                    if (CheckCollisionPointRec(GetMousePosition(), arrowButtonsNo[i]) &&
                        IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                        arrowColor = GREEN;
                    }
                    DrawRectangleRec(arrowButtonsNo[i], arrowColor);
                    DrawCenteredText("<", 20, arrowButtonsNo[i].x + arrowButtonsNo[i].width / 2.0f,
                        arrowButtonsNo[i].y + arrowButtonsNo[i].height / 2.0f, WHITE);

                    if (CheckCollisionPointRec(GetMousePosition(), arrowButtonsNo[i]) &&
                        IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && i < 1) {
                        activeField = i + 4;
                    }
                }
            }

            // Save button
            Rectangle saveButton = { (1200.0f - 200.0f) / 2.0f, 600.0f, 200.0f, 50.0f };
            DrawRectangleRec(saveButton, GREEN);
            DrawCenteredText("Save", 20, saveButton.x + saveButton.width / 2.0f,
                saveButton.y + saveButton.height / 2.0f, WHITE);

            if (CheckCollisionPointRec(GetMousePosition(), saveButton) &&
                IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                // Save current argument
                Argument newArg;
                newArg.mainQuestion = inputText;

                // Save yes arguments
                for (int i = 0; i < 3; i++) {
                    if (strlen(extraTextsYes[i]) > 0) {
                        newArg.yesArguments.push_back(extraTextsYes[i]);
                    }
                }

                // Save no arguments
                for (int i = 0; i < 2; i++) {
                    if (strlen(extraTextsNo[i]) > 0) {
                        newArg.noArguments.push_back(extraTextsNo[i]);
                    }
                }

                savedArguments.push_back(newArg);

                // Clear all fields
                inputText[0] = '\0';
                for (int i = 0; i < 3; i++) extraTextsYes[i][0] = '\0';
                for (int i = 0; i < 2; i++) extraTextsNo[i][0] = '\0';
                showExtraFieldsYes = false;
                showExtraFieldsNo = false;
                activeField = -1;
            }

            // Back button
            Rectangle backButton = { (1200.0f - 200.0f) / 2.0f, 700.0f, 200.0f, 50.0f };
            DrawRectangleRec(backButton, RED);
            DrawCenteredText("Back", 20, backButton.x + backButton.width / 2.0f,
                backButton.y + backButton.height / 2.0f, WHITE);

            if (CheckCollisionPointRec(GetMousePosition(), backButton) &&
                IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                displayTree = false;
                inputText[0] = '\0';
                showExtraFieldsYes = false;
                showExtraFieldsNo = false;
                activeField = -1;
                for (int i = 0; i < 3; i++) extraTextsYes[i][0] = '\0';
                for (int i = 0; i < 2; i++) extraTextsNo[i][0] = '\0';
            }
        }
        else if (displayMapper) {
            // Display saved arguments
            DisplayArguments(savedArguments);

            // Back button
            Rectangle backButton = { (1200.0f - 200.0f) / 2.0f, 700.0f, 200.0f, 50.0f };
            DrawRectangleRec(backButton, RED);
            DrawCenteredText("Back", 20, backButton.x + backButton.width / 2.0f,
                backButton.y + backButton.height / 2.0f, WHITE);

            if (CheckCollisionPointRec(GetMousePosition(), backButton) &&
                IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                displayMapper = false;
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}