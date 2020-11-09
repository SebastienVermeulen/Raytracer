#pragma once
#include <iostream>

class vec3;
class Camera;
class Scene;

class Renderer final
{
public:
	Renderer(Camera* pCamera);
	~Renderer();

	Renderer(Renderer& other) = delete;
	Renderer(Renderer&& other) = delete;
	Renderer operator=(Renderer& other) = delete;
	Renderer& operator=(Renderer&& other) = delete;

	void RenderLoop();

	void WriteColor(std::ostream& out, vec3& color) const;
	
	inline vec2 GetTargetSize() const 
	{
		return vec2((float)m_ImageWidth, (float)m_ImageHeight);
	}

private:
	Camera* m_pCamera;

	int m_ImageWidth;
	int m_ImageHeight;
};