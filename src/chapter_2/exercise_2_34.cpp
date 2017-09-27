#pragma once

#include <vector>
#include <map>

#include <GL/gl.h>

#include "../core/experiment.cpp"
#include "../core/helper.cpp"

class Exercise_2_34 : public Experiment {
    public:
        std::vector<float> moon;
        float radius = 10;
        enum class state { first, second } animation_state = state::first;

        Exercise_2_34() : Experiment("e2.34") {}

        std::vector<float> make_moon(int segments = 20, float left_radius = 10, float right_radius = 10) {
            std::vector<float> points;
            points.reserve(25 * 2 * 3);

            for (int i = 0; i < segments; ++i) {
                float x = std::cos(M_PI*i/segments);
                float y = std::sin(M_PI*i/segments);
                points.push_back(-y * left_radius);
                points.push_back(x * 10.f);
                points.push_back(0);
                points.push_back(y * right_radius);
                points.push_back(x * 10.f);
                points.push_back(0);
            }

            return points;
        }

        void init() {
            Color c(color_map::white);
            glClearColor(c.r, c.g, c.b, 1.0);

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glFrustum(-5, 5, -5, 5, 5, 1000);
            glTranslatef(0, 0, -60);
            moon = make_moon();
        }

        void render() {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glScalef(3, 3, 3);

            switch (animation_state) {
                case state::first: {
                    radius -= 0.07;
                    if (radius < -10.f) {
                      radius = 10.f;
                      animation_state = state::second;
                      break;
                    }
                    moon = make_moon(25, 10.f, radius);
                    break;
                }
                case state::second: {
                    radius -= 0.07;
                    if (radius < -10.f) {
                      radius = 10.f;
                      animation_state = state::first;
                      break;
                    }
                    moon = make_moon(25, -radius, 10.f);
                    break;
                }
            }


            color(color_map::yellow);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            draw_primitive(moon, GL_TRIANGLE_STRIP);

            //color(color_map::black);
            //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            //draw_primitive(moon, GL_TRIANGLE_STRIP);

            glFlush();
        }
};

