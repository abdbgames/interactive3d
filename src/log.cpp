#include "log.h"
#include "mesh.h"
#include "misc.h"
#include "engine.h"

Log::Log(const bool &dir) : m_dir(dir)
{
	m_l = new LogCap();
	m_r = new LogCap();

	addChild("LeftCap", m_l);
	addChild("RightCap", m_r);

	addProperty("Material", kg::BasicMaterial::getFromFile("flat.mat"), true);
	addProperty("Mesh", kg::MeshTable::find("Log"), true);
	addProperty("Transform", new kg::Transform(), true);
}

void Log::start()
{
	m_mat->setShininess(30);
	m_mat->setTextureID(new unsigned(kg::loadTexture("textures/wood.jpg")));
	m_transform->m_scale = kg::Vector3(0.8f, 0.8f, 4.2f);
	m_transform->m_rot.x = KG_PI / 2.0f;
	m_transform->m_freezePos = true;

	m_l->getTransform()->m_pos.z = -0.5f;
	m_r->getTransform()->m_pos.z = 0.5f;
	m_l->getTransform()->m_rot.x = KG_PI;

	m_front = m_transform->m_pos.z + m_transform->m_scale.x;
	m_back = m_transform->m_pos.z - m_transform->m_scale.x;
	m_top = m_transform->m_pos.y + m_transform->m_scale.y;
	m_bot = m_transform->m_pos.y;
}

void Log::update()
{
	const float speed = 2.2f;
	static float count = 0.0f;

	count += kg::getRandom(0.04f, 0.5f) * kg::Engine::getDeltaTime();

	m_transform->m_rot.y = sinf(count) * 0.3f;

	if (m_dir)
		m_transform->m_pos.x -= speed * kg::Engine::getDeltaTime();
	else
		m_transform->m_pos.x += speed * kg::Engine::getDeltaTime();

	kg::range(m_transform->m_pos.x, -49.2f, 49.2f);

	m_left = m_transform->m_pos.x - m_transform->m_scale.z * 0.5f;
	m_right = m_transform->m_pos.x + m_transform->m_scale.z * 0.5f;
}

LogCap::LogCap()
{
	addProperty("Material", kg::BasicMaterial::getFromFile("logCap.mat"),
		true);
	addProperty("Mesh", kg::MeshTable::find("Circle"), true);
	addProperty("Transform", new kg::Transform(), true);
	m_transform->m_rot.z = KG_PI / 2.0f;
}
