#include <fstream>
#include <string>
#include <cstdio>

#include "material.h"
#include "kgConstants.h"
#include "misc.h"

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
		{
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, *m_textureID);
		}
	}

	BasicMaterial::~BasicMaterial()
	{
		if (m_textureID)
			delete m_textureID;
	}
	
	Colour getColour(const std::string &n, std::ifstream &file)
	{
		if (n == "{")
		{
			std::string nn;
			Colour c;
			
			unsigned upTo = 0;
		
			while (file.good())
			{	
				file >> nn;
				
				if (file.eof())
					return Colour::White;
				
				if (nn == ",")
					continue;

				if (nn == "}")
					return c;
				
				switch (upTo)
				{
				case 0:
					c.r = atof(nn.c_str());
					break;
				case 1:
					c.g = atof(nn.c_str());
					break;
				case 2:
					c.b = atof(nn.c_str());
					break;
				case 3:
					c.a = atof(nn.c_str());
					break;
				default:
					printf("Unexpected input: %s", nn.c_str());
					break;
				}
				
				++upTo;
			}
		}
		
		if (n == "white")
			return Colour::White;
		if (n == "silver")
			return Colour::Silver;
		if (n == "gray")
			return Colour::Gray;
		if (n == "black")
			return Colour::Black;
		if (n == "red")
			return Colour::Red;
		if (n == "maroon")
			return Colour::Maroon;
		if (n == "yellow")
			return Colour::Yellow;
		if (n == "olive")
			return Colour::Olive;
		if (n == "lime")
			return Colour::Lime;
		if (n == "green")
			return Colour::Green;
		if (n == "aqua")
			return Colour::Aqua;
		if (n == "teal")
			return Colour::Teal;
		if (n == "blue")
			return Colour::Blue;
		if (n == "navy")
			return Colour::Navy;
		if (n == "fuchsia")
			return Colour::Fuchsia;
		if (n == "purple")
			return Colour::Purple;
		
		printf("Colour value was not able to be extablished!\n"
			"Falling back to white.\n");
		return Colour::White;
	}

	BasicMaterial *BasicMaterial::getFromFile(const char *fname)
	{
		BasicMaterial *m = new BasicMaterial();

		std::ifstream file;
		file.open(fname);

		if (!file.is_open())
		{
			printf("Could not open material file: %s\n", fname);
			delete m;
			return NULL;
		}
		
		KG_MATFILE_READ_MODE rm = KG_NAME;

		while (file.good())
		{
			std::string n;
			file >> n;
			
			if (file.eof())
			{
				printf("Reached unexpected end of file: %s\n", fname);
				file.close();
				return m;
			}
			
			if (n == "=")
				continue;
			
			static float s = 100.0f;
			
			switch (rm)
			{
			case KG_NAME:
				m->setName(n);
				rm = KG_NEW;
				break;
			case KG_NEW:
				if (n == "}")
				{
					file.close();
					return m;
				}
				
				if (n == "{")
					break;
				
				if (n == "ambient")
					rm = KG_AMBIENT;
				else if (n == "diffuse")
					rm = KG_DIFFUSE;
				else if (n == "specular")
					rm = KG_SPECULAR;
				else if (n == "shininess")
					rm = KG_SHININESS;
				else if (n == "texture")
					rm = KG_TEXTURE;
				else
				{
					printf("Unexpected format given.\n"
						"Material %s could not be loaded.", fname);
					delete m;
					file.close();
					return NULL;
				}
				
				break;
			case KG_AMBIENT:
				m->setAmbient(getColour(n, file));
				rm = KG_NEW;
				break;
			case KG_DIFFUSE:
				m->setDiffuse(getColour(n, file));
				rm = KG_NEW;
				break;
			case KG_SPECULAR:
				m->setSpecular(getColour(n, file));
				rm = KG_NEW;
				break;
			case KG_SHININESS:
				s = atof(n.c_str());
				m->setShininess(s);
				rm = KG_NEW;
				break;
			case KG_TEXTURE:
				m->setTextureID(new unsigned(loadTexture(n.c_str())));
				rm = KG_NEW;
				break;
			default:
				printf("Undefined case reading: %s\n", fname);
				delete m;
				file.close();
				return NULL;
			}
		}
		
		file.close();
		return m;
	}
}
