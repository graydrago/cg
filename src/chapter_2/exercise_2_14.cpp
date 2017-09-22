#pragma once

#include <vector>
#include <cmath>

#include <GL/gl.h>

#include "../core/experiment.cpp"
#include "../core/helper.cpp"

class Exercise_2_14 : public Experiment {
    public:
        Exercise_2_14() : Experiment("e2.14") {}

        void init() {
            Color c(color_map::white);
            glClearColor(c.r, c.g, c.b, 1.0);
            glOrtho(0, 100, 0, 100, -2, 5);
        }

        void render() {
            glClear(GL_COLOR_BUFFER_BIT);
            
            for (int id = 0; id < 2; ++id) {
                for (int i = 0; i < 2; ++i) {
                    if (i == 0) {
                        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                        color(0x84CECD);
                    }
                    if (i == 1) {
                        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                        color(color_map::black);
                    }
                    glBegin(GL_TRIANGLE_FAN);
                    glVertex3f(10, 10, 0);
                    glVertex3f(10, 90, 0);
                    glVertex3f(20, 80, 0);
                    glVertex3f(20, 20, 0);
                    glVertex3f(80, 20, 0);
                    glVertex3f(90, 10, 0);
                    glEnd();

                    glBegin(GL_TRIANGLE_FAN);
                    glVertex3f(90, 90, 0);
                    glVertex3f(10, 90, 0);
                    glVertex3f(20, 80, 0);
                    glVertex3f(80, 80, 0);
                    glVertex3f(80, 20, 0);
                    glVertex3f(90, 10, 0);
                    glEnd();
                }
            }
        }
};

