#include "ass2.h"
#include "keyboard.h"

// Default engine wide variables:
int Ass2::m_width = 1024, Ass2::m_height = 768;
float Ass2::m_aspect = 1.333333f;
bool Ass2::smoothShading = true, Ass2::drawAxis = false,
	Ass2::drawNormals = false , Ass2::drawTextures = true;
KG_DRAW_MODE Ass2::drawMode = KG_FILLED;
KG_LIGHT_MODE Ass2::lightMode = KG_FULL;

void Ass2::init()
{
	m_sT = 0.0f;
	m_dynObjects = 110;
	m_debug = false;
	m_camera.updateSize(&m_aspect);
	m_camera.updateBaseAngle(m_frog.getAngle());
	m_camera.updateOrigin(m_frog.getPos());
	m_frog.init();
	m_camera.init();
	m_floor.init();
	
	setDrawState(drawMode);
	setLightState(lightMode);
	setSmoothShading(smoothShading);
	
	m_dynObjList.resize(m_dynObjects);
	
	// Fill object list with cars and logs in random positions with random
	// speeds:
	for (int i = 0; i < m_dynObjects; ++i)
	{
		m_dynObjList[i].isCar = (rand() % 2) - 1;
		m_dynObjList[i].getPos().x = (m_dynObjList[i].isCar) ?
			kg::getRandom<float>(-49.0f, -1.0f) :
			kg::getRandom<float>(1.0f, 49.0f);
		m_dynObjList[i].getPos().z = kg::getRandom<float>(-49.8f, 49.8f);
		m_dynObjList[i].getVel().z = kg::getRandom<float>(-5.0f, 5.0f);
	}
}

void Ass2::updateTime()
{
	// Update time parameters:
	static float lastT = -1.0;

	m_t = glutGet(GLUT_ELAPSED_TIME) / (float)milli;

	if (lastT < 0.0)
	{
		lastT = m_t;
		return;
	}

	m_dT = m_t - lastT;

	// Debugging:
	if (m_debug)
		printf("Time: %f; DeltaTime: %f;\n", m_t, m_dT);

	lastT = m_t;
}

void Ass2::update()
{
	// Update time:
	updateTime();
	
	// If we are hitting a mouse button, lock the mouse to that position and
	// hide the cursor, otherwise unlock and set cursor to "clickable":
	if (kg::mouseControl::pollAny(KG_PRESSED))
	{
		// The locking itself always occurs at the end of an update, so it's
		// safe to put this call anywhere:
		kg::mouseControl::lockMouse(kg::mouseControl::m_x,
			kg::mouseControl::m_y);
		glutSetCursor(GLUT_CURSOR_NONE);
	}
	else
	{
		kg::mouseControl::unlockMouse();
		glutSetCursor(GLUT_CURSOR_INFO);
	}
	
	// If we are debugging print the stack of any keys pressed before this
	// update call:
	if (m_debug)
	{
		if (kg::keyboardControl::pollAny(KG_DOWN))
		{
			printf("Key(s) pressed before this update call: ");
			for (unsigned int i = 0;
				i < kg::keyboardControl::getPressBuffer().size(); ++i)
					printf("%c ", kg::keyboardControl::getPressBuffer()[i]);
		
			printf("\n");
		}
	}
	
	// Handle keyboard input:
	if (kg::keyboardControl::poll(KGkey_q, KG_DOWN) ||
		kg::keyboardControl::poll(KGkey_Q, KG_DOWN) ||
		kg::keyboardControl::poll(KGkey_esc, KG_DOWN))
			// Quit the program:
			exit(EXIT_SUCCESS);
			
	if (kg::keyboardControl::poll(KGkey_o, KG_DOWN) ||
		kg::keyboardControl::poll(KGkey_O, KG_DOWN))
		// Toggle axis drawing:
		drawAxis = !drawAxis;
	
	if (kg::keyboardControl::poll(KGkey_n, KG_DOWN) ||
		kg::keyboardControl::poll(KGkey_N, KG_DOWN))
		// Toggle normal drawing:
		drawNormals = !drawNormals;
		
	if (kg::keyboardControl::poll(KGkey_t, KG_DOWN) ||
		kg::keyboardControl::poll(KGkey_T, KG_DOWN))
		// Toggle texture drawing:
		drawTextures = !drawTextures;
	
	if (kg::keyboardControl::poll(KGkey_m, KG_DOWN) ||
		kg::keyboardControl::poll(KGkey_M, KG_DOWN))
		// Toggle smooth shading:
		toggleSmoothShading();
		
	if (kg::keyboardControl::poll(KGkey_p, KG_DOWN) ||
		kg::keyboardControl::poll(KGkey_P, KG_DOWN))
		// Cycle through draw modes:
		cycleDrawState();
		
	if (kg::keyboardControl::poll(KGkey_l, KG_DOWN) ||
		kg::keyboardControl::poll(KGkey_L, KG_DOWN))
		// Cycle through draw modes:
		cycleLightState();
	
	// Update primary objects:
	m_frog.update(m_dT);
	m_camera.update(m_dT);
	
	// Update secondary objects in object list:
	for (unsigned int i = 0; i < m_dynObjList.size(); ++i)
		m_dynObjList[i].update(m_dT);
	
	// Draw callback:
	glutPostRedisplay();

	// Start polling for input callbacks:
	kg::keyboardControl::postUpdate();
	kg::mouseControl::postUpdate();
}

