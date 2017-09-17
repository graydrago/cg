#pragma once

#include <GL/gl.h>

#include "../core/experiment.cpp"
#include "../core/app.cpp"

class Experiment_2_1 : public Experiment {
    public:
        Experiment_2_1() : Experiment("2.1") {}

        void render() {
            glClear(GL_COLOR_BUFFER_BIT);
            glPointSize(10);
            glColor3f(1, 1, 1);
            glBegin(GL_POINTS);
            glVertex3f(0, 0, 0);
            glVertex3f(0.5, 0, 0);
            glVertex3f(0.5, 0.5, 0);
            glEnd();
        }
};

