#include <iostream>
#include <memory>
#include <cstring>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <thread>

#include "core/app.cpp"
#include "core/experiment.cpp"
#include "core/switcher.cpp"

int main(int argc, char *argv[]) {
    std::unique_ptr<Experiment> experiment;
    selectExperiment("e3.2", experiment);
    std::string DEFAULT_TITLE = "CG";

    for (int i = 0; i < argc; ++i) {
        SDL_Log("%s", argv[i]);
    }

    if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
        SDL_LogCritical(SDL_LOG_CATEGORY_SYSTEM, "%s", SDL_GetError());
        return 1;
    }

    auto deleter = [](SDL_Window *w){ SDL_DestroyWindow(w); };
    auto make_window = [&DEFAULT_TITLE]() -> SDL_Window* {
        return SDL_CreateWindow(
               DEFAULT_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
               768, 768,
               SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    };
    std::unique_ptr<SDL_Window, decltype(deleter)> window(make_window(), deleter);
    if (window == nullptr) {
        SDL_LogCritical(SDL_LOG_CATEGORY_SYSTEM, "%s", SDL_GetError());
        return 1;
    }

    SDL_GLContext ctx = SDL_GL_CreateContext(window.get());
    if (ctx == NULL) {
        SDL_LogCritical(SDL_LOG_CATEGORY_SYSTEM, "%s", SDL_GetError());
        return 1;
    }

    glewInit();

    SDL_Event events;
    bool play = true;
    glClearColor(0, 0, 0, 1);

    experiment->init();
    Uint32 start_time = SDL_GetTicks();
    std::string text;
    SDL_StopTextInput();
    while (play) {
        while (SDL_PollEvent(&events)) {
            switch (events.type) {
                case SDL_QUIT:
                {
                    play = false;
                    break;
                }

                case SDL_TEXTINPUT:
                {
                    if (SDL_IsTextInputActive()) {
                        text += events.text.text;
                        std::string greating_string = ":" + text;
                        SDL_SetWindowTitle(window.get(), greating_string.c_str());
                    }
                    break;
                }

                case SDL_KEYDOWN:
                {
                    if (SDL_IsTextInputActive()) {
                        if (events.key.keysym.sym == SDLK_RETURN) {
                            SDL_StopTextInput();
                            selectExperiment(text, experiment);
                            experiment->init();
                            text = DEFAULT_TITLE;
                            SDL_SetWindowTitle(window.get(), text.c_str());
                        } else if (events.key.keysym.sym == SDLK_BACKSPACE) {
                            if (text.size() > 0) {
                                text.resize(text.size() - 1);
                            }
                            std::string greating_string = ":" + text;
                            SDL_SetWindowTitle(window.get(), greating_string.c_str());
                        }
                        break;
                    }

                    if (events.key.keysym.sym == SDLK_q || events.key.keysym.sym == SDLK_ESCAPE) {
                        play = false;
                    }

                    if ((events.key.keysym.sym == SDLK_BACKQUOTE) ||
                        (events.key.keysym.sym == SDLK_SEMICOLON && events.key.keysym.mod == KMOD_LSHIFT))
                    {
                        text = "";
                        std::string greating_string = ":" + text;
                        SDL_SetWindowTitle(window.get(), greating_string.c_str());
                        SDL_StartTextInput();
                    }

                    break;
                }
            }
            experiment->input(events);
        }

        Uint32 current_time = SDL_GetTicks();
        double elapsed = (current_time - start_time) * 0.001;
        start_time = current_time;

        int window_w = 0;
        int window_h = 0;
        SDL_GetWindowSize(window.get(), &window_w, &window_h);
        glViewport(0, 0, window_w, window_h);

        experiment->update(elapsed);
        experiment->render();

        SDL_GL_SwapWindow(window.get());
    }

    SDL_GL_DeleteContext(ctx);
    return 0;
}
