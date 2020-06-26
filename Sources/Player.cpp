/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Player
*/

#include "Player.hpp"

Player::Player(const irr::core::vector3df &pos, bool AI, int id)
	: _mesh(0), _AI(AI), _id(id), _idle(false), _walking(false), _bomb(false), _lastAnswer(-1) ,_lastAnswerT(std::chrono::steady_clock::now()) , _currentBombs(0)
{
	_pos = pos;
	_dir = irr::core::vector3df(0,0,0);
	for (int i = 0; i < 4; i++)
	_boosts[i] = 0;
	_boosts[0] = 1;
	if (!_AI && id == 0) {
		_keys[0] = irr::KEY_KEY_Z;
		_keys[1] = irr::KEY_KEY_Q;
		_keys[2] = irr::KEY_KEY_S;
		_keys[3] = irr::KEY_KEY_D;
		_keys[4] = irr::KEY_KEY_A;
	}
	if (!_AI && id == 1) {
		_keys[0] = irr::KEY_KEY_O;
		_keys[1] = irr::KEY_KEY_K;
		_keys[2] = irr::KEY_KEY_L;
		_keys[3] = irr::KEY_KEY_M;
		_keys[4] = irr::KEY_KEY_I;
	}
	if (id == 0 || id == 1)
		_dir.Z = 180;
	_lastBomb = 0;
}

Player::~Player()
{
	if (_mesh)
		_mesh->remove();
}

void Player::SetKey(int index, EKEY_CODE key)
{
	if (index >= 0 && index <= 4)
		_keys[index] = key;
}

void Player::loadMesh(irr::IrrlichtDevice *d, const char *mesh, const char *text)
{
	_mesh = d->getSceneManager()->addAnimatedMeshSceneNode(d->getSceneManager()->getMesh(mesh));
	if (!_mesh)
		exit(84);
	_mesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	_mesh->setFrameLoop(0, 10);
	// _mesh->setMaterialTexture(0, d->getVideoDriver()->getTexture(text));
	_mesh->setPosition(_pos);
	_mesh->setRotation(_dir);
	irr::core::vector3df scale = _mesh->getScale();
	scale.X *= 15;
	scale.Y *= 15;
	scale.Z *= 15;
	_mesh->setScale(scale);
}

irr::core::vector3df Player::getPos()
{
	return _pos;
}

int Player::getId()
{
	return _id;
}

void Player::bombExploded()
{
	_currentBombs -= 1;
}

bool Player::isAI()
{
	return _AI;
}

void Player::boostStat(char type)
{
	_boosts[type] += 1;
}

bool collision(irr::scene::ISceneNode* one, irr::scene::ISceneNode* two) {
   irr::core::aabbox3d<f32> b1, b2;

   b1 = one->getBoundingBox ();
   b2 = two->getBoundingBox ();

   one->getRelativeTransformation().transformBoxEx( b1 );
   two->getRelativeTransformation().transformBoxEx( b2 );
   return b1.intersectsWithBox( b2 );
}

bool isBusy(const irr::core::vector3df &dot, const std::vector<irr::scene::IMeshSceneNode *> &ground, const std::vector<irr::scene::IMeshSceneNode *> &unbreakable, const std::vector<irr::scene::IMeshSceneNode *> &breakable, bool boosted = false)
{
	for (int i = 0; i < ground.size(); i++) {
		if (ground[i]->getTransformedBoundingBox().isPointInside(dot))
			return true;
	}
	for (int i = 0; i < unbreakable.size(); i++) {
		if (unbreakable[i]->getTransformedBoundingBox().isPointInside(dot))
			return true;
	}
	if (boosted)
		return false;
	for (int i = 0; i < breakable.size(); i++) {
		if (breakable[i]->getTransformedBoundingBox().isPointInside(dot))
			return true;
	}
	return false;
}

bool isBusyBis(irr::scene::ISceneNode *dot, const std::vector<irr::scene::IMeshSceneNode *> &ground, const std::vector<irr::scene::IMeshSceneNode *> &unbreakable, const std::vector<irr::scene::IMeshSceneNode *> &breakable, bool boosted = false)
{
	for (int i = 0; i < ground.size(); i++) {
		if (collision(dot, ground[i]))
			return true;
	}
	if (boosted)
		return false;
	for (int i = 0; i < unbreakable.size(); i++) {
		if (collision(dot, unbreakable[i]))
			return true;
	}
	for (int i = 0; i < breakable.size(); i++) {
		if (collision(dot, breakable[i]))
			return true;
	}
	return false;
}

void Player::setAnim(const char *to_set)
{
	if (to_set == "idle" && !_idle) {
		_mesh->setFrameLoop(85, 130);
		_idle = true;
		_walking = false;
		_bomb = false;
	}
	if (to_set == "walking" && !_walking) {
		_mesh->setFrameLoop(0, 40);
		_walking = true;
		_idle = false,
		_bomb = false;
	}
	if (to_set == "bomb" && !_bomb) {
		_mesh->setFrameLoop(40, 60);
		_bomb = true;
		_idle = false;
		_walking = false;
	}
}

