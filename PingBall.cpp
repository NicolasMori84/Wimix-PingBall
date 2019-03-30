#include "PingBall.hh"

PingBall::PingBall() : ball(WINDOW_WIDTH, WINDOW_HEIGHT)
{
	srand(time(NULL));
	colors[0] = sf::Color(239, 83, 80);
	colors[1] = sf::Color(171, 71, 188);
	colors[2] = sf::Color(92, 107, 192);
	colors[3] = sf::Color(41, 182, 246);
	colors[4] = sf::Color(38, 166, 154);
	colors[5] = sf::Color(156, 204, 101);
	colors[6] = sf::Color(255, 202, 40);
	colors[7] = sf::Color(255, 112, 67);

	fluorColors[0] = sf::Color(255, 23, 68);
	fluorColors[1] = sf::Color(213, 0, 249);
	fluorColors[2] = sf::Color(61, 90, 254);
	fluorColors[3] = sf::Color(0, 176, 255);
	fluorColors[4] = sf::Color(29, 233, 182);
	fluorColors[5] = sf::Color(118, 255, 3);
	fluorColors[6] = sf::Color(255, 196, 0);
	fluorColors[7] = sf::Color(255, 61, 0);

	initialPosition[0] = sf::Vector2f(WINDOW_WIDTH * 0.2f, WINDOW_HEIGHT * 0.2f);
	initialPosition[1] = sf::Vector2f(WINDOW_WIDTH * 0.8f, WINDOW_HEIGHT * 0.2f);
	initialPosition[2] = sf::Vector2f(WINDOW_WIDTH * 0.2f, WINDOW_HEIGHT * 0.4f);
	initialPosition[3] = sf::Vector2f(WINDOW_WIDTH * 0.8f, WINDOW_HEIGHT * 0.4f);
	initialPosition[4] = sf::Vector2f(WINDOW_WIDTH * 0.2f, WINDOW_HEIGHT * 0.6f);
	initialPosition[5] = sf::Vector2f(WINDOW_WIDTH * 0.8f, WINDOW_HEIGHT * 0.6f);
	initialPosition[6] = sf::Vector2f(WINDOW_WIDTH * 0.2f, WINDOW_HEIGHT * 0.8f);
	initialPosition[7] = sf::Vector2f(WINDOW_WIDTH * 0.8f, WINDOW_HEIGHT * 0.8f);
}

PingBall::~PingBall()
{
	//music.close();
}

void PingBall::Run()
{
	std::cout << "Crate Game" << std::endl;
	/*if (playersID.size() < 2)
	{
		std::cerr << "Not enougth players !" << std::endl;
		finish = true;
		return;
	}*/

	finish = false;

	settings.antialiasingLevel = 8;
	window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "PingBall", sf::Style::Fullscreen, settings);
	//window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "PingBall", sf::Style::Default, settings);


	if (font.loadFromFile("Games/Pingball/HomenuliShadow.ttf") == false)
		std::cout << "ECHEC FONT LOAD" << std::endl;

	text.setFont(font);


	InitPlayers();
	InitBall();


	backgroundColor = BACKGROUND;

	frameTime = 0.f;
	timeElaspedBeforeStart = 0.f;
	timeForFlash = 0.f;

	music.SoundtrackPlay();
	clock.restart();

	timeFps = 0.f;
	frame = 0;


	Update();

	DestroyGame();
}

void PingBall::BackgroundHitWhenElimination()
{
	if (ball.lastMurderColor == sf::Color::Transparent)
		window.clear(backgroundColor);
	else
	{
		timeForFlash -= frameTime;
		if (timeForFlash < 0.f)
		{
			timeForFlash = 0.f;
			backgroundColor = BACKGROUND;
		}
		else
		{
			float coef = timeForFlash / BACKGROUNDANIMDURATION;
			backgroundColor.r = (BACKGROUND.r * (1 - coef)) + (ball.lastMurderColor.r * coef);
			backgroundColor.g = (BACKGROUND.g * (1 - coef)) + (ball.lastMurderColor.g * coef);
			backgroundColor.b = (BACKGROUND.b * (1 - coef)) + (ball.lastMurderColor.b * coef);

		}
		window.clear(backgroundColor);

	}
}

