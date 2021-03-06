#include "MyMesh.h"
void MyMesh::Init(void)
{
	m_bBinded = false;
	m_uVertexCount = 0;

	m_VAO = 0;
	m_VBO = 0;

	m_pShaderMngr = ShaderManager::GetInstance();
}
void MyMesh::Release(void)
{
	m_pShaderMngr = nullptr;

	if (m_VBO > 0)
		glDeleteBuffers(1, &m_VBO);

	if (m_VAO > 0)
		glDeleteVertexArrays(1, &m_VAO);

	m_lVertex.clear();
	m_lVertexPos.clear();
	m_lVertexCol.clear();
}
MyMesh::MyMesh()
{
	Init();
}
MyMesh::~MyMesh() { Release(); }
MyMesh::MyMesh(MyMesh& other)
{
	m_bBinded = other.m_bBinded;

	m_pShaderMngr = other.m_pShaderMngr;

	m_uVertexCount = other.m_uVertexCount;

	m_VAO = other.m_VAO;
	m_VBO = other.m_VBO;
}
MyMesh& MyMesh::operator=(MyMesh& other)
{
	if (this != &other)
	{
		Release();
		Init();
		MyMesh temp(other);
		Swap(temp);
	}
	return *this;
}
void MyMesh::Swap(MyMesh& other)
{
	std::swap(m_bBinded, other.m_bBinded);
	std::swap(m_uVertexCount, other.m_uVertexCount);

	std::swap(m_VAO, other.m_VAO);
	std::swap(m_VBO, other.m_VBO);

	std::swap(m_lVertex, other.m_lVertex);
	std::swap(m_lVertexPos, other.m_lVertexPos);
	std::swap(m_lVertexCol, other.m_lVertexCol);

	std::swap(m_pShaderMngr, other.m_pShaderMngr);
}
void MyMesh::CompleteMesh(vector3 a_v3Color)
{
	uint uColorCount = m_lVertexCol.size();
	for (uint i = uColorCount; i < m_uVertexCount; ++i)
	{
		m_lVertexCol.push_back(a_v3Color);
	}
}
void MyMesh::AddVertexPosition(vector3 a_v3Input)
{
	m_lVertexPos.push_back(a_v3Input);
	m_uVertexCount = m_lVertexPos.size();
}
void MyMesh::AddVertexColor(vector3 a_v3Input)
{
	m_lVertexCol.push_back(a_v3Input);
}
void MyMesh::CompileOpenGL3X(void)
{
	if (m_bBinded)
		return;

	if (m_uVertexCount == 0)
		return;

	CompleteMesh();

	for (uint i = 0; i < m_uVertexCount; i++)
	{
		//Position
		m_lVertex.push_back(m_lVertexPos[i]);
		//Color
		m_lVertex.push_back(m_lVertexCol[i]);
	}
	glGenVertexArrays(1, &m_VAO);//Generate vertex array object
	glGenBuffers(1, &m_VBO);//Generate Vertex Buffered Object

	glBindVertexArray(m_VAO);//Bind the VAO
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);//Bind the VBO
	glBufferData(GL_ARRAY_BUFFER, m_uVertexCount * 2 * sizeof(vector3), &m_lVertex[0], GL_STATIC_DRAW);//Generate space for the VBO

	// Position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(vector3), (GLvoid*)0);

	// Color attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(vector3), (GLvoid*)(1 * sizeof(vector3)));

	m_bBinded = true;

	glBindVertexArray(0); // Unbind VAO
}
void MyMesh::Render(matrix4 a_mProjection, matrix4 a_mView, matrix4 a_mModel)
{
	// Use the buffer and shader
	GLuint nShader = m_pShaderMngr->GetShaderID("Basic");
	glUseProgram(nShader); 

	//Bind the VAO of this object
	glBindVertexArray(m_VAO);

	// Get the GPU variables by their name and hook them to CPU variables
	GLuint MVP = glGetUniformLocation(nShader, "MVP");
	GLuint wire = glGetUniformLocation(nShader, "wire");

	//Final Projection of the Camera
	matrix4 m4MVP = a_mProjection * a_mView * a_mModel;
	glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(m4MVP));
	
	//Solid
	glUniform3f(wire, -1.0f, -1.0f, -1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, m_uVertexCount);  

	//Wire
	glUniform3f(wire, 1.0f, 0.0f, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_POLYGON_OFFSET_LINE);
	glPolygonOffset(-1.f, -1.f);
	glDrawArrays(GL_TRIANGLES, 0, m_uVertexCount);
	glDisable(GL_POLYGON_OFFSET_LINE);

	glBindVertexArray(0);// Unbind VAO so it does not get in the way of other objects
}
void MyMesh::AddTri(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft)
{
	//C
	//| \
	//A--B
	//This will make the triangle A->B->C 
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);
}
void MyMesh::AddQuad(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft, vector3 a_vTopRight)
{
	//C--D
	//|  |
	//A--B
	//This will make the triangle A->B->C and then the triangle C->B->D
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);

	AddVertexPosition(a_vTopLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopRight);
}
void MyMesh::GenerateCube(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = a_fSize * 0.5f;
	//3--2
	//|  |
	//0--1

	vector3 point0(-fValue,-fValue, fValue); //0
	vector3 point1( fValue,-fValue, fValue); //1
	vector3 point2( fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	vector3 point4(-fValue,-fValue,-fValue); //4
	vector3 point5( fValue,-fValue,-fValue); //5
	vector3 point6( fValue, fValue,-fValue); //6
	vector3 point7(-fValue, fValue,-fValue); //7

	//F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateCuboid(vector3 a_v3Dimensions, vector3 a_v3Color)
{
	Release();
	Init();

	vector3 v3Value = a_v3Dimensions * 0.5f;
	//3--2
	//|  |
	//0--1
	vector3 point0(-v3Value.x, -v3Value.y, v3Value.z); //0
	vector3 point1(v3Value.x, -v3Value.y, v3Value.z); //1
	vector3 point2(v3Value.x, v3Value.y, v3Value.z); //2
	vector3 point3(-v3Value.x, v3Value.y, v3Value.z); //3

	vector3 point4(-v3Value.x, -v3Value.y, -v3Value.z); //4
	vector3 point5(v3Value.x, -v3Value.y, -v3Value.z); //5
	vector3 point6(v3Value.x, v3Value.y, -v3Value.z); //6
	vector3 point7(-v3Value.x, v3Value.y, -v3Value.z); //7

	//F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();
	std::vector<vector3> points;
	double dAngle = 360.0 / a_nSubdivisions;
	vector3 point0(0, a_fHeight, 0);
	points.push_back(point0);
	vector3 point1(0, 0, 0);
	points.push_back(point1);

	for (int i = 0; i < a_nSubdivisions; i++) {
		vector3 point2(glm::sin(glm::radians(dAngle * i))*a_fRadius, 0, glm::cos(glm::radians(dAngle * i))*a_fRadius);
		points.push_back(point2);
	}

	for (int i = 0; i <= a_nSubdivisions; i++) {
		AddTri(points[0], points[i], points[i + 1]);
	}
	for (int i = 0; i <= a_nSubdivisions; i++) {
		AddTri(points[i+1], points[i], points[1]);
	}
	AddTri(points[0], points[points.size()-1], points[2]);
	AddTri(points[2], points[points.size() - 1], points[1]);

	// Replace this with your code
	//GenerateCube(a_fRadius * 2.0f, a_v3Color);
	// -------------------------------

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();
	std::vector<vector3> pointst;
	std::vector<vector3> pointsb;
	double dAngle = 360.0 / a_nSubdivisions;
	vector3 point0(0, a_fHeight, 0);
	pointst.push_back(point0);
	vector3 point1(0, 0, 0);
	pointsb.push_back(point1);

	for (int i = 0; i < a_nSubdivisions; i++) {
		vector3 point2(glm::sin(glm::radians(dAngle * i))*a_fRadius, 0, glm::cos(glm::radians(dAngle * i))*a_fRadius);
		pointsb.push_back(point2);
		vector3 point3(glm::sin(glm::radians(dAngle * i))*a_fRadius, a_fHeight, glm::cos(glm::radians(dAngle * i))*a_fRadius);
		pointst.push_back(point3);
	}

	for (int i = 0; i < a_nSubdivisions; i++) {
		AddTri(pointsb[i + 1], pointsb[i], pointsb[0]);
		AddTri(pointst[i + 1], pointst[0],pointst[i]);
	}
	AddTri( pointsb[pointsb.size() - 1], pointsb[0], pointsb[1]);
	AddTri( pointst[pointst.size() - 1], pointst[1], pointst[0]);

	for (int i = 0; i < a_nSubdivisions; i++) {
		AddQuad(pointsb[i], pointsb[i + 1], pointst[i], pointst[i + 1]);
	}
	AddQuad(pointsb[pointsb.size() - 1], pointsb[1], pointst[pointst.size() - 1], pointst[1]);

	// Replace this with your code
	//GenerateCube(a_fRadius * 2.0f, a_v3Color);
	// -------------------------------

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fOuterRadius < 0.01f)
		a_fOuterRadius = 0.01f;

	if (a_fInnerRadius < 0.005f)
		a_fInnerRadius = 0.005f;

	if (a_fInnerRadius > a_fOuterRadius)
		std::swap(a_fInnerRadius, a_fOuterRadius);

	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	std::vector<vector3> pointst;
	std::vector<vector3> pointsb;
	std::vector<vector3> pointsti;
	std::vector<vector3> pointsbi;
	double dAngle = 360.0 / a_nSubdivisions;
	

	for (int i = 0; i < a_nSubdivisions; i++) {
		vector3 point2(glm::sin(glm::radians(dAngle * i))*a_fOuterRadius, 0, glm::cos(glm::radians(dAngle * i))*a_fOuterRadius);
		pointsb.push_back(point2);
		vector3 point3(glm::sin(glm::radians(dAngle * i))*a_fOuterRadius, a_fHeight, glm::cos(glm::radians(dAngle * i))*a_fOuterRadius);
		pointst.push_back(point3);
		vector3 point4(glm::sin(glm::radians(dAngle * i))*a_fInnerRadius, 0, glm::cos(glm::radians(dAngle * i))*a_fInnerRadius);
		pointsbi.push_back(point4);
		vector3 point5(glm::sin(glm::radians(dAngle * i))*a_fInnerRadius, a_fHeight, glm::cos(glm::radians(dAngle * i))*a_fInnerRadius);
		pointsti.push_back(point5);
	}

	for (int i = 0; i < a_nSubdivisions-1; i++) {
		AddQuad(pointsb[i], pointsb[i + 1], pointst[i], pointst[i + 1]);
		AddQuad( pointsti[i], pointsti[i + 1], pointsbi[i], pointsbi[i + 1]);
		AddQuad( pointst[i], pointst[i + 1], pointsti[i], pointsti[i + 1]);
		AddQuad( pointsbi[i], pointsbi[i + 1],pointsb[i], pointsb[i + 1]);
	}
	AddQuad( pointsbi[pointsbi.size() - 1], pointsbi[0], pointsb[pointsb.size() - 1], pointsb[0]);
	AddQuad(pointst[pointst.size() - 1], pointst[0], pointsti[pointsti.size() - 1], pointsti[0]);
	AddQuad(pointsb[pointsb.size() - 1], pointsb[0], pointst[pointst.size() - 1], pointst[0]);
	AddQuad( pointsti[pointsti.size() - 1], pointsti[0], pointsbi[pointsbi.size() - 1], pointsbi[0]);
	// Replace this with your code
	//GenerateCube(a_fOuterRadius * 2.0f, a_v3Color);
	// -------------------------------

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateTorus(float a_fRadius, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	//Sets minimum and maximum of subdivisions
	if (a_nSubdivisions < 1)
	{
		GenerateCube(a_fRadius * 2.0f, a_v3Color);
		return;
	}


	Release();
	Init();
	std::vector<vector3> points1;
	std::vector<vector3> points2;
	std::vector<vector3> points3;
	std::vector<vector3> points4;
	std::vector<vector3> points5;
	std::vector<vector3> points6;
	std::vector<vector3> points7;
	std::vector<vector3> points8;
	std::vector<vector3> points9;
	a_nSubdivisions = 10;
	double dAngle = 360.0 / a_nSubdivisions;

	vector3 point0(0, a_fRadius*.9, 0);
	vector3 point1(0, -a_fRadius*.9, 0);

	for (int i = 0; i < a_nSubdivisions; i++) {
		vector3 point2(glm::sin(glm::radians(dAngle * i))*a_fRadius*glm::sin(glm::radians(20.0f)), a_fRadius*.8, glm::cos(glm::radians(dAngle * i))*a_fRadius*glm::sin(glm::radians(20.0f)));
		points1.push_back(point2);
		vector3 point3(glm::sin(glm::radians(dAngle * i))*a_fRadius*glm::sin(glm::radians(40.0f)), a_fRadius*.6, glm::cos(glm::radians(dAngle * i))*a_fRadius*glm::sin(glm::radians(40.0f)));
		points2.push_back(point3);
		vector3 point4(glm::sin(glm::radians(dAngle * i))*a_fRadius*glm::sin(glm::radians(60.0f)), a_fRadius*.4, glm::cos(glm::radians(dAngle * i))*a_fRadius*glm::sin(glm::radians(60.0f)));
		points3.push_back(point4);
		vector3 point5(glm::sin(glm::radians(dAngle * i))*a_fRadius*glm::sin(glm::radians(80.0f)), a_fRadius*.2, glm::cos(glm::radians(dAngle * i))*a_fRadius*glm::sin(glm::radians(80.0f)));
		points4.push_back(point5);
		vector3 point6(glm::sin(glm::radians(dAngle * i))*a_fRadius, 0, glm::cos(glm::radians(dAngle * i))*a_fRadius);
		points5.push_back(point6);
		vector3 point7(glm::sin(glm::radians(dAngle * i))*a_fRadius*glm::sin(glm::radians(20.0f)), -a_fRadius*.8, glm::cos(glm::radians(dAngle * i))*a_fRadius*glm::sin(glm::radians(20.0f)));
		points9.push_back(point7);
		vector3 point8(glm::sin(glm::radians(dAngle * i))*a_fRadius*glm::sin(glm::radians(40.0f)), -a_fRadius*.6, glm::cos(glm::radians(dAngle * i))*a_fRadius*glm::sin(glm::radians(40.0f)));
		points8.push_back(point8);
		vector3 point9(glm::sin(glm::radians(dAngle * i))*a_fRadius*glm::sin(glm::radians(60.0f)), -a_fRadius*.4, glm::cos(glm::radians(dAngle * i))*a_fRadius*glm::sin(glm::radians(60.0f)));
		points7.push_back(point9);
		vector3 point12(glm::sin(glm::radians(dAngle * i))*a_fRadius*glm::sin(glm::radians(80.0f)), -a_fRadius*.2, glm::cos(glm::radians(dAngle * i))*a_fRadius*glm::sin(glm::radians(80.0f)));
		points6.push_back(point12);
	}

	//tris
	for (int i = 0; i < a_nSubdivisions - 1; i++) {
		AddTri(points1[i], points1[i + 1], point0);
		AddTri(points9[i], point1, points9[i + 1]);
	}
	//quads
	for (int i = 0; i < a_nSubdivisions - 1; i++) {
		AddQuad(points2[i], points2[i + 1], points1[i], points1[i + 1]);
		AddQuad(points3[i], points3[i + 1], points2[i], points2[i + 1]);
		AddQuad(points4[i], points4[i + 1], points3[i], points3[i + 1]);
		AddQuad(points5[i], points5[i + 1], points4[i], points4[i + 1]);
		AddQuad(points6[i], points6[i + 1], points5[i], points5[i + 1]);
		AddQuad(points7[i], points7[i + 1], points6[i], points6[i + 1]);
		AddQuad(points8[i], points8[i + 1], points7[i], points7[i + 1]);
		AddQuad(points9[i], points9[i + 1], points8[i], points8[i + 1]);
	}
	AddTri(points1[points1.size() - 1], points1[0], point0);
	AddTri(points9[points9.size() - 1], point1, points9[0]);
	AddQuad(points2[points2.size() - 1], points2[0], points1[points1.size() - 1], points1[0]);
	AddQuad(points3[points3.size() - 1], points3[0], points2[points2.size() - 1], points2[0]);
	AddQuad(points4[points4.size() - 1], points4[0], points3[points3.size() - 1], points3[0]);
	AddQuad(points5[points5.size() - 1], points5[0], points4[points4.size() - 1], points4[0]);
	AddQuad(points6[points6.size() - 1], points6[0], points5[points5.size() - 1], points5[0]);
	AddQuad(points7[points7.size() - 1], points7[0], points6[points6.size() - 1], points6[0]);
	AddQuad(points8[points8.size() - 1], points8[0], points7[points7.size() - 1], points7[0]);
	AddQuad(points9[points9.size() - 1], points9[0], points8[points8.size() - 1], points8[0]);
	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateSphere(float a_fRadius, int a_nSubdivisions, vector3 a_v3Color)
{
	/*
	Hey Ash, 
	Maybe if you're reading this, Which I don't know if you would be. can you just give me extra credit?
	like Alberto doesn't have to know, this can be just between you and me.
	you know, maybe let me know.

	Hehe XD

	-J
	
	*/


	
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	//Sets minimum and maximum of subdivisions
	if (a_nSubdivisions < 1)
	{
		GenerateCube(a_fRadius * 2.0f, a_v3Color);
		return;
	}


	Release();
	Init();
	std::vector<vector3> points1;
	std::vector<vector3> points2;
	std::vector<vector3> points3;
	std::vector<vector3> points4;
	std::vector<vector3> points5;
	std::vector<vector3> points6;
	std::vector<vector3> points7;
	std::vector<vector3> points8;
	std::vector<vector3> points9;
	
	double dAngle = 360.0 / a_nSubdivisions;
	
	vector3 point0(0, a_fRadius, 0);
	vector3 point1(0, -a_fRadius, 0);
	
	for (int i = 0; i < a_nSubdivisions; i++) {
		vector3 point2(glm::sin(glm::radians(dAngle * i))*a_fRadius*glm::sin(glm::radians(25.0f)), a_fRadius*.9, glm::cos(glm::radians(dAngle * i))*a_fRadius*glm::sin(glm::radians(25.0f)));
		points1.push_back(point2);
		vector3 point3(glm::sin(glm::radians(dAngle * i))*a_fRadius*glm::sin(glm::radians(37.5f)), a_fRadius*.8, glm::cos(glm::radians(dAngle * i))*a_fRadius*glm::sin(glm::radians(37.5f)));
		points2.push_back(point3);
		vector3 point4(glm::sin(glm::radians(dAngle * i))*a_fRadius*glm::sin(glm::radians(55.0f)), a_fRadius*.65, glm::cos(glm::radians(dAngle * i))*a_fRadius*glm::sin(glm::radians(55.0f)));
		points3.push_back(point4);
		vector3 point5(glm::sin(glm::radians(dAngle * i))*a_fRadius*glm::sin(glm::radians(70.0f)), a_fRadius*.35, glm::cos(glm::radians(dAngle * i))*a_fRadius*glm::sin(glm::radians(75.0f)));
		points4.push_back(point5);
		vector3 point6(glm::sin(glm::radians(dAngle * i))*a_fRadius, 0, glm::cos(glm::radians(dAngle * i))*a_fRadius);
		points5.push_back(point6);
		vector3 point7(glm::sin(glm::radians(dAngle * i))*a_fRadius*glm::sin(glm::radians(25.0f)), -a_fRadius*.9, glm::cos(glm::radians(dAngle * i))*a_fRadius*glm::sin(glm::radians(25.0f)));
		points9.push_back(point7);
		vector3 point8(glm::sin(glm::radians(dAngle * i))*a_fRadius*glm::sin(glm::radians(35.0f)),-a_fRadius*.8, glm::cos(glm::radians(dAngle * i))*a_fRadius*glm::sin(glm::radians(35.0f)));
		points8.push_back(point8);
		vector3 point9(glm::sin(glm::radians(dAngle * i))*a_fRadius*glm::sin(glm::radians(55.0f)), -a_fRadius*.65, glm::cos(glm::radians(dAngle * i))*a_fRadius*glm::sin(glm::radians(55.0f)));
		points7.push_back(point9);
		vector3 point12(glm::sin(glm::radians(dAngle * i))*a_fRadius*glm::sin(glm::radians(75.0f)),-a_fRadius*.35, glm::cos(glm::radians(dAngle * i))*a_fRadius*glm::sin(glm::radians(75.0f)));
		points6.push_back(point12);
	}

	//tris
	for (int i = 0; i < a_nSubdivisions-1; i++) {
		AddTri(points1[i], points1[i + 1], point0);
		AddTri(points9[i], point1, points9[i + 1]);
	}
	//quads
	for (int i = 0; i < a_nSubdivisions - 1; i++) {
		AddQuad(points2[i], points2[i + 1], points1[i], points1[i + 1]);
		AddQuad(points3[i], points3[i + 1], points2[i], points2[i + 1]);
		AddQuad(points4[i], points4[i + 1], points3[i], points3[i + 1]);
		AddQuad(points5[i], points5[i + 1], points4[i], points4[i + 1]);
		AddQuad(points6[i], points6[i + 1],points5[i], points5[i + 1]);
		AddQuad(points7[i], points7[i + 1], points6[i], points6[i + 1]);
		AddQuad(points8[i], points8[i + 1], points7[i], points7[i + 1]);
		AddQuad(points9[i], points9[i + 1], points8[i], points8[i + 1]);
	}
	AddTri(points1[points1.size() - 1], points1[0], point0);
	AddTri(points9[points9.size() - 1], point1, points9[0]);
	AddQuad(points2[points2.size() - 1], points2[0],points1[points1.size() - 1], points1[0]);
	AddQuad(points3[points3.size() - 1], points3[0], points2[points2.size() - 1], points2[0]);
	AddQuad(points4[points4.size() - 1], points4[0], points3[points3.size() - 1], points3[0]);
	AddQuad(points5[points5.size() - 1], points5[0], points4[points4.size() - 1], points4[0]);
	AddQuad(points6[points6.size() - 1], points6[0], points5[points5.size() - 1], points5[0]);
	AddQuad(points7[points7.size() - 1], points7[0], points6[points6.size() - 1], points6[0]);
	AddQuad(points8[points8.size() - 1], points8[0], points7[points7.size() - 1], points7[0]);
	AddQuad(points9[points9.size() - 1], points9[0], points8[points8.size() - 1], points8[0]);
	
	//#closeenough
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}