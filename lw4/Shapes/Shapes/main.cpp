#include <SFML/Graphics.hpp>

#include "CShapesController.h"

const std::string WINDOW_TITLE = "Shapes in SFML";
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
	CShapesController shapesController(std::cin, std::cout);

	bool isInputFinished = false;

	while (window.isOpen())
	{
		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (!isInputFinished)
		{
			shapesController.HandleUserInput();

			if (std::cin.eof())
			{
				isInputFinished = true;
				shapesController.PrintTaskResult();
			}
		}

		window.clear(sf::Color::White);
		
		shapesController.DrawAllShapes(window);

		window.display();
	}

	return EXIT_SUCCESS;
}