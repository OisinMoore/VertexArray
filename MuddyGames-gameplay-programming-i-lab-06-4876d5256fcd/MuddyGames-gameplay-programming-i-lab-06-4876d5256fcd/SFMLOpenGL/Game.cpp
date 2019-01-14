#include <Game.h>

bool flip = false;
int current = 1;

Game::Game() : window(VideoMode(800, 600), "OpenGL Cube")
{

}

Game::~Game() {}

// vertices to make the cube starting with the given triangle
float vertices[] = { 
	1.0f, 1.0f, -5.0f, // 0
	-1.0f, 1.0f, -5.0f, // 1
  	-1.0f, -1.0f, -5.0f, // 2
	1.0f, -1.0f, -5.0f, // 3
	1.0f, 1.0f, -15.0f, // 4
	-1.0f, 1.0f, -15.0f, // 5
	-1.0f, -1.0f, -15.0f,// 6
	1.0f, -1.0f, -15.0f // 7
	 };
// colours for the cube
float colors[] = { 
1.0f,  0.0f,  0.0f,
0.0f,  0.0f,  1.0f,
1.0f,  0.0f,  0.0f,
0.0f,  1.0f,  1.0f,
0.0f,  1.0f,  1.0f,
1.0f,  0.0f,  1.0f,
0.0f, 0.0f, 0.0f,
0.0f, 0.0f, 0.0f
 };
// order in which the vertices our made to shape the cube
unsigned int vertex_index[] = {
0, 1 , 2,
2, 3, 0,
1, 4, 5,
1, 0, 4,
0, 7, 4,
3, 7 ,0,
6, 7, 3,
6, 3, 2,
6, 2, 1,
6, 1 ,5,
6, 4, 5,
6, 7, 4
};

void Game::run()
{

	initialize();

	Event event;

	while (isRunning) {

		cout << "Game running..." << endl;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		render();
	}

}

void Game::initialize()
{
	isRunning = true;

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
}

void Game::update()
{
	elapsed = clock.getElapsedTime();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		//rotates anti clockwise around a set point
		matrixApplicationFunction(MyMatrix3::rotationY(0.001));
		matrixApplicationFunction(MyMatrix3::rotationX(-0.001));
		matrixApplicationFunction(MyMatrix3::rotationZ(0.01));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		//rotates clockwise around a set point
		matrixApplicationFunction(MyMatrix3::rotationY(-0.001));
		matrixApplicationFunction(MyMatrix3::rotationX(0.001));
		matrixApplicationFunction(MyMatrix3::rotationZ(0.01));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		// rotates around the y axis
		matrixApplicationFunction(MyMatrix3::rotationY(-0.01));
		matrixApplicationFunction(MyMatrix3::rotationX(0.001));
		matrixApplicationFunction(MyMatrix3::rotationZ(-0.001));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
	{
		// rotates around the x axis
		matrixApplicationFunction(MyMatrix3::rotationY(0.001));
		matrixApplicationFunction(MyMatrix3::rotationX(0.01));
		matrixApplicationFunction(MyMatrix3::rotationZ(-0.001));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
	{
		// rotates around the x axis
		matrixApplicationFunction(MyMatrix3::rotationY(0.001));
		matrixApplicationFunction(MyMatrix3::rotationX(0.001));
		matrixApplicationFunction(MyMatrix3::rotationZ(-0.01));
	}
	// scale up
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		matrixApplicationFunction(MyMatrix3::scale(1.02));
	}
	// scale down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		matrixApplicationFunction(MyMatrix3::scale(-0.99));
	}
	cout << "Update up" << endl;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	cout << "Drawing" << endl;

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);


	glVertexPointer(3, GL_FLOAT, 0, &vertices);
	glColorPointer(3, GL_FLOAT, 0, &colors);

	/*glDrawArrays(GL_TRIANGLES, 0, );*/

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, &vertex_index);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	window.display();

}

void Game::unload()
{
	cout << "Cleaning up" << endl;
}

void Game::matrixApplicationFunction(MyMatrix3 t_matrix)
{
	for (int i = 0; i < 36; i += 3)
	{
		MyVector3 vector{vertices[i], vertices[i + 1], vertices[i + 2]};

		vector = t_matrix * vector;
		vertices[i] = vector.x;
		vertices[i + 1] = vector.y;
		vertices[i + 2] = vector.z;
	}

}

