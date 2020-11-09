#pragma once
class Ray;
class Material;
class vec3;
struct HitRecord;

class Renderable abstract
{
public:
	Renderable(Material* pMaterial);
	virtual ~Renderable();

	Renderable(Renderable& other) = delete;
	Renderable(Renderable&& other) = delete;
	Renderable operator=(Renderable& other) = delete;
	Renderable& operator=(Renderable&& other) = delete;

	virtual bool GetDepth(const Ray& ray, HitRecord& hit) const = 0;
	virtual void GetNormal(HitRecord& hit) const = 0;

protected:
	Material* m_pMaterial;
};