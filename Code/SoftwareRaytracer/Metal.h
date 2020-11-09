#pragma once
#include "Material.h"
#include "MathLib.h"

class Metal final : public Material
{
public:
	Metal(const vec3& albedo, const float fuzzFactor);
	virtual ~Metal() = default;

	Metal(Metal& other) = delete;
	Metal(Metal&& other) = delete;
	Metal operator=(Metal& other) = delete;
	Metal& operator=(Metal&& other) = delete;

	virtual bool Scatter(const Ray& rayIn, const HitRecord& hit, vec3& attenuation, Ray& rayOut) const override;

private:
	vec3 m_Albedo;
	float m_FuzzFactor;
};