/*
** EPITECH PROJECT, 2020
** Untitled (Workspace)
** File description:
** Game
*/

#include "Game.hpp"

Game::Game(irr::IrrlichtDevice *device, MyEventReceiver *ref)
 :	_irr(device), _timer(0), _event(ref), _map(new Map()), _numberAI(4), _currentLevel(1)
{
	_driver = _irr->getVideoDriver();
	_scene = _irr->getSceneManager();
	_gui = _irr->getGUIEnvironment();
	_font = _gui->getFont("../graphs/fonthaettenschweiler.bmp");
	_gui->getSkin()->setFont(_font);
	_mainCamera = _scene->addCameraSceneNode();
	_mainCamera->setPosition(irr::core::vector3df(100.0f,110.0f,-240.0f));
	_mainCamera->setTarget(irr::core::vector3df(100.0f,110.0f,0.0f));
	_playButton = _gui->addButton(irr::core::recti(10, 10, 110, 60));
	_playButton->setRelativePositionProportional(irr::core::rectf(0.015625, 0.02083, 0.171875, 0.125));
	_playButton->setImage(_driver->getTexture("../graphs/playButton.png"));
	_playButton->setScaleImage(true);
	_exitButton = _gui->addButton(irr::core::recti(10, 70, 110, 120));
	_exitButton->setRelativePositionProportional(irr::core::rectf(0.015625, 0.145833, 0.171875, 0.25));
	_exitButton->setImage(_driver->getTexture("../graphs/exitButton.png"));
	_exitButton->setScaleImage(true);
	_playersButton = _gui->addButton(irr::core::recti(10, 200, 110, 250));
	_playersButton->setRelativePositionProportional(irr::core::rectf(0.015625, 0.41666, 0.171875, 0.52083));
	_playersButton->setImage(_driver->getTexture("../graphs/autoButton.png"));
	_playersButton->setScaleImage(true);
	_timerText = _gui->addStaticText(L"", irr::core::recti(10, 150, 100, 200));
	_timerText->setRelativePositionProportional(irr::core::rectf(0.015625, 0.3125, 0.15625, 0.4166));
	_map->populate(_irr, _currentLevel);
	populatePlayers();
	std::srand(std::time(nullptr));
	_bindings1Pos.push_back(irr::core::rectf(0.86, 0.16, 0.89, 0.21));
	_bindings1Pos.push_back(irr::core::rectf(0.83, 0.21, 0.86, 0.25));
	_bindings1Pos.push_back(irr::core::rectf(0.86, 0.21, 0.89, 0.25));
	_bindings1Pos.push_back(irr::core::rectf(0.89, 0.21, 0.92, 0.25));
	_bindings1Pos.push_back(irr::core::rectf(0.81, 0.1, 0.84, 0.15));
	_bindings2Pos.push_back(irr::core::rectf(0.86, 0.37, 0.89, 0.42));
	_bindings2Pos.push_back(irr::core::rectf(0.83, 0.42, 0.86, 0.46));
	_bindings2Pos.push_back(irr::core::rectf(0.86, 0.42, 0.89, 0.46));
	_bindings2Pos.push_back(irr::core::rectf(0.89, 0.42, 0.92, 0.46));
	_bindings2Pos.push_back(irr::core::rectf(0.81, 0.31, 0.84, 0.35));
	wchar_t DefaultKey[20] = L"z\0q\0s\0d\0a\0o\0k\0l\0m\0i";
	for (int i = 0; i < 5; i++) {
		_player1Bindings.push_back(_gui->addButton(irr::core::recti(0, 0, 0, 0)));
		_player1Bindings[_player1Bindings.size() - 1]->setText(&DefaultKey[i * 2]);
		_player2Bindings.push_back(_gui->addButton(irr::core::recti(0, 0, 0, 0)));
		_player2Bindings[_player2Bindings.size() - 1]->setText(&DefaultKey[i * 2 + 10]);
		// _player1Bindings[_player1Bindings.size() - 1]->setImage(_driver->getTexture("../graphs/lolmdrtki.png"));
		// _player1Bindings[_player1Bindings.size() - 1]->setScaleImage(true);
	}
}

Game::~Game()
{
	cleanBombs();
	cleanPlayers();
	cleanPowerups();
	delete _map;
}

std::wstring getTimeString(time_t _time)
{
	std::wstring res(std::to_wstring((int)(_time/60)) + std::wstring(L":") + std::to_wstring((int)(_time%60)));
	return res;
}

