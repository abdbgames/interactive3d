#include "colour.h"
#include "misc.h"

namespace kg
{
	// Default colour values:
	Colour Colour::White = Colour(1.0f, 1.0f, 1.0f);
	Colour Colour::Silver = Colour(0.75f, 0.75f, 0.75f);
	Colour Colour::Gray = Colour(0.5f, 0.5f, 0.5f);
	Colour Colour::Black = Colour(0.0f, 0.0f, 0.0f);
	Colour Colour::Red = Colour(1.0f, 0.0f, 0.0f);
	Colour Colour::Maroon = Colour(0.5f, 0.0f, 0.0f);
	Colour Colour::Yellow = Colour(1.0f, 1.0f, 0.0f);
	Colour Colour::Olive = Colour(0.5f, 0.5f, 0.0f);
	Colour Colour::Lime = Colour(0.0f, 1.0f, 0.0f);
	Colour Colour::Green = Colour(0.0f, 0.5f, 0.0f);
	Colour Colour::Aqua = Colour(0.0f, 1.0f, 1.0f);
	Colour Colour::Teal = Colour(0.0f, 0.5f, 0.5f);
	Colour Colour::Blue = Colour(0.0f, 0.0f, 1.0f);
	Colour Colour::Navy = Colour(0.0f, 0.0f, 0.5f);
	Colour Colour::Fuchsia = Colour(1.0f, 0.0f, 1.0f);
	Colour Colour::Purple = Colour(0.5f, 0.0f, 0.5f);

	// A clamping tool to keep Colour value between 0.0f and 1.0f:
	void Colour::reClamp()
	{
		clamp(r, 0.0f, 1.0f);
		clamp(g, 0.0f, 1.0f);
		clamp(b, 0.0f, 1.0f);
		clamp(a, 0.0f, 1.0f);
	}
}

// Operator overloading:
kg::Colour operator +(const kg::Colour &a, const kg::Colour &b)
{
	return kg::Colour(a.r + b.r, a.g + b.g, a.b + b.b, a.a + b.a);
}

kg::Colour operator -(const kg::Colour &a, const kg::Colour &b)
{
	return kg::Colour(a.r - b.r, a.g - b.g, a.b - b.b, a.a - b.a);
}

kg::Colour operator *(const kg::Colour &a, const kg::Colour &b)
{
	return kg::Colour(a.r * b.r, a.g * b.g, a.b * b.b, a.a * b.a);
}

kg::Colour operator /(const kg::Colour &a, const kg::Colour &b)
{
	return kg::Colour(a.r / b.r, a.g / b.g, a.b / b.b, a.a / b.a);
}

kg::Colour operator +(const float &a, const kg::Colour &b)
{
	return kg::Colour(a + b.r, a + b.g, a + b.b, a + b.a);
}

kg::Colour operator -(const float &a, const kg::Colour &b)
{
	return kg::Colour(a - b.r, a - b.g, a - b.b, a - b.a);
}

kg::Colour operator *(const float &a, const kg::Colour &b)
{
	return kg::Colour(a * b.r, a * b.g, a * b.b, a * b.a);
}

kg::Colour operator /(const float &a, const kg::Colour &b)
{
	return kg::Colour(a / b.r, a / b.g, a / b.b, a / b.a);
}

kg::Colour operator +(const kg::Colour &a, const float &b)
{
	return kg::Colour(a.r + b, a.g + b, a.b + b, a.a + b);
}

kg::Colour operator -(const kg::Colour &a, const float &b)
{
	return kg::Colour(a.r - b, a.g - b, a.b - b, a.a - b);
}

kg::Colour operator *(const kg::Colour &a, const float &b)
{
	return kg::Colour(a.r * b, a.g * b, a.b * b, a.a * b);
}

kg::Colour operator /(const kg::Colour &a, const float &b)
{
	return kg::Colour(a.r / b, a.g / b, a.b / b, a.a / b);
}

