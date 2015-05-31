#include "log.h"
#include "mesh.h"
#include "misc.h"

Log::Log()
{
	m_l = new LogCap();
	m_r = new LogCap();

	addChild("LeftCap", m_l);
	addChild("RightCap", m_r);

	addProperty("Mesh", kg::MeshTable::find("Log"), true);
	addProperty("Transform", new kg::Transform(), true);
}

void Log::start()
{
	m_l->getTransform()->m_pos.x -= 0.5f;
	m_r->getTransform()->m_pos.x += 0.5f;
}

void Log::update()
{

}

LogCap::LogCap()
{
	addProperty("Mesh", kg::MeshTable::find("Circle"), true);
	addProperty("Transform", new kg::Transform(), true);
	m_transform->m_rot.z += kg::degToRad(45.0f);
}
