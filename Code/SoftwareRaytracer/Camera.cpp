#include "pch.h"
#include "Camera.h"
#include "Ray.h"
#include "Scene.h"

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
	, m_ViewWidth{ }
	, m_ViewHeight{ }
	, m_ActiveScene{}
	, m_RenderDist{ renderDist }
	, m_FocusDist{ focusDist }
	, m_Aperture{ aperture }
	, m_SamplesPerPixel{ samplesPerPixel }
	, m_MaxBounces{ maxBounces }
	, m_IsLookAtDir{ isLookAtDir }
	, m_DOF{ true }
{
	CalcViewSizes();
	CalculateViewDirections();
}

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

void Camera::SetOriginLookAt(const vec3& origin, const vec3& lookAt, const bool isLookAtDir)
{
	m_Origin = origin;
	m_LookAt = lookAt;
	m_IsLookAtDir = isLookAtDir;

	CalculateViewDirections();
}

void Camera::CalculateViewDirections()
{
	m_Forward = { m_LookAt };
	if (m_IsLookAtDir)
	{
		//Up in this case is always y = 1.f
		m_Right = vec3::Cross(m_Forward, { 0.f,1.f,0.f });
		m_Up = vec3::Cross(m_Right, m_Forward);
	}
	else
	{
		m_Forward = (m_LookAt - m_Origin).Normalised();
		//Up in this case is always y = 1.f
		m_Right = vec3::Cross(m_Forward, { 0.f,1.f,0.f });
		m_Up = vec3::Cross(m_Right, m_Forward);
	}


	m_Horizontal = m_FocusDist * m_ViewWidth * m_Right;
	m_Vertical = m_FocusDist * m_ViewHeight * m_Up;
	m_BottomLeft = m_Origin - m_Horizontal / 2.f - m_Vertical / 2.f + m_FocusDist * m_Forward * m_FocalLength;

	m_LensRadius = m_Aperture / 2.f;
}
void Camera::CalcViewSizes()
{
	m_ViewWidth = { m_FocalLength * tanf((float)M_PI * (m_FOV / 2.f) / 180.f) };
	m_ViewHeight = { m_ViewWidth / m_AspectRatio };
}
