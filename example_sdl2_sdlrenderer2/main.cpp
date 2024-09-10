
#include<stdio.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>

#include<iostream>
#include<string>
#include <functional> 

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

#include "core.h"


 //Main code
int main(int, char**)
{
    if (!init()) { printf("Not able to initialze, Error %s:", SDL_GetError()); }
    else {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
        io.ConfigDebugIsDebuggerPresent = true;

        ImFont* gFont = io.Fonts->AddFontFromFileTTF("Font/roboto/Roboto-Regular.ttf", 30);
        ImFont* BoldFont = io.Fonts->AddFontFromFileTTF("Font/roboto/Roboto-Bold.ttf", 45);


       
        ImGui::StyleColorsDark();

        ImGui_ImplSDL2_InitForSDLRenderer(gWindow, gRenderer);
        ImGui_ImplSDLRenderer2_Init(gRenderer);

        ImGuiStyle& style = ImGui::GetStyle();

        style.Colors[ImGuiCol_Button] = ImVec4(((float)0xCC / (float)255), ((float)0x6B / (float)255), ((float)0x47 / (float)255), 1.f);
        style.Colors[ImGuiCol_ButtonHovered] = ImVec4(((float)0xCC / (float)255), ((float)0x4A / (float)255), ((float)0x19 / (float)255), 1.f);
        style.Colors[ImGuiCol_ButtonActive] = ImVec4(((float)0x99 / (float)255), ((float)0x41 / (float)255), ((float)0x1F / (float)255), 1.f);
        style.Colors[ImGuiCol_FrameBg] = ImVec4(((float)0x99 / (float)255), ((float)0x67 / (float)255), ((float(0x54) / (float)255)), 1.f);

        style.WindowPadding = ImVec2(30, 25);
        style.ItemSpacing = ImVec2(20, 10);
        style.ItemInnerSpacing = ImVec2(10, 10);
        style.FramePadding = ImVec2(5, 5);
        style.WindowRounding = 15;
        style.FrameRounding = 10;
        
       

        // Main loop
        bool done = false;
        while (!done)
        {
            // Poll and handle events (inputs, window resize, etc.)
            // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
            // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
            // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
            // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                ImGui_ImplSDL2_ProcessEvent(&event);
                if (event.type == SDL_QUIT)
                    done = true;
                if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE
                    && event.window.windowID == SDL_GetWindowID(gWindow))
                    done = true;
            }
            if (SDL_GetWindowFlags(gWindow) & SDL_WINDOW_MINIMIZED)
            {
                SDL_Delay(10);
                continue;
            }

            // Start the Dear ImGui frame
            ImGui_ImplSDLRenderer2_NewFrame();
            ImGui_ImplSDL2_NewFrame();
            ImGui::NewFrame();

            //ImGui::ShowDemoWindow();

            ImGuiWindowFlags ImGui_flags = (ImGuiWindowFlags)(ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
            static int rows = 3, cols = 3;
            
            ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f), 0, ImVec2(0.5f, 0.5f));

            ImGui::Begin("Input", 0, ImGui_flags);
            ImGui::SetWindowSize(ImVec2(600, 400));

            // float old_size = ImGui::GetFont()->Scale;
             //ImGui::GetFont()->Scale *= 1.8;
            ImGui::PushFont(BoldFont);

            ImGui::Indent(40);
            ImGui::Text("Welcome to Digital Kolam !");
            ImGui::Unindent(40);
            ImGui::SeparatorText("");
            ImGui::PopFont();

            ImGui::Text("Name your Kolam: ");

            ImGui::SameLine();
            static char buf1[32] = "";
            int textX = ImGui::GetCursorPosX() + 60;
            ImGui::PushItemWidth(280);
            ImGui::InputText(" ", buf1, 32);

            style.ItemInnerSpacing = ImVec2(30, 30);
            ImGui::Text("No. of Rows:");
            ImGui::SameLine();

            int y = ImGui::GetCursorPosY();
            ImGui::SetCursorPos(ImVec2(textX, y));


            ImGui::PushItemFlag(ImGuiItemFlags_ButtonRepeat, true);
            

            float spacing = 40;
            ImGui::PushItemWidth(100);
            if (ImGui::ArrowButton("##left", ImGuiDir_Left)) { rows--; }
            ImGui::SameLine(0.0f, spacing);
            ImGui::Text("%d", rows);
            ImGui::SameLine(0.0f, spacing);
            if (ImGui::ArrowButton("##right", ImGuiDir_Right)) { rows++; }

            ImGui::PushID(1);
            ImGui::Text("No. of Columns:");
            ImGui::SameLine();
            y = ImGui::GetCursorPosY();
            ImGui::SetCursorPos(ImVec2(textX, y));
            if (ImGui::ArrowButton("##left", ImGuiDir_Left)) { cols--; }
            ImGui::SameLine(0.0f, spacing);
            ImGui::Text("%d", cols);
            ImGui::SameLine(0.0f, spacing);
            if (ImGui::ArrowButton("##right", ImGuiDir_Right)) { cols++; }
            ImGui::PopItemFlag();
            ImGui::PopID();

            style.FramePadding = ImVec2(30, 10);

            BoldFont->Scale *= 0.7;
            ImGui::PushFont(BoldFont);
            ImGui::Indent(164);
            ImGui::Dummy(ImVec2(0, 23));
            ImGui::Button("Let's Draw!");


            ImGui::PopFont();
            BoldFont->Scale /= 0.7;
            style.FramePadding = ImVec2(5, 5);

            ImGui::End();

            // Rendering
            ImGui::Render();
            SDL_RenderSetScale(gRenderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
            SDL_SetRenderDrawColor(gRenderer, 0xCB, 0x68, 0x43, 0xFF);
            SDL_RenderClear(gRenderer);
            ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), gRenderer);
            SDL_RenderPresent(gRenderer);
        }

        // Cleanup
        ImGui_ImplSDLRenderer2_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();

        SDL_DestroyRenderer(gRenderer);
        SDL_DestroyWindow(gWindow);
        SDL_Quit();

    }
    return 0;
}
