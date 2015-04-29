#include "platformInclude.h"

namespace kg
{
	template <typename T>
	void clamp(T &in, T min, T max)
	{
		if (in > max)
			in = max;
		else if (in < min)
			in = min;
	}
	
	template <typename T>
	void range(T &in, T min, T max)
	{
		T range = max - min;
	
		while (in > max)
			in -= range;
		while (in < min)
			in += range;
	}
}
