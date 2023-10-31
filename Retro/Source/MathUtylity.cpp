#include "MathUtylity.h"

mu::vec2Int::vec2Int(vec2 a)
{
	x = static_cast<int>(a.x);
	y = static_cast<int>(a.y);

}

mu::vec2Int::vec2Int(int32_t _x, int32_t _y)
{
	x = _x;
	y = _y;
}
