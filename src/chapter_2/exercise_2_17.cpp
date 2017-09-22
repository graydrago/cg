#pragma once

#include <vector>
#include <cmath>

#include <GL/gl.h>

#include "../core/experiment.cpp"
#include "../core/helper.cpp"

class Exercise_2_17 : public Experiment {
    public:
        int m_color;
        int m_segments;

        Exercise_2_17() : Experiment("e2.17") {}

        void init() {
            Color c(color_map::white);
            glClearColor(c.r, c.g, c.b, 1.0);
            glOrtho(-50, 50, -50, 50, -2, 5);
            m_color = 0x84CECD;
            m_segments = 100; 
            float line_width[2];
            glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, line_width);
            glLineWidth(line_width[1]);
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

        void render() {
            glClear(GL_COLOR_BUFFER_BIT);
            glBegin(GL_LINE_STRIP);
            color(color_map::red);
            for (int i = 0; i <= m_segments; ++i) {
              float ratio_ = (float)(i + m_segments)/ (float)(m_segments + m_segments);
              float y = -std::sin(i*6*M_PI/m_segments) * ratio_ * 40.f;
              float x = std::cos(i*6*M_PI/m_segments) * ratio_ * 40.f;
              glVertex3f(x, y, 0);
            }
            glEnd();
        }
};

