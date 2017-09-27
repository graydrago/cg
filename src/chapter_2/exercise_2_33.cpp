#pragma once

#include <vector>
#include <map>

#include <GL/gl.h>

#include "../core/experiment.cpp"
#include "../core/helper.cpp"

class Exercise_2_33 : public Experiment {
    public:
        std::vector<float> cone;
        float angle = 0;


        Exercise_2_33() : Experiment("e2.33") {}

        std::vector<float> make_slide(int segments = 10) {
            std::vector<float> points;
            points.reserve((25*3 + 2*3) * 2);
            float z = 10;
            float x_offset = 20;

            points.push_back(-40 + x_offset);
            points.push_back(0);
            points.push_back(-z);
            points.push_back(-40 + x_offset);
            points.push_back(0);
            points.push_back(z);

            for (int i = -segments; i <= 0; ++i) {
                float x = 40.f * i / segments;
                float y = 0.015*x*x + 10;
                x += x_offset;
                points.push_back(x);
                points.push_back(y);
                points.push_back(-z);
                points.push_back(x);
                points.push_back(y);
                points.push_back(z);
            }

            points.push_back(0 + x_offset);
            points.push_back(0);
            points.push_back(-z);
            points.push_back(0 + x_offset);
            points.push_back(0);
            points.push_back(z);

            return points;
        }

        void init() {
            Color c(color_map::white);
            glClearColor(c.r, c.g, c.b, 1.0);

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glFrustum(-5, 5, -5, 5, 5, 1000);
            glTranslatef(0, 0, -60);
            cone = make_slide();
        }

        void input(SDL_Event events) {
            switch (events.key.keysym.sym) {
                case SDLK_LEFT: {
                    angle -= 3;
                    break;
                }

                case SDLK_RIGHT: {
                    angle += 3;
                    break;
                }

            }
        }

        void render() {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glRotatef(angle, 0, 1, 0);
            glTranslatef(0, -30, 0);

            color(color_map::green);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            draw_primitive(cone, GL_TRIANGLE_STRIP);

            color(color_map::black);
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            draw_primitive(cone, GL_TRIANGLE_STRIP);

            glFlush();
        }
};

