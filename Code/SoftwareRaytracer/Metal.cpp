#include "pch.h"
#include "Metal.h"
#include "Ray.h"

Metal::Metal(const vec3& albedo, const float fuzzFactor)
	:m_Albedo(albedo)
	, m_FuzzFactor(fuzzFactor < 1.f ? fuzzFactor : 1.f)
{
}

bool Metal::Scatter(const Ray& rayIn, const HitRecord& hit, vec3& attenuation, Ray& rayOut) const
{
	//Make the ray origin and scatter direction 
	vec3 rayO = hit.hitPos + hit.hitNormal * MIN_OFFSET;
	vec3 reflected = vec3::Reflect(rayIn.GetDirection(), hit.hitNormal);

	//Create the ray and return the albedo
	rayOut = { rayIn.GetRenderedScene(), rayO, reflected + m_FuzzFactor * RandomPointInUnitSphere(), rayIn.GetRenderDist() };
	attenuation = m_Albedo;

	//Get the dot between the normal and the reflected direction
	return vec3::Dot(reflected, hit.hitNormal) > 0.f;
}
