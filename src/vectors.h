#ifndef vectors_h
#define vectors_h

namespace kg
{
	struct Vector3;

	struct Vector2
	{
		Vector2();
		Vector2(const Vector3 &v);
		Vector2(const float &_x, const float &_y);

		void normalise();

		float x, y;
		float getMagnitude();
		float getDistanceTo(const Vector2 &b);
		float *getV() { return &x; }

		static float getDistance(const Vector2 &a, const Vector2 &b);
		static float getDotProduct(const Vector2 &a, const Vector2 &b);
	};

	struct Vector3
	{
		Vector3();
		Vector3(const Vector2 &v);
		Vector3(const Vector2 &v, const float &_z);
		Vector3(const float &_x, const float &_y);
		Vector3(const float &_x, const float &_y, const float &_z);

		void normalise();

		float x, y, z;
		float getMagnitude();
		float getDistanceTo(const Vector3 &b);
		float *getV() { return &x; }

		static float getDistance(const Vector3 &a, const Vector3 &b);
		static float getDotProduct(const Vector3 &a, const Vector3 &b);
		
		static Vector3 getCrossProduct(const Vector3 &a, const Vector3 &b);
	};
}

kg::Vector2 operator +(const kg::Vector2 &a, const kg::Vector2 &b);
kg::Vector2 operator -(const kg::Vector2 &a, const kg::Vector2 &b);
kg::Vector2 operator *(const kg::Vector2 &a, const kg::Vector2 &b);
kg::Vector2 operator /(const kg::Vector2 &a, const kg::Vector2 &b);
kg::Vector3 operator +(const kg::Vector3 &a, const kg::Vector3 &b);
kg::Vector3 operator -(const kg::Vector3 &a, const kg::Vector3 &b);
kg::Vector3 operator *(const kg::Vector3 &a, const kg::Vector3 &b);
kg::Vector3 operator /(const kg::Vector3 &a, const kg::Vector3 &b);
kg::Vector2 operator +(const float &a, const kg::Vector2 &b);
kg::Vector2 operator -(const float &a, const kg::Vector2 &b);
kg::Vector2 operator *(const float &a, const kg::Vector2 &b);
kg::Vector2 operator /(const float &a, const kg::Vector2 &b);
kg::Vector3 operator +(const float &a, const kg::Vector3 &b);
kg::Vector3 operator -(const float &a, const kg::Vector3 &b);
kg::Vector3 operator *(const float &a, const kg::Vector3 &b);
kg::Vector3 operator /(const float &a, const kg::Vector3 &b);
kg::Vector2 operator +(const kg::Vector2 &a, const float &b);
kg::Vector2 operator -(const kg::Vector2 &a, const float &b);
kg::Vector2 operator *(const kg::Vector2 &a, const float &b);
kg::Vector2 operator /(const kg::Vector2 &a, const float &b);
kg::Vector3 operator +(const kg::Vector3 &a, const float &b);
kg::Vector3 operator -(const kg::Vector3 &a, const float &b);
kg::Vector3 operator *(const kg::Vector3 &a, const float &b);
kg::Vector3 operator /(const kg::Vector3 &a, const float &b);

#endif /* vectors_h */
