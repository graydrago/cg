#pragma once

#include <GL/gl.h>

#include "../core/experiment.cpp"
#include "../core/helper.cpp"

class Experiment_2_14 : public Experiment {
    public:
        Experiment_2_14() : Experiment("2.14") {}

        void init() {
            Color c(0x84CECD);
            glClearColor(c.r, c.g, c.b, 1.0);
            glOrtho(0, 100, 0, 100, -2, 5);
        }

        void render() {
            glClear(GL_COLOR_BUFFER_BIT);

            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glBegin(GL_TRIANGLE_STRIP);
            glVertex3f(10, 90, 0);
            glVertex3f(10, 10, 0);
            glVertex3f(35, 75, 0);
            glVertex3f(20, 20, 0);
            glVertex3f(90, 90, 0);
            glVertex3f(80, 40, 0);
            glEnd();
        }
};

