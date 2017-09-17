#pragma once

#include <GL/gl.h>

#include "../core/experiment.cpp"
#include "../core/app.cpp"

class Experiment_2_2 : public Experiment {
    public:
        Experiment_2_2() : Experiment("2.2") {}

        void render() {
            glClear(GL_COLOR_BUFFER_BIT);
            glPointSize(10);
            glColor3f(1, 1, 1);
            glBegin(GL_TRIANGLES);
            glVertex3f(0, 0, 0);
            glVertex3f(0.5, 0, 0);
            glVertex3f(0.5, 0.5, 0);
            glEnd();
        }
};

