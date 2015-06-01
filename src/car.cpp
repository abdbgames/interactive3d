#include "car.h"
#include "mesh.h"
#include "misc.h"
#include "engine.h"

Car::Car(const bool &dir) : m_dir(dir)
{
	m_ct = new CarTop();
	m_fl = new CarWheel();
	m_fr = new CarWheel();
	m_bl = new CarWheel();
	m_br = new CarWheel();

	addChild("CarTop", m_ct);
	addChild("FrontLeft", m_fl);
	addChild("FrontRight", m_fr);
	addChild("BackLeft", m_bl);
	addChild("BackRight", m_br);

	addProperty("Material", kg::BasicMaterial::getFromFile("car.mat"), true);
	addProperty("Mesh", kg::MeshTable::find("Sphere"), true);
	addProperty("Transform", new kg::Transform(), true);
}

void Car::start()
{
	m_transform->m_scale.x = 1.5f;
	m_transform->m_pos.y = 0.6f;
	m_transform->m_freezePos = true;

	m_bl->getTransform()->m_pos.x = -0.7f;
	m_fl->getTransform()->m_pos.x = 0.7f;
	m_bl->getTransform()->m_pos.z = -0.6f;
	m_fl->getTransform()->m_pos.z = -0.6f;
	m_br->getTransform()->m_pos.x = -0.7f;
	m_fr->getTransform()->m_pos.x = 0.7f;
	m_br->getTransform()->m_pos.z = 0.6f;
	m_fr->getTransform()->m_pos.z = 0.6f;
	m_ct->getTransform()->m_pos.x = -0.2f;
	m_ct->getTransform()->m_pos.y = 0.2f;

	m_radius = 0.75f;
}

void Car::update()
{
	const float speed = 5.2f;
	static float count = 0.0f;

	count += kg::getRandom(0.04f, 0.5f) * kg::Engine::getDeltaTime();

	m_transform->m_rot.y = sinf(count) * 0.3f;

	if (m_dir)
		m_transform->m_pos.x -= speed * kg::Engine::getDeltaTime();
	else
		m_transform->m_pos.x += speed * kg::Engine::getDeltaTime();

	kg::range(m_transform->m_pos.x, -49.2f, 49.2f);
}

CarWheel::CarWheel()
{
	addProperty("Material", kg::BasicMaterial::getFromFile("logCap.mat"),
		true);
	addProperty("Mesh", kg::MeshTable::find("Sphere"), true);
	addProperty("Transform", new kg::Transform(), true);
	m_transform->m_scale.x /= 1.5f;
	m_transform->m_scale.x *= 0.4f;
	m_transform->m_scale.y = 0.4f;
	m_transform->m_scale.z = 0.2f;
	m_transform->m_pos.y = -0.2f;
}

CarTop::CarTop()
{
	addProperty("Mesh", kg::MeshTable::find("Sphere"), true);
	addProperty("Transform", new kg::Transform(), true);
	m_transform->m_scale = m_transform->m_scale * 0.6f;
}
