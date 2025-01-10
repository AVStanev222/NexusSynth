#ifndef ARGUMENT_EDITOR_H
#define ARGUMENT_EDITOR_H

#include <raylib.h>
#include <string>
#include <vector>
#include <cstring>

struct Argument {
    std::string mainQuestion;
    std::vector<std::string> yesArguments;
    std::vector<std::string> noArguments;
};

// Function prototypes
void DrawCenteredText(const char* text, int fontSize, float centerX, float centerY, Color color);
void InputAndDisplayNumbers(std::vector<int>& numbers);
void HandleInputField(Rectangle inputBox, char* text, int maxLength, const char* placeholder);
void DisplayArguments(const std::vector<Argument>& arguments);

#endif // ARGUMENT_EDITOR_H