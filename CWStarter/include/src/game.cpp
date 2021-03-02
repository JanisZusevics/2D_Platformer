/*! \file gameObject.cpp
 * \brief Functions and Logic behind the Game 
 *
 * This contains the scene class which sets the level and updates the gameObjects 
 * Has some game logic and function described here
 */

#include "..\src\game.h"

 //! Constructor for Scene
 /*!
 */
Scene::Scene()
{
	/////////////// LOAD TEXTURES WITH KEY ////////////////////////////////////////////////////////////////////////////////////
	m_textureManager.addTexture('b', "../Assets/RockyMap2.png");
	m_textureManager.addTexture('c', "../Assets/Coins.png");
	m_textureManager.addTexture('p', "../Assets/Dwarf.png");
	m_textureManager.addTexture('e', "../Assets/slime2.png");
	m_textureManager.addTexture('d', "../Assets/platform.png");
	//////////////// BCKGROUND ////////////////////////////////////////////////////////////////////////////////////
	m_picture.setSize(sf::Vector2f(146.f, 137.f));
	m_picture.setPosition(-19.f, 79.5f);
	m_picture.setTexture(m_textureManager.getTexture('b'));
	m_pWorld = new b2World(mk_gravity);
	//////////////// CAMERAS ////////////////////////////////////////////////////////////////////////////////////
	m_camera.setSize(sf::Vector2f(45.2f, 36.4f));
	m_hud_Dislpay.setSize(sf::Vector2f(56.f, 42.f));
	m_debugDraw.setWorld(m_pWorld);
	m_pWorld->SetContactListener(&myContactListenerInstance);
	///////////////// GAME OBJECTS //////////////////////////////////////////////////////////////////////////////
	// BORDERS /////////////
	// Bouncy walls
	m_walls.push_back(wall(m_pWorld, sf::Vector2f(-10.f, 96.0f), sf::Vector2(20.0f, 192.0f)));
	m_walls.push_back(wall(m_pWorld, sf::Vector2f(118.f, 96.0f), sf::Vector2(20.0f, 192.0f)));
	// staticBlocks with slimes and sensors
	initLevel(m_pWorld, m_staticBlocks);
	// gems
	for (int i = 0; i < 11; i++) // for loop that draws 99 gems
	{
		float adjustment = 1.f + (i * 10);
		grid[i] = sf::Vector2f(sf::Vector2f(4.5f + adjustment, 188.0f));
		for (int j = 0; j < 9; j++)
		{
			float adjustment = 1.f + (j * 10);
			grid[j + i] = sf::Vector2f(sf::Vector2f(grid[i].x, 188.0f - adjustment));
			m_gems.push_back(new gems(m_pWorld, sf::Vector2f(grid[i + j]), m_textureManager.getTexture('c')));
		}
	}
	// dynamic blocks that raise the player when stepped on 
	m_dynamicBlocks.push_back(new dynamicBlock(m_pWorld, sf::Vector2f(65.f, 171.6f), m_textureManager.getTexture('d')));
	m_dynamicBlocks.push_back(new dynamicBlock(m_pWorld, sf::Vector2f(45.f, 171.6f), m_textureManager.getTexture('d')));
	// player initiation 
	m_player = new player(m_pWorld, sf::Vector2f(70.f, 145.2f), sf::Vector2(2.5f, 3.8f), m_textureManager.getTexture('p'));
	// UI
	m_hud = new hud();
}

//! Function to draw the game objects
/*!
\param target will choose what gets drawn
\param states defines the state for the target
*/
void Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Drawing game assets
	target.setView(m_camera.getView()); //set main camera view
	target.draw(m_picture); // draw the picture
	target.draw(*m_player); // draw the player
	//target.draw(*m_slime); // draw the player
	for (auto& block : m_gems) target.draw(*block); // draw the gems
	for (auto& slime : m_slime) target.draw(*slime); // draw the gems
	for (auto& block : m_dynamicBlocks) target.draw(*block); // draw the gems
	if (m_debug) target.draw(m_debugDraw); // debug draw
	// hud on top of everything
	target.setView(m_hud_Dislpay.getView());
	target.draw(*m_hud);
}

//! Function that is called every timestep
/*!
*/
void Scene::update(float timestep, sf::RenderWindow* game) // called every timestep
{
	//// UPDATE CALLS /////////////////////////////////////
	m_player->update();
	m_hud->update(m_player, game);
	for (slime* enemy : m_slime) enemy->update();
	for (gems* gem : m_gems) gem->update();
	for (dynamicBlock* block : m_dynamicBlocks) block->update();
	//// SET POSITIONS /////////////////////////////////////
	m_camera.setCentre(m_player->getPosition());
	m_hud_Dislpay.setCentre(m_player->getPosition());
	//// WORLD UPDATE /////////////////////////////////////
	m_pWorld->Step(timestep, mk_iVelIterations, mk_iVelIterations);
	//// DEBUG DELETE /////////////////////////////////////
	if (m_debug) m_debugDraw.clear();
}


