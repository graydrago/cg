#pragma once

#include <GL/gl.h>

#include "../core/experiment.cpp"
#include "../core/helper.cpp"

class Exercise_2_13 : public Experiment {
    public:
        Exercise_2_13() : Experiment("e2.13") {}

        void init() {
            Color c(0x84CECD);
            glClearColor(c.r, c.g, c.b, 1.0);
            glOrtho(0, 100, 0, 100, -2, 5);
        }

        void render() {
            glClear(GL_COLOR_BUFFER_BIT);

            for (int i = 0; i < 2; ++i) {
                if (i == 0) {
                    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                    color(color_map::white);
                }
                if (i == 1) {
                    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                    color(color_map::black);
                }
                glBegin(GL_TRIANGLE_STRIP);
                glVertex3f(10, 80, 0); // 0
                glVertex3f(10, 90, 0); // 1 
                glVertex3f(30, 80, 0); // 2
                glVertex3f(40, 90, 0); // 3
                glVertex3f(30, 10, 0); // 4
                glVertex3f(40, 20, 0); // 5
                glVertex3f(70, 10, 0); // 6
                glVertex3f(60, 20, 0); // 7
                glVertex3f(70, 80, 0); // 8
                glVertex3f(60, 90, 0); // 9
                glVertex3f(90, 80, 0); // 10
                glVertex3f(90, 90, 0); // 11
                glEnd();
            }
        }
};

