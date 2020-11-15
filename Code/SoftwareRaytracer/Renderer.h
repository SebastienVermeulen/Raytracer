#pragma once
#include <iostream>

class vec3;
class Camera;
class Scene;
class Window;

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

	void WriteColor(const int x, const int y, vec3& color) const;
	
	inline void SetWindow(Window* pWindow)
	{
		m_pWindow = pWindow;
	}

	inline Window* GetWindow() const 
	{
		return m_pWindow;
	}

private:
	Window* m_pWindow;
	Camera* m_pCamera;
};