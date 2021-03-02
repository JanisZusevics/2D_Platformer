#pragma once

/*! \file dynamicBlock.h
 * \brief Header file for the dynamic block 
 *
 * Dynamic blocks detect the player stepping on them and will raise like an elevator 
 * and then come back down
 */

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "../gameObject/gameObject.h"

/*! \class dynamicBlock
\brief A dynamic block that raises when in contact with the player
*/

class dynamicBlock : public PhysicalThing, public sf::RectangleShape
{

private:
	// Shape /////////////////////////////////////
	sf::Vector2f size = sf::Vector2f(2.f, 2.f); //!< all gems are a set size
	// Animations /////////////////////////////////
	int touching = 0; //!<  touching variable holds the number of objects the dynamic block is in contact with 
	sf::Sprite sprite;//!< Object uses a sprite
	sf::IntRect spriteLocation;//!< IntRect that controls what part of the source image is shown
public:
	dynamicBlock() {}; //!< Default Constructor
	dynamicBlock(b2World* world, const sf::Vector2f& position, const sf::Texture* texture); //!< Complete contructor
	void draw(sf::RenderTarget& target, sf::RenderStates states) const; //!< overriden draw function for sprite only 
	void update(); //!< Update rendering infomation 
	void BeginContact(b2Contact* contact, layers layer); //!< A function that called when a collision with this object occurs
	void EndContact(b2Contact* contact, layers layer);//!< A function that called when a collision with this object ends
};

