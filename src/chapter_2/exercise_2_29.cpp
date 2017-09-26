#pragma once

#include <vector>
#include <map>

#include <GL/gl.h>

#include "../core/experiment.cpp"
#include "../core/helper.cpp"

class Exercise_2_29 : public Experiment {
    public:

        Exercise_2_29() : Experiment("e2.29") {}

        void init() {
            Color c(color_map::white);
            glClearColor(c.r, c.g, c.b, 1.0);

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(-10, 90, -10, 90, -5, 5);
        }

        void render() {
            std::vector<GLuint> draw_types{GL_FILL, GL_LINE};
            std::map<GLuint, color_map> colors{
                std::make_pair(GL_FILL, color_map::green),
                std::make_pair(GL_LINE, color_map::black),
            };

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glTranslatef(0, 0, -5);
            for (auto type : draw_types) {
                color(colors[type]);
                glPolygonMode(GL_FRONT_AND_BACK, type);
                glBegin(GL_TRIANGLES);

                glVertex3f(0, 0, 0);
                glVertex3f(10, 0, 0);
                glVertex3f(20, 40, 0);

                glVertex3f(20, 40, 0);
                glVertex3f(10, 0, 0);
                glVertex3f(30, 40, 0);

                glVertex3f(30, 40, 0);
                glVertex3f(25, 30, 0);
                glVertex3f(50, 0, 0);

                glVertex3f(50, 0, 0);
                glVertex3f(25, 30, 0);
                glVertex3f(40, 0, 0);

                glVertex3f(20, 20, 0);
                glVertex3f(15, 10, 0);
                glVertex3f(30, 20, 0);

                glVertex3f(30, 20, 0);
                glVertex3f(15, 10, 0);
                glVertex3f(35, 10, 0);

                glEnd();
            }

            glFlush();
        }
};

