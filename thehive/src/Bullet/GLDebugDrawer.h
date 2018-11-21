#ifndef GL_DEBUG_DRAWER_H
#define GL_DEBUG_DRAWER_H

#include <stdio.h>
#include <iostream>
#include <irrlicht/irrlicht.h>
#include <LinearMath/btIDebugDraw.h>

#include <GameEngine/GameEngine.hpp>
#include <Singleton.hpp>
#include <Util.hpp>

class GLDebugDrawer : public btIDebugDraw
{
	int m_debugMode;

public:

	GLDebugDrawer();
	virtual ~GLDebugDrawer();

	virtual void	drawLine(const btVector3& _from,const btVector3& _to,const btVector3& _fromColor, const btVector3& _toColor);

	virtual void	drawLine(const btVector3& _from,const btVector3& _to,const btVector3& _color);

	virtual void	drawSphere (const btVector3& p, btScalar radius, const btVector3& color){}

	virtual void	drawTriangle(const btVector3& a,const btVector3& b,const btVector3& c,const btVector3& color,btScalar alpha){}

	virtual void	drawContactPoint(const btVector3& PointOnB,const btVector3& normalOnB,btScalar distance,int lifeTime,const btVector3& color){}

	virtual void	reportErrorWarning(const char* warningString){}

	virtual void	draw3dText(const btVector3& location,const char* textString){}

	virtual void	setDebugMode(int debugMode);

	virtual int		getDebugMode() const { return m_debugMode;}

};

#endif//GL_DEBUG_DRAWER_H
