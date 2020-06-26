/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** Bomb
*/

#ifndef BOMB_HPP_
#define BOMB_HPP_
#include <ctime>
#include <irrlicht.h>

class Bomb {
	public:
		Bomb(const time_t &, const irr::core::vector2di &, irr::IrrlichtDevice *, int, char = 0);
		~Bomb();

		bool explodes(const time_t &);
		irr::core::vector2di getPos();
		char getRadius();
		int getPlayerId();
	private:
		irr::scene::IAnimatedMeshSceneNode *_mesh;
		time_t _start;
		irr::core::vector2di _pos;
		time_t _explodingTime;
		char _radius;
		int _playerId;
};

irr::core::vector2di from3dTo2d(irr::core::vector3df from);

#endif /* !BOMB_HPP_ */
