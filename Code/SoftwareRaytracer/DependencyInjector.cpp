#include "pch.h"
#include "DependencyInjector.h"
#include "Camera.h"
#include "Renderer.h"

DependencyInjector* DependencyInjector::m_pInstance = nullptr;

DependencyInjector::~DependencyInjector()
{
	delete m_pCamera;

	m_pInstance = nullptr;
}

Renderer* DependencyInjector::InjectRenderer()
{
	return new Renderer(InjectCamera());
}
Camera* DependencyInjector::InjectCamera()
{
	if (!m_pCamera)
	{
		m_pCamera = new Camera();
	}
	return m_pCamera;
}
void DependencyInjector::SetCamera(Camera* pCam)
{
	if (m_pCamera)
	{
		delete m_pCamera;
	}
	m_pCamera = pCam;
}
