#pragma once

#include <vector>
#include <map>

#include <GL/gl.h>

#include "../core/experiment.cpp"
#include "../core/helper.cpp"

class Exercise_2_31 : public Experiment {
    public:
        std::vector<float> ring;
        int segments = 25;
        float angle = 20;

        Exercise_2_31() : Experiment("e2.31") {}

        void init() {
            Color c(color_map::white);
            glClearColor(c.r, c.g, c.b, 1.0);

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glFrustum(-5, 5, -5, 5, 5, 1000);
            glTranslatef(0, 0, -60);
            ring = make_ring(40, 10, segments);
        }

        void input(SDL_Event events) {
            switch (events.key.keysym.sym) {
                case SDLK_UP: {
                    segments += 1;
                    if (segments > 100) {
                      segments = 100;
                      break;
                    }
                    ring = make_ring(40, 10, segments);
                    break;
                }

                case SDLK_DOWN: {
                    segments -= 1;
                    if (segments < 3) {
                      segments = 3;
                      break;
                    }
                    ring = make_ring(40, 10, segments);
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
            glTranslatef(0, 0, -5);

            color(color_map::green);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            draw_primitive(ring, GL_TRIANGLE_STRIP);

            color(color_map::black);
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            draw_primitive(ring, GL_TRIANGLE_STRIP);

            glFlush();
        }
};

