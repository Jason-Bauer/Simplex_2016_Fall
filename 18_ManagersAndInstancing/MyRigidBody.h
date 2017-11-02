/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2017/05
----------------------------------------------*/
#ifndef __MYRIGIDBODY_H_
#define __MYRIGIDBODY_H_

#include "MyMesh.h"
#include "MyCamera.h"
#include "Definitions.h"

namespace Simplex 
{
class MyRigidBody
{
public:
	float fRadius;
	vector3 v3Center;
	vector3 v3Min;
	vector3 v3Max;

	Mesh* m_pBS = nullptr;
	Mesh* m_pBB = nullptr;
	MyRigidBody(MyMesh* a_pMesh);
	void Render(MyCamera* a_pCamera, matrix4 a_m4Transform);
};
}

#endif //__MYRIGIDBODY_H_