/*! \file main.cpp 
 * \brief Main file for the game
 *
 * Contains the entry point for the application
 * Responsible for the main game loop and window management
 */

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "game.h"

 /*! \mainpage IMAT 2906 Coursework - Coin Rush
 * A simple 2d platformer where you neeed to collect a certain amount of coins in a set time limit. 
 * You loose the game if the time runs out. Your final score gets printed out in the console
 * You win by collecting enough points befoer the timer. Remaining time gets printed out in the console
 * You get points by collecting coins. They respawn after a certain time to encourage the player to move around 
 * Slimes will knock you away. You can use this to manuever the map quicker.
 * Known Bugs:
 * - Sometimes the sprite for the slimes gets inverted. This is rare and happens more often in Release mode
 * - The Game will inexpliacbly crash and send a "read-exception violation". Cannot find the casue for the issue
 */


 //! Main function 
 /*!
 */
void main() /** Entry point for the application */
{


	sf::RenderWindow window(sf::VideoMode(640, 480), "Coin Rush"); // recomment // Open main window

	Scene scene;
	float fFrameTime = 1.f / 60.f;

	//recomment // Start a clock to provide time for the physics
	sf::Clock clock;

	// Run a game loop
	while (window.isOpen())
	{
		//recomment // Poll event loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// window closed button pressed
			if (event.type == sf::Event::Closed )
				window.close();
			// If a key is pressed
			if (event.type == sf::Event::KeyPressed)
			{
				//Debug Toggle
				if (event.key.code == sf::Keyboard::Tab)
				{
					scene.toggleDebug(); // toggle debug
				}
				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close(); // close when escape is pressed
				}

				scene.keyPress(event.key.code);
			}
			if (event.type == sf::Event::KeyReleased) {
				scene.OnKeyRelease(event.key.code);
			}

		}

		// Find out how much time has elapsed
		float m_fElapsedTime = clock.getElapsedTime().asSeconds();

		// If a frame has past the update the physics
		if (m_fElapsedTime > fFrameTime)
		{
			scene.update(m_fElapsedTime, &window);
			clock.restart();
		}

		// Clear the window
		window.clear(sf::Color(110,110, 110));


		window.draw(scene);
		window.display();
	}
	system("PAUSE");
}