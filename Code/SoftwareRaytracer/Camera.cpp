#include "pch.h"
#include "Camera.h"
#include "Ray.h"
#include "Scene.h"

#pragma region Default
Camera::Camera()
	:m_Origin({ 0.f, 0.f, 0.f })
	, m_LookAt({ 0.f, 0.f, -1.f })
	, m_Forward({})
	, m_Right({})
	, m_Up({})
	, m_AspectRatio{ 5.f / 3.f }//16.f / 9.f }
	, m_FOV{90.f}
	, m_FocalLength{ 1.f }
	, m_ViewWidth{ m_FocalLength * tanf((float)M_PI * (m_FOV / 2.f) / 180.f) }
	, m_ViewHeight{ m_ViewWidth / m_AspectRatio }
	, m_ActiveScene{}
	, m_RenderDist{1000.f}
	, m_FocusDist{ 1.f }
	, m_Aperture{ 1.f }
	, m_SamplesPerPixel{100}
	, m_MaxBounces{50}
	, m_DOF{ false }
{
	//Up in this case is always y = 1.f
	m_Forward = { m_LookAt };
	m_Right = vec3::Cross(m_Forward, { 0.f,1.f,0.f });
	m_Up = vec3::Cross(m_Right, m_Forward);

	const vec3 horizontal = m_ViewWidth * m_Right;
	const vec3 vertical = m_ViewHeight * m_Up;
	m_BottomLeft = m_Origin - horizontal / 2.f - vertical / 2.f + m_Forward * m_FocalLength;
}
#pragma endregion
#pragma region DefaultWithPosAndDOF
Camera::Camera(const vec3& origin, const float aspectRatio, const float FOV, const float focalLength, 
	const float renderDist, const float focusDist, const float aperture, const int samplesPerPixel, const int maxBounces)
	:m_Origin(origin)
	, m_LookAt({ 0.f, 0.f, -1.f })
	, m_Forward({})
	, m_Right({})
	, m_Up({})
	, m_AspectRatio{ aspectRatio }
	, m_FOV{ FOV }
	, m_FocalLength{ focalLength }
	, m_ViewWidth{ m_FocalLength * tanf((float)M_PI * (m_FOV / 2.f) / 180.f) }
	, m_ViewHeight{ m_ViewWidth / m_AspectRatio }
	, m_ActiveScene{}
	, m_RenderDist{ renderDist }
	, m_FocusDist{ focusDist }
	, m_Aperture{ aperture }
	, m_SamplesPerPixel{ samplesPerPixel }
	, m_MaxBounces{ maxBounces }
	, m_DOF{ true }
{
	//Up in this case is always y = 1.f
	m_Forward = { m_LookAt };
	m_Right = vec3::Cross(m_Forward, { 0.f,1.f,0.f });
	m_Up = vec3::Cross(m_Right, m_Forward);

	m_Horizontal = m_FocusDist * m_ViewWidth * m_Right;
	m_Vertical = m_FocusDist * m_ViewHeight * m_Up;
	m_BottomLeft = m_Origin - m_Horizontal / 2.f - m_Vertical / 2.f + m_FocusDist * m_Forward * m_FocalLength;

	m_LensRadius = m_Aperture / 2.f;
}
#pragma endregion 
#pragma region PosAndDir
Camera::Camera(const vec3& origin, const vec3& lookAt, const bool isLookAtDir, const float aspectRatio,
	const float FOV, const float focalLength, const float renderDist, const int samplesPerPixel,
	const int maxBounces)
	:m_Origin(origin)
	, m_LookAt(lookAt)
	, m_Forward({})
	, m_Right({})
	, m_Up({})
	, m_AspectRatio{ aspectRatio }
	, m_FOV{ FOV }
	, m_FocalLength{ focalLength }
	, m_ViewWidth{ m_FocalLength * tanf((float)M_PI * (m_FOV / 2.f) / 180.f) }
	, m_ViewHeight{ m_ViewWidth / m_AspectRatio }
	, m_ActiveScene{}
	, m_RenderDist{ renderDist }
	, m_FocusDist{ 1.f }
	, m_Aperture{ 1.f }
	, m_SamplesPerPixel{ samplesPerPixel }
	, m_MaxBounces{ maxBounces }
	, m_DOF{ false }
{
	m_Forward = { m_LookAt };
	if (isLookAtDir)
	{
		//Up in this case is always y = 1.f
		m_Right = vec3::Cross(m_Forward, { 0.f,1.f,0.f });
		m_Up = vec3::Cross(m_Right, m_Forward);
	}
	else
	{
		m_Forward = (lookAt - origin).Normalised();
		//Up in this case is always y = 1.f
		m_Right = vec3::Cross(m_Forward, { 0.f,1.f,0.f });
		m_Up = vec3::Cross(m_Right, m_Forward);
	}

	m_Horizontal = m_ViewWidth * m_Right;
	m_Vertical = m_ViewHeight * m_Up;
	m_BottomLeft = m_Origin - m_Horizontal / 2.f - m_Vertical / 2.f + m_Forward * m_FocalLength;
}
#pragma endregion
#pragma region PosAndDirAndDOF
Camera::Camera(const vec3& origin, const vec3& lookAt, const bool isLookAtDir, const float aspectRatio, const float FOV, const float focalLength,
	const float renderDist, const float focusDist, const float aperture, const int samplesPerPixel, const int maxBounces)
	:m_Origin(origin)
	, m_LookAt(lookAt)
	, m_Forward({})
	, m_Right({})
	, m_Up({})
	, m_AspectRatio{ aspectRatio }
	, m_FOV{ FOV }
	, m_FocalLength{ focalLength }
	, m_ViewWidth{ m_FocalLength * tanf((float)M_PI * (m_FOV / 2.f) / 180.f) }
	, m_ViewHeight{ m_ViewWidth / m_AspectRatio }
	, m_ActiveScene{}
	, m_RenderDist{ renderDist }
	, m_FocusDist{ focusDist }
	, m_Aperture{ aperture }
	, m_SamplesPerPixel{ samplesPerPixel }
	, m_MaxBounces{ maxBounces }
	, m_DOF{ true }
{
	m_Forward = { m_LookAt };
	if (isLookAtDir)
	{
		//Up in this case is always y = 1.f
		m_Right = vec3::Cross(m_Forward, { 0.f,1.f,0.f });
		m_Up = vec3::Cross(m_Right, m_Forward);
	}
	else 
	{
		m_Forward = (lookAt - origin).Normalised();
		//Up in this case is always y = 1.f
		m_Right = vec3::Cross(m_Forward, { 0.f,1.f,0.f });
		m_Up = vec3::Cross(m_Right, m_Forward);
	}

	m_Horizontal = m_FocusDist * m_ViewWidth * m_Right;
	m_Vertical = m_FocusDist * m_ViewHeight * m_Up;
	m_BottomLeft = m_Origin - m_Horizontal / 2.f - m_Vertical / 2.f + m_FocusDist * m_Forward * m_FocalLength;

	m_LensRadius = m_Aperture / 2.f;
}
#pragma endregion

Ray Camera::GetRay(const vec2& uv) const
{
	if (m_DOF)
	{
		vec3 lensDir = m_LensRadius * RandomPointInUnitDisk();
		vec3 offset = m_Right * lensDir.x() + m_Up * lensDir.y();

		vec3 direction = m_BottomLeft + uv.x() * m_Horizontal + uv.y() * m_Vertical - m_Origin - offset;
		return { m_ActiveScene, m_Origin + offset, direction.Normalised(), m_RenderDist };
	}
	else 
	{
		vec3 direction = m_BottomLeft + uv.x() * m_Horizontal + uv.y() * m_Vertical - m_Origin;
		return { m_ActiveScene, m_Origin, direction.Normalised(), m_RenderDist };
	}
}
