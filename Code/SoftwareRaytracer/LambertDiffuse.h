#pragma once
#include "MathLib.h"
#include "Material.h"

class Ray;
struct HitRecord;

class LambertDiffuse final : public Material 
{
public:
	LambertDiffuse(const vec3& albedo);
	virtual ~LambertDiffuse() = default;

	LambertDiffuse(LambertDiffuse & other) = delete;
	LambertDiffuse(LambertDiffuse && other) = delete;
	LambertDiffuse operator=(LambertDiffuse& other) = delete;
	LambertDiffuse& operator=(LambertDiffuse&& other) = delete;

	virtual bool Scatter(const Ray& rayIn, const HitRecord& hit, vec3& attenuation, Ray& rayOut) const override;

private:
	vec3 m_Albedo;
};
