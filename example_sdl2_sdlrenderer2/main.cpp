#include "common.h"



 //Main code
int main(int, char**){
    if (!init()) { printf("Not able to initialze, Error %s:", SDL_GetError()); }
    else if (!initImGui()) { printf("InitImGui didnt do its work"); }
    else if (!gSceneManager.ChangeScene(std::make_unique<PopUpMenu>())) 
        printf("Scene didnt change to PopUpMenu"); 
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

            gSceneManager.Update();

            // Rendering
            gSceneManager.Render();
            SDL_RenderPresent(gRenderer);
        }
    }
    close();
    return 0;
}
