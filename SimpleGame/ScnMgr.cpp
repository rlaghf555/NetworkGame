#include "stdafx.h"
#include "ScnMgr.h"
#include "Collision.h"

ScnMgr::ScnMgr()
{

	for (int i = 0; i < MAX_OBJECTS; ++i) {
		objs[i] = NULL;
	}
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	// Initialize Renderer
	m_Renderer = new Renderer(WINDOW_SIZEX, WINDOW_SIZEY);
	if (!m_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
	Character_Texture = m_Renderer->CreatePngTexture("./Textures/RedCircle.png");

	for (int i = 0; i < 8; ++i) {
		objs[i] = new object();
		objs[i]->setAcc(0, 0);
		objs[i]->setforce(0, 0);
		objs[i]->setfrictionCoef(5);
		objs[i]->setmass(1.f);
		objs[i]->setVelocity(0, 0);
		objs[i]->setSize(50, 50);
		objs[i]->setkind(KIND_HERO);
		objs[i]->setview(true);
	}
	for (int i = 8; i < MAX_OBJECTS; ++i) {
		objs[i] = new object();
		objs[i]->setAcc(0, 0);
		objs[i]->setforce(0, 0);
		objs[i]->setfrictionCoef(0.5f);
		objs[i]->setmass(1.f);
		objs[i]->setVelocity(0, 0);
		objs[i]->setSize(25, 25);
		objs[i]->setkind(KIND_BULLET);
		objs[i]->setview(true);
	}
	for (int i = 0; i < MAX_OBJECTS; ++i) {
		bool check= true;
		objs[i]->setLocation(rand() % (WINDOW_SIZEX -100)- 250, rand() % (WINDOW_SIZEY-100) - 250);		
		for (int j = 0; j < MAX_OBJECTS; ++j) {
			if (i != j) {
				if (CollisionCheck(objs[i], objs[j])) {
					check = false;
					break;
				}
			}
		}
		if (check == false) {
			i--;
			continue;
		}
	}
}
int seq = 0;
void ScnMgr::RenderScene()	//1�ʿ� �ּ� 60�� �̻� ��µǾ�� �ϴ� �Լ�
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	for (int i = 0; i < MAX_OBJECTS; ++i) {
		if (objs[i]->getview()) {
			float x, y;
			objs[i]->getLocation(&x, &y);
			float width, height;
			objs[i]->getSize(&width, &height);
			
			m_Renderer->DrawTextureRectHeight(x, y, 0, width, height, 1, 1, 1, 1, Character_Texture, 0);

		}
	}
}

ScnMgr::~ScnMgr()
{
	
}
float temp = 10.f;
void ScnMgr::Update(float elapsed_time_in_sec)
{
	ObjectCollision();
	for (int i = 0; i < MAX_OBJECTS; ++i) {
		if (objs[i]->getview()) {
			objs[i]->Update(elapsed_time_in_sec);
		}
	}
}

void ScnMgr::ApplyForce(float forceX, float forceY, float elapsed_time_in_sec)
{

	objs[HERO_ID]->ApplyForce(forceX, forceY, elapsed_time_in_sec);
	
}

void ScnMgr::AddObject(float px, float py, float pz, float sx, float sy, float vx, float vy,int kind)
{

}

void ScnMgr::Shoot(int ShootKey)
{
	if (ShootKey == SHOOT_NONE) {
		return;
	}
		float px, py;
		float sx, sy;
		float vx, vy;
		objs[HERO_ID]->getLocation(&px, &py);
		sx = 0.1f;
		sy = 0.1f;
		objs[HERO_ID]->getVelocity(&vx, &vy);
		switch (ShootKey) {
			case SHOOT_LEFT:
				vx += -10.f;
				vy += 0.f;
				break;
			case SHOOT_RIGHT:
				vx += 10.0f;
				vy += 0.f;
				break;
			case SHOOT_UP:
				vx += 0.f;
				vy += 10.f;
				break;
			case SHOOT_DOWN:
				vx += 0.f;
				vy += -10.f;
				break;
		}


	
}

void ScnMgr::DeleteObject(unsigned int id)
{

}

void ScnMgr::ObjectCollision()
{
	
	for (int i = 0; i < MAX_OBJECTS; ++i) {
		if(objs[i]->getview())
		for (int j = 0; j < MAX_OBJECTS; ++j) {
			if(i!=j)
			if (objs[j]->getview()) {
				if (CollisionCheck(objs[i], objs[j])) {
					//����ó��
					/*
					objs[i]kind ojbs[j]kind

					
					*/
					//ĳ���� - ĳ����  ���� �б�

					//ĳ���� - ��(������ ��-�Ծ�����, �� ��-, ���� ��)
					
					//�� - ��

				//	DeleteObject(j);
					std::cout << "collision" << std::endl;
				}
			}
		}
	}

}


int ScnMgr::FindEmptyObjectSlot()
{
	for (int i = 0; i < MAX_OBJECTS; ++i) {
		if (objs[i] == NULL)
			return i;
	}
	std::cout << "object list is full.\n";
	return -1;
}


