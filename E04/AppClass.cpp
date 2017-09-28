#include "AppClass.h"
void Application::InitVariables(void)
{
	
	////Change this to your name and email
	//m_sProgrammer = "Alberto Bobadilla - labigm@rit.edu";

	////Alberto needed this at this position for software recording.
	//m_pWindow->setPosition(sf::Vector2i(710, 0));

	//Make MyMesh object
	m_pMesh0 = new MyMesh();
	m_pMesh0->GenerateCube(1.0f, C_BROWN);
	
	m_pMesh1 = new MyMesh();
	m_pMesh1->GenerateCube(1.0f, C_BROWN);
	m_pMesh2 = new MyMesh();
	m_pMesh2->GenerateCube(1.0f, C_BROWN);
	m_pMesh3 = new MyMesh();
	m_pMesh3->GenerateCube(1.0f, C_BROWN);
	m_pMesh4 = new MyMesh();
	m_pMesh4->GenerateCube(1.0f, C_BROWN);
	m_pMesh5 = new MyMesh();
	m_pMesh5->GenerateCube(1.0f, C_BROWN);
	m_pMesh6 = new MyMesh();
	m_pMesh6->GenerateCube(1.0f, C_BROWN);
	m_pMesh7 = new MyMesh();
	m_pMesh7->GenerateCube(1.0f, C_BROWN);
	m_pMesh8 = new MyMesh();
	m_pMesh8->GenerateCube(1.0f, C_BROWN);
	m_pMesh9 = new MyMesh();
	m_pMesh9->GenerateCube(1.0f, C_BROWN);
	m_pMesh10 = new MyMesh();
	m_pMesh10->GenerateCube(1.0f, C_BROWN);
	m_pMesh11 = new MyMesh();
	m_pMesh11->GenerateCube(1.0f, C_BROWN);
	m_pMesh12 = new MyMesh();
	m_pMesh12->GenerateCube(1.0f, C_BROWN);
	m_pMesh13 = new MyMesh();
	m_pMesh13->GenerateCube(1.0f, C_BROWN);
	m_pMesh14 = new MyMesh();
	m_pMesh14->GenerateCube(1.0f, C_BROWN);
	m_pMesh15 = new MyMesh();
	m_pMesh15->GenerateCube(1.0f, C_BROWN);
	m_pMesh16 = new MyMesh();
	m_pMesh16->GenerateCube(1.0f, C_BROWN);
	m_pMesh17 = new MyMesh();
	m_pMesh17->GenerateCube(1.0f, C_BROWN);
	m_pMesh18 = new MyMesh();
	m_pMesh18->GenerateCube(1.0f, C_BROWN);
	m_pMesh19 = new MyMesh();
	m_pMesh19->GenerateCube(1.0f, C_BROWN);
	m_pMesh20 = new MyMesh();
	m_pMesh20->GenerateCube(1.0f, C_BROWN);
	m_pMesh21 = new MyMesh();
	m_pMesh21->GenerateCube(1.0f, C_BROWN);
	m_pMesh22 = new MyMesh();
	m_pMesh22->GenerateCube(1.0f, C_BROWN);
	m_pMesh23 = new MyMesh();
	m_pMesh23->GenerateCube(1.0f, C_BROWN);
	m_pMesh24 = new MyMesh();
	m_pMesh24->GenerateCube(1.0f, C_BROWN);
	m_pMesh25 = new MyMesh();
	m_pMesh25->GenerateCube(1.0f, C_BROWN);
	m_pMesh26 = new MyMesh();
	m_pMesh26->GenerateCube(1.0f, C_BROWN);
	m_pMesh27 = new MyMesh();
	m_pMesh27->GenerateCube(1.0f, C_BROWN);
	m_pMesh28 = new MyMesh();
	m_pMesh28->GenerateCube(1.0f, C_BROWN);
	m_pMesh29 = new MyMesh();
	m_pMesh29->GenerateCube(1.0f, C_BROWN);
	m_pMesh30 = new MyMesh();
	m_pMesh30->GenerateCube(1.0f, C_BROWN);
	m_pMesh31 = new MyMesh();
	m_pMesh31->GenerateCube(1.0f, C_BROWN);
	m_pMesh32 = new MyMesh();
	m_pMesh32->GenerateCube(1.0f, C_BROWN);
	m_pMesh33 = new MyMesh();
	m_pMesh33->GenerateCube(1.0f, C_BROWN);
	m_pMesh34 = new MyMesh();
	m_pMesh34->GenerateCube(1.0f, C_BROWN);
	m_pMesh35 = new MyMesh();
	m_pMesh35->GenerateCube(1.0f, C_BROWN);
	m_pMesh36 = new MyMesh();
	m_pMesh36->GenerateCube(1.0f, C_BROWN);
	m_pMesh37 = new MyMesh();
	m_pMesh37->GenerateCube(1.0f, C_BROWN);
	m_pMesh38 = new MyMesh();
	m_pMesh38->GenerateCube(1.0f, C_BROWN);
	m_pMesh39 = new MyMesh();
	m_pMesh39->GenerateCube(1.0f, C_BROWN);
	m_pMesh40 = new MyMesh();
	m_pMesh40->GenerateCube(1.0f, C_BROWN);
	m_pMesh41 = new MyMesh();
	m_pMesh41->GenerateCube(1.0f, C_BROWN);
	m_pMesh42 = new MyMesh();
	m_pMesh42->GenerateCube(1.0f, C_BROWN);
	m_pMesh43 = new MyMesh();
	m_pMesh43->GenerateCube(1.0f, C_BROWN);
	m_pMesh44 = new MyMesh();
	m_pMesh44->GenerateCube(1.0f, C_BROWN);
	m_pMesh45 = new MyMesh();
	m_pMesh45->GenerateCube(1.0f, C_BROWN);
	m_pMesh46 = new MyMesh();
	m_pMesh46->GenerateCube(1.0f, C_BROWN);
	m_pMesh47 = new MyMesh();
	m_pMesh47->GenerateCube(1.0f, C_BROWN);
	m_pMesh48 = new MyMesh();
	m_pMesh48->GenerateCube(1.0f, C_BROWN);
	
	meshes.push_back(m_pMesh0);
	meshes.push_back(m_pMesh1);
	meshes.push_back(m_pMesh2);
	meshes.push_back(m_pMesh3);
	meshes.push_back(m_pMesh4);
	meshes.push_back(m_pMesh5);
	meshes.push_back(m_pMesh6);
	meshes.push_back(m_pMesh7);
	meshes.push_back(m_pMesh8);
	meshes.push_back(m_pMesh9);
	meshes.push_back(m_pMesh10);
	meshes.push_back(m_pMesh11);
	meshes.push_back(m_pMesh12);
	meshes.push_back(m_pMesh13);
	meshes.push_back(m_pMesh14);
	meshes.push_back(m_pMesh15);
	meshes.push_back(m_pMesh16);
	meshes.push_back(m_pMesh17);
	meshes.push_back(m_pMesh18);
	meshes.push_back(m_pMesh19);
	meshes.push_back(m_pMesh20);
	meshes.push_back(m_pMesh21);
	meshes.push_back(m_pMesh22);
	meshes.push_back(m_pMesh23);
	meshes.push_back(m_pMesh24);
	meshes.push_back(m_pMesh25);
	meshes.push_back(m_pMesh26);
	meshes.push_back(m_pMesh27);
	meshes.push_back(m_pMesh28);
	meshes.push_back(m_pMesh29);
	meshes.push_back(m_pMesh30);
	meshes.push_back(m_pMesh31);
	meshes.push_back(m_pMesh32);
	meshes.push_back(m_pMesh33);
	meshes.push_back(m_pMesh34);
	meshes.push_back(m_pMesh35);
	meshes.push_back(m_pMesh36);
	meshes.push_back(m_pMesh37);
	meshes.push_back(m_pMesh38);
	meshes.push_back(m_pMesh39);
	meshes.push_back(m_pMesh40);
	meshes.push_back(m_pMesh41);
	meshes.push_back(m_pMesh42);
	meshes.push_back(m_pMesh43);
	meshes.push_back(m_pMesh44);
	meshes.push_back(m_pMesh45);
	meshes.push_back(m_pMesh46);
	meshes.push_back(m_pMesh47);
	meshes.push_back(m_pMesh48);
	
	//bottom half
	matricies.push_back(glm::translate(vector3(0.0f, 0.0f, 0.0f)));
	matricies.push_back(glm::translate(vector3(1.0f, 0.0f, 0.0f)));
	matricies.push_back(glm::translate(vector3(2.0f, 0.0f, 0.0f)));
	matricies.push_back(glm::translate(vector3(3.0f, 0.0f, 0.0f)));//
	matricies.push_back(glm::translate(vector3(4.0f, 0.0f, 0.0f)));
	matricies.push_back(glm::translate(vector3(5.0f, 0.0f, 0.0f)));
	matricies.push_back(glm::translate(vector3(6.0f, 0.0f, 0.0f)));
	matricies.push_back(glm::translate(vector3(7.0f, 0.0f, 0.0f)));
	matricies.push_back(glm::translate(vector3(8.0f, 0.0f, 0.0f)));
	matricies.push_back(glm::translate(vector3(9.0f, 0.0f, 0.0f)));
	matricies.push_back(glm::translate(vector3(10.0f, 0.0f, 0.0f)));
	matricies.push_back(glm::translate(vector3(10.0f, -1.0f, 0.0f)));
	matricies.push_back(glm::translate(vector3(10.0f, -2.0f, 0.0f)));
	matricies.push_back(glm::translate(vector3(0.0f, -1.0f, 0.0f)));
	matricies.push_back(glm::translate(vector3(0.0f, -2.0f, 0.0f)));
	matricies.push_back(glm::translate(vector3(2.0f, -1.0f, 0.0f)));
	matricies.push_back(glm::translate(vector3(2.0f, -2.0f, 0.0f)));
	matricies.push_back(glm::translate(vector3(8.0f, -1.0f, 0.0f)));
	matricies.push_back(glm::translate(vector3(8.0f, -2.0f, 0.0f)));
	matricies.push_back(glm::translate(vector3(3.0f, -3.0f, 0.0f)));
	matricies.push_back(glm::translate(vector3(4.0f, -3.0f, 0.0f)));
	matricies.push_back(glm::translate(vector3(6.0f, -3.0f, 0.0f)));
	matricies.push_back(glm::translate(vector3(7.0f, -3.0f, 0.0f)));
	matricies.push_back(glm::translate(vector3(3.0f, -1.0f, 0.0f)));
	matricies.push_back(glm::translate(vector3(4.0f, -1.0f, 0.0f)));
	matricies.push_back(glm::translate(vector3(5.0f, -1.0f, 0.0f)));
	matricies.push_back(glm::translate(vector3(6.0f, -1.0f, 0.0f)));
	matricies.push_back(glm::translate(vector3(7.0f, -1.0f, 0.0f)));
	//top
	matricies.push_back(glm::translate(vector3(1.0f, 1.0f, 0.0f)));
	matricies.push_back(glm::translate(vector3(2.0f, 1.0f, 0.0f)));
	matricies.push_back(glm::translate(vector3(3.0f, 2.0f, 0.0f)));
	matricies.push_back(glm::translate(vector3(4.0f, 1.0f, 0.0f)));
	matricies.push_back(glm::translate(vector3(5.0f, 1.0f, 0.0f)));
	matricies.push_back(glm::translate(vector3(6.0f, 1.0f, 0.0f)));
	matricies.push_back(glm::translate(vector3(7.0f, 2.0f, 0.0f)));
	matricies.push_back(glm::translate(vector3(8.0f, 1.0f, 0.0f)));
	matricies.push_back(glm::translate(vector3(9.0f, 1.0f, 0.0f)));
	matricies.push_back(glm::translate(vector3(2.0f, 2.0f, 0.0f)));
	matricies.push_back(glm::translate(vector3(3.0f, 2.0f, 0.0f)));
	matricies.push_back(glm::translate(vector3(3.0f, 2.0f, 0.0f)));
	matricies.push_back(glm::translate(vector3(4.0f, 2.0f, 0.0f)));
	matricies.push_back(glm::translate(vector3(5.0f, 2.0f, 0.0f)));
	matricies.push_back(glm::translate(vector3(6.0f, 2.0f, 0.0f)));
	matricies.push_back(glm::translate(vector3(8.0f, 2.0f, 0.0f)));
	matricies.push_back(glm::translate(vector3(3.0f, 3.0f, 0.0f)));
	matricies.push_back(glm::translate(vector3(7.0f, 3.0f, 0.0f)));
	matricies.push_back(glm::translate(vector3(2.0f, 4.0f, 0.0f)));
	matricies.push_back(glm::translate(vector3(8.0f, 4.0f, 0.0f)));

	

}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();
	for (int i = 0; i < 48; i++) {
		matricies[i][3][0] += .1;
	}
	for (int i = 0; i < 48; i++) {
		meshes[i]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), matricies[i]);
	}
	//m_pMesh0->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), ToMatrix4(m_qArcBall));
	//m_pMesh1->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3( 3.0f, 0.0f, 0.0f)));
		
	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();
	
	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();
	
	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	if (m_pMesh0 != nullptr)
	{
		delete m_pMesh0;
		m_pMesh0 = nullptr;
	}
	/*
	SafeDelete(m_pMesh1);
	SafeDelete(m_pMesh2);
	SafeDelete(m_pMesh3);
	SafeDelete(m_pMesh4);
	SafeDelete(m_pMesh5);
	SafeDelete(m_pMesh6);
	SafeDelete(m_pMesh7);
	SafeDelete(m_pMesh8);
	SafeDelete(m_pMesh9);
	*/

	//release GUI
	ShutdownGUI();
}