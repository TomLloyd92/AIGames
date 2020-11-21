#include "Grid.h"

//std::vector<Node*> path;

//The Grid
 std::vector<Node>levelGrid(2500);
static int const ROWS = 50;
static int const COLS = 50;
static int arr[ROWS][COLS];

std::vector<Node*> path;

void Grid::visit(Node* t_node)
{
	//std::cout << "Visiting: " << t_node->m_data.m_name << std::endl;
}

void Grid::updateArc()
{
	//Create the arcs
	for (int y = 0; y < COLS; y++)
	{
		for (int x = 0; x < ROWS; x++)
		{
			// List all neighbors:
			for (int direction = 0; direction < 9; direction++) 
			{
				if (direction == 4) continue; // Skip ourselves

				int n_row = x + ((direction % 3) - 1); // Neighbor row
				int n_col = y + ((direction / 3) - 1); // Neighbor column

				// Check the bounds:
				if (n_row >= 0 && n_row < ROWS && n_col >= 0 && n_col < COLS)
				{
					if (levelGrid.at(arr[n_row][n_col]).getPassable() == true)
					{
						/*
						//Distance between point and neighbour
						float weight = sqrt((levelGraph.nodeIndex(arr[n_row][n_col])->m_data.xPos - levelGraph.nodeIndex(arr[x][y])->m_data.xPos)
							* (levelGraph.nodeIndex(arr[n_row][n_col])->m_data.xPos - levelGraph.nodeIndex(arr[x][y])->m_data.xPos)
							+ (levelGraph.nodeIndex(arr[n_row][n_col])->m_data.yPos - levelGraph.nodeIndex(arr[x][y])->m_data.yPos)
							* (levelGraph.nodeIndex(arr[n_row][n_col])->m_data.yPos - levelGraph.nodeIndex(arr[x][y])->m_data.yPos));
						
						*/

						//levelGrid.at(arr[x][y]).setArc(&levelGrid.at(arr[n_row][n_col]));
					}
					else if(levelGrid.at(arr[n_row][n_col]).getPassable() == false)
					{
						//Remove Both Connecting Arcs
						levelGrid.at(arr[x][y]).removeArc(&levelGrid.at(arr[n_row][n_col]));
						levelGrid.at(arr[n_row][n_col]).removeArc(&levelGrid.at(arr[x][y]));
					}
				}
			}
		}
	}
}

void Grid::setImpassibleNode(sf::Vector2i t_impassibleNode)
{
	//Get node index of the impassible node and make impassible
	levelGrid.at(arr[t_impassibleNode.x][t_impassibleNode.y]).setPassable(false);

	updateArc();
	update();
}

void Grid::setGoal(sf::Vector2i t_goalNode)
{
	goalNode = arr[t_goalNode.x][t_goalNode.y];
	update();
}

void Grid::setStart(sf::Vector2i t_startNode)
{
	startNode = arr[t_startNode.x][t_startNode.y];
	update();
}

void Grid::aStar()
{
	
}

void Grid::createFlowField()
{
	//Set the goal node weight to zero
	levelGrid.at(goalNode).setWeight(0);	//Set goal node to 0
	levelGrid.at(goalNode).setMarked(true);	//Goal node is marked as true

	//
	std::queue<Node*> nodeQue;

	nodeQue.push(&levelGrid.at(goalNode));

	while (!nodeQue.empty())
	{
		//Get all arcs at from
		std::list<Node*> currentArchList = nodeQue.front()->getArcs();
		//Create List iterator to derefernce later
		std::list<Node*>::iterator it = currentArchList.begin();

		//Cast front of the que to Node
		Node* front = (Node*)nodeQue.front();

		for (; it != currentArchList.end(); it++)
		{
			if ((*it)->getMarked() == false)
			{
				(*it)->setWeight(front->getWeight() + 1);
				(*it)->setMarked(true);
				nodeQue.push(*it);
			}
		}

		/*
		// go through each connecting node
		auto iter = currentArchList.begin();
		auto endIter = currentArchList.end();

		for (; iter != endIter; ++iter)
		{
			// process the linked node if it isn't already marked.
			if ((*iter)->getMarked() == false)
			{
				(*it)->setWeight(front->getWeight() + 1);
				(*it)->setMarked(true);
				nodeQue.push(*it);
			}
		}
		*/
		nodeQue.pop();
	}
	//Update all the nodes colour and weight
	update();


	//Debug to note when flow field is complete
	std::cout << "Finished Flow Field" << std::endl;
}


