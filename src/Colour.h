#ifndef colour_h
#define colour_h

#include "PlatformInclude.h"

// NOTE: Down to personal prefrence, I like to spell colour properly ;)

namespace kg
{
	struct Colour
	{
		Colour(const float &_r, const float &_g, const float &_b,
			const float &_a) : r(_r), g(_g), b(_b), a(_a) {}
		Colour(const float &_r, const float &_g, const float &_b)
			: r(_r), g(_g), b(_b), a(1.0f) {}
		Colour() : r(1.0f), g(1.0f), b(1.0f), a(1.0f) {}

		float *getArray() { return &r; }

		float r, g, b, a;

		void reClamp();

		static Colour White, Silver, Gray, Black, Red, Maroon, Yellow, Olive,
			Lime, Green, Aqua, Teal, Blue, Navy, Fuchsia, Purple;
	};
}

const kg::Colour &operator +(const kg::Colour &a, const kg::Colour &b);
const kg::Colour &operator -(const kg::Colour &a, const kg::Colour &b);
const kg::Colour &operator *(const kg::Colour &a, const kg::Colour &b);
const kg::Colour &operator /(const kg::Colour &a, const kg::Colour &b);
const kg::Colour &operator +(const float &a, const kg::Colour &b);
const kg::Colour &operator -(const float &a, const kg::Colour &b);
const kg::Colour &operator *(const float &a, const kg::Colour &b);
const kg::Colour &operator /(const float &a, const kg::Colour &b);
const kg::Colour &operator +(const kg::Colour &a, const float &b);
const kg::Colour &operator -(const kg::Colour &a, const float &b);
const kg::Colour &operator *(const kg::Colour &a, const float &b);
const kg::Colour &operator /(const kg::Colour &a, const float &b);

#endif /* colour_h */
