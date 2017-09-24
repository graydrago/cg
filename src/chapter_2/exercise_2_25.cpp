#pragma once

#include <vector>

#include <GL/gl.h>

#include "../core/experiment.cpp"
#include "../core/helper.cpp"

class Exercise_2_25 : public Experiment {
    public:
        std::vector<float> m_points;
        int m_segments;

        Exercise_2_25() : Experiment("e2.25") {}

        void init() {
            Color c(color_map::white);
            glClearColor(c.r, c.g, c.b, 1.0);
            m_points = make_helix(10, 2, 5, 25);

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glFrustum(-5, 5, -5, 5, 5, 100);
        }

        void render() {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            color(color_map::red);
            glPointSize(10);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glTranslatef(0, 0, -31);

            glPushMatrix();
            glTranslatef(-7, 0, 0);
            draw_primitive(m_points, GL_LINE_STRIP);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(7, 10, 13);
            glRotatef(90, 1, 0, 0);
            draw_primitive(m_points, GL_LINE_STRIP);
            glPopMatrix();

            glFlush();
        }
};

