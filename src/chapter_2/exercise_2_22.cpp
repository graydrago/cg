#pragma once

#include <vector>
#include <cmath>

#include <GL/gl.h>

#include "../core/experiment.cpp"
#include "../core/helper.cpp"

class Exercise_2_22 : public Experiment {
    public:
        std::vector<color_map> m_colors;
        int m_segments;

        Exercise_2_22() : Experiment("e2.22") {}

        void init() {
            Color c(color_map::white);
            glClearColor(c.r, c.g, c.b, 1.0);
            glOrtho(-50, 50, -50, 50, -2, 5);
            m_segments = 100; 

            m_colors = {
                color_map::purple,
                color_map::yellow,
                color_map::blue,
                color_map::red,
                color_map::green,
            };
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

        void draw_circle(float r, float x, float y, float z) {
            glBegin(GL_POLYGON);
            for (int i = 0; i <= m_segments; ++i) {
                float _y = -std::sin(i*2*M_PI/m_segments) * r + y;
                float _x = std::cos(i*2*M_PI/m_segments) * r + x;
                glVertex3f(_x, _y, z);
            }
            glEnd();
        }

        void render() {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            int size = m_colors.size();
            int r_part = 20.f/size;
            float i = 1;

            glEnable(GL_DEPTH_TEST);
            for (auto c : m_colors) {
                color(c);
                draw_circle(r_part*i, -25, 0, (5.f-i)/5.f); 
                i += 1;
            }
            glDisable(GL_DEPTH_TEST);

            i = 1;
            for (auto c : m_colors) {
                color(c);
                draw_circle(r_part*i, 25, 0, (5.f-i)/5.f); 
                i += 1;
            }

            glFlush();
        }
};

