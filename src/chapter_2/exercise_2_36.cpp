#pragma once

#include <vector>
#include <map>

#include <GL/gl.h>

#include "../core/experiment.cpp"
#include "../core/helper.cpp"

class Exercise_2_36 : public Experiment {
    public:
        std::vector<float> m_shape;
        float m_dir_y = 0;
        float m_dir_x = 0;
        float m_angle_x = 0;
        float m_angle_y = 0;
        float m_radius = 40;
        float m_lat_segments = 32;
        float m_lon_segments = 16;
        enum class ShapeType {hemisphere, cake} m_shape_type;

        Exercise_2_36() : Experiment("e2.36") {}

        void init() {
            Color c(color_map::white);
            glClearColor(c.r, c.g, c.b, 1.0);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glFrustum(-5, 5, -5, 5, 5, 1000);
            glPointSize(4);
            glEnable(GL_DEPTH_TEST);
            m_shape_type = ShapeType::hemisphere;
            m_shape = make_shape();
        }

        void input(SDL_Event events) {
            switch (events.type) {
                case SDL_KEYDOWN: {
                    switch (events.key.keysym.sym) {
                        case SDLK_w: {
                            m_lat_segments += 2;
                            if (m_lat_segments > 100) m_lat_segments = 100;
                            m_shape = make_shape();
                            break;
                        }
                        case SDLK_s: {
                            m_lat_segments -= 2;
                            if (m_lat_segments < 4) m_lat_segments = 4;
                            m_shape = make_shape();
                            break;
                        }
                        case SDLK_a: {
                            m_lon_segments += 2;
                            if (m_lon_segments > 100) m_lon_segments = 100;
                            m_shape = make_shape();
                            break;
                        }
                        case SDLK_d: {
                            m_lon_segments -= 2;
                            if (m_lon_segments < 4) m_lon_segments = 4;
                            m_shape = make_shape();
                            break;
                        }
                        case SDLK_1: {
                            m_shape_type = ShapeType::hemisphere;
                            m_shape = make_shape();
                            break;
                        }
                        case SDLK_2: {
                            m_shape_type = ShapeType::cake;
                            m_shape = make_shape();
                            break;
                        }
                        case SDLK_LEFT: m_dir_y = -1; break;
                        case SDLK_RIGHT: m_dir_y = 1; break;
                        case SDLK_UP: m_dir_x = -1; break;
                        case SDLK_DOWN: m_dir_x = 1; break;
                    }
                    break;
                }

                case SDL_KEYUP: {
                    switch (events.key.keysym.sym) {
                        case SDLK_LEFT: m_dir_y = 0; break;
                        case SDLK_RIGHT: m_dir_y = 0; break;
                        case SDLK_UP: m_dir_x = 0; break;
                        case SDLK_DOWN: m_dir_x = 0; break;
                    }
                    break;
                }
            }
        }


        void update(double elapsed) {
            m_angle_x += m_dir_x * elapsed * 40.f;
            m_angle_y += m_dir_y * elapsed * 40.f;
        }


        void render() {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glTranslatef(0, 0, -60);
            glRotatef(m_angle_x, 1, 0, 0);
            glRotatef(m_angle_y, 0, 1, 0);

            color(color_map::green);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            draw_primitive(m_shape, GL_TRIANGLES);
            color(color_map::black);
            glScalef(1.001, 1.001, 1.001);
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            draw_primitive(m_shape, GL_TRIANGLES);
        }


        std::vector<float> make_shape() {
            std::vector<float> shape;
            switch (m_shape_type) {
              case ShapeType::hemisphere: shape = make_half_hemisphere(m_radius, m_lat_segments, m_lon_segments); break;
              case ShapeType::cake: shape = make_cake(m_radius, m_lat_segments, m_lon_segments); break;
            }
            return shape;
        }


