#pragma once

#include <GL/gl.h>

#include "../core/experiment.cpp"

class Experiment_2_5 : public Experiment {
    public:
        Experiment_2_5() : Experiment("2.5") {}

        void init() {
            glClearColor(132.f/255.f, 205.f/255.f, 206.f/255.f, 1.0);
            glOrtho(0, 100*2, 0, 100*2, -2, 5);
        }

        void render() {
            glClear(GL_COLOR_BUFFER_BIT);
            glColor3f(1, 1, 1);

            glBegin(GL_POLYGON);
            glVertex3f(20, 20, 0);
            glVertex3f(80, 20, 0);
            glVertex3f(80, 80, 0);
            glVertex3f(20, 80, 0);
            glEnd();

            glBegin(GL_POLYGON);
            glVertex3f(20, 120, 5);
            glVertex3f(80, 120, 0);
            glVertex3f(80, 180, -10);
            glEnd();

            glBegin(GL_POLYGON);
            glVertex3f(120, 120, 0);
            glVertex3f(180, 120, 0);
            glVertex3f(180, 180, 0);
            glVertex3f(120, 180, 0);
            glEnd();
        }
};

