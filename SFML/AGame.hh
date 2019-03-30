#pragma once

#include <list>
#include <vector>
#include "Wimix_Player.hh"

#if defined(WIMIX_EXPORTS) && defined(_WIN32)
	#define WIMIX_API __declspec(dllexport) 
#elif defined _WIN32
	#define WIMIX_API __declspec(dllimport) 
#endif

class AGame
{
protected:
	std::vector<Wimix_Player*> players;

public:
	virtual ~AGame() {};

	void SetPlayers(std::vector<Wimix_Player*> const &clientsID)
	{
		players = clientsID;
	}

	virtual void Run() = 0;

	virtual int GetMinPlayers() = 0;

	virtual int GetMaxPlayers() = 0;
};

extern "C"
{
	#if _WIN32
		WIMIX_API AGame *GetDllGame();
	#else
		AGame *GetDllGame();
	#endif
}