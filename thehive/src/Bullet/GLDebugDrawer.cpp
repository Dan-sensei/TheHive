#include "GLDebugDrawer.h"

GLDebugDrawer::GLDebugDrawer()
:m_debugMode(0)
{}

GLDebugDrawer::~GLDebugDrawer()
{}

void	GLDebugDrawer::drawLine(const btVector3& _from,const btVector3& _to,const btVector3& _fromColor, const btVector3& _toColor)
{
	gg::Vector3f from(_from.getX(),_from.getY(),_from.getZ());
	gg::Vector3f to(_to.getX(),_to.getY(),_to.getZ());
	// float color[4] = {_fromColor.getX(),_fromColor.getY(),_fromColor.getZ(),0};
	float color[4] = {226,45,13,0};

	//Singleton<GameEngine>::Instance()->draw3DLine(from,to,color);
}

void	GLDebugDrawer::drawLine(const btVector3& _from,const btVector3& _to,const btVector3& _color)
{
	drawLine(_from,_to,_color,_color);
}

void	GLDebugDrawer::setDebugMode(int debugMode)
{
	m_debugMode = debugMode;

}
