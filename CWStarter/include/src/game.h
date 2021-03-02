#pragma once

/*! \file game.h
 * \brief Header file for the game
 *
 * This the game overview and lists the content of the game
 */

#include "ExternalLibraries\Box2DEngine\Box2D\Box2D.h"
#include <SFML/Graphics.hpp>
#include "..\utilities\SFMLDebugDraw.h"

#include "..\utilities\Camera2D.h"
#include "..\gameObject\staticBlock.h"
#include "..\gameObject\dynamicBlock.h"
#include "..\utilities\contactListener.h"
#include "..\UI\hud.h"
#include "..\gameObject\gems.h"
#include "utilities/textureManager.h"
#include "gameObject/slime.h"
#include "utilities/enemySensor.h"

 /*! \class Scene
 \brief A class that controls the Level and the game.
 */

class Scene : public sf::Drawable 
{
private:
	//// TEXTURES	/////////////////////////////////////////////////////////////////////////////////
	textureManager m_textureManager; //!< Texture manager that ensure each texture is only loaded in once
	//// WORLD	/////////////////////////////////////////////////////////////////////////////////
	sf::RectangleShape m_picture; //!< Picture drawn to the scene
	Camera2D m_camera; //!< View used to zoom in to the scene
	Camera2D m_hud_Dislpay; //!< Hud camera allows to be drawn on top of everything
	hud* m_hud; //!< HUD that displays timer and score
	b2World* m_pWorld = nullptr; //!< Pointer to the Box2D world.  Using pointers as BOX2D has it's own memory management
	const int mk_iVelIterations = 7; //!< On each update there will be 7 velocity iterations in the physics engine
	const int mk_iPosIterations = 5; //!< On each update there will be 5 position iterations on each update
	const b2Vec2 mk_gravity = b2Vec2(0.f, 19.81f); //!< Standard earth gravity will be used (negate the value ofcourse!)
	contactListener myContactListenerInstance; //!< contact listener
	//// GAME OBJECTS	/////////////////////////////////////////////////////////////////////////////////
	std::vector<StaticBlock> m_staticBlocks; //!< A collection of fixed blocks. 
	std::vector<wall> m_walls; //!< A collection of fixed blocks that bounce the player away. 
	std::vector<dynamicBlock*> m_dynamicBlocks; //!< A collection of moving blocks taht raise when the player steps on them
	std::vector<enemySensors*> m_enemySensors; //!< A collection of sensors that turn the NPC slimes around 
	std::vector<gems*> m_gems; //!< A collection of collectables that are animated and increase the score on pickup
	std::vector<slime*> m_slime; //!< A collection of NPC Slimes
	std::map<int, sf::Vector2f> grid; //!< A map that is used to draw 99 gems on the map 
	player* m_player; //!<  The player is controleld by the keyboard
	//// DEBUG	/////////////////////////////////////////////////////////////////////////////////
	bool m_debug = false; //!< Toggle for debug drawing
	SFMLDebugDraw m_debugDraw; //!< Box2D debug drawing
public:
	Scene(); //!< Constructor the sets up the scene
	~Scene(); //!< Constructor the sets up the scene
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override; //!< Overidden draw function from drawable - does the drawing
	void update(float timestep, sf::RenderWindow* game); //!< Updates the scene based on time passing
	void keyPress(sf::Keyboard::Key key); //!< Actions relevant key events
	void OnKeyRelease(sf::Keyboard::Key key); //!< Actions on key release
	void toggleDebug(); //!< Toggle for debug drawing
	void initLevel(b2World* world, std::vector<StaticBlock> block); //!< Spawns the level layout with the NPC Slimes, which in turn spawns sensors
	void spawnSlime(b2World* world, sf::Vector2f position); //!< Spawns an NPC Slime with 2 sensors to lock it into a an area
};