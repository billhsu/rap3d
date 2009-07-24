#include "RapMath.h"

#include <cstdlib>

float random(float start, float end)
{
return start+(end-start)*rand()/(RAND_MAX + 1.0f);
}
