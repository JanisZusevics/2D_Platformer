/*! \file slime.h
 * \brief Header file for the slime
 *
 * slimes are the NPC's of the game
 * This is an overview of how slime operate
 */
#pragma once


#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "..\gameObject\gameObject.h"

/*! \class slime
\brief A class that controls the NPC slimes with animations
*/

class slime : public PhysicalThing, public sf::CircleShape 
{
private:
	//////////// BODY //////////////////////////
	b2Body * m_arm; //!< The arm rotates and moves the player 
	b2Body * m_launcher; //!< The launcher is a spherical part that interacts only with the player and launches them away 
	//////////// ANIMATION ///////////////////////////
	sf::Sprite sprite; //!< uses a sprite
	sf::IntRect spriteLocation; //!< int rect controls what part of the sprite is being shown
	sf::Clock anim; //!< clock that regulates the animations
	float xAdjust = -2.f; //!< used to adjust the position of the sprite when flipping - can be buggy
	bool direction; //!< holds the bool of the direction the slime is going in 
	///////////////  JOINTS ////////////////////////
	b2RevoluteJoint * m_joint; //!< Revolute joint used to rotate the arm aroudn the body to simulate slime-like movement
	b2DistanceJoint * m_distJoint; //!< distance joint hold the launcher in place. The body doesnt interact with the player. 
public:
	slime(b2World* world, const sf::Vector2f& position, const sf::Vector2f& size, sf::Texture* texture); //!< constructor
	void draw(sf::RenderTarget& target, sf::RenderStates states) const; //!< draw function - draws sprite
	void update(); //!< called each cycle
	void BeginContact(b2Contact* contact, layers layer); //!< collision function inherited from parent
};

