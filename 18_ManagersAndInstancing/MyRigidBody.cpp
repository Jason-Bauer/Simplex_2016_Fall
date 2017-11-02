#include "MyRigidBody.h"

Simplex::MyRigidBody::MyRigidBody(MyMesh* a_mesh)
{
	m_pBS = new Mesh();
	//m_pBS->GenerateIcoSphere(1, 2, C_WHITE);
	if (a_mesh == nullptr) {
		return;
	}
	std::vector<vector3> pointslis = a_mesh->GetVertexList();
	if (pointslis.size() < 1) {
		return;
	}
	fRedius = 0.0f;
	 v3center;
	 v3min = pointslis[0];
	 v3Max = pointslis[0];
	for (uint i = 1; i < pointslis.size(); i++) {
		if (pointslis[i].x < v3min.x)
			v3min.x = pointslis[i].x;
		else if (pointslis[i].x > v3Max.x)
			v3Max.x = pointslis[i].x;

		if (pointslis[i].y < v3min.y)
			v3min.y = pointslis[i].y;
		else if (pointslis[i].y > v3Max.y)
			v3Max.y = pointslis[i].y;

		if (pointslis[i].z < v3min.z)
			v3min.z = pointslis[i].z;
		else if (pointslis[i].z > v3Max.z)
			v3Max.z = pointslis[i].z;

	}
	v3center = (v3min + v3Max) / 2.0f;
	fRedius = glm::distance(v3center, v3Max);
	m_pBS->GenerateIcoSphere(fRedius, 2, C_WHITE);
	m_pBB = new Mesh();
	m_pBB->GenerateCube(1, C_WHITE);
}

void Simplex::MyRigidBody::Render(MyCamera* a_pcam, matrix4 a_m4transform)
{
	float* pTemp = new float[16];
	matrix4 m4resize = glm::scale(a_m4transform, vector3(fRedius));
	memcpy(pTemp, glm::value_ptr(m4resize), 16 * sizeof(float));
	m_pBS->RenderWire(a_pcam->GetProjectionMatrix(), a_pcam->GetViewMatrix(), pTemp, 1);
	
	vector3 v3size=v3Max-v3min;
	m4resize =glm::scale(a_m4transform, v3size);
	memcpy(pTemp, glm::value_ptr(m4resize), 16 * sizeof(float));
	m_pBB->RenderWire(a_pcam->GetProjectionMatrix(), a_pcam->GetViewMatrix(), pTemp, 1);
	SafeDelete(pTemp);
}
