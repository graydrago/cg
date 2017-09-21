#pragma once

#include <vector>
#include <cmath>

#include <GL/gl.h>

#include "../core/experiment.cpp"
#include "../core/helper.cpp"

class Experiment_2_18 : public Experiment {
    public:
        Experiment_2_18() : Experiment("2.18") {}

        std::vector<Color> colors;
        int segments;

        void init() {
            Color c(color_map::white);
            glClearColor(c.r, c.g, c.b, 1.0);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(-50, 50, -50, 50, -2, 5);

            colors.reserve(segments);
            segments = 20;
            for (int i = 0; i < 100; ++i) colors.push_back(get_random_color());

            float line_width[2];
            glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, line_width);
            glLineWidth(line_width[1]);
        }

        void input(SDL_Event events) {
            if (events.key.keysym.sym == SDLK_UP) {
              segments += 1;
              if (segments > 100) segments = 100;
            }
            if (events.key.keysym.sym == SDLK_DOWN) {
                segments -= 1;
                if (segments < 3) segments = 3;
            }
        }

        void render() {
            glClear(GL_COLOR_BUFFER_BIT);

            float radius{40.f};
            glBegin(GL_LINE_LOOP);
            for (int i = 0; i < segments; ++i) {
                float y = std::sin(i*2*M_PI/segments) * radius;
                float x = std::cos(i*2*M_PI/segments) * radius;
                color(colors[i]);
                glVertex3f(x, y, 0);
            }
            glEnd();
        }
};