        std::vector<float> make_half_hemisphere(float radius = 40, int latitude_segments = 32, int longitude_segments = 8) {
            using std::cos;
            using std::sin;

            std::vector<float> points;
            int half_latitude_segments = latitude_segments / 2;
            int half_longitude_segments = longitude_segments / 2;
            float lts = 2*M_PI/latitude_segments;
            float lns = M_PI*0.5/longitude_segments;

            for (int j = 0; j < half_longitude_segments; ++j) {
                for (int i = -half_latitude_segments; i < half_latitude_segments; ++i) {
                    // a
                    points.push_back(cos((j+1)*lns) * cos(i*lts) * radius);
                    points.push_back(sin((j+1)*lns) * radius);
                    points.push_back(cos((j+1)*lns) * sin(i*lts) * radius);
                    // b
                    points.push_back(cos(j*lns) * cos(i*lts) * radius);
                    points.push_back(sin(j*lns) * radius);
                    points.push_back(cos(j*lns) * sin(i*lts) * radius);
                    // c
                    points.push_back(cos((j+1)*lns) * cos((i+1)*lts) * radius);
                    points.push_back(sin((j+1)*lns) * radius);
                    points.push_back(cos((j+1)*lns) * sin((i+1)*lts) * radius);
                    // b
                    points.push_back(cos(j*lns) * cos(i*lts) * radius);
                    points.push_back(sin(j*lns) * radius);
                    points.push_back(cos(j*lns) * sin(i*lts) * radius);
                    // d
                    points.push_back(cos(j*lns) * cos((i+1)*lts) * radius);
                    points.push_back(sin(j*lns) * radius);
                    points.push_back(cos(j*lns) * sin((i+1)*lts) * radius);
                    // c
                    points.push_back(cos((j+1)*lns) * cos((i+1)*lts) * radius);
                    points.push_back(sin((j+1)*lns) * radius);
                    points.push_back(cos((j+1)*lns) * sin((i+1)*lts) * radius);
                }
            }
            return points;
        }


        std::vector<float> make_cake(float radius = 40, int latitude_segments = 4, int longitude_segments = 16) {
            using std::cos;
            using std::sin;

            std::vector<float> points;
            float lts = M_PI*0.2/latitude_segments;
            float lns = M_PI/longitude_segments;
            int half_latitude_segments = latitude_segments / 2;
            int half_longitude_segments = longitude_segments / 2;

            for (int j = 0; j < half_longitude_segments; ++j) {
                for (int i = -half_latitude_segments; i < half_latitude_segments; ++i) {
                    // a
                    points.push_back(cos((j+1)*lns) * cos(i*lts) * radius);
                    points.push_back(sin((j+1)*lns) * radius);
                    points.push_back(cos((j+1)*lns) * sin(i*lts) * radius);
                    // b
                    points.push_back(cos(j*lns) * cos(i*lts) * radius);
                    points.push_back(sin(j*lns) * radius);
                    points.push_back(cos(j*lns) * sin(i*lts) * radius);
                    // c
                    points.push_back(cos((j+1)*lns) * cos((i+1)*lts) * radius);
                    points.push_back(sin((j+1)*lns) * radius);
                    points.push_back(cos((j+1)*lns) * sin((i+1)*lts) * radius);
                    // b
                    points.push_back(cos(j*lns) * cos(i*lts) * radius);
                    points.push_back(sin(j*lns) * radius);
                    points.push_back(cos(j*lns) * sin(i*lts) * radius);
                    // d
                    points.push_back(cos(j*lns) * cos((i+1)*lts) * radius);
                    points.push_back(sin(j*lns) * radius);
                    points.push_back(cos(j*lns) * sin((i+1)*lts) * radius);
                    // c
                    points.push_back(cos((j+1)*lns) * cos((i+1)*lts) * radius);
                    points.push_back(sin((j+1)*lns) * radius);
                    points.push_back(cos((j+1)*lns) * sin((i+1)*lts) * radius);
                }
            }

            for (int j = 0; j < half_longitude_segments; ++j) {
                int i = -half_latitude_segments;
                // a
                points.push_back(cos(j*lns) * cos(i*lts) * radius);
                points.push_back(sin(j*lns) * radius);
                points.push_back(cos(j*lns) * sin(i*lts) * radius);
                // c
                points.push_back(0);
                points.push_back(0);
                points.push_back(0);
                // b
                points.push_back(cos((j+1)*lns) * cos(i*lts) * radius);
                points.push_back(sin((j+1)*lns) * radius);
                points.push_back(cos((j+1)*lns) * sin(i*lts) * radius);

                i = half_latitude_segments;
                // a
                points.push_back(cos(j*lns) * cos(i*lts) * radius);
                points.push_back(sin(j*lns) * radius);
                points.push_back(cos(j*lns) * sin(i*lts) * radius);
                // c
                points.push_back(0);
                points.push_back(0);
                points.push_back(0);
                // b
                points.push_back(cos((j+1)*lns) * cos(i*lts) * radius);
                points.push_back(sin((j+1)*lns) * radius);
                points.push_back(cos((j+1)*lns) * sin(i*lts) * radius);
            }

            

            return points;
        }
};

