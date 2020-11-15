#pragma once

class Window final
{
public:
	Window(const std::string& name, const int width = 800, const int height = 480);
	~Window();

	Window(Window & other) = delete;
	Window(Window && other) = delete;
	Window operator=(Window& other) = delete;
	Window& operator=(Window&& other) = delete;

	void Tick();
	void DrawPixel(const vec3 color, const int x, const int y);
	void PresentBuffer();
	void Clear();
	
	inline SDL_Surface* GetDrawingSurface() const 
	{
		return m_pWindowSurface;
	}
	inline vec2 GetWindowSize() const 
	{
		return vec2((float)m_Width, (float)m_Height);
	}

	inline bool IsClosed() const 
	{
		return m_Close;
	}

private:
	bool Init();

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	SDL_Surface* m_pWindowSurface;
	SDL_Surface* m_pSurface;

	const std::string& m_Name;
	const int m_Width;
	const int m_Height;

	bool m_Close;
};
