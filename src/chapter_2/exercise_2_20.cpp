#pragma once

#include <vector>
#include <cmath>

#include <GL/gl.h>

#include "../core/experiment.cpp"
#include "../core/helper.cpp"

class Exercise_2_20 : public Experiment {
    public:
        int m_color;
        int m_segments;

        Exercise_2_20() : Experiment("e2.20") {}

        void init() {
            Color c(color_map::white);
            glClearColor(c.r, c.g, c.b, 1.0);
            glOrtho(-50, 50, -50, 50, -2, 5);
            m_color = 0x84CECD;
            m_segments = 100; 
        }

        void input(SDL_Event events) {
            if (events.key.keysym.sym == SDLK_UP) {
                m_segments += 1;
                if (m_segments > 100) m_segments = 100;
            }
            if (events.key.keysym.sym == SDLK_DOWN) {
                m_segments -= 1;
                if (m_segments < 3) m_segments = 3;
            }
        }

        void draw_circle_annulus() {
            float inner_r = 20.f;
            float outer_r = 40.f;
            for (int i = 0; i <= m_segments; ++i) {
                float y = -std::sin(i*2*M_PI/m_segments) * outer_r;
                float x = std::cos(i*2*M_PI/m_segments) * outer_r;
                glVertex3f(x, y, 0);

                y = -std::sin(i*2*M_PI/m_segments) * inner_r;
                x = std::cos(i*2*M_PI/m_segments) * inner_r;
                glVertex3f(x, y, 0);
            }
        }

        void render() {
            glClear(GL_COLOR_BUFFER_BIT);

            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glBegin(GL_TRIANGLE_STRIP);
            color(color_map::green);
            draw_circle_annulus();
            glEnd();

            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glBegin(GL_TRIANGLE_STRIP);
            color(color_map::black);
            draw_circle_annulus();
            glEnd();
        }
};

