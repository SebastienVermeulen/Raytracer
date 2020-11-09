#include "pch.h"
#include "LambertDiffuse.h"
#include "Ray.h"

LambertDiffuse::LambertDiffuse(const vec3& albedo)
	:m_Albedo(albedo)
{
}

bool LambertDiffuse::Scatter(const Ray& rayIn, const HitRecord& hit, vec3& attenuation, Ray& rayOut) const 
{
	//Make the ray origin and scatter direction 
	vec3 rayO = hit.hitPos + hit.hitNormal * MIN_OFFSET;
	vec3 rayD = hit.hitNormal + RandomPointInUnitSphere();
	rayD.Normalise();

	//Check on the offchance that it is a zero vector
	if (rayD.NearZero())
	{
		rayD = hit.hitNormal;
	}

	//Create the ray and return the albedo
	rayOut = { rayIn.GetRenderedScene(), rayO, rayD, rayIn.GetRenderDist() };
	attenuation = m_Albedo;
	return true;
}