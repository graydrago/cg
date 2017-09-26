#pragma once

#include <vector>
#include <map>

#include <GL/gl.h>

#include "../core/experiment.cpp"
#include "../core/helper.cpp"

class Exercise_2_32 : public Experiment {
    public:
        std::vector<float> cone;
        int segments = 8;
        float angle = 20;
        float radius = 20;
        float height = 30;

        Exercise_2_32() : Experiment("e2.32") {}

        void init() {
            Color c(color_map::white);
            glClearColor(c.r, c.g, c.b, 1.0);

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glFrustum(-5, 5, -5, 5, 5, 1000);
            glTranslatef(0, 0, -60);
            cone = make_cone(radius, height, segments);
        }

        void input(SDL_Event events) {
            switch (events.key.keysym.sym) {
                case SDLK_UP: {
                    segments += 1;
                    if (segments > 100) {
                      segments = 100;
                      break;
                    }
                    cone = make_cone(radius, height, segments);
                    break;
                }

                case SDLK_DOWN: {
                    segments -= 1;
                    if (segments < 3) {
                      segments = 3;
                      break;
                    }
                    cone = make_cone(radius, height, segments);
                    break;
                }

                case SDLK_LEFT: {
                    angle -= 1;
                    break;
                }

                case SDLK_RIGHT: {
                    angle += 1;
                    break;
                }

            }
        }

        void render() {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glRotatef(angle, 0, 1, 0);
            glTranslatef(0, -10, 0);
            glScalef(1, -1, 1);

            color(color_map::green);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            draw_primitive(cone, GL_TRIANGLE_FAN);

            color(color_map::black);
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            draw_primitive(cone, GL_TRIANGLE_FAN);

            glFlush();
        }
};

