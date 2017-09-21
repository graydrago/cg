#pragma once

#include <GL/gl.h>

#include "../core/experiment.cpp"
#include "../core/helper.cpp"

class Experiment_2_17 : public Experiment {
    public:
        Experiment_2_17() : Experiment("2.17") {}

        void init() {
            Color c(color_map::white);
            glClearColor(c.r, c.g, c.b, 1.0);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(0, 100, 0, 100, -2, 5);
        }

        void render() {
            glClear(GL_COLOR_BUFFER_BIT);

            auto first_pylygon = [](){
                color(0x84CECD);
                glScalef(0.5, 0.5, 1);
                glBegin(GL_POLYGON);
                glVertex3f(20, 20, 0);
                glVertex3f(80, 20, 0);
                glVertex3f(40, 40, 0);
                glVertex3f(20, 80, 0);
                glEnd();
            };

            auto second_pylygon = [](){
                color(0x84CECD);
                glScalef(0.5, 0.5, 1);
                glBegin(GL_POLYGON);
                glVertex3f(80, 20, 0);
                glVertex3f(40, 40, 0);
                glVertex3f(20, 80, 0);
                glVertex3f(20, 20, 0);
                glEnd();
            };

            glMatrixMode(GL_MODELVIEW);

            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glLoadIdentity();
            glTranslatef(0, 40, 0);
            first_pylygon();

            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glLoadIdentity();
            glTranslatef(40, 40, 0);
            first_pylygon();

            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glLoadIdentity();
            glTranslatef(0, 0, 0);
            second_pylygon();

            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glLoadIdentity();
            glTranslatef(40, 0, 0);
            second_pylygon();

            glFlush();
        }
};

