#include "TestLevel.h"

std::vector<Node*> path;

Graph<NodeData, int> levelGraph(2500);

static int const ROWS = 50;
static int const COLS = 50;
static int arr[ROWS][COLS];


void TestLevel::visit(Node* t_node)
{
	std::cout << "Visiting: " << t_node->m_data.m_name << std::endl;
}

void TestLevel::updateArc()
{
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

						levelGraph.addArc(arr[n_row][n_col], arr[x][y], weight);
					}
					else
					{
						levelGraph.nodeIndex(arr[x][y])->removeArc(levelGraph.nodeIndex(arr[n_row][n_col]));
						levelGraph.nodeIndex(arr[n_row][n_col])->removeArc(levelGraph.nodeIndex(arr[x][y]));
					}
				}
			}
		}
	}
}

void TestLevel::setImpassibleNode(sf::Vector2i t_impassibleNode)
{
	//Get node index of the impassible node and make impassible
	levelGraph.nodeIndex(arr[t_impassibleNode.x][t_impassibleNode.y])->m_data.passable = false;

	updateArc();
}

void TestLevel::setGoal(sf::Vector2i t_goalNode)
{
	goalNode = arr[t_goalNode.x][t_goalNode.y];
	levelGraph.nodeIndex(arr[t_goalNode.x][t_goalNode.y])->m_data.rectangle.setFillColor(sf::Color::Red);
}

void TestLevel::setStart(sf::Vector2i t_startNode)
{
	startNode = arr[t_startNode.x][t_startNode.y];
	levelGraph.nodeIndex(arr[t_startNode.x][t_startNode.y])->m_data.rectangle.setFillColor(sf::Color::Green);
}

void TestLevel::aStar()
{
	path.clear();
	levelGraph.aStar(levelGraph.nodeIndex(startNode), levelGraph.nodeIndex(goalNode), path);
	for (auto& node : path) {

		node->m_data.rectangle.setFillColor(sf::Color(0, 255, 0, 255));
	}
}

void TestLevel::breathFirst()
{

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
			//Set Positions
			nodeData.xPos = x * TILE_WIDTH;
			nodeData.yPos = y * TILE_WIDTH;

			//Make all Passable and white
			nodeData.passable = true;
			nodeData.rectangle.setFillColor(sf::Color(255, 255, 255, 255));
			//Add the data to the graph
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

						levelGraph.addArc(arr[n_row][n_col], arr[x][y], weight);
					}
					else
					{
						//float weight = 1000000;
						//levelGraph.addArc(arr[n_row][n_col], arr[x][y], weight);
					}
				}
			}
		}
	}

	//Initial Graph Setup
	for (int i = 0; i < 2500; i++)
	{
		levelGraph.nodeIndex(i)->m_data.rectangle.setSize(sf::Vector2f(TILE_WIDTH, TILE_WIDTH));
		levelGraph.nodeIndex(i)->m_data.rectangle.setPosition(levelGraph.nodeIndex(i)->m_data.xPos, levelGraph.nodeIndex(i)->m_data.yPos);
		levelGraph.nodeIndex(i)->m_data.rectangle.setOutlineThickness(-1);
		levelGraph.nodeIndex(i)->m_data.rectangle.setOutlineColor(sf::Color::Black);
	}
}

TestLevel::~TestLevel()
{
}

void TestLevel::update()
{
	for (int i = 0; i < 2500; i++)
	{
		if (levelGraph.nodeIndex(i)->m_data.passable)
		{
			levelGraph.nodeIndex(i)->m_data.rectangle.setFillColor(sf::Color::White);
		}
		else
		{
			levelGraph.nodeIndex(i)->m_data.rectangle.setFillColor(sf::Color::Black);
		}
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
