#pragma once

#include <string>
#include <SDL2/SDL.h>

#include "app.cpp"

class Experiment {
    private:
        std::string m_name;

    public:
        Experiment(std::string name) : m_name(name) {};
        virtual ~Experiment() { SDL_Log("Destroyed: %s", m_name.c_str()); };
        virtual void init() {};
        virtual void update(double) {};
        virtual void render() {};
        virtual void run() {};
};


