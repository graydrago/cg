#pragma once

#include <SDL2/SDL_events.h>
#include <GL/gl.h>
#include <glm/vec3.hpp>

class RotationUtil {
    public:
        glm::vec3 m_angles {0, 0, 0};
        glm::vec3 m_pos {0, 0, 0};
        glm::vec3 m_dir {0, 0, 0};
        glm::vec3 m_pos_dir {0, 0, 0};
        float m_speed = 40;

        explicit RotationUtil() {};

        void input(SDL_Event events) {
            switch (events.type) {
                case SDL_KEYDOWN: {
                    switch (events.key.keysym.sym) {
                        case SDLK_KP_4: m_dir.y = -1; break;
                        case SDLK_KP_6: m_dir.y = 1; break;
                        case SDLK_KP_8: m_dir.x = -1; break;
                        case SDLK_KP_2: m_dir.x = 1; break;
                        case SDLK_KP_7: m_dir.z = 1; break;
                        case SDLK_KP_9: m_dir.z = -1; break;
                        case SDLK_KP_PLUS: m_pos_dir.z = 1; break;
                        case SDLK_KP_MINUS: m_pos_dir.z = -1; break;
                    }
                    break;
                }

                case SDL_KEYUP: {
                    switch (events.key.keysym.sym) {
                        case SDLK_KP_4:
                        case SDLK_KP_6:
                            m_dir.y = 0; break;
                        case SDLK_KP_8:
                        case SDLK_KP_2:
                            m_dir.x = 0; break;
                        case SDLK_KP_7:
                        case SDLK_KP_9:
                            m_dir.z = 0;break;
                        case SDLK_KP_PLUS:
                        case SDLK_KP_MINUS:
                            m_pos_dir.z = 0; break;
                    }
                    break;
                }
            }

        }

        void update(double elapsed) {
            m_angles.x += m_dir.x * elapsed * m_speed;
            m_angles.y += m_dir.y * elapsed * m_speed;
            m_angles.z += m_dir.z * elapsed * m_speed;
            m_pos.z += m_pos_dir.z * elapsed * m_speed;
        }

        void rotate() {
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glTranslatef(m_pos.x, m_pos.y, m_pos.z);
            glRotatef(m_angles.x, 1, 0, 0);
            glRotatef(m_angles.y, 0, 1, 0);
            glRotatef(m_angles.z, 0, 0, 1);
        };
};
