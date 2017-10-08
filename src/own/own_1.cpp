#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <glm/glm.hpp>

#include <GL/gl.h>

#include "../core/experiment.cpp"
#include "../core/helper.cpp"

class Own_1 : public Experiment {
    public:
        std::vector<float> m_shape;
        std::vector<float> m_line;
        std::vector<float> m_intersections;
        int m_selected_point;

        Own_1() : Experiment("o1") {}

        void init() {
            Color c(color_map::white);
            glClearColor(c.r, c.g, c.b, 1.0);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(0, 767, 0, 767, 0, 100);
            glPointSize(9);
            //glEnable(GL_DEPTH_TEST);
            m_shape = make_cave_polygon();
            m_line = make_line(0, 200, 800, 800);
            m_selected_point = 0;

            update_intersections();
        }

        void input(SDL_Event events) {
            switch (events.type) {
                case SDL_KEYDOWN: {
                    switch (events.key.keysym.sym) {
                        case SDLK_1: m_selected_point = 0; break;
                        case SDLK_2: m_selected_point = 1; break;
                    }
                }
                case SDL_MOUSEBUTTONDOWN: {
                    if (events.button.button == SDL_BUTTON_LEFT) {
                        if (m_selected_point == 0) {
                            m_line[0] = events.button.x;
                            m_line[1] = 768 - events.button.y;
                        } else {
                            m_line[3] = events.button.x;
                            m_line[4] = 768 - events.button.y;
                        }
                        update_intersections();
                    }
                    break;
                }

            }
        }


        //void update(double elapsed) {
        //}


        void render() {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            color(color_map::green);
            draw_primitive(m_shape, GL_LINE_LOOP);

            color(color_map::red);
            draw_primitive(m_line, GL_LINES);

            auto line = get_line_by_id(m_shape, 0);
            color(color_map::purple);
            draw_primitive(line, GL_LINES);

            color(color_map::blue);
            draw_primitive(m_intersections, GL_POINTS);
        }


        std::vector<float> make_rectangle() {
            std::vector<float> points;

            points.push_back(100);
            points.push_back(100);
            points.push_back(  0);

            points.push_back(600);
            points.push_back(100);
            points.push_back(  0);

            points.push_back(600);
            points.push_back(600);
            points.push_back(  0);

            points.push_back(100);
            points.push_back(600);
            points.push_back(  0);

            return points;
        }


        std::vector<float> make_cave_polygon() {
            std::vector<float> points;

            points.push_back(100);
            points.push_back(100);
            points.push_back(  0);

            points.push_back(350);
            points.push_back(300);
            points.push_back(  0);

            points.push_back(600);
            points.push_back(100);
            points.push_back(  0);

            points.push_back(600);
            points.push_back(600);
            points.push_back(  0);

            points.push_back(100);
            points.push_back(600);
            points.push_back(  0);

            return points;
        }

        std::vector<float> get_line_by_id(std::vector<float> &points, unsigned long id) {
            std::vector<float> p;
            if (id >= (points.size()/3 - 1)) {
                p.insert(p.begin(), points.begin()+id*3, points.begin()+id*3+3);
                p.insert(p.begin(), points.begin(), points.begin()+3);
            } else {
                p.insert(p.begin(), points.begin()+id*3, points.begin()+id*3+6);
            }
            return p;
        }


        std::vector<float> make_line(float x1, float y1, float x2, float y2) {
            std::vector<float> points;

            points.push_back(x1);  // 0
            points.push_back(y1);  // 1
            points.push_back( 0);  // 2

            points.push_back(x2);  // 3
            points.push_back(y2);  // 4
            points.push_back( 0);  // 5

            return points;
        }

        // A = y2-y1
        // B = x1-x2
        // C = A*x1+B*y1
        //
        // A1x + B1y = C1
        // A2x + B2y = C2
        //
        // det = A1*B2 - A2*B1
        //
        // x = (B2*C1 - B1*C2)/det
        // y = (A1*C2 - A2*C1)/det
        std::vector<float> line_intersections(std::vector<float> &line_a, std::vector<float> &line_b) {
            std::vector<float> points;
            float A1, A2;
            float B1, B2;
            float C1, C2;
            float x1 = line_a[0]; float y1 = line_a[1];
            float x2 = line_a[3]; float y2 = line_a[4];

            if (x1 == x2) x2 += 0.1;
            if (y1 == y2) y2 += 0.1;

            A1 = y2 - y1;
            B1 = x1 - x2;
            C1 = A1*x1 + B1*y1;

            float _x1 = line_b[0]; float _y1 = line_b[1];
            float _x2 = line_b[3]; float _y2 = line_b[4];

            if (_x1 == _x2) _x2 += 0.1;
            if (_y1 == _y2) _y2 += 0.1;

            A2 = _y2 - _y1;
            B2 = _x1 - _x2;
            C2 = A2*_x1 + B2*_y1;

            float det = A1*B2 - A2*B1;
            if (det == 0) {
            } else {
                auto x = (B2*C1 - B1*C2) / det;
                auto y = (A1*C2 - A2*C1) / det;
                if (std::min(x1, x2) < x and std::max(x1, x2) > x and
                    std::min(y1, y2) < y and std::max(y1, y2) > y and
                    std::min(_x1, _x2) < x and std::max(_x1, _x2) > x and
                    std::min(_y1, _y2) < y and std::max(_y1, _y2) > y)
                {
                    points.push_back(x);
                    points.push_back(y);
                    points.push_back(0);
                }
            }

            return points;
        }


        void print_point(std::vector<float> &shape, unsigned long id) {
            std::cout << "x:" << shape[id] << " y:" << shape[id+1] << " z:" << shape[id+2] << std::endl;
        }


        void update_intersections() {
            m_intersections.clear();
            for (unsigned int i = 0; i < m_shape.size()/3; ++i) {
                auto l = get_line_by_id(m_shape, i);
                std::vector<float> intr = line_intersections(l, m_line);
                m_intersections.insert(m_intersections.end(), intr.begin(), intr.end());
            }
        }
};