Grid::Grid()
{
	//Set Array relative to graph
	int inputNumber = 0;
	for (int y = 0; y < COLS; y++)
	{
		for (int x = 0; x < ROWS; x++)
		{
			arr[x][y] = inputNumber;
			inputNumber++;
		}
	}

	//Create the Graph
	for (int y = 0; y < COLS; y++)
	{
		for (int x = 0; x < ROWS; x++)
		{
			//Set Positions
			sf::Vector2f newPos;
			newPos.x = x * TILE_WIDTH;
			newPos.y = y * TILE_WIDTH;
			levelGrid.at(arr[x][y]).setPos(newPos);

			//Set up node Squares
			levelGrid.at(arr[x][y]).setPassable(true);
			levelGrid.at(arr[x][y]).rectangle.setSize(sf::Vector2f(TILE_WIDTH, TILE_WIDTH));
			levelGrid.at(arr[x][y]).rectangle.setFillColor(sf::Color(255, 255, 255, 255));
			levelGrid.at(arr[x][y]).rectangle.setOutlineThickness(-1);
			levelGrid.at(arr[x][y]).rectangle.setOutlineColor(sf::Color::Black);
			levelGrid.at(arr[x][y]).rectangle.setPosition(newPos);
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

					if (levelGrid.at(arr[n_row][n_col]).getPassable() == true)
					{

						/*
						//Distance between point and neighbour
						float weight = sqrt((levelGraph.nodeIndex(arr[n_row][n_col])->m_data.xPos - levelGraph.nodeIndex(arr[x][y])->m_data.xPos)
							* (levelGraph.nodeIndex(arr[n_row][n_col])->m_data.xPos - levelGraph.nodeIndex(arr[x][y])->m_data.xPos)
							+ (levelGraph.nodeIndex(arr[n_row][n_col])->m_data.yPos - levelGraph.nodeIndex(arr[x][y])->m_data.yPos)
							* (levelGraph.nodeIndex(arr[n_row][n_col])->m_data.yPos - levelGraph.nodeIndex(arr[x][y])->m_data.yPos));
						*/

						levelGrid.at(arr[x][y]).setArc(&levelGrid.at(arr[n_row][n_col]));
					}
					else
					{
						//All Grid should be passable at the start
					}
				}
			}
		}
	}
}

Grid::~Grid()
{
}

void Grid::update()
{
	for (int i = 0; i < levelGrid.size(); i++)
	{
		//Set Correct Colors
		if (startNode == i)
		{
			levelGrid.at(i).rectangle.setFillColor(sf::Color::Green);
		}
		else if (goalNode == i)
		{
			levelGrid.at(i).rectangle.setFillColor(sf::Color::Red);
		}
		else if (levelGrid.at(i).getPassable())
		{
			levelGrid.at(i).rectangle.setFillColor(sf::Color(0, 0, 255, 255/ levelGrid.at(i).getWeight()));
		}
		else if (levelGrid.at(i).getPassable() == false)
		{
			levelGrid.at(i).rectangle.setFillColor(sf::Color::Black);
		}

		//Set Text to correct position
		levelGrid.at(i).update();
	}
}

void Grid::render(sf::RenderWindow& t_window)
{
	for (int i = 0; i < levelGrid.size(); i++)
	{
		t_window.draw(levelGrid.at(i).rectangle);
		t_window.draw(levelGrid.at(i).getTextWeight());
	}
}

void Grid::setup(sf::Font& t_font)
{
	for (int i = 0; i < levelGrid.size(); i++)
	{
		levelGrid.at(i).setUp(t_font);
	}
}

void Grid::initialise()
{
}