void Game::populatePlayers()
{
	std::vector<std::string> playerMeshes;
	playerMeshes.push_back(std::string("../graphs/BomberBlue.b3d"));
	playerMeshes.push_back(std::string("../graphs/BomberGreen.b3d"));
	playerMeshes.push_back(std::string("../graphs/BomberPink.b3d"));
	playerMeshes.push_back(std::string("../graphs/BomberRed.b3d"));
	std::vector<irr::core::vector3df> playerStarts;
	playerStarts.push_back(irr::core::vector3df(0.0f,0.0f,0.0f));
	playerStarts.push_back(irr::core::vector3df(200.0f,0.0f,0.0f));
	playerStarts.push_back(irr::core::vector3df(0.0f,240.0f,0.0f));
	playerStarts.push_back(irr::core::vector3df(200.0f,240.0f,0.0f));
	cleanPlayers();
	for (int i = 0; i < 4; i++) {
		_players.push_back(new Player(playerStarts[i], (i < 4 - _numberAI) ? false : true, i));
		_players[_players.size()-1]->loadMesh(_irr, playerMeshes[i].c_str(), "");
		// _players[_players.size()-1]->loadMesh(_irr, "../graphs/BomberMan.b3d", playerTextures[i].c_str());
	}
}

void Game::destroyObjects(const irr::core::vector2di &bPos, const char radius)
{
	irr::core::vector2di cursor(0);
	irr::core::vector2di tmpPos(0);
	Player *tmpPlayer = nullptr;
	char tmpRad = 0;
	int d = 0;
	int index = 0;

	cursor.Y = bPos.Y; // SAME LINE CHECKING LEFT AND ON SPOT
	for (cursor.X = (bPos.X); (cursor.X >= 0) && (bPos.X - cursor.X <= radius); cursor.X--) {
		if (_map->getBlock(cursor) == "unbreakable")
			break;
		if (_map->getBlock(cursor) == "breakable") {
			_map->breakBlock(cursor);
			if (std::rand() % 5 == 0)
				_powerUps.push_back(new PowerUp(std::rand()%4,cursor,_irr));
		}
		if (hasPlayer(cursor)) {
			int d = hasPlayerIndex(cursor);
			delete _players[hasPlayerIndex(cursor)];
			_players.erase(_players.begin() + d);
		}
		if (hasBomb(cursor)) {
			index = hasBombIndex(cursor);
			tmpPos = _bombs[index]->getPos();
			tmpRad = _bombs[index]->getRadius();
			tmpPlayer = getPlayerById(_bombs[index]->getPlayerId());
			if (tmpPlayer != nullptr)
				tmpPlayer->bombExploded();
			delete _bombs[index];
			_bombs.erase(_bombs.begin() + index);
			destroyObjects(tmpPos, tmpRad);
		}
	} // SAME LINE CHECKING RIGHT
	for (cursor.X = (bPos.X + 1); (cursor.X <= 10) && (cursor.X - bPos.X <= radius); cursor.X++) {
		if (_map->getBlock(cursor) == "unbreakable")
			break;
		if (_map->getBlock(cursor) == "breakable") {
			_map->breakBlock(cursor);
			if (std::rand() % 5 == 0)
				_powerUps.push_back(new PowerUp(std::rand()%4,cursor,_irr));
		}
		if (hasPlayer(cursor)) {
			int d = hasPlayerIndex(cursor);
			delete _players[hasPlayerIndex(cursor)];
			_players.erase(_players.begin() + d);
		}
		if (hasBomb(cursor)) {
			index = hasBombIndex(cursor);
			tmpPos = _bombs[index]->getPos();
			tmpRad = _bombs[index]->getRadius();
			tmpPlayer = getPlayerById(_bombs[index]->getPlayerId());
			if (tmpPlayer != nullptr)
				tmpPlayer->bombExploded();
			delete _bombs[index];
			_bombs.erase(_bombs.begin() + index);
			destroyObjects(tmpPos, tmpRad);
		}
	}

	cursor.X = bPos.X; // SAME COL CHECKING BOT
	for (cursor.Y = (bPos.Y - 1); (cursor.Y >= 0) && (bPos.Y - cursor.Y <= radius); cursor.Y--) {
		if (_map->getBlock(cursor) == "unbreakable")
			break;
		if (_map->getBlock(cursor) == "breakable") {
			_map->breakBlock(cursor);
			if (std::rand() % 5 == 0)
				_powerUps.push_back(new PowerUp(std::rand()%4,cursor,_irr));
		}
		if (hasPlayer(cursor)) {
			int d = hasPlayerIndex(cursor);
			delete _players[hasPlayerIndex(cursor)];
			_players.erase(_players.begin() + d);
		}
		if (hasBomb(cursor)) {
			index = hasBombIndex(cursor);
			tmpPos = _bombs[index]->getPos();
			tmpRad = _bombs[index]->getRadius();
			tmpPlayer = getPlayerById(_bombs[index]->getPlayerId());
			if (tmpPlayer != nullptr)
				tmpPlayer->bombExploded();
			delete _bombs[index];
			_bombs.erase(_bombs.begin() + index);
			destroyObjects(tmpPos, tmpRad);
		}
	} // SAME COL CHECKING TOP
	for (cursor.Y = (bPos.Y + 1); (cursor.Y <= 12) && (cursor.Y - bPos.Y <= radius); cursor.Y++) {
		if (_map->getBlock(cursor) == "unbreakable")
			break;
		if (_map->getBlock(cursor) == "breakable") {
			_map->breakBlock(cursor);
			if (std::rand() % 5 == 0)
				_powerUps.push_back(new PowerUp(std::rand()%4,cursor,_irr));
		}
		if (hasPlayer(cursor)) {
			int d = hasPlayerIndex(cursor);
			delete _players[hasPlayerIndex(cursor)];
			_players.erase(_players.begin() + d);
		}
		if (hasBomb(cursor)) {
			index = hasBombIndex(cursor);
			tmpPos = _bombs[index]->getPos();
			tmpRad = _bombs[index]->getRadius();
			tmpPlayer = getPlayerById(_bombs[index]->getPlayerId());
			if (tmpPlayer != nullptr)
				tmpPlayer->bombExploded();
			delete _bombs[index];
			_bombs.erase(_bombs.begin() + index);
			destroyObjects(tmpPos, tmpRad);
		}
	}
}


