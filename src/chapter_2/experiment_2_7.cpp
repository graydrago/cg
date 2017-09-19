#pragma once

#include <GL/gl.h>

#include "../core/experiment.cpp"
#include "../core/helper.cpp"

class Experiment_2_7 : public Experiment {
    public:
        Experiment_2_7() : Experiment("2.7") {}

        void init() {
            glClearColor(132.f/255.f, 205.f/255.f, 206.f/255.f, 1.0);
            glOrtho(0, 100, 0, 100, -2, 5);
        }

        void render() {
            glClear(GL_COLOR_BUFFER_BIT);

            glBegin(GL_POLYGON);
            color(color_map::green);
            glVertex3f(20, 20, 0);
            color(color_map::red);
            glVertex3f(80, 20, 0);
            color(color_map::blue);
            glVertex3f(80, 80, 0);
            color(color_map::yellow);
            glVertex3f(20, 80, 0);
            glEnd();
        }
};

