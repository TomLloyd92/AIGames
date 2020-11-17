#include "TestLevel.h"



std::vector<Node*> path;

Graph<NodeData, int> levelGraph(2500);
int const ROWS = 50;
int const COLS = 50;
int arr[ROWS][COLS];


void TestLevel::visit(Node* t_node)
{
	std::cout << "Visiting: " << t_node->m_data.m_name << std::endl;
}




TestLevel::TestLevel()
{
	//Create the Graph
	int inputNumber = 0;
	for (int y = 0; y < COLS; y++)
	{
		for (int x = 0; x < ROWS; x++)
		{
			arr[x][y] = inputNumber;
			inputNumber++;
		}
	}

	//Node Data
	NodeData nodeData;
	int nodeIndex = 0;
	std::ifstream myfile;


	//Create the Graph
	for (int y = 0; y < COLS; y++)
	{
		for (int x = 0; x < ROWS; x++)
		{
			nodeData.xPos = x * TILE_WIDTH;
			nodeData.yPos = y * TILE_WIDTH;

			/*
			if (y == 3 && x == 3)
			{
				nodeData.passable = false;
				nodeData.rectangle.setFillColor(sf::Color(255, 0, 0, 255));

			}
			*/
			//else
			{
				nodeData.passable = true;
				nodeData.rectangle.setFillColor(sf::Color(255, 255, 255, 255));
			}

			levelGraph.addNode(nodeData, arr[x][y]);
		}
	}

	//Create the arcs
	for (int y = 0; y < COLS; y++)
	{
		for (int x = 0; x < ROWS; x++)
		{
			// List all neighbors:
			for (int direction = 0; direction < 9; direction++) {
				if (direction == 4) continue; // Skip ourselves

				int n_row = x + ((direction % 3) - 1); // Neighbor row
				int n_col = y + ((direction / 3) - 1); // Neighbor column

				// Check the bounds:
				if (n_row >= 0 && n_row < ROWS && n_col >= 0 && n_col < COLS)
				{

					if (levelGraph.nodeIndex(arr[n_row][n_col])->m_data.passable == true)
					{

						//Distance between point and neighbour
						float weight = sqrt((levelGraph.nodeIndex(arr[n_row][n_col])->m_data.xPos - levelGraph.nodeIndex(arr[x][y])->m_data.xPos)
							* (levelGraph.nodeIndex(arr[n_row][n_col])->m_data.xPos - levelGraph.nodeIndex(arr[x][y])->m_data.xPos)
							+ (levelGraph.nodeIndex(arr[n_row][n_col])->m_data.yPos - levelGraph.nodeIndex(arr[x][y])->m_data.yPos)
							* (levelGraph.nodeIndex(arr[n_row][n_col])->m_data.yPos - levelGraph.nodeIndex(arr[x][y])->m_data.yPos));

						std::cout << weight << std::endl;

						levelGraph.addArc(arr[n_row][n_col], arr[x][y], weight);
					}
				}
			}
		}
	}
	
}

TestLevel::~TestLevel()
{
}

void TestLevel::update(sf::Time t_deltaTime)
{
	
	for (int i = 0; i < 2500; i++)
	{
		levelGraph.nodeIndex(i)->m_data.rectangle.setSize(sf::Vector2f(TILE_WIDTH, TILE_WIDTH));
		levelGraph.nodeIndex(i)->m_data.rectangle.setPosition(levelGraph.nodeIndex(i)->m_data.xPos, levelGraph.nodeIndex(i)->m_data.yPos);
		levelGraph.nodeIndex(i)->m_data.rectangle.setOutlineThickness(-1);
		levelGraph.nodeIndex(i)->m_data.rectangle.setOutlineColor(sf::Color::Black);

	}

	//Testing aStar by colouring in the squares

	levelGraph.aStar(levelGraph.nodeIndex(arr[0][0]), levelGraph.nodeIndex(arr[4][3]), path);
	for (auto& node : path) {

		node->m_data.rectangle.setFillColor(sf::Color(0, 255, 0, 255));
	}

	
}

void TestLevel::render(sf::RenderWindow& t_window)
{
	

	for (int i = 0; i < 2500; i++)
	{

		t_window.draw(levelGraph.nodeIndex(i)->m_data.rectangle);



	}
	

}

void TestLevel::setup(sf::Font& t_font)
{
}

void TestLevel::initialise()
{
}
