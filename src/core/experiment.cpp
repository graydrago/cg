#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <GL/gl.h>

#include "app.cpp"

class Experiment {
    private:
        std::string m_name;
        float m_elapsed;

    public:
        Experiment(std::string name) : m_name(name) {
            SDL_Log("Created: %s", name.c_str());
        };
        virtual ~Experiment() { SDL_Log("Destroyed: %s", m_name.c_str()); };
        virtual void init() {};
        virtual void input(SDL_Event) {};
        virtual void update(double) {};
        virtual void render() {};
        virtual void run() {};
};


