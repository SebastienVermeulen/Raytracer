#include "pch.h"
#include "Renderer.h"
#include "Camera.h"
#include "Scene.h"
#include "Ray.h"

Renderer::Renderer(Camera* pCamera)
	:m_ImageHeight{ 480 }
	, m_ImageWidth{ 800 }
	, m_pCamera{ pCamera }
{
}
Renderer::~Renderer() 
{
	m_pCamera = nullptr;
}

void Renderer::RenderLoop()
{
	//Render
	std::cerr << "\nFirst frame render to file.\n";
	std::cout << "P3\n" << m_ImageWidth << ' ' << m_ImageHeight << "\n255\n";

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
	//Rows
	for (int height{ (int)m_ImageHeight - 1 }; height >= 0; height--)
	{
		//Collumns
		for (int width{ }; width <= (int)m_ImageWidth - 1; width++)
		{
			//Multisampling
			for (int sample = 0; sample < sampleNr; sample++)
			{
				//Render target uv
				uv[0] = ((float)width + RandomInRange(-0.5f, 0.5f)) 
					/ (float)(m_ImageWidth - 1);
				uv[1] = ((float)height + RandomInRange(-0.5f, 0.5f))
					/ (float)(m_ImageHeight - 1);

				//Pass along uv to make a ray
				ray = m_pCamera->GetRay(uv);
				pixel += scene.RayColor(ray, bounceNr);
				hit = HitRecord{};
			}
			WriteColor(std::cout, pixel /= (float)sampleNr);
			pixel = vec3{};
		}
	}
	std::cerr << "\nDone.\n";
}

void Renderer::WriteColor(std::ostream& out, vec3& color) const
{
	//Gamma correction, gamma = 2.0
	float r{ sqrtf(color.r()) };
	float g{ sqrtf(color.g()) };
	float b{ sqrtf(color.b()) };

	out << static_cast<int>(256 * Clamp(r, 0.f, 0.999f)) << ' '
		<< static_cast<int>(256 * Clamp(g, 0.f, 0.999f)) << ' '
		<< static_cast<int>(256 * Clamp(b, 0.f, 0.999f)) << '\n';
}
