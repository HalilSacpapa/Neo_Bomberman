/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** PowerUp
*/

#include "PowerUp.hpp"

PowerUp::PowerUp(char type, const irr::core::vector2di &pos, irr::IrrlichtDevice *d)
	:	_pos(pos), _type(type)
{
	_mesh = d->getSceneManager()->addSphereSceneNode(8.0f);
	_mesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	if (type == 0)
		_mesh->setMaterialTexture(0, d->getVideoDriver()->getTexture("../graphs/powerupOneLegend.png"));
	if (type == 1)
		_mesh->setMaterialTexture(0, d->getVideoDriver()->getTexture("../graphs/powerupTwoLegend.png"));
	if (type == 2)
		_mesh->setMaterialTexture(0, d->getVideoDriver()->getTexture("../graphs/powerupThreeLegend.png"));
	if (type == 3)
		_mesh->setMaterialTexture(0, d->getVideoDriver()->getTexture("../graphs/powerupFourLegend.png"));
	_mesh->setPosition(irr::core::vector3df(pos.X * 20, pos.Y * 20, -8.0f));
}

PowerUp::~PowerUp()
{
	if (_mesh)
		_mesh->remove();
}

const irr::core::vector2di &PowerUp::getPos()
{
	return _pos;
}

char PowerUp::getType()
{
	return _type;
}