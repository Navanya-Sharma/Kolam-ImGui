#pragma once
#include "common.h"

extern ImGuiIO* io;
extern ImFont* gFont;
extern ImFont* BoldFont;
extern ImGuiStyle* style;

bool initImGui();
bool setupImGui();
void InitialPopUp();