#include "Ball.hh"


Ball::Ball(int screenW, int screenH)
{
	speed = speed * screenW;
	radius = radius * screenW;

	ball.setFillColor(BALLCOLOR);
	ball.setRadius(radius);
	screenWidth = screenW;
	screenHeight = screenH;

	distanceFromTarget = 1;
	lastMurderColor = sf::Color::Transparent;
	timeElapsed = 0.f;
	speed = (initialSpeed + initialSpeed * (timeElapsed / 120)) * screenWidth;
}

Ball::~Ball() { }

void Ball::Update(float frameTime)
{
	if (distanceFromTarget != 1)
		RadiusAnimation();
	timeElapsed += frameTime;
	speed = (initialSpeed + initialSpeed * (timeElapsed / 120)) * screenWidth;
	Move(frameTime);
	center.x = position.x + radius;
	center.y = position.y + radius;
}

void Ball::RadiusAnimation()
{
	if (target == nullptr)
		return;
	float miTrajet = distanceFromTarget / 2;
	float distance = sqrt(pow(target->position.y - position.y, 2) + pow(target->position.x - position.x, 2));

	radius = (Initialradius * screenWidth) * (abs(abs((miTrajet - distance) / miTrajet) - 1) + 1);
	std::cout << radius << std::endl;

	ball.setRadius(radius);

}

void Ball::Move(float frameTime)
{
	if (target == nullptr)
		return;
	float angle = atan2((target->position.y + target->radius) - (position.y + radius), (target->position.x + target->radius) - (position.x + radius));


	position.x += cos(angle) * speed * frameTime;
	position.y += sin(angle) * speed * frameTime;

	ball.setPosition(position);
}

/*bool Ball::CheckCollision(std::vector<Player*>& players)
{
	bool playerCollision = false;

	playerCollision = CheckPlayerCollision(players);
	//CheckZoneCollision(players);
	return playerCollision;
}*/

bool Ball::CheckPlayerCollision(std::vector<Player*>& players)
{
	bool collision = false;
	int playerID;
	int targetID = target->id;

	for (auto &player : players)
		if (sqrt(pow(player->center.x - center.x, 2) + pow(player->center.y - center.y, 2)) <= player->radius + radius)
		{
			playerID = player->id;
			auto it = players.begin();
			for (it = players.begin(); it != players.end(); ++it)
				if ((*it)->id == playerID)
					break;
			lastMurderColor = player->color;
			player->Wplayer->SendTCPPacket("VIBRATE");
			delete player;
			players.erase(it);
			collision = true;

			if (players.size() < 2)
			{
				target = nullptr;
				return true;
			}
			target = players[rand() % players.size()];

			
		}
	return collision;
}

bool Ball::CheckZoneCollision(std::vector<Player*>& players)
{
	bool collision = false;

	if (players.size() < 2)
		return collision;
	for (int i = 0; i < players.size(); ++i)
	{
		if (players[i]->shootZoneRadius == players[i]->shootZoneMaxRadius)
			continue;
		if (sqrt(pow(players[i]->center.x - center.x, 2) + pow(players[i]->center.y - center.y, 2)) <= players[i]->shootZoneRadius + radius)
		{
			int randP = rand() % (players.size() - 1);
			if (players[randP]->id == players[i]->id)
				target = players[players.size() - 1];
			else
				target = players[randP];
			collision = true;
			distanceFromTarget = sqrt(pow(target->position.y - position.y, 2) + pow(target->position.x - position.x, 2));
		}
	}
	return collision;
}
