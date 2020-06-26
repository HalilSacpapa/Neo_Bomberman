/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** Bomb
*/

#include "Bomb.hpp"

Bomb::Bomb(const time_t &start, const irr::core::vector2di &pos, irr::IrrlichtDevice *d, int id, char boost)
	:	_start(start), _pos(pos), _explodingTime(4), _radius(boost + 2), _playerId(id)
{
    _mesh = d->getSceneManager()->addAnimatedMeshSceneNode(d->getSceneManager()->getMesh("../graphs/Bomb.md2"));
    _mesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    // _mesh->setFrameLoop(0, 100);
    // _mesh->setMaterialTexture(0, d->getVideoDriver()->getTexture("../graphs/bla.png"));
    _mesh->setPosition(irr::core::vector3df(pos.X * 20, pos.Y * 20, 0.0f));
	irr::core::vector3df scale = _mesh->getScale();
	scale.X /= 50;
	scale.Y /= 50;
	scale.Z /= 50;
	_mesh->setScale(scale);
    // _mesh->setRotation(_dir);
}

Bomb::~Bomb()
{
	if (_mesh)
		_mesh->remove();
}

bool Bomb::explodes(const time_t &time)
{
	if (time - _start >= _explodingTime)
		return true;
	return false;
}

int Bomb::getPlayerId()
{
	return _playerId;
}

irr::core::vector2di Bomb::getPos()
{
	return _pos;
}

char Bomb::getRadius()
{
	return _radius;
}

irr::core::vector2di from3dTo2d(irr::core::vector3df from)
{
	irr::core::vector2di res((int)((from.X + 10) / 20),(int)((from.Y + 10) / 20));
	return res;
}
