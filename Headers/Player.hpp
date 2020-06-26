/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_
#include <irrlicht.h>
#include <iostream>
#include <vector>
#include "Command.hpp"
#include "Bomb.hpp"
#include "Map.hpp"
#include <thread>

class Player {
	public:
		Player(const irr::core::vector3df &pos, bool AI, int id);
		~Player();

		void update(MyEventReceiver *event, Map *, std::vector<Bomb *> &, const time_t &, irr::IrrlichtDevice *, const std::vector<Player *> &);
		void loadMesh(irr::IrrlichtDevice *,const char *,const char *);
		irr::core::vector3df getPos();
		int getId();
		void boostStat(char type);
		void bombExploded();
		void SetKey(int , EKEY_CODE);
		bool isAI();
	private:
		irr::scene::IAnimatedMeshSceneNode *_mesh;
		irr::core::vector3df _pos;
		char _boosts[4];
		irr::EKEY_CODE _keys[5];
		irr::core::vector3df _dir;
		bool _AI;
		int _id;
		bool _idle;
		bool _walking;
		bool _bomb;
		time_t _lastBomb;
		int _lastAnswer;
		std::chrono::steady_clock::time_point _lastAnswerT;
		char _currentBombs;

		void setAnim(const char *);
		void move(const char *, Map *);
};

int bombermanIA(std::vector<std::vector<int>> map, std::vector<std::vector<int>> players, std::vector<std::vector<int>> map_bomb, int x, int y);

#endif /* !PLAYER_HPP_ */
