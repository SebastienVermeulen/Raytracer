#pragma once
class Ray;
class Scene;

class Camera 
{
public:
	Camera(const vec3& origin = {0.f, 0.f, 0.f}, const vec3& lookAt = { 0.f, 0.f, 0.f }, const bool isLookAtDir = false,
		const float aspectRatio = 5.f / 3.f, const float FOV = 90.f, const float focalLength = 1.f,
		const float renderDist = 1000.f, const float focusDist = 1.f, const float aperture = 1.f, 
		const int samplesPerPixel = 5, const int maxBounces = 5);
	~Camera() = default;

	Camera(Camera& other) = delete;
	Camera(Camera&& other) = delete;
	Camera operator=(Camera& other) = delete;
	Camera& operator=(Camera&& other) = delete;

	Ray GetRay(const vec2& uv) const;

	inline vec3 GetCameraSizes() const
	{
		return vec3(m_ViewHeight, m_ViewWidth, m_FocalLength);
	}
	inline vec3 GetCameraOrigin() const
	{
		return m_Origin;
	}
	inline int GetSampleNr() const
	{
		return m_SamplesPerPixel;
	}
	inline int GetMaxNrBounces() const
	{
		return m_MaxBounces;
	}

	inline const Scene& GetActiveScene() const
	{
		return *m_ActiveScene;
	}

	void SetOriginLookAt(const vec3& origin, const vec3& lookAt, const bool isLookAtDir);
	inline void SetAspectRatio(const float aspectRatio)
	{
		m_AspectRatio = aspectRatio;

		CalcViewSizes();
	}
	inline void SetFOV(const float FOV) 
	{
		m_FOV = FOV;

		CalcViewSizes();
	}
	inline void SetFocalLength(const float focalLength)
	{
		m_FocalLength = focalLength;

		CalculateViewDirections();
		CalcViewSizes();
	}
	inline void SetActiveScene(Scene* scene) 
	{
		m_ActiveScene = scene;
	}
	inline void SetRenderDist(const float renderDist) 
	{
		m_RenderDist = renderDist;
	}
	inline void SetFocusDist(const float focusDist)
	{
		m_FocusDist = focusDist;

		CalculateViewDirections();
	}
	inline void SetAperture(const float aperture)
	{
		m_Aperture = aperture;

		CalculateViewDirections();
	}
	inline void SetSamplesPerPixel(const int samplesPerPixel)
	{
		m_SamplesPerPixel = samplesPerPixel;
	}
	inline void SetMaxBounces(const int maxBounces)
	{
		m_MaxBounces = maxBounces;
	}
	inline void SetDOF(const bool DOF) 
	{
		m_DOF = DOF;
	}

private:
	void CalculateViewDirections();
	void CalcViewSizes();

	Scene* m_ActiveScene;

	//Camera look directions
	vec3 m_Origin;
	vec3 m_LookAt;
	vec3 m_Right, m_Up, m_Forward;

	vec3 m_BottomLeft;
	vec3 m_Horizontal;
	vec3 m_Vertical;

	//Ratio between the width and the height of the screen
	float m_AspectRatio;
	//The angle that the width of the screen tracks, field of view
	float m_FOV;
	//Distance from the camera point to the "screen"
	float m_FocalLength;
	//Screen sizes
	float m_ViewWidth;
	float m_ViewHeight;

	//Render/world settings
	float m_RenderDist;
	float m_LensRadius;
	float m_FocusDist;
	float m_Aperture;

	//Per pixel settings
	int m_SamplesPerPixel;
	int m_MaxBounces;

	bool m_IsLookAtDir;
	bool m_DOF;
};
