#pragma once
#include "Client.hh"

class Player
{
	Client &client;

public:
	Player(Client &c);
	~Player();

	bool IsDisconnected() const;
	void SendTCPPacket(std::string const &msg);
	bool HasReceiveUDPPacket() const;
	const std::vector<std::string> GetUDPPacket();

private:
	const std::vector<std::string> Split(const std::string& s, const char& c) const;
};

