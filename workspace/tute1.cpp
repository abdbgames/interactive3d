#include "stdafx.h"
#include "tute1.h"
#include "keyboard.h"

void Tute1::init()
{

}

void Tute1::update()
{
	kg::keyboardControl::keyBufferBegin();
	kg::keyboardControl::keyBufferEnd();
}

void Tute1::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glutSwapBuffers();
}

void Tute1::end()
{

}
