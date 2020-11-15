#include "pch.h"
#include "Window.h"

Window::Window(const std::string& name, const int width, const int height)
	:m_pWindow{ nullptr }
	, m_Name{ name }
	, m_Width{ width }
	, m_Height{ height }
	, m_Close{ false }
{
	m_Close = !Init();
}
Window::~Window()
{
	SDL_FreeSurface(m_pSurface);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
}
bool Window::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		std::cerr << "Failed init SDL window.\n";
		return false;
	}

	m_pWindow = SDL_CreateWindow(m_Name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED
		, m_Width, m_Height, 0);
	if (!m_pWindow) 
	{
		SDL_Log("Failed creation window: %s.\n", SDL_GetError());
		return false;
	}

	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_PRESENTVSYNC);
	if (!m_pRenderer)
	{
		SDL_Log("Failed creation renderer: %s.\n", SDL_GetError());
		return false;
	}

	Clear();
	return true;
}

void Window::Tick()
{
	SDL_Event event;

	if (!SDL_PollEvent(&event))
	{
		return;
	}

	switch (event.type)
	{
	case SDL_QUIT:
		m_Close = true;
		break;
	}
}

void Window::DrawPixel(const vec3 color, const int x, const int y)
{
	SDL_SetRenderDrawColor(m_pRenderer, (Uint8)color.x(), (Uint8)color.y(), (Uint8)color.z(), 255);
	SDL_RenderDrawPoint(m_pRenderer, x, (m_Height - 1) - y);
}
void Window::PresentBuffer()
{
	SDL_RenderPresent(m_pRenderer);
}
void Window::Clear()
{
	SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, 255);
	SDL_RenderClear(m_pRenderer);
}
