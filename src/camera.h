#ifndef camera_h
#define camera_h

#include "vectors.h"
#include "platformInclude.h"

namespace kg
{
	struct Camera
	{
		Camera() : m_fov(75.0f), m_near(0.01f), m_far(150.0f), m_zoom(18.0f),
			m_sensitivity(6.7f), m_perspective(true), m_lookAt(NULL),
			m_rot(45.0f, 180.0f) {}

		void modelViewGL();
		void projectionGL();
		void updateRot(const int &dx, const int &dy);
		void updateZoom(const int &dy);

		const Vector3 getCamPos();

		float m_fov, m_near, m_far, m_zoom, m_sensitivity;

		bool m_perspective;

		Vector2 m_rot;

		Vector3 m_pos, *m_lookAt;
	};
}

#endif
