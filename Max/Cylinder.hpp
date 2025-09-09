#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"

#include <cmath>
#include "GLFW/glfw3.h"
//#include <corecrt_math_defines.h>

class Cylinder
{

    public:
    
    void drawCylinder(float radius, float height, int segments) 
    {

        float angleStep = 2.0f * 3.14159f / segments;

        // Draw the top and bottom circles
        glBegin(GL_TRIANGLE_FAN);
        glColor3f(1, 0, 0);
        glVertex3f(0.0f, height / 2.0f, 0.0f); // Top center
        for (int i = 0; i <= segments; ++i) {
            float angle = i * angleStep;
            glVertex3f(radius * cos(angle), height / 2.0f, radius * sin(angle));
        }
        glEnd();

        glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0.0f, -height / 2.0f, 0.0f); // Bottom center
        for (int i = 0; i <= segments; ++i) {
            float angle = i * angleStep;
            glVertex3f(radius * cos(angle), -height / 2.0f, radius * sin(angle));
        }
        glEnd();

        // Draw the side surface
        glBegin(GL_QUAD_STRIP);
        glColor3f(0, 1, 0);
        for (int i = 0; i <= segments; ++i) {
            float angle = i * angleStep;
            float x = radius * cos(angle);
            float z = radius * sin(angle);
            glVertex3f(x, height / 2.0f, z);  // Top vertex
            glVertex3f(x, -height / 2.0f, z); // Bottom vertex
        }
        glEnd();
    }
};