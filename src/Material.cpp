#include "Material.h"

namespace kg
{
	void BasicMaterial::render()
	{
		// Set material properties:
		glMaterialfv(GL_FRONT, GL_AMBIENT, m_specular.getArray());
		glMaterialfv(GL_FRONT, GL_DIFFUSE, m_specular.getArray());
		glMaterialfv(GL_FRONT, GL_SPECULAR, m_specular.getArray());
		glMaterialfv(GL_FRONT, GL_SHININESS, &m_shininess);
		glColor4fv(m_ambient.getArray());

		// Bind texture if possible:
		if (m_textureID)
			glBindTexture(GL_TEXTURE_2D, *m_textureID);
	}
}
