#include "frog.h"
#include "transform.h"
#include "material.h"
#include "misc.h"
#include "keyboard.h"

using namespace kg;

void FrogParabola::render()
{
	glDisable(GL_LIGHTING);

	// Draw initial velocity:
	glColor4fv(Colour::Purple.getArray());

	Vector3 vDraw = *m_initVel / 5.0f;

	glPopMatrix();
	glPushMatrix();
	glTranslatef(m_t->m_pos.x, m_t->m_pos.y, m_t->m_pos.z);

	glBegin(GL_LINE_STRIP);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3fv(vDraw.getV());
	glEnd();

	// Draw parabola:
	glPopMatrix();
	glPushMatrix();
	glScalef(1.0f, 1.0f, 1.0f);
	glTranslatef(m_initPos->x, m_initPos->y, m_initPos->z);

	float flightTime = (2.0f * m_t->m_speed * sinf(m_t->m_rot.y)) / KG_GR, t,
		in = flightTime / (float)m_pSteps, preCalc = 0.5f * -KG_GR;

	Vector2 dir(cosf(m_t->m_rot.x), sinf(m_t->m_rot.x));

	// Set colour depending on air status:
	glColor4fv((*m_inAir) ? Colour::Red.getArray() : Colour::Blue.getArray());

	// Work out direction:
	bool xBack = (m_initVel->x < 0.0f);
	bool zBack = (m_initVel->z < 0.0f);

	glBegin(GL_LINE_STRIP);

	// Always draw a starting point otherwise we may run into issues with
	// selectivly drawing verts:
	Vector3 v(m_t->m_pos - *m_initPos);
	glVertex3fv(v.getV());

	// Calculation loop, adding points as we go:
	for (unsigned i = 0; i <= m_pSteps; ++i)
	{
		t = i * in;
		Vector3 c(m_initVel->x * t, (preCalc * t * t) + (m_initVel->y * t),
			m_initVel->z * t);

		// Don't draw this vert if the frog has passed it:
		if (((xBack && c.x >= v.x) || (!xBack && v.x >= c.x)) &&
			((zBack && c.z >= v.z) || (!zBack && v.z >= c.z)))
			continue;

		glVertex3fv(c.getV());
	}

	glEnd();

	glPopMatrix();
	glPushMatrix();
	
	// Re-apply popped matrix:
	m_t->glStuff();

	if (Engine::getLightState() != KG_UNLIT)
		glEnable(GL_LIGHTING);
}

FrogBase::FrogBase()
{
	m_logOn = NULL;
	m_numLogs = 0;
	m_logs = NULL;
	m_numCars = 0;
	m_cars = NULL;
	m_body = new FrogBody();
	m_inAir = false;
	m_gameOver = false;
	m_lives = 5;
	m_points = 0;
	m_rotSpeed = 1.2f;

	addChild("body", m_body);

	Engine::setLives(m_lives);
	Engine::setScore(m_points);

	addProperty("Transform", new Transform(), true);
	addProperty("Parabola", new FrogParabola(m_transform, &m_initVel,
		&m_initPos, &m_inAir), false);
}

bool checkCollision(kg::Vector3 &pos, float *bounds)
{
	return (pos.x >= *bounds && pos.x <= *(bounds + 1) &&
		pos.y >= *(bounds + 5) && pos.y <= *(bounds + 4) &&
		pos.z >= *(bounds + 3) && pos.z <= *(bounds + 2));
}

void FrogBase::start()
{	
	if (!m_transform)
		return;
	
	m_transform->m_freezePos = true;
	m_transform->m_freezeRotX = true;
	m_transform->m_freezeRotY = false;
	m_transform->m_freezeRotZ = true;

	m_transform->m_pos = Vector3(0.0f, 0.0f, -45.0f);
	m_transform->m_rot.x = KG_PI / 2.0f;
	m_transform->m_rot.y = 0.7854f; // 45 deg in radians.
	m_transform->m_speed = 4.0f;

	m_radius = 0.25f;

	Engine::setCameraLookAt(&m_transform->m_pos);

	m_checkpoints.push_back(m_transform->m_pos);
}

