#pragma once
#include <Vector>
#include "Object.h"
class Ray;
struct HitRecord;

class Scene final : public Object
{
public:
	Scene() = default;
	~Scene();

	Scene(Scene& other) = delete;
	Scene(Scene&& other) = delete;
	Scene operator=(Scene& other) = delete;
	Scene& operator=(Scene&& other) = delete;

	virtual bool RayCast(const Ray& ray, HitRecord& hit) const override;
	vec3 RayColor(const Ray& ray, const int maxBounes) const;

	inline void AddObject(Object* object) 
	{
		m_Objects.push_back(object);
	}
	inline const std::vector<Object*>& GetRenderObjects() const 
	{
		return m_Objects;
	}

private:
	std::vector<Object*> m_Objects;
};