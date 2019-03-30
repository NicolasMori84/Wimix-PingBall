#pragma once
#include "Client.hh"

class Wimix_Player
{
	Client &client;

public:
	Wimix_Player(Client &c);
	~Wimix_Player();

	bool IsDisconnected() const;
	void SendTCPPacket(std::string const &msg);
	bool HasReceiveUDPPacket() const;
	const std::vector<std::string> GetUDPPacket();

private:
	const std::vector<std::string> Split(const std::string& s, const char& c) const;
};

