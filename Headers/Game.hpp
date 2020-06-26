/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_
#include "Map.hpp"
#include "Player.hpp"
#include "Bomb.hpp"
#include "PowerUp.hpp"
class Game {
	public:
		Game(irr::IrrlichtDevice *device, MyEventReceiver *);
		~Game();

		void populatePlayers();
		void run();
	private:
		irr::IrrlichtDevice *_irr;
		irr::video::IVideoDriver *_driver;
		irr::scene::ISceneManager *_scene;
		irr::gui::IGUIEnvironment *_gui;
		irr::scene::ICameraSceneNode *_mainCamera;
		irr::gui::IGUIButton *_playButton;
		irr::gui::IGUIButton *_playersButton;
		irr::gui::IGUIButton *_exitButton;
		irr::gui::IGUIButton *_exitButton2;
		std::vector<irr::gui::IGUIButton *> _player1Bindings;
		std::vector<irr::core::rectf> _bindings1Pos;
		std::vector<irr::gui::IGUIButton *> _player2Bindings;
		std::vector<irr::core::rectf> _bindings2Pos;
		// irr::scene::ITextSceneNode *_timerNode;
		irr::gui::IGUIStaticText *_timerText;
		MyEventReceiver *_event;
		irr::gui::IGUIFont *_font;

		time_t _timer;
		Map *_map;
		std::vector<Player *> _players;
		std::vector<Bomb *> _bombs;
		std::vector<PowerUp *> _powerUps;
		int _numberAI;
		int _currentLevel;

		Player *getPlayerById(int);
		bool hasPlayer(const irr::core::vector2di &);
		int hasPlayerIndex(const irr::core::vector2di &);
		bool hasBomb(const irr::core::vector2di &);
		int hasBombIndex(const irr::core::vector2di &);
		void destroyObjects(const irr::core::vector2di &, const char);
		void handleBombs(const time_t &);
		void handlePowerups();
		void cleanBombs();
		void cleanPlayers();
		void cleanPowerups();
};

#endif /* !GAME_HPP_ */
