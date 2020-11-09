#pragma once
#include "MathLib.h"
class Ray;
struct HitRecord;

class Object abstract
{
public:
	Object() = default;
	Object(vec3 position) 
		:m_Position(position)
	{
	}
	virtual ~Object();

	Object(Object& other) = delete;
	Object(Object&& other) = delete;
	Object operator=(Object& other) = delete;
	Object& operator=(Object&& other) = delete;

	virtual bool RayCast(const Ray& ray, HitRecord& hit) const = 0;

protected:
	vec3 m_Position;
};