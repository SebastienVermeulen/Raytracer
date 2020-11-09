#include "pch.h"
#include "Renderable.h"

Renderable::Renderable(Material* pMaterial)
	:m_pMaterial(pMaterial)
{
}
Renderable::~Renderable() 
{
	//A material could be shared over multiple objects
	if (m_pMaterial)
	{
		delete m_pMaterial;
	}
}
