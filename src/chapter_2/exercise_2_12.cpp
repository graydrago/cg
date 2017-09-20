#pragma once

#include <GL/gl.h>

#include "../core/experiment.cpp"
#include "../core/helper.cpp"

class Exercise_2_12 : public Experiment {
    public:
        Exercise_2_12() : Experiment("e2.12") {}

        void init() {
            Color c(color_map::white);
            glClearColor(c.r, c.g, c.b, 1.0);
            glOrtho(0, 100, 0, 100, -2, 5);
        }

        void render() {
            glClear(GL_COLOR_BUFFER_BIT);

            for (int i = 0; i < 2; ++i) {
                if (i == 0) {
                    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                    color(0x84CECD);
                }
                if (i == 1) {
                    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                    color(color_map::black);
                }

                /**
                 * 0       2       4       6       8       10   evens
                 * *-------*-------*-------*-------*-------*
                 *  \     / \     / \     / \     / \     /
                 *   \   /   \   /   \   /   \   /   \   /
                 *    \ /     \ /     \ /     \ /     \ /
                 *     *-------*-------*-------*-------*
                 *     1       3       5       7       9        odds
                 **/
                glBegin(GL_TRIANGLE_STRIP);
                glVertex3f(30, 70, 0); // 0
                glVertex3f(20, 20, 0); // 1
                glVertex3f(30, 30, 0); // 2
                glVertex3f(80, 20, 0); // 3
                glVertex3f(70, 30, 0); // 4
                glVertex3f(80, 80, 0); // 5
                glVertex3f(70, 70, 0); // 6
                glVertex3f(20, 80, 0); // 7
                glVertex3f(30, 70, 0); // 8
                glVertex3f(20, 20, 0); // 9
                glEnd();
            }
        }
};

