#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <thread>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL_opengles2.h>
#endif

#include "../smolEngine/smolEngine.h"

using namespace std;
using namespace chrono;

static const unsigned int WINDOW_WIDTH = 576*4/3;
static const unsigned int WINDOW_HEIGHT = 576;
static const unsigned int FPS = 60;
static const auto FDT = 1.0s / FPS;

static SDL_Window* initSDLWindowWithOpenGL() {
    if(SDL_Init(SDL_INIT_VIDEO)!=0) throw exception(SDL_GetError());
    
    SDL_version compiled;
    SDL_VERSION(&compiled);
    cout << "SDL Compiled with " << to_string(compiled.major) << '.' << to_string(compiled.minor) << '.' << to_string(compiled.patch);

    SDL_version linked;
    SDL_GetVersion(&linked);
    cout << "SDL Linked with "  << to_string(linked.major) << '.' << to_string(linked.minor) << '.' << to_string(linked.patch);

    // setup SDL window
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // GL 3.1 + GLSL 130
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    
    auto window = SDL_CreateWindow("SDL+OpenGL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    if (!window) throw exception(SDL_GetError());

    return window;
}

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
        auto window = initSDLWindowWithOpenGL();
        auto gl_context = createSdlGlContext(window);
        initOpenGL();

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
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO(); (void)io;
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
            io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;;


            // Setup Dear ImGui style

            ImGui::StyleColorsDark();
            //ImGui::StyleColorsLight();

            // Setup Platform/Renderer backends
            ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
            ImGui_ImplOpenGL3_Init("#version 130");


            while (processSDLEvents()) {
                // Iniciar el frame de ImGui
                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplSDL2_NewFrame(window);
                ImGui::NewFrame();

                ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
                ImGui::DockSpace(dockspace_id, ImVec2(10.0f, 10.0f), ImGuiDockNodeFlags_PassthruCentralNode);

                // Crear ventanas o paneles que se pueden acoplar
                if (ImGui::Begin("Panel 1"), ImGuiWindowFlags_MenuBar) {
                    // Contenido del primer panel
                    ImGui::Text("Contenido del Panel 1");
                    ImGui::End();
                }

                if (ImGui::Begin("Panel 2"), ImGuiWindowFlags_MenuBar) {
                    // Contenido del segundo panel
                    ImGui::Text("Contenido del Panel 2");
                    ImGui::End();
                }


                const auto frame_start = steady_clock::now();
                engine.step(FDT);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
                engine.render();
                ImGui::Render();
                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
                SDL_GL_SwapWindow(window);
                const auto frame_end = steady_clock::now();
                const auto frame_duration = frame_end - frame_start;
                if (frame_duration < FDT) this_thread::sleep_for(FDT - frame_duration);
            }
        }

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();

        SDL_GL_DeleteContext(gl_context);
        SDL_DestroyWindow(window);
        SDL_Quit();

        return EXIT_SUCCESS;
    }
    catch(const exception& ex) {
        cerr << ex.what() << endl;
        return EXIT_FAILURE;
    }
}