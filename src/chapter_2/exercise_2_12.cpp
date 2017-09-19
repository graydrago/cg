#pragma once

#include <GL/gl.h>

#include "../core/experiment.cpp"
#include "../core/helper.cpp"

class Exercise_2_12 : public Experiment {
    public:
        Exercise_2_12() : Experiment("e2.12") {}

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
                glVertex3f(10, 90, 0);
                glVertex3f(10, 10, 0);
                glVertex3f(35, 75, 0);
                glVertex3f(20, 20, 0);
                glVertex3f(90, 90, 0);
                glVertex3f(80, 40, 0);
                glEnd();
            }
        }
};

