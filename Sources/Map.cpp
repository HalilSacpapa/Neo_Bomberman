/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Map
*/

#include "Map.hpp"

Map::Map(int level)
 :	_populated(false), _wishedLevel(level)
{
	generateLevel(_wishedLevel);
}

Map::~Map()
{
	clean();
}

void Map::populate(irr::IrrlichtDevice *device, int level)
{
	if (_populated) {
		_wishedLevel = level;
		clean();
		_populated = false;
		generateLevel(_wishedLevel);
	}
	_wishedLevel = level;
	// _groundBlocks.push_back(device->getSceneManager()->addCubeSceneNode(1.0f, 0, -1, irr::core::vector3df(0.0f, 0.0f, 0.0f))); /* DESCRIBE X Y Z COORDS */
	// _groundBlocks[_groundBlocks.size()-1]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	// _groundBlocks[_groundBlocks.size()-1]->setMaterialTexture(0, device->getVideoDriver()->getTexture("../graphs/bla.png"));
	// _groundBlocks.push_back(device->getSceneManager()->addCubeSceneNode(1.0f, 0, -1, irr::core::vector3df(5.0f, 0.0f, 0.0f)));
	// _groundBlocks[_groundBlocks.size()-1]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	// _groundBlocks[_groundBlocks.size()-1]->setMaterialTexture(0, device->getVideoDriver()->getTexture("../graphs/unbreakableBlock.png"));
	// _groundBlocks.push_back(device->getSceneManager()->addCubeSceneNode(1.0f, 0, -1, irr::core::vector3df(0.0f, 5.0f, 0.0f)));
	// _groundBlocks[_groundBlocks.size()-1]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	// _groundBlocks[_groundBlocks.size()-1]->setMaterialTexture(0, device->getVideoDriver()->getTexture("../graphs/breakableBlock.png"));
	// _groundBlocks.push_back(device->getSceneManager()->addCubeSceneNode(1.0f, 0, -1, irr::core::vector3df(0.0f, 0.0f, 5.0f)));
	// _groundBlocks[_groundBlocks.size()-1]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	// _groundBlocks[_groundBlocks.size()-1]->setMaterialTexture(0, device->getVideoDriver()->getTexture("../graphs/groundBlock.png"));
	// _populated = true;
	// return;
	size_t iSize = _level.size() + 2;
	size_t jSize = _level[0].size() + 2;
	for (size_t i = 0; i < iSize; i++) {
		for (size_t j = 0; j < jSize; j++) {
			_groundBlocks.push_back(device->getSceneManager()->addCubeSceneNode(20.0f, 0, -1, irr::core::vector3df(20.0f * j - 20.0f, 20.0f * i - 20.0f, ((i == 0 || j == 0 || i == iSize - 1 || j == jSize - 1)?0.0f:20.0f))));
			_groundBlocks[_groundBlocks.size()-1]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
			_groundBlocks[_groundBlocks.size()-1]->setMaterialTexture(0, device->getVideoDriver()->getTexture("../graphs/groundBlock.png"));
		}
	}
	for (int i = 0; i < _level.size(); i++) {
		for (int j = 0; j < _level[i].size(); j++) {
			if (_level[i][j] == 1) {
				_breakableBlocks.push_back(device->getSceneManager()->addCubeSceneNode(20.0f, 0, -1, irr::core::vector3df(20.0f * j, 20.0f * i, 0.0f)));
				_breakableBlocks[_breakableBlocks.size()-1]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
				_breakableBlocks[_breakableBlocks.size()-1]->setMaterialTexture(0, device->getVideoDriver()->getTexture("../graphs/breakableBlock.png"));
				_breakablePos.push_back(irr::core::vector2di(j, i));
			} else if (_level[i][j] == 2) {
				_unbreakableBlocks.push_back(device->getSceneManager()->addCubeSceneNode(20.0f, 0, -1, irr::core::vector3df(20.0f * j, 20.0f * i, 0.0f)));
				_unbreakableBlocks[_unbreakableBlocks.size()-1]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
				_unbreakableBlocks[_unbreakableBlocks.size()-1]->setMaterialTexture(0, device->getVideoDriver()->getTexture("../graphs/unbreakableBlock.png"));
				_unbreakablePos.push_back(irr::core::vector2di(j, i));
			}
		}
	}
	_populated = true;
}

std::vector<std::vector<int>> Map::getLevel()
{
  return (_level);
}

const std::vector<irr::scene::IMeshSceneNode *> &Map::getGround()
{
  return (_groundBlocks);
}

const std::vector<irr::scene::IMeshSceneNode *> &Map::getUnbreak()
{
  return (_unbreakableBlocks);
}

