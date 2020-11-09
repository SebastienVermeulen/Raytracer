#pragma once
#include "Material.h"
#include "MathLib.h"

class Dielectric final : public Material 
{
public:
	Dielectric(const float refractionIdx);
	virtual ~Dielectric() = default;

	Dielectric(Dielectric & other) = delete;
	Dielectric(Dielectric && other) = delete;
	Dielectric operator=(Dielectric& other) = delete;
	Dielectric& operator=(Dielectric&& other) = delete;

	virtual bool Scatter(const Ray& rayIn, const HitRecord& hit, vec3& attenuation, Ray& rayOut) const override;

private:
	float Reflectance(const float cos, const float refIdx) const;

	float m_RefractionIdx;
};