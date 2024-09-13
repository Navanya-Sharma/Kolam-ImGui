#include<SDL.h>
#include<SDL_image.h>
//#include<SDL_ttf.h>
#include<SDL_mixer.h>

#include<stdio.h>
#include<iostream>
/*#include<string>
#include <functional> 
#include <memory>

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"*/

#include "core.h"
#include "PopUpMenu.h"
#include "KolamButtons.h"
#include "DrawKolam.h"
#include "Texture.h"


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
                
                if (event.type == SDL_QUIT)
                    done = true;
                if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE
                    && event.window.windowID == SDL_GetWindowID(gWindow))
                    done = true;
                
                gSceneManager.HandleEvent(&event);
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
