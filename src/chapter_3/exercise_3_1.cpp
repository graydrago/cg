#pragma once

#include <vector>
#include <map>
#include <glm/glm.hpp>

#include <GL/gl.h>

#include "../core/experiment.cpp"
#include "../core/helper.cpp"
#include "../core/camera/RotationUtil.cpp"

class Exercise_3_1 : public Experiment {
    public:
        RotationUtil rotationUtil;
        std::vector<glm::vec3> m_shape;
        std::vector<glm::vec3> m_colors;
        std::vector<unsigned int> m_indexes;
        enum class render_type { fill, wire } m_render_type;

        Exercise_3_1() : Experiment("e3.1") {}

        void init() {
            Color c(color_map::white);
            glClearColor(c.r, c.g, c.b, 1.0);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glFrustum(-5, 5, -5, 5, 5, 1000);
            glEnable(GL_DEPTH_TEST);
            m_shape = make_shape();
            m_render_type = render_type::fill;

            for (unsigned int i = 0; i < m_shape.size(); i++) {
                m_indexes.push_back(i);
            }

            for (unsigned int i = 0; i < m_shape.size()/3; i++) {
                auto c = random_color_v3();
                m_colors.push_back(c);
                m_colors.push_back(c);
                m_colors.push_back(c);
            }

            glEnableClientState(GL_VERTEX_ARRAY);
            glEnableClientState(GL_COLOR_ARRAY);

            glVertexPointer(3, GL_FLOAT, 0, m_shape.data());
            glColorPointer(3, GL_FLOAT, 0, m_colors.data());

            rotationUtil.m_pos.z = -100;
        }

        void input(SDL_Event events) {
            rotationUtil.input(events);

            switch (events.type) {
                case SDL_KEYDOWN: {
                    switch (events.key.keysym.sym) {
                        case SDLK_1: m_render_type = render_type::fill; break;
                        case SDLK_2: m_render_type = render_type::wire; break;
                    }
                }
            }
        }


        void update(double elapsed) {
            rotationUtil.update(elapsed);
        }


        void render() {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            rotationUtil.rotate();

            switch (m_render_type) {
                case render_type::fill: 
                    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                    break;
                case render_type::wire:
                    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                    break;
            }

            glBegin(GL_TRIANGLES);
                for (auto i : m_indexes) { glArrayElement(i); }
            glEnd();
            
            //for (float i = 0.5; i < 2; i += 0.1)  {
                //glScalef(i, i, i);
                //glDrawElements(GL_TRIANGLES, m_shape.size(), GL_UNSIGNED_INT, m_indexes.data());
            //}
        }


        // a -- c
        // |  / |
        // | /  |
        // b -- d
        //
        // abc bdc
        //
        // a = { j: 1, i: 0 }
        // b = { j: 0, i: 0 }
        // c = { j: 1, i: 1 }
        // d = { j: 0, i: 1 }
        std::vector<glm::vec3> make_shape() {
            using std::cos;
            using std::sin;

            float radius = 40;
            int latitude_segments = 32;
            int longitude_segments = 16;

            std::vector<glm::vec3> points;
            int half_latitude_segments = latitude_segments / 2;
            int half_longitude_segments = longitude_segments / 2;
            float lts = 2*M_PI/latitude_segments;
            float lns = M_PI/longitude_segments;

            for (int j = 0; j < half_longitude_segments; ++j) {
                for (int i = -half_latitude_segments; i < half_latitude_segments; ++i) {
                    glm::vec3 a { cos((j+1)*lns) * cos(i*lts) * radius,
                                  sin((j+1)*lns) * radius,
                                  cos((j+1)*lns) * sin(i*lts) * radius };
                    glm::vec3 b { cos(j*lns) * cos(i*lts) * radius,
                                  sin(j*lns) * radius,
                                  cos(j*lns) * sin(i*lts) * radius };
                    glm::vec3 c { cos((j+1)*lns) * cos((i+1)*lts) * radius,
                                  sin((j+1)*lns) * radius,
                                  cos((j+1)*lns) * sin((i+1)*lts) * radius };
                    glm::vec3 d { cos(j*lns) * cos((i+1)*lts) * radius,
                                  sin(j*lns) * radius,
                                  cos(j*lns) * sin((i+1)*lts) * radius };
                    points.push_back(a);
                    points.push_back(b);
                    points.push_back(c);
                    points.push_back(b);
                    points.push_back(d);
                    points.push_back(c);
                }
            }

            return points;
        };
};