void FrogBase::kill(const std::string &message)
{
	m_transform->m_pos = m_checkpoints[m_checkpoints.size() - 1];

	Engine::newMessage(message, 2.0f);

	m_transform->m_freezePos = true;
	m_transform->m_pos.y = 0.0f;

	m_inAir = false;

	if (m_lives > 0)
	{
		--m_lives;
		Engine::setLives(m_lives);
	}
	else
	{
		Engine::newMessage("===GAME OVER!!!===\n", -1.0f);
		m_gameOver = true;
	}
}

void FrogBase::update()
{
	if (m_gameOver) return;

	static float offset;

	// Clamp frog to stay in scene:
	clamp(m_transform->m_pos.x, -50.0f, 50.0f);
	clamp(m_transform->m_pos.z, -50.0f, 50.0f);

	// When on the road:
	bool onRoad = true;

	if (onRoad)
	{
		// Check against all cars:
		for (unsigned i = 0; i < m_numCars; ++i)
			if (Vector3::getDistance(m_transform->m_pos,
				m_cars[i]->getTransform()->m_pos) <= 2.7f)
				kill("Frog got run over by a car!");
	}

	// First checkpoint:
	if (m_checkpoints.size() == 1)
	{
		if (m_transform->m_pos.z >= 0.0f)
			m_checkpoints.push_back(m_transform->m_pos);
	}
	else if (m_transform->m_pos.z >= 45.0f)
	{
		// Gained a point:
		++m_points;
		Engine::setScore(m_points);

		m_checkpoints.pop_back();

		m_transform->m_pos = m_checkpoints[m_checkpoints.size() - 1];

		Engine::newMessage("You got to the end! Here's a point!", 2.0f);

		m_transform->m_freezePos = true;
		m_transform->m_pos.y = 0.0f;

		m_inAir = false;
	}

	// When the frog is not in the air:
	if (!m_inAir)
	{
		// Get rotation input:
		if (keyboardControl::poll(KGKey_left, KG_PRESSED))
			m_transform->m_rot.x -= m_rotSpeed * Engine::getDeltaTime();

		if (keyboardControl::poll(KGKey_right, KG_PRESSED))
			m_transform->m_rot.x += m_rotSpeed * Engine::getDeltaTime();

		if (keyboardControl::poll(KGKey_a, KG_PRESSED) ||
			keyboardControl::poll(KGKey_A, KG_PRESSED))
			m_transform->m_rot.y += m_rotSpeed * Engine::getDeltaTime();

		if (keyboardControl::poll(KGKey_d, KG_PRESSED) ||
			keyboardControl::poll(KGKey_D, KG_PRESSED))
			m_transform->m_rot.y -= m_rotSpeed * Engine::getDeltaTime();

		if (keyboardControl::poll(KGKey_w, KG_PRESSED) ||
			keyboardControl::poll(KGKey_W, KG_PRESSED))
			m_transform->m_speed += m_rotSpeed * Engine::getDeltaTime();

		if (keyboardControl::poll(KGKey_s, KG_PRESSED) ||
			keyboardControl::poll(KGKey_S, KG_PRESSED))
			m_transform->m_speed -= m_rotSpeed * Engine::getDeltaTime();

		// Keep x angle in range (6.28318f is 360 degrees in radians):
		range<float>(m_transform->m_rot.x, 0.0f, 6.28318f);
		// Hard clamp y angle and speed (3.1416f is 180 degrees in radians):
		clamp<float>(m_transform->m_rot.y, 0.0f, 3.1416f);
		clamp<float>(m_transform->m_speed, 0.0f, 8.5f);

		if (m_logOn)
			m_transform->m_pos.x = m_logOn->getTransform()->m_pos.x + offset;

		// Try grabbing spacebar input:
		if (kg::keyboardControl::poll(KGKey_space, KG_DOWN))
		{
			// Start jump:
			m_inAir = true;
			m_transform->m_freezePos = false;

			if (m_logOn)
				m_logOn = NULL;
		}

		// Set the initial position:
		m_initPos = m_transform->m_pos;
		m_initVel = m_transform->getVelocity();

		// Early return:
		return;
	}

	// Frog is in air, apply gravity and velocity:
	m_transform->applyGravity(KG_GR);

	bool inDrink = (m_transform->m_pos.z >= 12.0f &&
		m_transform->m_pos.z <= 28.0f);

	// Not on a log:
	if (!onRoad && inDrink && !m_logOn)
	{
		// Log collision code:
		for (unsigned i = 0; i < m_numLogs; ++i)
		{
			if (checkCollision(m_transform->m_pos, m_logs[i]->getBounds()))
			{
				// Found a collision:
				m_logOn = m_logs[i];
				offset = m_transform->m_pos.x -
					m_logOn->getTransform()->m_pos.x;
				m_inAir = false;
				m_transform->m_freezePos = true;
				m_transform->m_pos.y = *(m_logOn->getBounds() + 4);
				return;
			}
		}

		if (m_transform->m_pos.y <= -0.2f)
			kill("Frog drowned in the drink!\n");

		return;
	}

	// Check if frog hit the ground:
	if (m_transform->m_pos.y <= 0.0f)
	{
		m_inAir = false;
		m_transform->m_freezePos = true;
		m_transform->m_pos.y = 0.0f;
	}
}

