#pragma once

#include <vector>

#include <GL/gl.h>

#include "../core/experiment.cpp"
#include "../core/helper.cpp"

class Exercise_2_27 : public Experiment {
    public:
        std::vector<float> m_points;

        Exercise_2_27() : Experiment("e2.27") {}

        void init() {
            Color c(color_map::white);
            glClearColor(c.r, c.g, c.b, 1.0);
            m_points = make_sin(6*M_PI, 2*M_PI, 1, 1000);

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glFrustum(-5, 5, -5, 5, 5, 100);
        }

        void render() {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            color(color_map::red);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glTranslatef(0, 0, -7);

            glPushMatrix();
            glTranslatef(-7, 0, 0);
            draw_primitive(m_points, GL_LINE_STRIP);
            glPopMatrix();

            glFlush();
        }
};

