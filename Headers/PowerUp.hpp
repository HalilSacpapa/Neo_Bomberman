/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** PowerUp
*/

#ifndef POWERUP_HPP_
#define POWERUP_HPP_
#include <irrlicht.h>
/*
[0]	ONE		NUMBER OF BOMBS			BLACK
[1]	TWO		RADIUS OF BOMBS			BLUE
[2]	THREE	WALLHACK				GREEN
[3]	FOUR	SPEEDHACK				PINK
							*/

class PowerUp {
	public:
		PowerUp(char, const irr::core::vector2di &, irr::IrrlichtDevice *);
		~PowerUp();

		const irr::core::vector2di &getPos();
		char getType();
	private:
		irr::scene::IMeshSceneNode *_mesh;
		irr::core::vector2di _pos;
		char _type;
};

#endif /* !POWERUP_HPP_ */
