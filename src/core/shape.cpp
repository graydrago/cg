#pragma once

#include <vector>
#include <glm/glm.hpp>

namespace Shape {

    std::vector<glm::vec3> circle(float radius = 40.f, int segments = 50) {
        using namespace glm;
        std::vector<vec3> points;
        points.reserve(segments * 3);
        for (int i = 0; i <= segments; ++i) {
            points.push_back(vec3(std::sin(i*2*M_PI/segments) * radius,
                                  std::cos(i*2*M_PI/segments) * radius,
                                  0));
        }
        return points;
    }

};
