#pragma once

/*! \file hud.h
 * \brief Header file for the HUD / GUI
 *
 * The hud tracks score and time left
 * This is an overview of how the HUD operate
 */


#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "..\gameObject\player.h"

 /*! \class hud
 \brief A class that controls the Graphical user interface and displays the timer and the score 
 */

class hud : public sf::Drawable
{
private:
	// TEXT /////////////////////////////////////////////////////////////////////////////////////
	sf::Font gameFont; //!< Font used in the HUD
	sf::Text m_score; //!< Score that gets displayed 
	sf::Text m_timer; //!< The time left 
	// TIME /////////////////////////////////////////////////////////////////////////////////////
	sf::Clock clock; //!< Timer for the player
	double time; //!< keeps track of time
	// POSITIONING /////////////////////////////////////////////////////////////////////////////////////
	sf::Vector2f anchor; //!< Used to position the hud
	int xPos = -20; //!< used for x axis positioning
	int yPos = 15; //!< used for y axis positioning
	// SCORE /////////////////////////////////////////////////////////////////////////////////////
	int playerScore; //!< Current player score
	int goalScore = 300; //!< goal score
public:
	hud(); // constructor
	void update(player* player, sf::RenderWindow* game); //!< update
	void draw(sf::RenderTarget &target, sf::RenderStates states) const override; //!< draw function 
	void initFont(); //!< initialise the font 
	void initText(sf::Text* text); //!< initialise the text
};