//! Function to get player input
/*!
\param code refers to the key pressed
*/
void Scene::keyPress(sf::Keyboard::Key key)
{
	//// CAMERA CONTROLS  - zoom FOR DEBUGGING /////////////////////////////////////
	switch (key)
	{
	case sf::Keyboard::Q:
		m_camera.zoom(1.1f);
		break;
	case sf::Keyboard::E:
		m_camera.zoom(0.9f);
		break;
	}
	//// PLAYER CONTROLS /////////////////////////////////////
	m_player->keyboard(key);
}

//! Function to get player input on release
/*!
\param code refers to the key pressed
*/
void Scene::OnKeyRelease(sf::Keyboard::Key key)
{
	m_player->onKeyRelease(key); // player controls
}

//! Function to turn on or off the debug draw
/*!
*/
void Scene::toggleDebug()
{
	m_debug = !m_debug; // debug toggle
}

//! Function to deconstruct the scene
/*!
*/
Scene::~Scene() // Deconstructor defenition
{
	// clean up pointers ///////////////////////
	delete m_pWorld;
	delete m_player;
	delete m_hud;
	for (gems* gem : m_gems) delete gem;
	for (slime* slime : m_slime) delete slime;
	for (dynamicBlock* block : m_dynamicBlocks) delete block;
	m_pWorld = nullptr;
	m_player = nullptr;
	m_hud = nullptr;

}

