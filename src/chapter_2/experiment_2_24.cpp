#pragma once

#include <vector>
#include <cmath>

#include <GL/gl.h>

#include "../core/experiment.cpp"
#include "../core/helper.cpp"

class Experiment_2_24 : public Experiment {
    public:
        std::vector<float> m_hsphere;
        float m_dir_y;
        float m_dir_x;
        float m_angle_x;
        float m_angle_y;

        Experiment_2_24() : Experiment("2.24") {}

        void init() {
            Color c(color_map::white);
            glClearColor(c.r, c.g, c.b, 1.0);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glFrustum(-5, 5, -5, 5, 5, 1000);
            glPointSize(4);
            glEnable(GL_DEPTH_TEST);
            m_hsphere = make_hemisphere();
            m_dir_x = 0;
            m_dir_y = 0;
            m_angle_x = 0;
            m_angle_y = 0;
        }

        void input(SDL_Event events) {
            switch (events.type) {
                case SDL_KEYDOWN: {
                    switch (events.key.keysym.sym) {
                        case SDLK_LEFT: m_dir_y = -1; break;
                        case SDLK_RIGHT: m_dir_y = 1; break;
                        case SDLK_UP: m_dir_x = -1; break;
                        case SDLK_DOWN: m_dir_x = 1; break;
                    }
                    break;
                }

                case SDL_KEYUP: {
                    switch (events.key.keysym.sym) {
                        case SDLK_LEFT: m_dir_y = 0; break;
                        case SDLK_RIGHT: m_dir_y = 0; break;
                        case SDLK_UP: m_dir_x = 0; break;
                        case SDLK_DOWN: m_dir_x = 0; break;
                    }
                    break;
                }
            }
        }


        void update(double elapsed) {
            m_angle_x += m_dir_x * elapsed * 40.f;
            m_angle_y += m_dir_y * elapsed * 40.f;
        }


        void render() {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glTranslatef(0, 0, -60);
            glRotatef(m_angle_x, 1, 0, 0);
            glRotatef(m_angle_y, 0, 1, 0);

            color(color_map::green);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            draw_primitive(m_hsphere, GL_TRIANGLES);
            color(color_map::black);
            glScalef(1.001, 1.001, 1.001);
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            draw_primitive(m_hsphere, GL_TRIANGLES);
        }
};

