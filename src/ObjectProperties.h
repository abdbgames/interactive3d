#ifndef objectProperties_h
#define objectProperties_h

#define NULL 0

namespace kg
{
	struct BaseProperty
	{
		// Constructors:
		BaseProperty() : m_name(NULL) {}
		BaseProperty(const char *name);

		// Desrtuctor:
		~BaseProperty();

		// Virtual Methods:
		virtual void update() {}

		// Methods:
		void setName(const char *name);

		const char *getName() { return m_name; }

	protected:
		// Protected Methods:
		char *m_name;
	};
}

#endif