//! Function to spawn in static blocks, slimes and sensors
/*!
\param world for the game world
\param block for the type of block to spawn in 
*/
 void Scene::initLevel(b2World* world, std::vector<StaticBlock> block)
{
	// bottom
	block.push_back(StaticBlock(world, sf::Vector2f(128.f, 202.f), sf::Vector2(296.0f, 20.0f)));
	// top
	block.push_back(StaticBlock(world, sf::Vector2f(128.f, 94.f), sf::Vector2(296.0f, 20.0f)));
	// Climeable walls
	block.push_back(StaticBlock(world, sf::Vector2f(50.f, 157.f), sf::Vector2(2.0f, 32.0f)));
	block.push_back(StaticBlock(world, sf::Vector2f(60.f, 157.f), sf::Vector2(2.0f, 32.0f)));
	//1
	block.push_back(StaticBlock(world, sf::Vector2f(5.f, 182.f), sf::Vector2(10.0f, 2.0f)));
	block.push_back(StaticBlock(world, sf::Vector2f(25.f, 182.f), sf::Vector2(10.0f, 2.0f)));
	block.push_back(StaticBlock(world, sf::Vector2f(45.f, 182.f), sf::Vector2(10.0f, 2.0f)));
	block.push_back(StaticBlock(world, sf::Vector2f(55.f, 182.f), sf::Vector2(10.0f, 2.0f)));
	block.push_back(StaticBlock(world, sf::Vector2f(65.f, 182.f), sf::Vector2(10.0f, 2.0f)));
	block.push_back(StaticBlock(world, sf::Vector2f(85.f, 182.f), sf::Vector2(10.0f, 2.0f)));
	block.push_back(StaticBlock(world, sf::Vector2f(105.f, 182.f), sf::Vector2(10.0f, 2.0f)));
	spawnSlime(m_pWorld, sf::Vector2f(35.5f, 190.0f));
	spawnSlime(m_pWorld, sf::Vector2f(15.5f, 190.0f));
	spawnSlime(m_pWorld, sf::Vector2f(75.5f, 190.0f));
	spawnSlime(m_pWorld, sf::Vector2f(95.5f, 190.0f));
	//2
	block.push_back(StaticBlock(world, sf::Vector2f(15.f, 172.f), sf::Vector2(10.0f, 2.0f)));
	block.push_back(StaticBlock(world, sf::Vector2f(25.f, 172.f), sf::Vector2(10.0f, 2.0f)));
	block.push_back(StaticBlock(world, sf::Vector2f(45.f, 172.f), sf::Vector2(10.0f, 2.0f)));
	block.push_back(StaticBlock(world, sf::Vector2f(65.f, 172.f), sf::Vector2(10.0f, 2.0f)));
	block.push_back(StaticBlock(world, sf::Vector2f(85.f, 172.f), sf::Vector2(10.0f, 2.0f)));
	block.push_back(StaticBlock(world, sf::Vector2f(95.f, 172.f), sf::Vector2(10.0f, 2.0f)));
	spawnSlime(m_pWorld, sf::Vector2f(55.5f, 180.0f));
	//3						   
	block.push_back(StaticBlock(world, sf::Vector2f(5.f, 162.f), sf::Vector2(10.0f, 2.0f)));
	block.push_back(StaticBlock(world, sf::Vector2f(35.f, 162.f), sf::Vector2(10.0f, 2.0f)));
	block.push_back(StaticBlock(world, sf::Vector2f(75.f, 162.f), sf::Vector2(10.0f, 2.0f)));
	block.push_back(StaticBlock(world, sf::Vector2f(105.f, 162.f), sf::Vector2(10.0f, 2.0f)));
	spawnSlime(m_pWorld, sf::Vector2f(16.5f, 170.0f));
	spawnSlime(m_pWorld, sf::Vector2f(94.5f, 170.0f));
	//4						   
	block.push_back(StaticBlock(world, sf::Vector2f(25.f, 152.f), sf::Vector2(10.0f, 2.0f)));
	block.push_back(StaticBlock(world, sf::Vector2f(35.f, 152.f), sf::Vector2(10.0f, 2.0f)));
	block.push_back(StaticBlock(world, sf::Vector2f(75.f, 152.f), sf::Vector2(10.0f, 2.0f)));
	block.push_back(StaticBlock(world, sf::Vector2f(85.f, 152.f), sf::Vector2(10.0f, 2.0f)));
	//5						   
	block.push_back(StaticBlock(world, sf::Vector2f(5.f, 142.f), sf::Vector2(10.0f, 2.0f)));
	block.push_back(StaticBlock(world, sf::Vector2f(35.f, 142.f), sf::Vector2(10.0f, 2.0f)));
	block.push_back(StaticBlock(world, sf::Vector2f(45.f, 142.f), sf::Vector2(10.0f, 2.0f)));
	block.push_back(StaticBlock(world, sf::Vector2f(65.f, 142.f), sf::Vector2(10.0f, 2.0f)));
	block.push_back(StaticBlock(world, sf::Vector2f(75.f, 142.f), sf::Vector2(10.0f, 2.0f)));
	block.push_back(StaticBlock(world, sf::Vector2f(105.f, 142.f), sf::Vector2(10.0f, 2.0f)));
	spawnSlime(m_pWorld, sf::Vector2f(26.5f, 150.0f));
	spawnSlime(m_pWorld, sf::Vector2f(84.5f, 150.0f));
	//6						   
	block.push_back(StaticBlock(world, sf::Vector2f(15.f, 132.f), sf::Vector2(10.0f, 2.0f)));
	block.push_back(StaticBlock(world, sf::Vector2f(25.f, 132.f), sf::Vector2(10.0f, 2.0f)));
	block.push_back(StaticBlock(world, sf::Vector2f(45.f, 132.f), sf::Vector2(10.0f, 2.0f)));
	block.push_back(StaticBlock(world, sf::Vector2f(55.f, 132.f), sf::Vector2(10.0f, 2.0f)));
	block.push_back(StaticBlock(world, sf::Vector2f(65.f, 132.f), sf::Vector2(10.0f, 2.0f)));
	block.push_back(StaticBlock(world, sf::Vector2f(85.f, 132.f), sf::Vector2(10.0f, 2.0f)));
	block.push_back(StaticBlock(world, sf::Vector2f(95.f, 132.f), sf::Vector2(10.0f, 2.0f)));
	spawnSlime(m_pWorld, sf::Vector2f(38.5f, 140.0f));
	spawnSlime(m_pWorld, sf::Vector2f(73.5f, 140.0f));
	//7						   
	block.push_back(StaticBlock(world, sf::Vector2f(5.f, 122.f), sf::Vector2(10.0f, 2.0f)));
	block.push_back(StaticBlock(world, sf::Vector2f(35.f, 122.f), sf::Vector2(10.0f, 2.0f)));
	block.push_back(StaticBlock(world, sf::Vector2f(75.f, 122.f), sf::Vector2(10.0f, 2.0f)));
	block.push_back(StaticBlock(world, sf::Vector2f(95.f, 122.f), sf::Vector2(10.0f, 2.0f)));
	spawnSlime(m_pWorld, sf::Vector2f(25.5f, 130.0f));
	spawnSlime(m_pWorld, sf::Vector2f(55.5f, 130.0f));
	spawnSlime(m_pWorld, sf::Vector2f(85.5f, 130.0f));
	//8						   
	block.push_back(StaticBlock(world, sf::Vector2f(25.f, 112.f), sf::Vector2(10.0f, 2.0f)));
	block.push_back(StaticBlock(world, sf::Vector2f(35.f, 112.f), sf::Vector2(10.0f, 2.0f)));
	block.push_back(StaticBlock(world, sf::Vector2f(55.f, 112.f), sf::Vector2(10.0f, 2.0f)));
	block.push_back(StaticBlock(world, sf::Vector2f(75.f, 112.f), sf::Vector2(10.0f, 2.0f)));
	block.push_back(StaticBlock(world, sf::Vector2f(85.f, 112.f), sf::Vector2(10.0f, 2.0f)));
}

 //! Function to spawn in slimes with 2 adjancent sensors to keep in place
/*!
\param world for the game world
\param position for the location of the slime 
*/
void Scene::spawnSlime(b2World* world, sf::Vector2f position) {
	m_slime.push_back(new slime(m_pWorld, sf::Vector2f(position.x, position.y), sf::Vector2(1.f, 0.8f), m_textureManager.getTexture('e')));
	m_enemySensors.push_back(new enemySensors(m_pWorld, sf::Vector2f(position.x + 7.f, position.y), 's'));
	m_enemySensors.push_back(new enemySensors(m_pWorld, sf::Vector2f(position.x + -7.f, position.y), 's'));

}

