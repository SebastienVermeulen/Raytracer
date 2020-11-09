#pragma once
#include "Object.h"
#include "Renderable.h"
class Ray;
struct HitRecord;

class Sphere final : public Object, Renderable
{
public:
	Sphere() = default;
	Sphere(vec3 position, float radius, Material* pMaterial);
	virtual ~Sphere();

	Sphere(Sphere& other) = delete;
	Sphere(Sphere&& other) = delete;
	Sphere operator=(Sphere& other) = delete;
	Sphere& operator=(Sphere&& other) = delete;

	bool RayCast(const Ray& ray, HitRecord& hit) const override;

	virtual bool GetDepth(const Ray& ray, HitRecord& hit) const override;
	virtual void GetNormal(HitRecord& hit) const override;

private:
	float m_Radius;
};