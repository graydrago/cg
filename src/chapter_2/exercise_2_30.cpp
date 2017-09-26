#pragma once

#include <vector>
#include <map>

#include <GL/gl.h>

#include "../core/experiment.cpp"
#include "../core/helper.cpp"

class Exercise_2_30 : public Experiment {
    public:
        std::vector<float> disk;
        std::vector<GLuint> draw_types;
        std::map<GLuint, color_map> colors;

        Exercise_2_30() : Experiment("e2.30") {}

        void init() {
            Color c(color_map::white);
            glClearColor(c.r, c.g, c.b, 1.0);

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(-50, 50, -50, 50, -5, 5);
            disk = make_disc(7, 15, 32);

            draw_types = {GL_FILL};
            colors = {
                std::make_pair(GL_FILL, color_map::green),
                std::make_pair(GL_LINE, color_map::black),
            };
        }

        void input(SDL_Event events) {
            if (events.key.keysym.sym == SDLK_SPACE) {
                if (draw_types.size() == 1) {
                    draw_types = {GL_FILL, GL_LINE};
                } else {
                    draw_types = {GL_FILL};
                }
            }
        }

        void render() {

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glTranslatef(0, 0, -5);
            for (auto type : draw_types) {
                color(colors[type]);
                glPolygonMode(GL_FRONT_AND_BACK, type);
                glPushMatrix();
                glTranslatef(0, 11, 0);
                draw_primitive(disk, GL_TRIANGLE_STRIP);
                glPopMatrix();

                glPushMatrix();
                glTranslatef(0, -11, 0);
                draw_primitive(disk, GL_TRIANGLE_STRIP);
                glPopMatrix();
                //glBegin(GL_TRIANGLE_STRIP);
                //glEnd();
            }

            glFlush();
        }
};

