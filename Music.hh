#pragma once

#include <SFML/Audio.hpp>
#include <iostream>

class Music
{
public:
	Music();
	~Music();

	void SoundtrackPlay();
	void CollisionPlay();
	void OndePlay();
	void RebondPlay();
	void EndPlay();

private:

	sf::Music soundtrack;
	sf::Sound collision;
	sf::Sound onde;
	sf::Sound end;
	sf::Sound rebond;
	sf::SoundBuffer collisionB;
	sf::SoundBuffer ondeB;
	sf::SoundBuffer endB;
	sf::SoundBuffer rebondB;

	bool error = false;




};

