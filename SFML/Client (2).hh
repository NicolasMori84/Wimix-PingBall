#pragma once
#include <atomic>
#include <mutex>
#include <vector>
#include "NetworkManager.hh"

class Client
{
public:
	std::shared_ptr<Network::Socket>	tcpSocket;
	sockaddr_in							udpInfo;
	uint32_t							udpPacketIndex;

	int									id;
	
	std::atomic<bool>					hasReceiveUDPMessage;
	std::atomic<bool>					isConnected;
	std::atomic<bool>					inGame;

private:
	std::string							tcpPacket;
	std::string							udpPacket;
	
	std::mutex							tcpPacketM;
	std::mutex							udpPacketM;

public:
	Client();
	~Client();

	std::string const	GetTCPPacket();
	void				SetTCPPacket(std::string const &msg);

	std::string const	GetUDPPacket();
	void				SetUDPPacket(std::string const &msg);

	const std::vector<std::string> Split(const std::string& s, const char& c) const;
};

