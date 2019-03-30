#include "Player.hh"


Player::Player()
{
	position.x = 0.f;
	position.y = 0.f;
	move.x = 0.f;
	move.y = 0.f;
	
	radius = radius * WINDOW_WIDTH;
	shootZoneRadius = shootZoneRadius * WINDOW_WIDTH;
	shootZoneBorderWidth = shootZoneBorderWidth * WINDOW_WIDTH;
	shootZoneMaxRadius = shootZoneMaxRadius * WINDOW_WIDTH;
	speed = speed * WINDOW_WIDTH;

	player.setRadius(radius);
	shootZone.setRadius(shootZoneRadius);
	shootZone.setOutlineThickness(shootZoneBorderWidth);
	shootZone.setFillColor(sf::Color::Transparent);
	shootZone.setOutlineColor(sf::Color::Transparent);

	diffPlayerShootZone = shootZoneRadius - radius;
}

Player::~Player() { }

void Player::Update(float frameTime)
{
	Move(frameTime);
	UpdateOutline(frameTime);
	
	timeBeforeSpace -= frameTime;
	if (timeBeforeSpace < 0.f)
		timeBeforeSpace = 0.f;
}

void Player::Move(float frameTime)
{
	position += move * frameTime;
	if (position.x + radius > WINDOW_WIDTH)
		position.x = WINDOW_WIDTH - radius;
	else if (position.x + radius < 0)
		position.x = -radius;
	if (position.y + radius > WINDOW_HEIGHT)
		position.y = WINDOW_HEIGHT - radius;
	if (position.y + radius < 0)
		position.y = -radius;
	center.x = position.x + radius;
	center.y = position.y + radius;
	player.setPosition(position);
}

void Player::UpdateOutline(float frameTime)
{
	if (shootZoneRadius < shootZoneMaxRadius)
	{
		shootZoneRadius += shootZoneMaxRadius * frameTime * OUTLINEANIMDURATION;
		if (shootZoneRadius >= shootZoneMaxRadius)
		{
			shootZoneRadius = shootZoneMaxRadius;
			shootZone.setOutlineColor(sf::Color::Transparent);
			//shootZone.setFillColor(sf::Color::Transparent);
		}
		else
		{
			//sf::Color actualColor = shootZone.getFillColor();
			sf::Color actualColor = shootZone.getOutlineColor();
			float alpha = (float)actualColor.a;
			alpha -= 255.f * frameTime * OUTLINEANIMDURATION;
			actualColor.a = (alpha < 0.f) ? 0.f : alpha;
			//shootZone.setFillColor(actualColor);
			shootZone.setOutlineColor(actualColor);
		}
		shootZone.setRadius(shootZoneRadius);
		diffPlayerShootZone = shootZoneRadius - radius;
	}
	shootZone.setPosition(position.x - diffPlayerShootZone, position.y - diffPlayerShootZone);
}
