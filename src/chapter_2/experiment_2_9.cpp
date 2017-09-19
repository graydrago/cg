#pragma once

#include <GL/gl.h>

#include "../core/experiment.cpp"
#include "../core/helper.cpp"

class Experiment_2_9 : public Experiment {
    public:
        Experiment_2_9() : Experiment("2.9") {}

        void init() {
            Color c(0x84CECD);
            glClearColor(c.r, c.g, c.b, 1.0);
            glOrtho(0, 100, 0, 100, -2, 5);
        }

        void render() {
            glClear(GL_COLOR_BUFFER_BIT);

            color(color_map::red);
            glBegin(GL_POLYGON);
            glVertex3f(20, 20, 0);
            glVertex3f(80, 20, 0);
            glVertex3f(80, 80, 0);
            glVertex3f(20, 80, 0);
            glEnd();

            color(color_map::green);
            glBegin(GL_POLYGON);
            glVertex3f(40, 40, 0);
            glVertex3f(60, 40, 0);
            glVertex3f(60, 60, 0);
            glVertex3f(40, 60, 0);
            glEnd();
        }
};

