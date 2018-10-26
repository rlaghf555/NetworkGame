#pragma once

#include "Renderer.h"
#include "object.h"
#include "Global.h"
#include "Collision.h"
class ScnMgr
{
public:
	ScnMgr();
	~ScnMgr();
	void RenderScene();
	void Update(float elapsed_time_in_sec);
	void ApplyForce(float forceX, float forceY, float elapsed_time_in_sec);
	void AddObject(float px,float py,float pz, float sx,float sy,float vx,float vy,int kind);
	void Shoot(int ShootKey);
	void DeleteObject(unsigned int id);
	void ObjectCollision();
	int FindEmptyObjectSlot();
private:
	Renderer *m_Renderer;
	object *objs[MAX_OBJECTS];
	GLuint Character_Texture;
};

