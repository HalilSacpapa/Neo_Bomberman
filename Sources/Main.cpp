/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** Main
*/

#include "indie.hpp"

int exit_properly(std::string err = "", int ret = 84, bool usage = false)
{
	if (err != "")
		std::cerr << err << std::endl;
	if (usage)
		std::cout << "Work In Progress. This is a game." << std::endl;
	exit(ret);
}

irr::IrrlichtDevice *handleDevice(MyEventReceiver *handler)
{
	if (irr::IrrlichtDevice::isDriverSupported(irr::video::EDT_OPENGL))
		return (irr::createDevice(irr::video::EDT_OPENGL,
					core::dimension2d<u32>(640,480), 16, false, false, false, handler));
	if (irr::IrrlichtDevice::isDriverSupported(irr::video::EDT_DIRECT3D9))
		return (irr::createDevice(irr::video::EDT_DIRECT3D9,
					core::dimension2d<u32>(640,480), 16, false, false, false, handler));
	if (irr::IrrlichtDevice::isDriverSupported(irr::video::EDT_DIRECT3D8))
		return (irr::createDevice(irr::video::EDT_DIRECT3D8,
					core::dimension2d<u32>(640,480), 16, false, false, false, handler));
	if (irr::IrrlichtDevice::isDriverSupported(irr::video::EDT_BURNINGSVIDEO))
		return (irr::createDevice(irr::video::EDT_BURNINGSVIDEO,
					core::dimension2d<u32>(640,480), 16, false, false, false, handler));
	if (irr::IrrlichtDevice::isDriverSupported(irr::video::EDT_SOFTWARE))
		return (irr::createDevice(irr::video::EDT_SOFTWARE,
					core::dimension2d<u32>(640,480), 16, false, false, false, handler));
	if (irr::IrrlichtDevice::isDriverSupported(irr::video::EDT_NULL))
		return (irr::createDevice(irr::video::EDT_NULL,
					core::dimension2d<u32>(640,480), 16, false, false, false, handler));
	exit_properly("Error while creating Irrlicht device. None of these drivers are available\n\tEDT_OPENGL\n\tEDT_DIRECT3D9\n\tEDT_DIRECT3D8\n\tEDT_BURNINGSVIDEO\n\tEDT_SOFTWARE");
	return (nullptr);
}

int main()
{
	MyEventReceiver *event = new MyEventReceiver();
	irr::IrrlichtDevice *device = handleDevice(event);
	if (!device)
		exit_properly("Error while creating Irrlicht device. None of these drivers are available\n\tEDT_OPENGL\n\tEDT_DIRECT3D9\n\tEDT_DIRECT3D8\n\tEDT_BURNINGSVIDEO\n\tEDT_SOFTWARE");
	Game *handler = new Game(device, event);
	handler->run();
	return 0;
}