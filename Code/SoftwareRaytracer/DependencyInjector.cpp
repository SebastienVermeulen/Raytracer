#include "pch.h"
#include "DependencyInjector.h"
#include "Renderer.h"
#include "Window.h"
#include "Camera.h"

DependencyInjector* DependencyInjector::m_pInstance = nullptr;

DependencyInjector::~DependencyInjector()
{
	delete m_pWindow;
	delete m_pCamera;

	m_pInstance = nullptr;
}

Renderer* DependencyInjector::InjectRenderer()
{
	return new Renderer(InjectCamera());
}
Window* DependencyInjector::InjectWindow(const int width, const int height)
{
	if (!m_pWindow)
	{
		m_pWindow = new Window("Renderer", width, height);
	}
	return m_pWindow;
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