void Game::handleBombs(const time_t &time)
{
	irr::core::vector2di tmpPos(0);
	Player *tmp = nullptr;
	char tmpRad = 0;
	for (int i = 0; i < _bombs.size(); i++) {
		if (_bombs[i]->explodes(time)) {
			tmpPos = _bombs[i]->getPos();
			tmpRad = _bombs[i]->getRadius();
			tmp = getPlayerById(_bombs[i]->getPlayerId());
			if (tmp != nullptr)
				tmp->bombExploded();
			delete _bombs[i];
			_bombs.erase(_bombs.begin() + i);
			destroyObjects(tmpPos, tmpRad);
		}
	}
}

void Game::handlePowerups()
{
	for (int p = 0; p < _players.size(); p++) {
		for (int u = 0; u < _powerUps.size(); u++) {
			if (from3dTo2d(_players[p]->getPos()).equals(_powerUps[u]->getPos())) {
				_players[p]->boostStat(_powerUps[u]->getType());
				delete _powerUps[u];
				_powerUps.erase(_powerUps.begin() + u);
			}
		}
	}
}

void Game::run()
{
	std::vector<std::string> playerButtonsFiles({"../graphs/autoButton.png", "../graphs/soloButton.png", "../graphs/duoButton.png"});
	int currentPlayers = 0;
	time_t startingTime = std::time(nullptr);
	time_t handleBrokenButton = std::time(nullptr);
	time_t handleBrokenButtonBis = std::time(nullptr);
	_timer = startingTime;
	bool waiting = false;
	int Which = 0;
	bool gameDone = false;
	while (_irr->run()) {
		std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
		_playButton->setRelativePositionProportional(irr::core::rectf(0.015625, 0.02083, 0.171875, 0.125));
		_exitButton->setRelativePositionProportional(irr::core::rectf(0.015625, 0.145833, 0.171875, 0.25));
		_playersButton->setRelativePositionProportional(irr::core::rectf(0.015625, 0.41666, 0.171875, 0.5208333));
		_timerText->setRelativePositionProportional(irr::core::rectf(0.015625, 0.3125, 0.15625, 0.4166));
		if (_players.size() == 1) {
			std::cout << "Game has ended !" << std::endl;
			if (_players[0]->isAI()) {
				std::cout << "You lost !\nYou will stay on the same level." << std::endl;
			} else {
				_currentLevel = (_currentLevel % 3) + 1;
				std::cout << "You won !\nYou can go to the level " << _currentLevel << " !" << std::endl;
			}
			gameDone = true;
		}
		if (_exitButton->isPressed())
			break;
		if (gameDone || (_playButton->isPressed() && (std::time(nullptr) - handleBrokenButtonBis) >= 2)) {
			handleBrokenButtonBis = std::time(nullptr);
			_timer = std::time(nullptr);
			_map->populate(_irr, _currentLevel);
			populatePlayers();
			cleanPowerups();
			cleanBombs();
			gameDone = false;
		}
		for (int i = 0; i < _player1Bindings.size(); i++) {
			_player1Bindings[i]->setRelativePositionProportional(_bindings1Pos[i]);
			if (_player1Bindings[i]->isPressed() && !waiting) {
				_player1Bindings[i]->setText(L"...");
				waiting = true;
				Which = i;
			}
		}
		for (int i = 0; i < _player2Bindings.size(); i++) {
			_player2Bindings[i]->setRelativePositionProportional(_bindings2Pos[i]);
			if (_player2Bindings[i]->isPressed() && !waiting) {
				_player2Bindings[i]->setText(L"...");
				waiting = true;
				Which = i + 5;
			}
		}
		if (waiting) {
			if (_event->LastKeyDown() != -1) {
				if (Which >= 5) {
					getPlayerById(1)->SetKey(Which - 5, (EKEY_CODE)_event->LastKeyDown());
					_player2Bindings[Which - 5]->setText(_event->CharLastKeyDown());
					waiting = false;
				} else {
					getPlayerById(0)->SetKey(Which, (EKEY_CODE)_event->LastKeyDown());
					_player1Bindings[Which]->setText(_event->CharLastKeyDown());
					waiting = false;
				}
			}
		}
		if (_playersButton->isPressed() && (std::time(nullptr) - handleBrokenButton) >= 2) {
			handleBrokenButton = std::time(nullptr);
			currentPlayers = (currentPlayers + 1) % 3;
			_playersButton->setImage(_driver->getTexture(playerButtonsFiles[currentPlayers].c_str()));
			_playersButton->setPressedImage(_driver->getTexture(playerButtonsFiles[currentPlayers].c_str()));
			_numberAI = 4 - currentPlayers;
		}
		time_t tmp = std::time(nullptr);
		for (int i = 0; i < _players.size(); i++)
			_players[i]->update(_event, _map, _bombs, tmp, _irr, _players);
		handleBombs(tmp);
		handlePowerups();
		auto diff = std::time(nullptr) - _timer;
		_timerText->setText(getTimeString(diff).c_str());
		_driver->beginScene(true, true, irr::video::SColor(255,255,255,255));
		_scene->drawAll();
		_gui->drawAll();
		_driver->endScene();
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		auto chronoDiff = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
		auto needed = (1000000 / 100) - chronoDiff;
		std::this_thread::sleep_for(std::chrono::microseconds(needed));
	}
	std::cout << "Thanks for playing ! Cleaning up..." << std::endl;
	_irr->drop();
}

