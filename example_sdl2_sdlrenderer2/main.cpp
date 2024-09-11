#include "common.h"


 //Main code
int main(int, char**){
    if (!init()) { printf("Not able to initialze, Error %s:", SDL_GetError()); }
    else {        
        if (!initImGui()) { printf("InitImGui didnt do its work"); }
        else if(!setupImGui()) { printf("SetupImGui didnt do its work"); }
        else {
            bool done = false;
            while (!done)
            {
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

                InitialPopUp();

                // Rendering
                ImGui::Render();
                SDL_RenderSetScale(gRenderer, io->DisplayFramebufferScale.x, io->DisplayFramebufferScale.y);
                SDL_SetRenderDrawColor(gRenderer, 0xCB, 0x68, 0x43, 0xFF);
                SDL_RenderClear(gRenderer);
                ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), gRenderer);
                SDL_RenderPresent(gRenderer);
            }
        }
        
        close();
    }
    return 0;
}
