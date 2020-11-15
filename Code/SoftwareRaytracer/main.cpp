//********************************************************
//  Made by Vermeulen Sebastien, 08/11/2020
//  With documentation from: "Ray tracing in one weekend"
//********************************************************
// Features: Scenes and cameras, spheres, normals, 
//	multisampling, true Lambartian reflections (diffuse),
//	gamma correction, materials, (naive) metals, glass, 
//	hollow glass, depth of field
//********************************************************

//Core
#include "pch.h"
#include "DependencyInjector.h"
//Render
#include "Window.h"
#include "Renderer.h"
#include "Camera.h"
#include "Ray.h"
//Objects
#include "Scene.h"
#include "Sphere.h"

Scene* CreateRandomScene() 
{
	Scene* pScene = new Scene();

	Material* pGroundMat = new LambertDiffuse({ 0.5f,0.5f,0.5f });
	pScene->AddObject(new Sphere(vec3{ 0.f, -1000.f, 0.f }, 1000.f, pGroundMat));

	Material* pObjectMaterial{};
	for (int i = -11; i < 11; i++) 
	{
		for (int j = -11; j < 11; j++)
		{
			float randMaterialValue = RandomFloat();
			vec3 center{ i + 0.9f * RandomFloat(), 0.2f, j + 0.9f * RandomFloat() };

			if (vec3::Length(center - vec3{ 4.f, 0.2f, 0.f }) <= 0.9)
			{
				continue;
			}

			if (randMaterialValue < 0.8) 
			{
				// diffuse
				auto albedo = RandomVec3() * RandomVec3();
				pObjectMaterial = new LambertDiffuse(albedo);
				pScene->AddObject(new Sphere(center, 0.2f, pObjectMaterial));
			}
			else if (randMaterialValue < 0.95) 
			{
				// metal
				auto albedo = RandomVec3InRange(0.5f, 1.f);
				auto fuzz = RandomInRange(0.f, 0.5f);
				pObjectMaterial = new Metal(albedo, fuzz);
				pScene->AddObject(new Sphere(center, 0.2f, pObjectMaterial));
			}
			else 
			{
				// glass
				pObjectMaterial = new Dielectric(1.5f);
				pScene->AddObject(new Sphere(center, 0.2f, pObjectMaterial));
			}
		}
	}

	pObjectMaterial = new Dielectric(1.5f);
	pScene->AddObject(new Sphere(vec3(0.f, 1.f, 0.f), 1.0f, pObjectMaterial));

	pObjectMaterial = new LambertDiffuse(vec3(0.4f, 0.2f, 0.1f));
	pScene->AddObject(new Sphere(vec3(-4.f, 1.f, 0.f), 1.0f, pObjectMaterial));

	pObjectMaterial = new Metal(vec3(0.7f, 0.6f, 0.5f), 0.0f);
	pScene->AddObject(new Sphere(vec3(4.f, 1.f, 0.f), 1.0f, pObjectMaterial));

	return pScene;
}

int main(int argc, const char* argv[])
{
#pragma region InitSDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cerr << "SDL failed initialisation.\n";
	}
	else
	{
		std::cerr << "SDL succeded initialisation.\n";
	}
#pragma endregion

	//Seed rand
	std::srand(unsigned int(time(nullptr)));

#pragma region Scene1
	//Materials
	Material* pSilver = new Metal({ 0.8f,0.8f,0.8f }, 0.4f);
	Material* pGold = new Metal({ 0.7f,0.6f,0.2f }, 0.1f);
	Material* pYellow = new LambertDiffuse({ 0.8f,0.8f,0.f });
	Material* pOrange = new LambertDiffuse({ 0.7f,0.3f,0.3f });
	Material* pGlass = new Dielectric(1.5f);

	//Scene1
	Scene* pScene1 = new Scene();
	pScene1->AddObject(new Sphere(vec3{ -1.f, 0.f, -4.f }, 0.5f, pSilver));
	pScene1->AddObject(new Sphere(vec3{ 1.f, 0.f, -4.f }, 0.5f, pGold));
	pScene1->AddObject(new Sphere(vec3{ 0.f, 0.f, -4.f }, 0.5f, pOrange));
	pScene1->AddObject(new Sphere(vec3{ -1.0f, 0.f, -2.98f }, 0.5f, pGlass));
	pScene1->AddObject(new Sphere(vec3{ -1.0f, 0.f, -2.98f }, -0.45f, pGlass));
	pScene1->AddObject(new Sphere(vec3{ 1.f, 0.f, -3.f }, 0.25f, pGlass));
	pScene1->AddObject(new Sphere(vec3{ 0.f, -50.5f, -4.f }, 50.f, pYellow));
#pragma endregion
#pragma region Scene2
	//Scene2
	Scene* pScene2 = CreateRandomScene();
#pragma endregion

#pragma region InitRenderer
	//Renderer
	DependencyInjector* pInjector = DependencyInjector::Instance();
	Camera* pCam = new Camera();
	pCam->SetOriginLookAt({ 13.f, 2.f, 3.f }, { 0.f, 0.f, 0.f }, false);
	pCam->SetAspectRatio(5.f / 3.f);
	pCam->SetFOV(90.f);
	pCam->SetFocalLength(1.f);
	pCam->SetActiveScene(pScene2);
	pCam->SetRenderDist(1000.f);
	pCam->SetFocusDist(10.f);
	pCam->SetAperture(0.1f);
	pCam->SetSamplesPerPixel(10);
	pCam->SetMaxBounces(10);
	pCam->SetDOF(true);
	pInjector->SetCamera(pCam);
	Renderer* pRenderer = pInjector->InjectRenderer();
	Window* pWindow = pInjector->InjectWindow(800, 480);
	pRenderer->SetWindow(pWindow);
#pragma endregion

	//Render and track time
	std::chrono::steady_clock::time_point start = std::chrono::high_resolution_clock::now();
	pRenderer->RenderLoop();
	std::chrono::steady_clock::time_point end = std::chrono::high_resolution_clock::now();

#pragma region TimerOut
	//Calculate the time difference
	unsigned int microsec = (unsigned int)std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
	unsigned int millisec = (unsigned int)std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	unsigned int sec = (unsigned int)std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
	std::cerr << "The render time was: " << microsec << " mis.\n";
	std::cerr << "The render time was: " << millisec << " ms.\n";
	std::cerr << "The render time was: " << sec << " s.\n";
#pragma endregion

	while (!pWindow->IsClosed())
	{
		//Wait until closed
		pWindow->Tick();
	}

#pragma region Cleanup
	//Cleanup
	delete pSilver;
	delete pGold;
	delete pYellow;
	delete pOrange;
	delete pGlass;
	delete DependencyInjector::Instance();
	delete pRenderer;
	if (pScene1) 
	{
		delete pScene1;
		pScene1 = nullptr;
	}
	if (pScene2)
	{
		delete pScene2;
		pScene2 = nullptr;
	}
#pragma endregion

	return 0;
}