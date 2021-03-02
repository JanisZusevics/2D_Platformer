#pragma once

/*! \file player.h
 * \brief Header file for the player
 *
 * player has left and right movement, a jump, and animations
 * This is an overview of how the player operates
 */

#include <ExternalLibraries/Box2DEngine/Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "..\gameObject\dynamicBlock.h"

 /*! \class player
 \brief A class that controls the player with animations
 */
class player : public PhysicalThing, public sf::RectangleShape {
private:
	////// BODY ////////////////////////////////////////////////
	int touching = 0; //!< A count of how many objects the player is in contact with 
	int score = 0; //!< A count of the score the player has obtained 
	/////// FUNCTION ////////////////////////////////////////////
	int jumpVelocity; //!<  The linear velocity of the player sued to stop the palyer to jumping while they are in the air
	/////// ANIMATION ////////////////////////////////////////////
	sf::Sprite sprite; //!< The player uses a sprite
	sf::IntRect spriteLocation; //!< int rect controls what part of the sprite are being shown 
	sf::Clock anim; //!< a clock that controls the aniamtion 
	float xAdjust = 3.2; //!< value that adjusts the sprite location to account for it being flipped
public:
	player() {}; //!< default constructor
	player(b2World* world, const sf::Vector2f& position, const sf::Vector2f& size, sf::Texture* texture); //!< constructor
	void update(); //!< update each cycle
	void keyboard(sf::Keyboard::Key code); //!< keyboard input
	void onKeyRelease(sf::Keyboard::Key code); //!< keybaord release input
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override; //!< Overidden draw function from drawable - does the drawing
	bool grounded() {return touching;} //!< returns if the player is grounded  
	void BeginContact(b2Contact* contact, layers layer); //!< begin contact - inherited function 
	void EndContact(b2Contact* contact, layers layer); //!< End contact  - inherited class
	float getScore(); //!< returns the current score

};
