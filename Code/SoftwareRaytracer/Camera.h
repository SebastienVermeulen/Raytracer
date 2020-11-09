#pragma once
class Ray;
class Scene;

class Camera 
{
public:
	Camera();
	Camera(const vec3& origin, const float aspectRatio, const float FOV, const float focalLength, 
		const float renderDist, const float focusDist, const float aperture, const int samplesPerPixel,
		const int maxBounces);
	Camera(const vec3& origin, const vec3& lookAt, const bool isLookAtDir, const float aspectRatio,
		const float FOV, const float focalLength, const float renderDist, const int samplesPerPixel, 
		const int maxBounces);
	Camera(const vec3& origin, const vec3& lookAt, const bool isLookAtDir, const float aspectRatio, 
		const float FOV, const float focalLength, const float renderDist, const float focusDist,
		const float aperture, const int samplesPerPixel, const int maxBounces);
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
	inline void SetActiveScene(Scene* scene) 
	{
		m_ActiveScene = scene;
	}

private:
	Scene* m_ActiveScene;

	//Camera look directions
	vec3 m_Origin;
	vec3 m_LookAt;
	vec3 m_Right, m_Up, m_Forward;

	vec3 m_BottomLeft;
	vec3 m_Horizontal;
	vec3 m_Vertical;

	//Ratio between the width and the height of the screen
	const float m_AspectRatio;
	//The angle that the width of the screen tracks, field of view
	const float m_FOV;
	//Distance from the camera point to the "screen"
	const float m_FocalLength;
	//Screen sizes
	const float m_ViewWidth;
	const float m_ViewHeight;

	//Render/world settings
	const float m_RenderDist;
	float m_LensRadius;
	const float m_FocusDist;
	const float m_Aperture;

	//Per pixel settings
	const int m_SamplesPerPixel;
	const int m_MaxBounces;

	const bool m_DOF;
};