void Player::move(const char *dir, Map *map)
{
	float moveSpeed = 1 + _boosts[3] / 2;
	bool isWallHacking = ((_boosts[2] != 0)?true:false);
	if (dir == std::string("up") ) {
		setAnim("walking");
		_pos.Y += moveSpeed;
		if (isBusy(_pos, map->getGround(), map->getUnbreak(), map->getBreak(), isWallHacking)) {
			_pos.Y -= moveSpeed;
		} else {
			_dir.Z = 180;
			_mesh->setPosition(_pos);
			_mesh->setRotation(_dir);
		}
	}
	if (dir == std::string("left") ) {
		setAnim("walking");
		_pos.X -= moveSpeed;
		if (isBusy(_pos, map->getGround(), map->getUnbreak(), map->getBreak(), isWallHacking)) {
			_pos.X += moveSpeed;
		} else {
			_dir.Z = 270;
			_mesh->setPosition(_pos);
			_mesh->setRotation(_dir);
		}
	}
	if (dir == std::string("down") ) {
		setAnim("walking");
		_pos.Y -= moveSpeed;
		if (isBusy(_pos, map->getGround(), map->getUnbreak(), map->getBreak(), isWallHacking)) {
			_pos.Y += moveSpeed;
		} else {
			_dir.Z = 0;
			_mesh->setPosition(_pos);
			_mesh->setRotation(_dir);
		}
	}
	if (dir == std::string("right") ) {
		setAnim("walking");
		_pos.X += moveSpeed;
		if (isBusy(_pos, map->getGround(), map->getUnbreak(), map->getBreak(), isWallHacking)) {
			_pos.X -= moveSpeed;
		} else {
			_dir.Z = 90;
			_mesh->setPosition(_pos);
			_mesh->setRotation(_dir);
		}
	}
	// std::cout << "Player X\t" << from3dTo2d(_pos).X << "\tY\t" << from3dTo2d(_pos).Y << std::endl;
}

bool isOccupied(const irr::core::vector2di &check, Map *map)
{
	for (int i = 0; i < map->getUnbreak().size(); i++) {
		if (map->getUnBreakPos()[i].equals(check))
			return true;
	}
	for (int i = 0; i < map->getBreak().size(); i++) {
		if (map->getBreakPos()[i].equals(check))
			return true;
	}
	return false;
}

bool cellHasPlayer(const irr::core::vector2di &cell, const std::vector<Player *> &p)
{
	for (int i = 0; i < p.size(); i++)
		if (from3dTo2d(p[i]->getPos()).equals(cell))
			return true;
	return false;
}

Bomb *cellHasBomb(const irr::core::vector2di &cell, const std::vector<Bomb *> &b)
{
	for (int i = 0; i < b.size(); i++)
		if (b[i]->getPos().equals(cell))
			return b[i];
	return nullptr;
}

void Player::update(MyEventReceiver *event, Map *map, std::vector<Bomb *> &bombs, const time_t &t, irr::IrrlichtDevice *d, const std::vector<Player *> &p)
{
	if (_AI) {
		std::vector<std::vector<int>> playerMap;
		for (int i = 0; i < 13; i++) {
			playerMap.push_back(std::vector<int>());
			for (int j = 0; j < 11; j++)
				playerMap[i].push_back(0);
			for (int j = 0; j < 11; j++) {
					if (cellHasPlayer(irr::core::vector2di(j, 12 - i), p))
						playerMap[i][j] = 1;
			}
		}
		std::vector<std::vector<int>> bombMap;
		for (int i = 0; i < 13; i++) {
			bombMap.push_back(std::vector<int>());
			for (int j = 0; j < 11; j++)
				bombMap[i].push_back(0);
			for (int j = 0; j < 11; j++) {
					Bomb *tmp = cellHasBomb(irr::core::vector2di(j, 12 - i), bombs);
					if (tmp)
						bombMap[i][j] = (int)tmp->getRadius();
			}
		}
		irr::core::vector2di tmpLol = from3dTo2d(_pos);
		std::vector<std::vector<int>> tmpVec;
		if (_lastAnswer == -1 || std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - _lastAnswerT).count() >= 300000) {
			// std::thread t1(bombermanIA, map->getLevel(), playerMap, bombMap, tmpLol.Y, tmpLol.X);
 			std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
			for (int i = map->getLevel().size() - 1; i >= 0; i--)
				tmpVec.push_back(map->getLevel()[i]);
			_lastAnswer = bombermanIA(tmpVec, playerMap, bombMap, 12 - tmpLol.Y, tmpLol.X);
			tmpVec.clear();
			std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
			// std::cout << "IA took " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us.\n";
			//_lastAnswer = 5;
			_lastAnswerT = std::chrono::steady_clock::now();
		}
		if (_lastAnswer == 0) {
			if (std::time(nullptr) - _lastBomb < 1	||
				_currentBombs >= _boosts[0]			||
				isOccupied(from3dTo2d(_pos),map))
				return ;
			_lastBomb = std::time(nullptr);
			setAnim("bomb");
			bombs.push_back(new Bomb(t, from3dTo2d(_pos), d, _id, _boosts[1]));
			_currentBombs += 1;
		} else if (_lastAnswer == 1) {
			move("up", map);
		} else if (_lastAnswer == 3) {
			move("left", map);
		} else if (_lastAnswer == 2) {
			move("down", map);
		} else if (_lastAnswer == 4) {
			move("right", map);
		} else {
			setAnim("idle");
		}
		// std::cout << "Bot with id " << _id << " is trying to get updated." << std::endl;
	} else {
		if (event->IsKeyDown(_keys[4])) {
			if (std::time(nullptr) - _lastBomb < 1	||
				_currentBombs >= _boosts[0]			||
				isOccupied(from3dTo2d(_pos),map))
				return ;
			_lastBomb = std::time(nullptr);
			setAnim("bomb");
			bombs.push_back(new Bomb(t, from3dTo2d(_pos), d, _id, _boosts[1]));
			_currentBombs += 1;
		} else if (event->IsKeyDown(_keys[0])) {
			move("up", map);
		} else if (event->IsKeyDown(_keys[1])) {
			move("left", map);
		} else if (event->IsKeyDown(_keys[2])) {
			move("down", map);
		} else if (event->IsKeyDown(_keys[3])) {
			move("right", map);
		} else {
			setAnim("idle");
		}
	}
}