#include "pch.h"
#include "Sphere.h"
#include "Ray.h"
#include "Scene.h"

Sphere::Sphere(vec3 position, float radius, Material* pMaterial)
	:Object(position)
    ,Renderable(pMaterial)
	, m_Radius(radius)
{
}
Sphere::~Sphere() 
{
}

bool Sphere::RayCast(const Ray& ray, HitRecord& hit) const
{
    if (GetDepth(ray, hit))
    {
        hit.hitPos = ray.GetOrigin() + ray.GetDirection() * hit.depth;
        GetNormal(hit);
        hit.pHitMaterial = m_pMaterial;
        hit.SetNormal(ray, hit.hitNormal);
        return true;
    }
    return false;
}

bool Sphere::GetDepth(const Ray& ray, HitRecord& hit) const
{
    const float renderDist = ray.GetRenderDist();
    const vec3 rayDir = ray.GetDirection();
    const vec3 center = m_Position - ray.GetOrigin();
    const float A = vec3::Dot(rayDir, rayDir);
    const float B = -2.f * vec3::Dot(rayDir, center);
    const float C = vec3::Dot(center, center) - m_Radius * m_Radius;

    const float D = B * B - 4 * A * C;
    if (D <= 0)
    {
        //No hit or 1 hit
        return false;
    }

    //Calc intersects
    const float sqrtD = sqrt(D);
    float t1 = (-B - sqrtD) / (2 * A);
    float t2 = (-B + sqrtD) / (2 * A);

    //Calc closest prevent negative
    if (t1 <= 0)
        t1 = renderDist;
    if (t2 <= 0)
        t2 = renderDist;
    t1 = std::min(t1, t2);

    //Return intersect distance
    if (renderDist <= t1)
    {
        return false;
    }

    hit.depth = std::min(t1, hit.depth);
    return true;
}
void Sphere::GetNormal(HitRecord& hit) const
{
    hit.hitNormal = (hit.hitPos - m_Position);
    hit.hitNormal /= m_Radius;
}