FrogBody::FrogBody()
{
	//m_head = new FrogHead();
	m_legLeft = new FrogInnerLeg();
	m_legRight = new FrogInnerLeg();
	m_armLeft = new FrogInnerArm();
	m_armRight = new FrogInnerArm();

	//addChild("head", m_head);
	addChild("legLeft", m_legLeft);
	addChild("legRight", m_legRight);
	addChild("armLeft", m_armLeft);
	addChild("armRight", m_armRight);

	addProperty("Transform", new Transform(), true);
	addProperty("Material", BasicMaterial::getFromFile("Frog.mat"), true);
	addProperty("Mesh", MeshTable::find("Cube"), true);
}

void FrogBody::start()
{
	m_transform->m_scale = Vector3(0.6f, 0.4f, 0.8f);
	m_transform->m_pos.y = 0.3f;
	m_transform->m_rot.x = -(KG_PI / 2.0f);
	
	Transform *working = m_armLeft->getTransform();
	working->m_pos.x -= 0.53f;
	working = m_armRight->getTransform();
	working->m_pos.x += 0.53f;
	working = m_legLeft->getTransform();
	working->m_pos.x -= 0.53f;
	working = m_legRight->getTransform();
	working->m_pos.x += 0.53f;
}

void FrogBody::update()
{
	
}

FrogOuterLeg::FrogOuterLeg()
{
	m_fLeft = new FrogFinger();
	m_fMid = new FrogFinger();
	m_fRight = new FrogFinger();

	addChild("leftF", m_fLeft);
	addChild("midF", m_fMid);
	addChild("rightF", m_fRight);

	addProperty("Transform", new Transform(), true);
	addProperty("Mesh", MeshTable::find("Cube"), true);
}

void FrogOuterLeg::start()
{
	
}

void FrogOuterLeg::update()
{
	
}

FrogMiddleLeg::FrogMiddleLeg()
{
	m_child = new FrogOuterLeg();

	addChild("child", m_child);

	addProperty("Transform", new Transform(), true);
	addProperty("Mesh", MeshTable::find("Cube"), true);
}

void FrogMiddleLeg::start()
{
	
}

void FrogMiddleLeg::update()
{
	
}

FrogInnerLeg::FrogInnerLeg()
{
	//m_child = new FrogMiddleLeg();

	//addChild("child", m_child);

	addProperty("Transform", new Transform(), true);
	addProperty("Mesh", MeshTable::find("Cube"), true);
}

