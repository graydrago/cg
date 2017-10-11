#pragma once

#include <string>
#include <random>
#include <cassert>
#include <GL/gl.h>
#include <glm/glm.hpp>

static std::mt19937 gen(time(0)); 
static std::uniform_real_distribution<> urd(0, 1); 


enum class color_map : int{
    white = 0xffffff,
    navy = 0x001f3f,
    blue = 0X0074d9,
    aqua = 0X7fdbff,
    teal = 0X39cccc,
    olive = 0X3d9970,
    green = 0X2ecc40,
    lime = 0X01ff70,
    yellow = 0Xffdc00,
    orange = 0Xff851b,
    red = 0Xff4136,
    maroon = 0X85144B,
    fuchsia = 0Xf012be,
    purple = 0Xb10dc9,
    black = 0X111111,
    gray = 0Xaaaaaa,
    silver = 0Xdddddd,
};


struct Color {
  float r;
  float g;
  float b;
  Color(int hex) {
    r = static_cast<float>((hex >> 16) & 255)/255.f;
    g = static_cast<float>((hex >> 8) & 255)/255.f;
    b = static_cast<float>(hex & 255)/255.f;
  };
  Color(float _r, float _g, float _b) : r(_r), g(_g), b(_b) {};
  Color(color_map c) : Color(static_cast<int>(c)) {};
};


void color(Color c) { glColor3f(c.r, c.g, c.b); }
void color(int hex) { Color c(hex); glColor3f(c.r, c.g, c.b); }
void color(color_map c) { color(static_cast<int>(c)); }
void random_color() { glColor3f(urd(gen), urd(gen), urd(gen)); }
Color get_random_color() { return Color(urd(gen), urd(gen), urd(gen)); }


std::vector<float> make_circle(float radius = 40.f, int segments = 50) {
    std::vector<float> points;
    points.reserve(segments * 3);
    for (int i = 0; i <= segments; ++i) {
        float y = std::sin(i*2*M_PI/segments) * radius;
        float x = std::cos(i*2*M_PI/segments) * radius;
        points.push_back(x);
        points.push_back(y);
        points.push_back(0);
    }
    return points;
}


std::vector<float> make_disc(float outer_r = 40.f, float inner_r = 20.f, int segments = 50) {
    std::vector<float> points;
    points.reserve(segments * 3 * 2);
    for (int i = 0; i <= segments; ++i) {
        float y = std::sin(i*2*M_PI/segments) * outer_r;
        float x = std::cos(i*2*M_PI/segments) * outer_r;
        points.push_back(x);
        points.push_back(y);
        points.push_back(0);

        y = std::sin(i*2*M_PI/segments) * inner_r;
        x = std::cos(i*2*M_PI/segments) * inner_r;
        points.push_back(x);
        points.push_back(y);
        points.push_back(0);
    }
    return points;
}


std::vector<float> make_ring(float radius = 40.f, float width = 10.f, int segments = 25) {
    std::vector<float> points;
    points.reserve(segments * 3 * 2);
    for (int i = 0; i <= segments; ++i) {
        float y = std::sin(i*2*M_PI/segments) * radius;
        float x = std::cos(i*2*M_PI/segments) * radius;
        points.push_back(x);
        points.push_back(y);
        points.push_back(0);
        points.push_back(x);
        points.push_back(y);
        points.push_back(width);
    }
    return points;
}


std::vector<float> make_cone(float radius = 10.f, float height = 40.f, int segments = 25) {
    std::vector<float> points;
    points.reserve(segments * 3 + 3);
    points.push_back(0);
    points.push_back(height);
    points.push_back(0);
    for (int i = 0; i <= segments; ++i) {
        float x = std::sin(i*2*M_PI/segments) * radius;
        float z = std::cos(i*2*M_PI/segments) * radius;
        points.push_back(x);
        points.push_back(0);
        points.push_back(z);
    }
    return points;
}


std::vector<float> make_helix(float len = M_PI, float height = 1, float radius = 40.f, int segments = 25) {
    std::vector<float> points;
    int _s = segments * len;
    float _h = height / segments;
    points.reserve(_s);
    for (int i = 0; i <= _s; ++i) {
        float y = std::sin(i*len/_s) * radius;
        float x = std::cos(i*len/_s) * radius;
        points.push_back(x);
        points.push_back(y);
        points.push_back(_h * i);
    }
    return points;
}


std::vector<float> make_sin(float len = M_PI, float period = M_PI, float amplitude = 1, unsigned int segments = 50) {
    std::vector<float> points;
    float step = len / segments;
    points.reserve(segments);
    for (unsigned int i = 0; i < segments; ++i) {
        float y = amplitude * std::sin((2*M_PI/period) * step*(float)i);
        float x = step * i;
        points.push_back(x);
        points.push_back(y);
        points.push_back(0);
    }
    return points;
}


std::vector<float> make_ellipse(float radius_x, float radius_y, int segments = 100) {
    std::vector<float> points;
    float step = (2*M_PI) / segments;
    points.reserve(segments);
    for (int i = 0; i <= segments; ++i) {
        float y = radius_y * std::sin(i*step);
        float x = radius_x * std::cos(i*step);
        points.push_back(x);
        points.push_back(y);
        points.push_back(0);
    }
    return points;
}


std::vector<float> make_sphere(float radius = 40, int latitude_segments = 32, int longitude_segments = 32) {
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

    using std::cos;
    using std::sin;

    std::vector<float> points;
    int half_latitude_segments = latitude_segments / 2;
    int half_longitude_segments = longitude_segments / 2;
    float lts = 2*M_PI/latitude_segments;
    float lns = M_PI/longitude_segments;

    for (int j = -half_longitude_segments; j < half_longitude_segments; ++j) {
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


std::vector<float> make_hemisphere(float radius = 40, int latitude_segments = 32, int longitude_segments = 16) {
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

    using std::cos;
    using std::sin;

    std::vector<float> points;
    int half_latitude_segments = latitude_segments / 2;
    int half_longitude_segments = longitude_segments / 2;
    float lts = 2*M_PI/latitude_segments;
    float lns = M_PI/longitude_segments;

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


void draw_primitive(std::vector<float> &points, GLenum type = GL_POINTS) {
    int size = points.size() / 3;
    glBegin(type);
    for (int i = 0; i < size; ++i) {
        glVertex3f(points[i*3], points[i*3+1], points[i*3+2]);
    }
    glEnd();
}


void draw_primitive(std::vector<glm::vec2> &points, GLenum type = GL_POINTS) {
    glBegin(type);
    for (auto p : points) {
        glVertex3f(p.x, p.y, 0);
    }
    glEnd();
}


void draw_primitive(std::vector<glm::vec3> &points, GLenum type = GL_POINTS) {
    glBegin(type);
    for (auto p : points) {
        glVertex3f(p.x, p.y, p.z);
    }
    glEnd();
}
