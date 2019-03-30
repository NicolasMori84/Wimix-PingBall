#pragma once
#include "Player.hh"

#define BALLCOLOR sf::Color(178, 178, 178)

class Ball
{
public:
	sf::CircleShape	ball;
	sf::Vector2f	position;
	sf::Vector2f	center;
	float			Initialradius = 0.01f;
	float			radius = 0.01f;
	float			initialSpeed = 0.3f;
	float			speed = 0;
	float			timeElapsed = 0;

	Player			*target = nullptr;

	int				screenWidth;
	int				screenHeight;

	float			distanceFromTarget = 1;
	sf::Color		lastMurderColor;

public:
	Ball(int screenWidth, int screenHeight);
	~Ball();

	void Update(float frameTime);
	void Move(float frameTime);
	void RadiusAnimation();


	//bool CheckCollision(std::vector<Player*> &players);
	bool CheckPlayerCollision(std::vector<Player*> &players);
	bool CheckZoneCollision(std::vector<Player*> &players);
};

