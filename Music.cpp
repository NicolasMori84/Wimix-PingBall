#include "Music.hh"

Music::Music()
{
	error = false;


	if (!soundtrack.openFromFile("Games/PingBall/Music/Soundtrack - Active_Form.wav"))
		error = true;
	if (!collisionB.loadFromFile("Games/PingBall/Music/Collision - Crash_Impact_Sweetener.wav"))
		error = true;
	if (!ondeB.loadFromFile("Games/PingBall/Music/Onde.wav"))
		error = true;
	if (!endB.loadFromFile("Games/PingBall/Music/Fin - Dying Robot-SoundBible.com.wav"))
		error = true;
	if (!rebondB.loadFromFile("Games/PingBall/Music/Rebond.wav"))
		error = true;

	if (!error)
	{
		soundtrack.setLoop(true);
		collision.setBuffer(collisionB);
		onde.setBuffer(ondeB);
		end.setBuffer(endB);
		rebond.setBuffer(rebondB);

		soundtrack.setVolume(20.f);
		collision.setVolume(80.f);
		onde.setVolume(100.f);
		end.setVolume(50.f);
		rebond.setVolume(40.f);
	}
}


Music::~Music()
{
}

void Music::SoundtrackPlay()
{
	soundtrack.play();
}

void Music::CollisionPlay()
{
	collision.play();
}

void Music::OndePlay()
{
	onde.play();
}

void Music::RebondPlay()
{
	rebond.play();
}

void Music::EndPlay()
{
	end.play();
}

