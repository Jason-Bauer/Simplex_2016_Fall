#ifndef __MYRIGIDBODY_H_
#define __MYRIGIDBODY_H_

#include "MyMesh.h"
#include"MyCamera.h"
#include"Definitions.h"


namespace Simplex {
	class MyRigidBody
	{
	public:
		Mesh* m_pBS=nullptr;
		Mesh* m_pBB = nullptr;
		float fRedius;
		vector3 v3center;
		vector3 v3min;
		vector3 v3Max;
		MyRigidBody(MyMesh* a_mesh);
		void Render(MyCamera* a_pcam,matrix4 a_m4transform);
	};

}
#endif //__MYRIGIDBODY_H_