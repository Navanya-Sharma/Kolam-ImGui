#include "PopUpMenu.h"

bool PopUpMenu::Init() {
    bool pass = true;

    ImGui::StyleColorsDark();
    style = &ImGui::GetStyle();
    if (!style) { printf("Style not loaded");pass = false; }
    else {
        style->Colors[ImGuiCol_Button] = ImVec4(((float)0xCC / (float)255), ((float)0x6B / (float)255), ((float)0x47 / (float)255), 1.f);
        style->Colors[ImGuiCol_ButtonHovered] = ImVec4(((float)0xCC / (float)255), ((float)0x4A / (float)255), ((float)0x19 / (float)255), 1.f);
        style->Colors[ImGuiCol_ButtonActive] = ImVec4(((float)0x99 / (float)255), ((float)0x41 / (float)255), ((float)0x1F / (float)255), 1.f);
        style->Colors[ImGuiCol_FrameBg] = ImVec4(((float)0x99 / (float)255), ((float)0x67 / (float)255), ((float(0x54) / (float)255)), 1.f);

        style->WindowPadding = ImVec2(30, 25);
        style->ItemSpacing = ImVec2(20, 10);
        style->ItemInnerSpacing = ImVec2(30, 30);
        style->FramePadding = ImVec2(5, 5);

        style->WindowRounding = 15;
        style->FrameRounding = 10;
    }

    return pass;
}

void PopUpMenu::Update()
{
    // Start the Dear ImGui frame
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    ImGuiWindowFlags ImGui_flags = (ImGuiWindowFlags)(ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
    static int rows = 3, cols = 3;

    ImGui::SetNextWindowPos(ImVec2(io->DisplaySize.x * 0.5f, io->DisplaySize.y * 0.5f), 0, ImVec2(0.5f, 0.5f));
    ImGui::Begin("Input", 0, ImGui_flags);
    ImGui::SetWindowSize(ImVec2(600, 400));

    //HEADING
    ImGui::PushFont(BoldFont); ImGui::Indent(40);
    ImGui::Text("Welcome to Digital Kolam !"); ImGui::Unindent(40);
    ImGui::SeparatorText("");
    ImGui::PopFont();

    //NAME
    ImGui::Text("Name your Kolam: ");ImGui::SameLine();
    static char buf1[32] = "";
    int textX = ImGui::GetCursorPosX() + 60;
    ImGui::PushItemWidth(280);
    ImGui::InputText(" ", buf1, 32);

    //ROWS
    ImGui::Text("No. of Rows:");
    ImGui::SameLine();

    int y = ImGui::GetCursorPosY();
    ImGui::SetCursorPos(ImVec2(textX, y));
    ImGui::PushItemFlag(ImGuiItemFlags_ButtonRepeat, true);
    ImGui::PushItemWidth(100);

    if (ImGui::ArrowButton("##left", ImGuiDir_Left)) { rows = rows - 1 > 0 ? rows - 1 : 1; }

    float spacing = 40;
    ImGui::SameLine(0.0f, spacing);
    ImGui::Text("%d", rows);
    ImGui::SameLine(0.0f, spacing);

    if (ImGui::ArrowButton("##right", ImGuiDir_Right)) { rows = rows + 1 < 10 ? rows + 1 : 9; };

    //COLUMNS
    ImGui::PushID(1);
    ImGui::Text("No. of Columns:");
    ImGui::SameLine();

    y = ImGui::GetCursorPosY();
    ImGui::SetCursorPos(ImVec2(textX, y));

    if (ImGui::ArrowButton("##left", ImGuiDir_Left)) { cols = cols - 1 > 0 ? cols - 1 : 1; }

    ImGui::SameLine(0.0f, spacing);
    ImGui::Text("%d", cols);
    ImGui::SameLine(0.0f, spacing);

    if (ImGui::ArrowButton("##right", ImGuiDir_Right)) { cols = cols + 1 < 10 ? cols + 1 : 9; }
    ImGui::PopItemFlag();
    ImGui::PopID();

    //lETS DRAW BUTTON
    style->FramePadding = ImVec2(30, 10);
    BoldFont->Scale *= 0.7;
    ImGui::PushFont(BoldFont);
    ImGui::Indent(164);
    ImGui::Dummy(ImVec2(0, 23));
    if (ImGui::Button("Let's Draw!")) {
        if(!gSceneManager.ChangeScene(std::make_unique<DrawKolam>()))
            printf("Can not change the scene to DrawKolam");
    }
        
    ImGui::PopFont();
    BoldFont->Scale /= 0.7;
    style->FramePadding = ImVec2(5, 5);

    ImGui::End();
}

void PopUpMenu::Render() {
    ImGui::Render();
    SDL_RenderSetScale(gRenderer, io->DisplayFramebufferScale.x, io->DisplayFramebufferScale.y);
    SDL_SetRenderDrawColor(gRenderer, 0xCB, 0x68, 0x43, 0xFF);
    SDL_RenderClear(gRenderer);
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), gRenderer);
}
