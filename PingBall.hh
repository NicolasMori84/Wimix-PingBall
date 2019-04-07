#pragma once

#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <math.h>
#include <iostream>
#include "Ball.hh"
#include "Music.hh"
#include "Player.hh"

#define MAXPLAYER 10

#define BACKGROUND sf::Color(43, 42, 48)

#define TIMEBEFORESHOOT 0.3f

#define BALLSPEEDCROISSANCE 50.f

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
/*#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600*/

#define TIMEBEFORESTART 3.f

#define BACKGROUNDANIMDURATION 0.5f // (1.f / 0.5f)



class PingBall : public AGame
{
public:
	PingBall();
	virtual ~PingBall();

	sf::RenderWindow	window;
	sf::ContextSettings	settings;
	sf::Event event;
	sf::Clock clock;
	
	float frameTime;

	sf::Color backgroundColor;
	sf::Color colors[MAXPLAYER];
	sf::Color fluorColors[MAXPLAYER];
	sf::Vector2f initialPosition[MAXPLAYER];

	// Players
	std::vector<Player*> players;

	//// Ball
	Ball	ball;

	//Music
	Music music;

	float	timeElaspedBeforeStart = 0.f;
	float	timeForFlash = 0.f;

	sf::Font font;
	sf::Text text;

	bool finish = true;

	float			timeFps = 0.f;
	int frame;

public:
	void Update();
	void DestroyGame();

	virtual size_t GetMinPlayers();
	virtual size_t GetMaxPlayers();
	virtual void Run();

private:
	void InitPlayers();
	void InitBall();

	void EventHandler();

	void OnReceivePosition(Player *player, std::vector<std::string> & packet);
	void ShootBall(Player *player);

	//Animation visuelle
	void BackgroundHitWhenElimination();
	void textReadyGo();
};