void Game::cleanBombs()
{
	for (int i = 0; i < _bombs.size(); i++)
		delete _bombs[i];
	_bombs.clear();
}

void Game::cleanPlayers()
{
	for (int i = 0; i < _players.size(); i++)
		delete _players[i];
	_players.clear();
}


void Game::cleanPowerups()
{
	for (int i = 0; i < _powerUps.size(); i++)
		delete _powerUps[i];
	_powerUps.clear();
}

bool Game::hasPlayer(const irr::core::vector2di &pos)
{
	for (int i = 0; i < _players.size(); i++)
		if (from3dTo2d(_players[i]->getPos()).equals(pos))
			return true;
	return false;
}

int Game::hasPlayerIndex(const irr::core::vector2di &pos)
{
	for (int i = 0; i < _players.size(); i++)
		if (from3dTo2d(_players[i]->getPos()).equals(pos))
			return i;
	return -1;
}

bool Game::hasBomb(const irr::core::vector2di &pos)
{
	for (int i = 0; i < _bombs.size(); i++)
		if (_bombs[i]->getPos().equals(pos))
			return true;
	return false;
}

int Game::hasBombIndex(const irr::core::vector2di &pos)
{
	for (int i = 0; i < _bombs.size(); i++)
		if (_bombs[i]->getPos().equals(pos))
			return i;
	return -1;
}

Player *Game::getPlayerById(int id)
{
	for (int i = 0; i < _players.size(); i++)
		if (_players[i]->getId() == id)
			return _players[i];
	return nullptr;
}