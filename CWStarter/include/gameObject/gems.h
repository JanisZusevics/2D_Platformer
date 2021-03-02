#pragma once

/*! \file gems.h
 * \brief Header file for the gems
 *
 * gems or "coins" are the collectable of the game
 * This is an overview of how gems operate
 * Includes commented out Audio code that I couldn't figure out why it wouldn't load
 */


#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
//#include  <SFML/Audio.hpp> // commented out audio code

#include "..\gameObject\gameObject.h"
#include "..\gameObject\dynamicBlock.h"

/*! \class gems 
\brief A class that controls the Gem in-game collectables, which respawns after being collected
*/

class gems :  public PhysicalThing, public sf::Drawable
{
private:	
	//////////// BODY ///////////////////////////
	b2BodyDef l_bodyDef;  //!< body definition used in the constructor 
	sf::Vector2f size = sf::Vector2f(2.f, 2.f); //!< Gems have fixed size fixture
	float  collected = 0; //!< bool that holds if the gem has ben collected
	//////////// TIME ///////////////////////////
	sf::Clock respawn;//!< A timer in control of gem respawn
	sf::Clock anim; //!< A timer that controls the aniamtion of the gems 
	int seconds; //!< variable used to track time
	//////////// SPRITE ///////////////////////////
	sf::Sprite sprite; //!< A sprite is used for the gems
	sf::IntRect spriteLocation; //!< intRect controls what part of the sprite is being shown
	////////////// AUDIO /////////////////////////// 	   //!< commented out Audio code
	//sf::SoundBuffer buffer;							   //!< commented out Audio code
	//sf::Sound ping;									   //!< commented out Audio code
public:	
	gems(b2World* world, const sf::Vector2f& position, sf::Texture* texture);//!< constructor
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;//!< draw function that draws a sprite
	void update(); //!< Updates each cycle
	void BeginContact(b2Contact* contact, layers layer); //!< Begin contact - inherited function
	void endContact(); //!< End contact - inherited function 
};