void Ass2::draw()
{
	// Clear screen:
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Allow depth buffering:
	glEnable(GL_DEPTH_TEST);

	// "Draw" our camera, this set's up the scene to look as if it was being
	// looked at by the camera object:
	m_camera.draw();
	
	// Enable light 0 (scene ambient lighting):
	glEnable(GL_LIGHT0);
	
	static GLfloat pos[] = {1.0f, 1.0f, 1.0f, 0.0f};
	static GLfloat ambient[] = {0.05f, 0.05f, 0.05f, 1.0f};
	static GLfloat other[] = {1.0f, 1.0f, 1.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, other);
	glLightfv(GL_LIGHT0, GL_SPECULAR, other);

	// Draw axis:
	kg::drawAxis(1.5f);
	
	// Draw primary objects:
	m_frog.draw();
	m_floor.draw();
	
	// Draw secondary objects in object list:
	for (unsigned int i = 0; i < m_dynObjList.size(); ++i)
		m_dynObjList[i].draw();

	// Swap buffers:
	glutSwapBuffers();
}

void Ass2::grabSize(int w, int h)
{
	// Set local width/height:
	m_width = w;
	m_height = h;
	
	// Set aspect:
	m_aspect = (float)w/(float)h;
	
	// Reset viewport:
	glViewport(0, 0, w, h);
}

void Ass2::setDrawState(const KG_DRAW_MODE &d)
{
	drawMode = d;
	
	switch (drawMode)
	{
	case KG_FILLED:
		printf("Setting filled pollygon rendering mode,"
			" with backface culling.\n");
		glPolygonMode(GL_FRONT, GL_FILL);
		break;
	case KG_FILLED_NOCULL:
		printf("Setting filled pollygon rendering mode,"
			" with no backface culling.\n");
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	case KG_WIRE:
		printf("Setting wireframe rendering mode\n");
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case KG_POINTS:
		printf("Setting vertex points rendering mode\n");
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		break;
	}
}

void Ass2::setLightState(const KG_LIGHT_MODE &l)
{
	lightMode = l;
	
	switch (lightMode)
	{
	case KG_FULL:
		printf("Turning on full lighting.\n");
		glEnable(GL_LIGHTING);
		break;
	case KG_DIR:
		printf("Turning on directional lighting only.\n");
		glEnable(GL_LIGHTING);
		break;
	case KG_UNLIT:
		printf("Turning off lighting.\n");
		glDisable(GL_LIGHTING);
		break;
	}
}

void Ass2::setSmoothShading(const bool &ss)
{
	smoothShading = ss;
	
	if (smoothShading)
		glShadeModel(GL_SMOOTH);
	else
		glShadeModel(GL_FLAT);
}

void Ass2::cycleDrawState()
{
	// Cycle to the next draw state, if the draw state is the last,
	// go to the first:
	if (drawMode == KG_POINTS)
		setDrawState(KG_FILLED);
	else
	{
		// Dont mind C++ having a siezure...
		// Seriously, try putting drawMode + 1 straight into setDrawState,
		// or even make t a KG_DRAW_MODE type to bein with, this breaks it...
		// I spent so long debugging this stupid error:
		int t = drawMode + 1;
		setDrawState((KG_DRAW_MODE)t);
	}
}

void Ass2::cycleLightState()
{
	// Cycle to the next light state, if the light state is the last,
	// go to the first:
	if (lightMode == KG_UNLIT)
		setLightState(KG_FULL);
	else
	{
		int t = lightMode + 1;
		setLightState((KG_LIGHT_MODE)t);
	}
}

void Ass2::toggleSmoothShading()
{
	// Toggles smooth shading:
	setSmoothShading(!smoothShading);
}

