#include "pch.h"
#include "Scene.h"
#include "Ray.h"
#include "Material.h"

Scene::~Scene() 
{
	for (size_t i = 0; i < m_Objects.size(); i++)
	{
		delete m_Objects[i];
		m_Objects[i] = nullptr;
	}
}

bool Scene::RayCast(const Ray& ray, HitRecord& hit) const
{
	HitRecord tempHit{};
	vec3 finalColor{};
	//Set starting dist to max
	hit.depth = ray.GetRenderDist();

	//Go over all renderable objects
	//Determine the closest proper intersect
	for (size_t i = 0; i < m_Objects.size(); i++)
	{
		if (m_Objects[i]->RayCast(ray, tempHit) && hit.depth > tempHit.depth)
		{
			hit = tempHit;
		}
	}

	return (hit.depth < ray.GetRenderDist());
}
vec3 Scene::RayColor(const Ray& ray, const int maxBounes) const
{
	// Too many bounces returns 0
	if (maxBounes <= 0)
	{
		return vec3{ 0.f, 0.f, 0.f };
	}

	HitRecord hit{};
	if (RayCast(ray, hit))
	{
		//Check the material to recieve the correct bounce ray
		Ray rayOut{};
		vec3 col{};

		if (hit.pHitMaterial && hit.pHitMaterial->Scatter(ray, hit, col, rayOut))
		{
			//Start a new bounce with a bounce less as the max amount allowed
			return col * RayColor(rayOut, maxBounes - 1);
		}

		return vec3{ 0.f, 0.f, 0.f };
	}

	//Background
	auto t = 0.5f * (ray.GetDirection().y() + 1.0f);
	return (1.0f - t) * vec3 { 1.0f, 1.0f, 1.0f } + t * vec3{ 0.5f, 0.7f, 1.0f };
}
