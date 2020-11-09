#pragma once
class Camera;
class Renderer;

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
	Camera* InjectCamera();
	void SetCamera(Camera* pCam);

protected:
	DependencyInjector() = default;
	static DependencyInjector* m_pInstance;

private:
	Camera* m_pCamera = nullptr;
};