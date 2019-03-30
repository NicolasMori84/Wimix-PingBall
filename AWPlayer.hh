#pragma once
#include <vector>

class AWPlayer
{
public:
	enum ControllerType
	{
		BUTTON,
		JOYSTICK,
		DIRECTIONNALBUTTON,
		GYROSCOPE
	};

	enum ControllerLocation
	{
		LEFT,
		RIGHT
	};

public:
	virtual ~AWPlayer() { };

	virtual bool IsDisconnected() const = 0;

	virtual void SendTCPPacket(std::string msg) = 0;
	virtual void SetController(ControllerLocation pos, ControllerType type) = 0;
	virtual bool ControllerUpdate(ControllerLocation pos, std::vector<std::string> &update) = 0;
};
