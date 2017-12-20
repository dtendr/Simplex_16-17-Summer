#include "AppClass.h"
using namespace Simplex;
void Application::InitVariables(void)
{
	////Change this to your name and email
	//m_sProgrammer = "Alberto Bobadilla - labigm@rit.edu";

	////Alberto needed this at this position for software recording.
	//m_pWindow->setPosition(sf::Vector2i(710, 0));

	//Set the position and target of the camera
	//(I'm at [0,0,10], looking at [0,0,0] and up is the positive Y axis)
	m_pCameraMngr->SetPositionTargetAndUp(AXIS_Z * 10.0f, ZERO_V3, AXIS_Y);

	//init the camera
	m_pCamera = new MyCamera();
	m_pCamera->SetPositionTargetAndUp(
		vector3(15.0f, 15.0f, 60.0f), //Where my eyes are
		vector3(15.0f, 15.0f, 19.0f), //where what I'm looking at is
		AXIS_Y);					//what is up

	//Get the singleton
	m_pMyMeshMngr = MyMeshManager::GetInstance();
	m_pMyMeshMngr->SetCamera(m_pCamera);

	//generate new maze
	m_mGen = new Maze();

	//run A* after maze generation
	//m_mGen->AStar(start, end);
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
	uint nCount = 0;
	for (int y = 0; y < m_mGen->MazeY(); y++)
	{

		for (int x = 0; x < m_mGen->MazeX(); x++)
		{
			if (m_mGen->MazeMap()[y][x] == false) 
			{
				m_pMyMeshMngr->AddCubeToRenderList(glm::translate(vector3(x, y, 0.0f)));
				nCount++;
			}
			else 
			{
				//grab two points based on max Y
				//basically grabbing a pseudo-random start and end point
				if (y == 0)
				{
					if (!m_mGen->ENM()) 
					{
						start = { x, y };

						//render a sphere as marker for start point
						m_pMyMeshMngr->AddSphereToRenderList(glm::translate(vector3(x, y, 0.0f)));

						m_mGen->ENM(true);
					}
					//no longer needed since path tracks beginning/ending as well
					else {

						m_pMyMeshMngr->AddSphereToRenderList(glm::translate(vector3(start.first, start.second, 0.0f)));
					}
				}
				if (y + 1 == m_mGen->MazeY()) 
				{
					if (!m_mGen->EXM())
					{
						end = { x, y };

						//render a sphere as marker for end point
						m_pMyMeshMngr->AddSphereToRenderList(glm::translate(vector3(x, y, 0.0f)));

						m_mGen->EXM(true);
					}
					//no longer needed since path tracks beginning/ending as well
					else {

						m_pMyMeshMngr->AddSphereToRenderList(glm::translate(vector3(end.first, end.second, 0.0f)));
					}
				}

			}


		}
	}

	//probably not efficient, but testing
	m_mGen->AStar(start, end);

	for (int y = 0; y < m_mGen->MazeY(); y++)
	{

		for (int x = 0; x < m_mGen->MazeX(); x++)
		{
			if (m_mGen->Path()[y][x] == true) 
			{
				m_pMyMeshMngr->AddSphereToRenderList(glm::translate(vector3(x, y, 0.0f)));
			}
		}
	}

	m_pMeshMngr->Print("Objects: " + std::to_string(nCount) + "\n", C_BLUE);

}
void Application::Display(void)
{
	//Clear the screen
	ClearScreen();

	//Render the list of MyMeshManager
	m_pMyMeshMngr->Render();

	//clear the MyMeshManager list
	m_pMyMeshMngr->ClearRenderList();

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
	//release the singleton
	MyMeshManager::ReleaseInstance();

	SafeDelete(m_mGen);

	//release the camera
	SafeDelete(m_pCamera);

	//release GUI
	ShutdownGUI();
}
