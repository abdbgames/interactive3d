#include "stdafx.h"
#include "platformInclude.h"
#include "tute5.h"
#include "keyboard.h"
#include "frog.h"

void Tute5::init()
{
    wireframe = false;
}

void Tute5::update()
{
    if (kg::keyboardControl::onKeyPress(KGkey_p))
        wireframe = true;
        
    if (kg::keyboardControl::onKeyPress(KGkey_o))
        wireframe = false;
}

void Tute5::draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    drawAxis(Vector3(0.0f, 0.0f, 0.0f), 1.0f);

    glLoadIdentity();
/*
    glScalef(0.2f, 0.2f, 0.2f);
    glRotatef(45.0f, 0.4f, 0.2f, 1.0f);
    glTranslatef(0.7f, 0.0f, 0.0f);

    glColor3f(1.0, 1.0, 1.0);
    if (wireframe)
        glutWireTeapot(1.0f);
    else
        glutSolidTeapot(1.0f);
    drawAxis(Vector3(0.0f, 0.0f, 0.0f), 1.5f);
*/

	Frog frog;
	frog.init();
	frog.draw();
	
	Vector3 test(5, 6, 7);

    glutSwapBuffers();
}

void Tute5::end()
{

}

void Tute5::drawAxis(const Vector3 &pos, const float &size)
{
    // Set the colour and set points for the lines that make our axis:
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(pos.x, pos.y, pos.z);
    glVertex3f(pos.x + size, pos.y, pos.z);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(pos.x, pos.y, pos.z);
    glVertex3f(pos.x, pos.y + size, pos.z);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(pos.x, pos.y, pos.z);
    glVertex3f(pos.x, pos.y, pos.z + size);
    glEnd();
}
