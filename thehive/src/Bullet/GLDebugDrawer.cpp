#include "GLDebugDrawer.h"
#include <SurrealEngine/SurrealEngine.hpp>

GLDebugDrawer::GLDebugDrawer()
:m_debugMode(0)
{}

GLDebugDrawer::~GLDebugDrawer()
{}

void	GLDebugDrawer::drawLine(const btVector3& _from,const btVector3& _to,const btVector3& _fromColor, const btVector3& _toColor)
{
	glm::vec3 from(_from.getX(),_from.getY(),_from.getZ());
	glm::vec3 to(_to.getX(),_to.getY(),_to.getZ());
	// float color[4] = {_fromColor.getX(),_fromColor.getY(),_fromColor.getZ(),0};

	gg::Color color(226,45,13);

	Singleton<SurrealEngine>::Instance()->Draw3DLine(from,to,color);
}

void	GLDebugDrawer::drawLine(const btVector3& _from,const btVector3& _to,const btVector3& _color)
{
	drawLine(_from,_to,_color,_color);
}

void	GLDebugDrawer::setDebugMode(int debugMode)
{
	m_debugMode = debugMode;

}
