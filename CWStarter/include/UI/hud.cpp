/*! \file hud.cpp
 * \brief Functions and Logic behind the hud
 *
 * the hud dislpays the time left and the points
 * The hud also controls the game ending and winning state
 */

#include "..\UI\hud.h"
#include <iostream>
#include <iomanip>

 //! Constructor for the HUD
 /*!
 */
hud::hud() 
{ 
	// initialise the font and the UI elements
	initFont();
	initText(&m_timer);
	initText(&m_score);	
}

//! Function that is called every timestep
/*!
\param player gets score value
\param game allows the window manipulation 
*/
void hud::update(player* player, sf::RenderWindow* game) { // Gets called every timestep
	// anchor the position to the player, same as the main camera
	anchor = player->getPosition(); 
	// get the player score
	playerScore = abs(player->getScore())  ;
	m_score.setPosition(anchor.x , anchor.y + yPos); // anchor
	m_score.setString(std::to_string(playerScore) + "/" + std::to_string(goalScore)); // output score
	// timer
	m_timer.setPosition(anchor.x + xPos, anchor.y + yPos); // anchor
	time = 60 - clock.getElapsedTime().asSeconds(); // timer
	if (time < 0 || playerScore >= goalScore) { // timer is responsible for game winning and loosing states
		if (playerScore >= goalScore)
		{
			std::cout << "\n\n\n     ****     V I C T O R Y   *******\n\n\n" << " Time left: " << time <<  " seconds\n\n\n" << std::endl; // print time left when won 
			game->close();
		}
		else {
			std::cout << "\n\n\n     ****     D E F E A T   *******\n\n\n" << " Your Score: " << playerScore << "/" << goalScore << "\n\n\n"; // print score left when lost
			game->close();
		}
	}
	m_timer.setString(std::to_string(time))  ; // output time
}

//! Function that gets called when the player enters a collision
/*!
\param text chooses the text to initialise
*/
void hud::initText(sf::Text* text) // initialise the text to fit
{
	// set values to fit the UI 
	text->setFont(gameFont);
	text->setString("Hello world");
	text->setCharacterSize(50);
	text->setFillColor(sf::Color::White);
	text->setScale(sf::Vector2(0.06f, 0.06f));
}

//! Function that gets called when the player enters a collision
/*!
*/
void hud::initFont() // Locate the font
{
	this->gameFont.loadFromFile("../Assets/Font/gameFont.ttf"); // load the font
	if (!gameFont.loadFromFile("../Assets/Font/gameFont.ttf"))
	{
		std::cout << "error : " << std::endl;
	}
}

//! Function to draw the UI
/*!
\param target will choose what gets drawn
\param states defines the state for the target
*/
void hud::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_timer); // draw the timer
	target.draw(m_score); // draw the score
}