void PingBall::textReadyGo()
{
	if (timeElaspedBeforeStart > (2.f / 3.f) * TIMEBEFORESTART)
		text.setString("G O !");
	else
		text.setString("R E A D Y ?");
	text.setCharacterSize(150 * timeElaspedBeforeStart);

	sf::Color colorText = sf::Color::Yellow;

	float coef = timeElaspedBeforeStart / TIMEBEFORESTART;

	colorText.a = colorText.a * coef;
	text.setFillColor(colorText);

	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	text.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f));

	window.draw(text);
}

void PingBall::Update()
{
	std::vector<std::string> cmd;
	while (!finish)
	{
		EventHandler();

		BackgroundHitWhenElimination();

		for (size_t i = 0; i < players.size(); ++i)
		{
			if (players[i]->Wplayer->ControllerUpdate(AWPlayer::LEFT, cmd))
				OnReceivePosition(players[i], cmd);
			else if (players[i]->Wplayer != nullptr && players[i]->Wplayer->ControllerUpdate(AWPlayer::RIGHT, cmd))
				ShootBall(players[i]);
			players[i]->Update(frameTime);
			window.draw(players[i]->shootZone);
			window.draw(players[i]->player);
		}

		if (timeElaspedBeforeStart > TIMEBEFORESTART)
		{
			ball.Update(frameTime);
			window.draw(ball.ball);
			if (ball.CheckPlayerCollision(players))
			{
				music.CollisionPlay();
				timeForFlash = BACKGROUNDANIMDURATION;
			}
			if (ball.CheckZoneCollision(players))
			{
				music.RebondPlay();

			}
		}
		else
		{
			textReadyGo();
		}

		window.display();


		if (players.size() < 2)
		{
			finish = true;
			return;
		}

		timeElaspedBeforeStart += frameTime;
		frameTime = clock.restart().asSeconds();

		timeFps += frameTime;
		frame++;
		if (timeFps > 1)
		{
			std::cout << "Frame : " << frame << std::endl;
			timeFps = 0.f;
			frame = 0;
		}

	}
}

void PingBall::DestroyGame()
{
	int i = 0;
	for (auto &player : players)
		delete player;
	while (players.size())
		players.erase(players.begin());
	players.clear();
	window.close();
}

int PingBall::GetMinPlayers()
{
	return 2;
}

int PingBall::GetMaxPlayers()
{
	return 6;
}


void PingBall::InitPlayers()
{
	Player *newPlayer = nullptr;

	// Init player
	int i = 0;

	std::cout << "Nbr_joueur Init : " << wPlayers.size() << std::endl;

	/*players.push_back(players.size() + 1);//bot
	players.push_back(players.size() + 1);//bot
	players.push_back(players.size() + 1);//bot*/
	for (int i = 0; i < wPlayers.size(); i++)
	{
		newPlayer = new Player();
		newPlayer->Wplayer = wPlayers[i];
		newPlayer->id = i;
		newPlayer->position.x = initialPosition[i].x;
		newPlayer->position.y = initialPosition[i].y;
		newPlayer->color = colors[i];
		newPlayer->zoneColor = fluorColors[i];
		newPlayer->player.setFillColor(newPlayer->color);
		players.push_back(newPlayer);
	}
}

void PingBall::InitBall()
{
	ball.position.x = WINDOW_WIDTH / 2;
	ball.position.y = WINDOW_HEIGHT / 2;

	int randP = rand() % players.size();
	ball.target = players[randP];

	ball.ball.setPosition(ball.position);
}

void PingBall::EventHandler()
{
	while (window.pollEvent(event))
		if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
		{
			finish = true;
			return;
		}
}

void PingBall::OnReceivePosition(Player *player, std::vector<std::string> & packet)
{
	int angleDeg = 0;
	float force = 0;

	angleDeg = std::atoi(packet[0].c_str());
	force = (float)std::atoi(packet[1].c_str()) / 100.f;

	float angleRad = (angleDeg * M_PI) / 180.f;

	player->move.x = cos(angleRad) * (player->speed * force);
	player->move.y = -sin(angleRad) * (player->speed * force);
	return;
}

void PingBall::ShootBall(Player *player)
{
	music.OndePlay();
	if (player->timeBeforeSpace > 0.f)
		return;
	player->timeBeforeSpace = TIMEBEFORESHOOT;
	player->shootZoneRadius = player->radius;
	player->shootZone.setRadius(player->shootZoneRadius);
	//player->shootZone.setFillColor(player->zoneColor);
	player->shootZone.setOutlineColor(player->zoneColor);
}

AGame *GetDllGame()
{
	return new PingBall();
}