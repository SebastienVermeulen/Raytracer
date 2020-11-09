#pragma once
#include "Vector"
class Object;
class Scene;
class Material;

class Ray final
{
public:
	Ray()
		:m_ActiveScene{ nullptr }
		, m_Origin{0,0,0}
		, m_Direction{ vec3{0,0,-1.f}.Normalised() }
		, m_RenderDist{1000.0f}
	{
	}
	Ray(Scene* pScene, const vec3& o, const vec3& d, const float renderDist)
		:m_ActiveScene{ pScene }
		, m_Origin{ o }
		, m_Direction{ d }
		, m_RenderDist{ renderDist }
	{
	}
	~Ray() = default;

	Ray(Ray& other) = delete;
	Ray(Ray&& other) = delete;
	Ray operator=(Ray& other) = delete;
	Ray& operator=(Ray&& other) noexcept
	{
		m_ActiveScene = other.m_ActiveScene;
		m_Origin = other.m_Origin;
		m_Direction = other.m_Direction;
		m_RenderDist = other.m_RenderDist;
		return *this;
	}

	inline vec3 GetOrigin() const 
	{ 
		return m_Origin; 
	}
	inline vec3 GetDirection() const 
	{ 
		return m_Direction; 
	}
	vec3 GetBackGround();
	inline float GetRenderDist() const 
	{
		return m_RenderDist;
	}
	inline Scene* GetRenderedScene() const 
	{
		return m_ActiveScene;
	}
		
	inline vec3 MoveAt(const float t) 
	{
		return m_Origin + m_Direction * t;
	}

private:
	Scene* m_ActiveScene;

	vec3 m_Origin;
	vec3 m_Direction;

	float m_RenderDist;
};

struct HitRecord
{
	vec3 hitPos = vec3{};
	vec3 hitNormal = vec3{};
	Material* pHitMaterial = nullptr;
	float depth = FLT_MAX;
	bool frontFace = true;

	inline void SetNormal(const Ray& ray, const vec3& normal)
	{
		frontFace = vec3::Dot(ray.GetDirection(), normal) < 0;
		hitNormal = frontFace ? normal : -1.f * normal;
	}
};
