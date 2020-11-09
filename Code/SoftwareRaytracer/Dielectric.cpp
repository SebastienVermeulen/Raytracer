#include "pch.h"
#include "Dielectric.h"
#include "Ray.h"

Dielectric::Dielectric(const float refractionIdx)
	:m_RefractionIdx(refractionIdx)
{
}

bool Dielectric::Scatter(const Ray& rayIn, const HitRecord& hit, vec3& attenuation, Ray& rayOut) const
{
	const vec3 dir = rayIn.GetDirection();
	
	//Non colored glass
	attenuation = { 1.f, 1.f, 1.f };
	
	//Get the correct refraction
	const float refractRat = hit.frontFace ? (1.f / m_RefractionIdx) : m_RefractionIdx;

	//Prevent Snells law from "breaking" when leaving the material
	const float cosAngle = std::fminf(vec3::Dot(-1.f * dir, hit.hitNormal), 1.f);
	const float sinAngle = sqrtf(1.f - cosAngle * cosAngle);
	const bool cantRefrac = refractRat * sinAngle > 1.f;

	//Make the ray origin and scatter direction 
	vec3 rayO = hit.hitPos - hit.hitNormal * MIN_OFFSET;
	vec3 refracted{};
	if (cantRefrac || Reflectance(cosAngle, refractRat) > RandomFloat())
	{
		refracted = vec3::Reflect(dir, hit.hitNormal);
	}
	else 
	{
		refracted = vec3::Refract(dir, hit.hitNormal, refractRat);
	}

	rayOut = { rayIn.GetRenderedScene(), rayO, refracted, rayIn.GetRenderDist() };
	return true;
}

float Dielectric::Reflectance(const float cos, const float refIdx) const
{
	//Schlicks approximation for reflectance
	float r0 = (1 - refIdx) / (1 + refIdx);
	r0 = r0 * r0;
	return r0 + (1 - r0) * powf((1 - cos), 5.f);
}
