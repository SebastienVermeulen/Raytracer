#pragma once
#include "MathLib.h"
class Ray;
struct HitRecord;

class Material abstract
{
public:
	Material() = default;
	virtual ~Material() = default;

	Material(Material & other) = delete;
	Material(Material && other) = delete;
	Material operator=(Material& other) = delete;
	Material& operator=(Material&& other) = delete;

	virtual bool Scatter(const Ray& rayIn, const HitRecord& hit, vec3& attenuation, Ray& rayOut) const = 0;
};
