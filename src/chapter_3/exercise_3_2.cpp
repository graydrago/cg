#pragma once

#include <vector>
#include <map>
#include <glm/glm.hpp>

#include <GL/gl.h>

#include "./exercise_3_1.cpp"
#include "../core/helper.cpp"
#include "../core/camera/RotationUtil.cpp"

class Exercise_3_2 : public Exercise_3_1 {
    public:
        Exercise_3_2() : Exercise_3_1 () {}

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

            glDrawElements(GL_TRIANGLES, m_shape.size(), GL_UNSIGNED_INT, m_indexes.data());
        }
};

