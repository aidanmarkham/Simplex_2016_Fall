#include "AppClass.h"
using namespace Simplex;
void Application::InitVariables(void)
{

	////Change this to your name and email
	m_sProgrammer = "Aidan Markham - apm4337@rit.edu";

	////Alberto needed this at this position for software recording.
	//m_pWindow->setPosition(sf::Vector2i(710, 0));


	//Set the position and target of the camera
	//(I'm at [0,0,10], looking at [0,0,0] and up is the positive Y axis)
	m_pCameraMngr->SetPositionTargetAndUp(AXIS_Z * 10.0f, ZERO_V3, AXIS_Y);

	//init the camera
	m_pCamera = new MyCamera();
	m_pCamera->SetPositionTargetAndUp(
		vector3(-25.0f, 30.0f, 25.0f), //Where my eyes are
		vector3(-24.0f, 29.2f, 25.0f), //where what I'm looking at is
		AXIS_Y);					//what is up

//Get the singleton
	m_pMyMeshMngr = MyMeshManager::GetInstance();
	m_pMyMeshMngr->SetCamera(m_pCamera);

	markerx = 49;
	markery = 0;

	for (int j = 0; j < 50; j += 1)
	{
		for (int i = 0; i < 50; i += 1)
		{
			world[i][j] = nullptr;


		}
	}

}

void Simplex::Application::StepAstar()
{
	int lowestScore = 99999;
	int lowestIndex;
	for (int i = 0; i < openList.size; i++) 
	{
		if (openList[i].score < lowestScore) {
			lowestScore = openList[i].score;
			lowestIndex = i;
		}
	}
	if (lowestScore != 99999) {
		closedList.push_back(openList[lowestIndex]);
		openList.erase(openList.begin() + lowestIndex);
	}


}
void Simplex::Application::CheckAdjacent(int x, int y)
{
	vector2 location = vector2(x, y);

	if (world[x - 1][y] != nullptr) {
		ProcessNode(world[x - 1][y]);
	}

}
void Simplex::Application::ProcessNode(Node * n)
{
	for (int i = 0; i < closedList.size; i++)
	{
		if (&closedList[i] == n) {
			return;
		}
	}

	bool found = false;
	for (int i = 0; i < openList.size; i++)
	{
		if (&openList[i] == n) {
			found = true;
		}
	}
	if (found) {
		
	}
}

void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();



	//Add objects to the Manager
	for (int j = 0; j < 50; j += 1)
	{
		for (int i = 0; i < 50; i += 1)
		{
			if (world[i][j] != nullptr) {
				m_pMyMeshMngr->AddConeToRenderList(glm::translate(vector3(i * 2, 0.0f, j * 2)));
			}
			else {
				m_pMyMeshMngr->AddCubeToRenderList(glm::translate(vector3(i * 2, 0.0f, j * 2)));
			}

			if (j == markerx && i == markery) {
				m_pMyMeshMngr->AddSphereToRenderList(glm::translate(vector3(i * 2, 1.0f, j * 2)));
			}
		}
	}
}
void Application::Display(void)
{
	//Clear the screen
	ClearScreen();

	//clear the render list
	m_pMeshMngr->ClearRenderList();

	//Render the list of MyMeshManager
	m_pMyMeshMngr->Render();

	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the MyMeshManager list
	m_pMyMeshMngr->ClearRenderList();

	//draw gui
	DrawGUI();

	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	//release the singleton
	MyMeshManager::ReleaseInstance();

	//release the camera
	SafeDelete(m_pCamera);

	//release GUI
	ShutdownGUI();
}
