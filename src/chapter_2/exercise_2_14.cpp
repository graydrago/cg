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
            Color c(0x84CECD);
            glClearColor(c.r, c.g, c.b, 1.0);
            glOrtho(0, 100, 0, 100, -2, 5);
        }

        void render() {
            glClear(GL_COLOR_BUFFER_BIT);

            std::vector<float> r_list{40.f, 20.f};
            std::vector<color_map> fill_colors{color_map::red, static_cast<color_map>(0x84CECD)};
            std::vector<color_map> stroke_colors{color_map::black, static_cast<color_map>(0x84CECD)};
            int segments = 100;
            for (int id = 0; id < 2; ++id) {
                for (int i = 0; i < 2; ++i) {
                    if (i == 0) {
                        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                        color(fill_colors[id]);
                    }
                    if (i == 1) {
                        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                        color(stroke_colors[id]);
                    }
                    glBegin(GL_TRIANGLE_FAN);
                    for (int i = 0; i < 100; ++i) {
                      float y = std::sin(i*2*M_PI/segments) * r_list[id] + 50;
                      float x = std::cos(i*2*M_PI/segments) * r_list[id] + 50;
                      glVertex3f(x, y, 0);
                    }
                    glEnd();
                }
            }
        }
};