void FrogInnerLeg::start()
{
	m_transform->m_scale = Vector3(0.15f, 0.2f, 0.5f);
	m_transform->m_pos.y -= 0.53f;
	m_transform->m_pos.z -= 0.3f;
	m_transform->m_rot.x -= degToRad(45.0f);
}

void FrogInnerLeg::update()
{
	
}

FrogOuterArm::FrogOuterArm()
{
	m_fLeft = new FrogFinger();
	m_fMid = new FrogFinger();
	m_fRight = new FrogFinger();

	addChild("leftF", m_fLeft);
	addChild("midF", m_fMid);
	addChild("rightF", m_fRight);

	addProperty("Transform", new Transform(), true);
	addProperty("Mesh", MeshTable::find("Cube"), true);
}

void FrogOuterArm::start()
{
	
}

void FrogOuterArm::update()
{
	
}

FrogMiddleArm::FrogMiddleArm()
{
	m_child = new FrogOuterArm();

	addChild("child", m_child);

	addProperty("Transform", new Transform(), true);
	addProperty("Mesh", MeshTable::find("Cube"), true);
}

void FrogMiddleArm::start()
{
	
}

void FrogMiddleArm::update()
{
	
}

FrogInnerArm::FrogInnerArm()
{
	//m_child = new FrogMiddleArm();

	//addChild("child", m_child);

	addProperty("Transform", new Transform(), true);
	addProperty("Mesh", MeshTable::find("Cube"), true);
}

void FrogInnerArm::start()
{
	m_transform->m_scale = Vector3(0.15f, 0.2f, 0.5f);
	m_transform->m_pos.y -= 0.64f;
	m_transform->m_pos.z += 0.22f;
	m_transform->m_rot.x -= degToRad(45.0f);
}

void FrogInnerArm::update()
{
	m_transform->m_rot.y += 0.45f * Engine::getDeltaTime();
}

FrogHead::FrogHead()
{
	m_eyeLeft = new FrogEye();
	m_eyeRight = new FrogEye();
	m_mouthLower = new FrogMouth();
	m_mouthUpper = new FrogMouth();

	addChild("eyeLeft", m_eyeLeft);
	addChild("eyeRight", m_eyeRight);
	addChild("mouthLower", m_mouthLower);
	addChild("mouthUpper", m_mouthUpper);

	addProperty("Transform", new Transform(), true);
	addProperty("Mesh", MeshTable::find("Cube"), true);
}

void FrogHead::start()
{
	
}

void FrogHead::update()
{
	
}

FrogMouth::FrogMouth()
{
	addProperty("Transform", new Transform(), true);
	addProperty("Mesh", MeshTable::find("Cube"), true);
}

void FrogMouth::start()
{
	
}

void FrogMouth::update()
{
	
}

FrogEye::FrogEye()
{
	m_pupil = new FrogPupil();
	m_hidden = true;

	addChild("pupil", m_pupil);

	addProperty("Transform", new Transform(), true);
	addProperty("Material",
		BasicMaterial::getFromFile("frogEye.mat"), true);
	addProperty("Mesh", MeshTable::find("Cube"), true);
}

void FrogEye::start()
{
	
}

void FrogEye::update()
{
	
}

FrogPupil::FrogPupil()
{
	m_hidden = true;

	addProperty("Transform", new Transform(), true);
	addProperty("Material",
		BasicMaterial::getFromFile("frogPupil.mat"), true);
	addProperty("Mesh", MeshTable::find("SinglePlane"), true);
}

void FrogPupil::start()
{
	
}

void FrogPupil::update()
{
	
}

FrogFinger::FrogFinger()
{
	addProperty("Transform", new Transform(), true);
	addProperty("Mesh", MeshTable::find("Cube"), true);
}

void FrogFinger::start()
{
	
}

void FrogFinger::update()
{
	
}
