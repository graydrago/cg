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
        std::vector<glm::vec2> m_shape;
        std::vector<glm::vec2> m_line;
        std::vector<glm::vec2> m_circle;
        std::vector<glm::vec2> m_intersections;
        std::vector<unsigned int> m_intersections_id;
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
            m_circle = make_circle(300, 400, 400, 100);

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
                            m_line[0].x = events.button.x;
                            m_line[0].y = 768 - events.button.y;
                        } else {
                            m_line[1].x = events.button.x;
                            m_line[1].y = 768 - events.button.y;
                        }
                        update_intersections();
                    }
                    break;
                }

            }

            if (m_selected_point == 0) {
                m_line[0].x = events.button.x;
                m_line[0].y = 768 - events.button.y;
            } else {
                m_line[1].x = events.button.x;
                m_line[1].y = 768 - events.button.y;
            }
            update_intersections();
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

            color(color_map::blue);
            draw_primitive(m_intersections, GL_POINTS);

            draw_circle(m_circle);
        }


        void draw_circle(std::vector<glm::vec2> &points, GLenum type = GL_POINTS) {
            using namespace glm;
            vec2 start_segment = m_line[0];
            vec2 end_segment = m_line[1];
            auto a = normalize(start_segment - end_segment);
            a = vec2(a.y, -a.x); // line's right vector
            glBegin(type);
            for (auto p : points) {
                auto b = normalize(start_segment - p);
                auto d = dot(a, b);
                if (d > 0) {
                    color(color_map::aqua);
                } else {
                    color(color_map::maroon);
                }
                glVertex3f(p.x, p.y, 0);

            }
            glEnd();
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


        std::vector<glm::vec2> make_circle(float r = 1, float cx = 0, float cy = 0, int amount = 360) {
            constexpr auto end_point = M_PI * 2;
            auto step = end_point / amount;
            std::vector<glm::vec2> points;
            for (float i = 0; i <= end_point; i += step) {
                glm::vec2 p(r * cos(i) + cx, r * sin(i) + cy);
                points.push_back(p);
            }
            return points;
        }


        std::vector<glm::vec2> make_cave_polygon() {
            using namespace glm;
            std::vector<vec2> points;

            points.push_back(vec2(100, 100));
            points.push_back(vec2(350, 300));
            points.push_back(vec2(600, 100));
            points.push_back(vec2(600, 600));
            points.push_back(vec2(100, 600));

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


        std::vector<glm::vec2> get_line_by_id(std::vector<glm::vec2> &points, unsigned long id) {
            std::vector<glm::vec2> p;
            if (id >= (points.size() - 1)) {
                p.push_back(*(points.end() - 1));
                p.push_back(points[0]);
            } else {
                p.push_back(points[id]);
                p.push_back(points[id+1]);
            }
            return p;
        }


        std::vector<glm::vec2> make_line(float x1, float y1, float x2, float y2) {
            std::vector<glm::vec2> points;
            points.push_back(glm::vec2(x1, y1));
            points.push_back(glm::vec2(x2, y2));
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
        std::vector<glm::vec2> line_intersections(std::vector<glm::vec2> &line_a, std::vector<glm::vec2> &line_b) {
            std::vector<glm::vec2> points;
            float A1, A2;
            float B1, B2;
            float C1, C2;
            float x1 = line_a[0].x; float y1 = line_a[0].y;
            float x2 = line_a[1].x; float y2 = line_a[1].y;

            if (x1 == x2) x2 += 0.1;
            if (y1 == y2) y2 += 0.1;

            A1 = y2 - y1;
            B1 = x1 - x2;
            C1 = A1*x1 + B1*y1;

            float _x1 = line_b[0].x; float _y1 = line_b[0].y;
            float _x2 = line_b[1].x; float _y2 = line_b[1].y;

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
                    points.push_back(glm::vec2(x, y));
                }
            }

            return points;
        }


        void update_intersections() {
            m_intersections.clear();
            m_intersections_id.clear();
            for (unsigned int i = 0; i < m_shape.size(); ++i) {
                auto l = get_line_by_id(m_shape, i);
                std::vector<glm::vec2> intr = line_intersections(l, m_line);
                if (not intr.empty()) {
                    m_intersections_id.push_back(i);
                }
                m_intersections.insert(m_intersections.end(), intr.begin(), intr.end());
            }

            print_intersections_id(m_intersections_id);
        }


        void print_point(std::vector<float> &shape, unsigned long id) {
            std::cout << "x:" << shape[id] << " y:" << shape[id+1] << " z:" << shape[id+2] << std::endl;
        }


        void print_intersections_id(std::vector<unsigned int> &intersections_id) {
            using namespace std;
            cout << "intersections id: ";
            for (auto i : intersections_id) { cout << i << " "; }
            cout << endl;
        }
};

