#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "AGame.hh"

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
/*#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600*/

#define OUTLINEANIMDURATION 3.33333f // (1.f / 0.3f)

class Player
{
public:
	int				id;
	AWPlayer		*Wplayer;

	sf::Vector2f	position;
	sf::Vector2f	center;

	sf::Vector2f	move;

	sf::Color		color;
	sf::Color		zoneColor;
	float			radius = 0.02f;
	float			shootZoneBorderWidth = 0.01f;
	float			shootZoneRadius = 0.1f;
	float			shootZoneMaxRadius = 0.1f;
	float			speed = 0.3f;

	float			diffPlayerShootZone = 0.f;

	float			timeBeforeSpace = 0.f;

	bool			alive = true;

	sf::CircleShape player;
	sf::CircleShape shootZone;


public:
	Player();
	~Player();

	void Update(float frameTime);

private:
	void Move(float frameTime);

	void UpdateOutline(float frameTime);
};

