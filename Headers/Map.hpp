/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Map
*/

#ifndef MAP_HPP_
#define MAP_HPP_
#include "irrlicht.h"
#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <ostream>
#include <chrono>
#include <ctime>
#include <algorithm>

class Map {
  public:
    Map(int level = 1);
    ~Map();


	void populate(irr::IrrlichtDevice *device, int level = 1);

    std::vector<std::vector<int>> getLevel();
	const std::vector<irr::scene::IMeshSceneNode *> &getGround();
	const std::vector<irr::scene::IMeshSceneNode *> &getUnbreak();
	const std::vector<irr::scene::IMeshSceneNode *> &getBreak();
	const std::vector<irr::core::vector2di> &getBreakPos();
	const std::vector<irr::core::vector2di> &getUnBreakPos();

	void breakBlock(const irr::core::vector2di &);
	std::string getBlock(const irr::core::vector2di &);
	int getBlockIndex(const irr::core::vector2di &);
  private:
    std::vector<std::vector<int>> _level;
	std::vector<irr::scene::IMeshSceneNode *> _groundBlocks;
	std::vector<irr::scene::IMeshSceneNode *> _unbreakableBlocks;
	std::vector<irr::scene::IMeshSceneNode *> _breakableBlocks;
	std::vector<irr::core::vector2di> _breakablePos;
	std::vector<irr::core::vector2di> _unbreakablePos;
	bool _populated;
	int _wishedLevel;
    void generateLevel(int);
    int check_corner(int, int);
    void base_map(int);
	void clean();
};

#endif /* !MAP_HPP_ */
