#pragma once

#include <iostream>

#include <vector>
#include <map>
#include <glm/glm.hpp>

#include <GL/gl.h>

#include "../core/experiment.cpp"
#include "../core/shape.cpp"
#include "../core/helper.cpp"
#include "../core/camera/RotationUtil.cpp"

class Exercise_3_4 : public Experiment {
    public:
        RotationUtil rotationUtil;
        std::vector<glm::vec3> m_shape;
        std::vector<glm::vec3> m_colors;
        std::vector<std::vector<unsigned int>> m_indeces;
        int m_primitives_count = 0;
        enum class render_type { fill, wire } m_render_type;

        Exercise_3_4() : Experiment("e3.4") {}

        void init() {
            Color c(color_map::white);
            glClearColor(c.r, c.g, c.b, 1.0);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glFrustum(-5, 5, -5, 5, 5, 1000);
            //glEnable(GL_DEPTH_TEST);
            m_render_type = render_type::fill;

            int id = 0;
            for (float i = 40; i > 0; i -= 5) {
                auto circle = Shape::circle(i, 50);
                auto color = random_color_v3();
                
                std::vector<unsigned int> indeces;

                m_shape.insert(m_shape.end(), circle.begin(), circle.end());
                for (unsigned long j = 0; j < circle.size(); ++j) {
                    m_colors.push_back(color);
                    indeces.push_back(id);
                    id++;
                }
                m_indeces.push_back(indeces);
                m_primitives_count += 1;
            }

            std::cout << "p count" << m_primitives_count << std::endl;
            std::cout << "colors" << m_colors.size() << std::endl;
            std::cout << "vertices" << m_shape.size() << std::endl;

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

            std::vector<unsigned int *> data;
            std::vector<int> count;
            for (auto &i : m_indeces) {
                data.push_back(i.data());
                count.push_back(i.size());
            }

            //color(color_map::lime);
            glColor3f(0, 0, 0);
            glMultiDrawElements(GL_TRIANGLE_FAN, count.data(), GL_UNSIGNED_INT, (const void **)(data.data()), m_primitives_count);
        }

};

