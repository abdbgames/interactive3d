#ifndef transform_h
#define transform_h

#include "objectProperties.h"
#include "vectors.h"

namespace kg
{
	struct Transform2D : public BaseProperty
	{
		Transform2D() : m_speed(0.0f), m_angle(0.0f), m_freezePos(false),
			m_freezeAngle(false), m_scale(1.0f, 1.0f) {}
		Transform2D(const Vector2 &pos) : m_pos(pos), m_speed(0.0f),
			m_angle(0.0f), m_freezePos(false), m_freezeAngle(false),
			m_scale(1.0f, 1.0f) {}
		Transform2D(const Vector2 &pos, const float &angle) : m_pos(pos),
			m_speed(0.0f), m_angle(angle), m_freezePos(false),
			m_freezeAngle(false), m_scale(1.0f, 1.0f) {}
		Transform2D(const Vector2 &pos, const float &speed, const float &angle)
			: m_pos(pos), m_speed(speed), m_angle(angle), m_freezePos(false),
			m_freezeAngle(false), m_scale(1.0f, 1.0f) {}
		Transform2D(const Vector2 &pos, const Vector2 &scale) : m_pos(pos),
			m_scale(scale), m_speed(0.0f), m_angle(0.0f), m_freezePos(false),
			m_freezeAngle(false) {}
		Transform2D(const Vector2 &pos, const float &angle,
			const Vector2 &scale) : m_pos(pos), m_scale(scale), m_speed(0.0f),
			m_angle(angle), m_freezePos(false), m_freezeAngle(false) {}
		Transform2D(const Vector2 &pos, const float &speed, const float &angle,
			const Vector2 &scale)
			: m_pos(pos), m_scale(scale), m_speed(speed), m_angle(angle),
			m_freezePos(false), m_freezeAngle(false) {}

		virtual void update();

		void glStuff();

		const Vector2 &getVelocity() { return m_vel; }

		Vector2 m_pos, m_scale;

		float m_speed, m_angle;

		bool m_freezePos, m_freezeAngle;

	protected:
		Vector2 m_vel;
	};

	struct Transform : public BaseProperty
	{
		Transform() : m_speed(0.0f), m_freezePos(false),
			m_scale(1.0f, 1.0f, 1.0f), m_freezeRotX(false),
			m_freezeRotY(false), m_freezeRotZ(false) {}
		Transform(const Vector3 &pos) : m_pos(pos), m_speed(0.0f),
			m_freezePos(false), m_freezeRotX(false), m_freezeRotY(false),
			m_freezeRotZ(false), m_scale(1.0f, 1.0f, 1.0f) {}
		Transform(const Vector3 &pos, const float &speed) : m_pos(pos),
			m_speed(speed), m_freezePos(false), m_freezeRotX(false),
			m_freezeRotY(false), m_freezeRotZ(false),
			m_scale(1.0f, 1.0f, 1.0f) {}
		Transform(const Vector3 &pos, const Vector3 &scale) : m_pos(pos),
			m_scale(scale), m_speed(0.0f), m_freezePos(false),
			m_freezeRotX(false), m_freezeRotY(false), m_freezeRotZ(false)  {}
		Transform(const Vector3 &pos, const Vector3 &scale, const float &speed)
			: m_pos(pos), m_scale(scale), m_speed(speed), m_freezePos(false),
			m_freezeRotX(false), m_freezeRotY(false), m_freezeRotZ(false)  {}

		virtual void update();

		void glStuff();

		const Vector3 &getVelocity() { return m_vel; }

		// m_rot is a temporary "fix" until I get Quaternions/Matrix
		// implimentations shoved into my transform struct :)
		Vector3 m_pos, m_scale, m_rot;

		float m_speed;

		bool m_freezePos, m_freezeRotX, m_freezeRotY, m_freezeRotZ;

	protected:
		Vector3 m_vel;
	};
}

#endif /* transform_h */
