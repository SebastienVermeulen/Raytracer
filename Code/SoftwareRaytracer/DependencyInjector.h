#pragma once
class Renderer;
class Window;
class Camera;

class DependencyInjector 
{
public:
	static inline DependencyInjector* Instance() 
	{
		if (!m_pInstance) 
		{
			m_pInstance = new DependencyInjector();
		}
		return m_pInstance;
	}
	virtual ~DependencyInjector();

	DependencyInjector(DependencyInjector& other) = delete;
	DependencyInjector(DependencyInjector&& other) = delete;
	DependencyInjector operator=(DependencyInjector& other) = delete;
	DependencyInjector& operator=(DependencyInjector&& other) = delete;

	Renderer* InjectRenderer();
	Window* InjectWindow(const int width, const int height);
	Camera* InjectCamera();
	
	void SetCamera(Camera* pCam);

protected:
	DependencyInjector() = default;
	static DependencyInjector* m_pInstance;

private:
	Window* m_pWindow = nullptr;
	Camera* m_pCamera = nullptr;
};