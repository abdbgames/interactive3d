#ifndef material_h
#define material_h

#include "ObjectProperties.h"
#include "Colour.h"

namespace kg
{
	struct BasicMaterial : public BaseProperty
	{
		BasicMaterial() : m_shininess(100), m_textureID(NULL) {}
		BasicMaterial(const unsigned &textureID) : m_shininess(100),
			m_textureID(new unsigned(textureID)) {}
		BasicMaterial(const Colour &ambient, const Colour &diffuse,
			const Colour &specular, const float &shininess)
			: m_ambient(ambient), m_diffuse(diffuse), m_specular(specular),
			m_shininess(shininess), m_textureID(NULL) {}
		BasicMaterial(const Colour &ambient, const Colour &diffuse,
			const Colour &specular, const float &shininess,
			const unsigned &textureID) : m_ambient(ambient),
			m_diffuse(diffuse), m_specular(specular),
			m_shininess(shininess), m_textureID(new unsigned(textureID)) {}

		const Colour &getAmbient() { return m_ambient; }
		const Colour &getDiffuse() { return m_diffuse; }
		const Colour &getSpecular() { return m_specular; }

		const float &getShinniness() { return m_shininess; }
		const float *getAmbientArray() { return m_ambient.getArray(); }
		const float *getDiffuseArray() { return m_diffuse.getArray(); }
		const float *getSpecularArray() { return m_specular.getArray(); }

		void setAmbient(const Colour &ambient) { m_ambient = ambient; }
		void setDiffuse(const Colour &diffuse) { m_diffuse = diffuse; }
		void setSpecular(const Colour &specular) { m_specular = specular; }
		void setShininess(const float &shininess) { m_shininess = shininess; }
		void render();

	private:
		Colour m_ambient, m_diffuse, m_specular;

		float m_shininess;

		unsigned *m_textureID;
	};
}

#endif /* material_h */
