#include "pch.h"
#include "Ray.h"
#include "Object.h"
#include "Scene.h"
#include "Material.h"

vec3 Ray::GetBackGround() 
{
    float t = m_Direction.y();
    return (1.f - t) * vec3(1, 1, 1) + t * vec3(0.5f, 0.7f, 1);
}
