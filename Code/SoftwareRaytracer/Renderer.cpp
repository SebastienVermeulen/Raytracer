#include "pch.h"
#include "Renderer.h"
#include "Window.h"
#include "Camera.h"
#include "Scene.h"
#include "Ray.h"
#include <SDL.h>

Renderer::Renderer(Camera* pCamera)
	:m_pWindow{ nullptr }
	, m_pCamera{ pCamera }
{
}
Renderer::~Renderer() 
{
	m_pWindow = nullptr;
	m_pCamera = nullptr;
}

void Renderer::RenderLoop()
{
	vec2 windowSize = m_pWindow->GetWindowSize();

	//Render
	std::cerr << "\nFirst frame render to window.\n";
	std::cerr << "Window size: " << windowSize.x() << ' ' << windowSize.y() << "\nColor value range: 255\n";


	//To render scene
	HitRecord hit{};
	const Scene& scene = m_pCamera->GetActiveScene();

	//Create uv
	vec2 uv{};
	Ray ray{};

	//Output
	vec3 pixel{};
	const int sampleNr = m_pCamera->GetSampleNr();
	const int bounceNr = m_pCamera->GetMaxNrBounces();

	//Main render loop
	m_pWindow->Clear();

	//Rows
	for (int height{ (int)windowSize.y() - 1 }; height >= 0; height--)
	{
		//Collumns
		for (int width{ }; width <= (int)windowSize.x() - 1; width++)
		{
			//Multisampling
			for (int sample = 0; sample < sampleNr; sample++)
			{
				//Render target uv
				uv[0] = ((float)width + RandomInRange(-0.5f, 0.5f)) 
					/ (windowSize.x() - 1.f);
				uv[1] = ((float)height + RandomInRange(-0.5f, 0.5f))
					/ (windowSize.y() - 1.f);

				//Pass along uv to make a ray
				ray = m_pCamera->GetRay(uv);
				pixel += scene.RayColor(ray, bounceNr);
				hit = HitRecord{};
			}
			WriteColor(width, height, pixel /= (float)sampleNr);
			pixel = vec3{};
		}
	}

	m_pWindow->PresentBuffer();
	std::cerr << "\nFrame finished render.\n";
}

void Renderer::WriteColor(const int x, const int y, vec3& color) const
{
	//Gamma correction, gamma = 2.0
	color[0] = 255.f * sqrtf(color.r());
	color[1] = 255.f * sqrtf(color.g());
	color[2] = 255.f * sqrtf(color.b());

	m_pWindow->DrawPixel(color, x, y);
}
