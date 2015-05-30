#include "frog.h"
#include "transform.h"
#include "material.h"
#include "engine.h"
#include "misc.h"

using namespace kg;

FrogBase::FrogBase()
{
	m_body = new FrogBody();

	addChild("body", m_body);
}

void FrogBase::start()
{
	addProperty("Transform", new Transform(), true);
	addProperty("Material", BasicMaterial::getFromFile("Frog.mat"), true);
	
	if (!m_transform)
		return;
	
	m_transform->m_freezePos = true;
	m_transform->m_freezeRotX = true;
	m_transform->m_freezeRotY = true;
	m_transform->m_freezeRotZ = true;

	m_transform->m_pos = Vector3(0.0f, 0.0f, -1.0f);

	Engine::setCameraLookAt(&m_transform->m_pos);
}

void FrogBase::update()
{
	
}

FrogBody::FrogBody()
{
	m_head = new FrogHead();
	m_legLeft = new FrogInnerLeg();
	m_legRight = new FrogInnerLeg();
	m_armLeft = new FrogInnerArm();
	m_armRight = new FrogInnerArm();

	addChild("head", m_head);
	addChild("legLeft", m_legLeft);
	addChild("legRight", m_legRight);
	addChild("armLeft", m_armLeft);
	addChild("armRight", m_armRight);

	addProperty("Transform", new Transform(), true);
	addProperty("Mesh", MeshTable::find("Cube"), true);
}

void FrogBody::start()
{
	m_transform->m_scale = Vector3(0.6f, 0.4f, 0.8f);
	
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
	m_child = new FrogMiddleLeg();

	addChild("child", m_child);

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
	m_child = new FrogMiddleArm();

	addChild("child", m_child);

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
