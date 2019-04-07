#pragma once

#include <list>
#include <vector>
#include "AWPlayer.hh"

#if defined(WIMIX_EXPORTS) && defined(_WIN32)
	#define WIMIX_API __declspec(dllexport) 
#elif defined _WIN32
	#define WIMIX_API __declspec(dllimport) 
#endif

class AGame
{
protected:
	std::vector<AWPlayer*> wPlayers;

public:
	virtual ~AGame() {};

	void SetPlayers(std::vector<AWPlayer*> const &clientsID)
	{
		wPlayers = clientsID;
	}

	virtual void Run() = 0;

	virtual size_t GetMinPlayers() = 0;

	virtual size_t GetMaxPlayers() = 0;
};

extern "C"
{
	#if _WIN32
		WIMIX_API AGame *GetDllGame();
	#else
		AGame *GetDllGame();
	#endif
}