const std::vector<irr::core::vector2di> &Map::getBreakPos()
{
	return _breakablePos;
}

const std::vector<irr::core::vector2di> &Map::getUnBreakPos()
{
	return _unbreakablePos;
}

const std::vector<irr::scene::IMeshSceneNode *> &Map::getBreak()
{
  return (_breakableBlocks);
}

std::string Map::getBlock(const irr::core::vector2di &pos)
{
	for (int i = 0; i < _breakablePos.size(); i++)
		if (_breakablePos[i].equals(pos))
			return "breakable";
	for (int i = 0; i < _unbreakablePos.size(); i++)
		if (_unbreakablePos[i].equals(pos))
			return "unbreakable";
	return ("empty");
}

int Map::getBlockIndex(const irr::core::vector2di &pos)
{
	for (int i = 0; i < _breakablePos.size(); i++)
		if (_breakablePos[i].equals(pos))
			return i;
	for (int i = 0; i < _unbreakablePos.size(); i++)
		if (_unbreakablePos[i].equals(pos))
			return i;
	return (-1);
}

void Map::breakBlock(const irr::core::vector2di &pos)
{
	if (getBlock(pos) == "empty" || getBlock(pos) == "unbreakable")
		return ;
	// std::cout << "\nDROPPING BLOCK\t" << pos.X << "\t" << pos.Y << std::endl;
	// s->addToDeletionQueue(_breakableBlocks[i]);
	int i = getBlockIndex(pos);
	_breakableBlocks[i]->remove();
	_breakableBlocks.erase(_breakableBlocks.begin() + i);
	_breakablePos.erase(_breakablePos.begin() + i);
	_level[pos.Y][pos.X] = 0;
}

void Map::generateLevel(int level)
{
  base_map(level);
  srand(time(NULL));
  float tmp = (143 * ((rand() % 20 + 30)) / 130);
  int fill = tmp;
  int total = 143;

  for (int x = 0; x != 13; x++) {
    for (int y = 0; y != 11; y++) {
      if (fill == 0)
        return;
      srand(time(NULL));
      tmp = rand() % total;
      if (tmp < fill && _level[x][y] != 2 && check_corner(x, y) == 0) {
        _level[x][y] = 1;
        fill--;
      }
      total--;
    }
  }
}

void Map::base_map(int level)
{
  std::vector<int> tmp;
  std::vector<std::vector<int>> map;
  _level.reserve(sizeof(std::vector<std::vector<int>>));
  if (level == 1) {
	for (int x = 0; x != 13; x++) {
	for (int y = 0; y != 11; y++) {
		if (x%2 != 0 && y%2 != 0)
		tmp.push_back(2);
		else
		tmp.push_back(0);
	}
	_level.push_back(tmp);
	tmp.clear();
	}
  } else if (level == 2) {
	for (int x = 0; x != 13; x++) {
	for (int y = 0; y != 11; y++) {
		if (x%3 != 0 && y%3 != 0 && x != 0 && x != 12 && y != 0 && y != 10)
		tmp.push_back(2);
		else
		tmp.push_back(0);
	}
	_level.push_back(tmp);
	tmp.clear();
	}
  } if (level == 3) {
	for (int x = 0; x != 13; x++) {
	for (int y = 0; y != 11; y++) {
		if (x%3 != 0 && y%2 != 0 && x != 0 && x != 12 && y != 0 && y != 10)
		tmp.push_back(2);
		else
		tmp.push_back(0);
	}
	_level.push_back(tmp);
	tmp.clear();
	}
  }
}

int Map::check_corner(int x, int y)
{
  if ((x == 0 && y == 0) || (x == 0 && y == 1) || (x == 1 && y == 0))
    return (1);
  else if ((x == 0 && y == 10) || (x == 0 && y == 9) || (x == 1 && y == 10))
    return (1);
  else if ((x == 12 && y == 0) || (x == 11 && y == 0) || (x == 12 && y == 1))
    return (1);
  else if ((x == 12 && y == 10) || (x == 12 && y == 9) || (x == 11 && y == 10))
    return (1);
  return (0);
}

void Map::clean()
{
	for (int i = 0; i < _groundBlocks.size(); i++)
		_groundBlocks[i]->remove();
	for (int i = 0; i < _unbreakableBlocks.size(); i++)
		_unbreakableBlocks[i]->remove();
	for (int i = 0; i < _breakableBlocks.size(); i++)
		_breakableBlocks[i]->remove();
	_breakableBlocks.clear();
	_unbreakableBlocks.clear();
	_groundBlocks.clear();
	_breakablePos.clear();
	_unbreakablePos.clear();
	_level.clear();
}