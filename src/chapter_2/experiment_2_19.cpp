#pragma once

#include <vector>
#include <cmath>

#include <GL/gl.h>

#include "../core/experiment.cpp"
#include "../core/helper.cpp"

class Experiment_2_19 : public Experiment {
    public:
        Experiment_2_19() : Experiment("2.19") {}

        std::vector<Color> colors;
        int segments;

        void init() {
            Color c(color_map::white);
            glClearColor(c.r, c.g, c.b, 1.0);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(-50, 50, -5, 95, -2, 5);

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

            float t = -1;
            float step = 1.f/(static_cast<float>(segments)/2.f);
            int i = 0;
            glBegin(GL_LINE_STRIP);
            while (t <= 1.01) {
                float x = 50.f*t;
                float y = 95.f * pow(t, 2);
                color(colors[i++]);
                glVertex3f(x, y, 0);
                t += step;
            }
            glEnd();
        }
};

