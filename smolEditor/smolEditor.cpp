#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <thread>
#include <filesystem>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL_opengles2.h>
#endif

#include "../smolEngine/smolEngine.h"
#include "../smolEngine/Application.h"

using namespace std;
using namespace chrono;

static SDL_GLContext createSdlGlContext(SDL_Window* window) {
    auto gl_context = SDL_GL_CreateContext(window);
    if(!gl_context) throw exception(SDL_GetError());
    if(SDL_GL_MakeCurrent(window,gl_context)!=0) throw exception(SDL_GetError());
    if(SDL_GL_SetSwapInterval(1)!=0) throw exception(SDL_GetError());
    return gl_context;
}

static void initOpenGL() {
    auto glew_init_error = glewInit();
    if(glew_init_error!=GLEW_OK) throw exception((char*)glewGetErrorString(glew_init_error));
    if(!GLEW_VERSION_3_1) throw exception("OpenGL 3.1 Not Supported!");
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glClearColor(1, 1, 1, 1);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

static bool processSDLEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        ImGui_ImplSDL2_ProcessEvent(&event);
        switch (event.type) {
        case SDL_QUIT: return false;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
            case SDLK_ESCAPE: return false;
            }
            break;
        }
    }
    return true;
}

int main(int argc, char* argv[])
{
    try {
        /*auto window = initSDLWindowWithOpenGL();
        auto gl_context = createSdlGlContext(window);
        initOpenGL();*/

        // TEMP: intentando crear la demo window
        /*bool showDemoWindow = true;
        ImVec4 bg_color = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);*/

        {
            smolEngine engine;
            engine.camera.fov = 60;
            engine.camera.aspect = static_cast<double>(WINDOW_WIDTH) / WINDOW_HEIGHT;
            engine.camera.zNear = 0.1;
            engine.camera.zFar = 100;
            engine.camera.eye = vec3(5, 1.75, 5);
            engine.camera.center = vec3(0, 1, 0);
            engine.camera.up = vec3(0, 1, 0);

            // Setup Dear ImGui context
            //IMGUI_CHECKVERSION();
            //ImGui::CreateContext();
            //ImGuiIO& io = ImGui::GetIO(); (void)io;
            //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
            //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
            //io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
            //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows


            //// Setup Dear ImGui style

            //ImGui::StyleColorsDark();
            ////ImGui::StyleColorsLight();



            //// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
            //ImGuiStyle& style = ImGui::GetStyle();
            //if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
            //{
            //    style.WindowRounding = 0.0f;
            //    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
            //}


            // Setup Platform/Renderer backends
            /*ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
            ImGui_ImplOpenGL3_Init("#version 130");*/



            // Main loop
            bool done = false;

            while (!done) {

                SDL_Event event;
                while (SDL_PollEvent(&event))
                {
                    ImGui_ImplSDL2_ProcessEvent(&event);
                    if (event.type == SDL_QUIT)
                        done = true;
                    if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                        done = true;
                }




                //// Iniciar el frame de ImGui
                //ImGui_ImplOpenGL3_NewFrame();
                //ImGui_ImplSDL2_NewFrame(window);
                //ImGui::NewFrame();

                /*ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
                ImGui::DockSpace(dockspace_id, ImVec2(10.0f, 10.0f), ImGuiDockNodeFlags_PassthruCentralNode);*/


                // TEMP: intentando crear la demo window
                /*if (showDemoWindow)
                    ImGui::ShowDemoWindow(&showDemoWindow);*/

                /*static float f = 0.0f;
                static int counter = 0;*/

                //if (ImGui::Begin("Hello, world!"), ImGuiWindowFlags_MenuBar)
                //{
                //    ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
                //    ImGui::Checkbox("Demo Window", &showDemoWindow);      // Edit bools storing our window open/close state
                //    ImGui::Checkbox("Another Window", &showDemoWindow);
                //    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f

                //    if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                //        counter++;
                //    ImGui::SameLine();
                //    ImGui::Text("counter = %d", counter);

                //    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
                //    ImGui::End();
                //}

                //// Crear ventanas o paneles que se pueden acoplar
                //if (ImGui::Begin("Panel 1"), ImGuiWindowFlags_MenuBar) {
                //    // Contenido del primer panel
                //    ImGui::Text("Contenido del Panel 1");
                //    ImGui::End();
                //}

                //if (ImGui::Begin("Panel 2"), ImGuiWindowFlags_MenuBar) {
                //    // Contenido del segundo panel
                //    ImGui::Text("Contenido del Panel 2");
                //    ImGui::End();
                //}

                //const auto frame_start = steady_clock::now();
                //engine.step(FDT);
               /* glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);*/
                //engine.render();
                /*ImGui::Render();*/
               /* glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
                glClearColor(bg_color.x * bg_color.w, bg_color.y * bg_color.w, bg_color.z * bg_color.w, bg_color.w);*/
                /*glClear(GL_COLOR_BUFFER_BIT);*/
                //ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());



                //// Update and Render additional Platform Windows
                //// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
                ////  For this specific demo app we could also call SDL_GL_MakeCurrent(window, gl_context) directly)
                //if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
                //{
                //    SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
                //    SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
                //    ImGui::UpdatePlatformWindows();
                //    ImGui::RenderPlatformWindowsDefault();
                //    SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
                //}


                /*SDL_GL_SwapWindow(window);*/
                /*const auto frame_end = steady_clock::now();
                const auto frame_duration = frame_end - frame_start;
                if (frame_duration < FDT) this_thread::sleep_for(FDT - frame_duration);*/
            }
        }

        //ImGui_ImplOpenGL3_Shutdown();
        //ImGui_ImplSDL2_Shutdown();
        //ImGui::DestroyContext();

        //SDL_GL_DeleteContext(gl_context);

        return EXIT_SUCCESS;
    }
    catch(const exception& ex) {
        cerr << ex.what() << endl;
        return EXIT_FAILURE;
    }
}


class smolEditorApp : public Application
{
public:

    smolEditorApp(int argc, char** argv) : Application(argc, argv)
    {
        AddModuleBack(new Editor());
    }

    ~smolEditorApp()
    {

    }
};

Application* CreateApplication(int argc, char** argv)
{
    return new smolEditorApp(argc, argv);
}