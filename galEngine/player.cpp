#include "player.h"

gameWeapon::gameWeapon(shipWeapon t)
{
	sw = t;
	s = NULL;
}

void gameWeapon::setShip(gameShip* t)
{
	s = t;
}

vector<addInfo> gameWeapon::getAddInfo()
{
	return sw.add;
}

gameShip::gameShip(ship t)
{
	s = t;
	sc = NULL;
}

void gameShip::addShipWeapon(gameWeapon* t)
{
	sw.push_back(t);
}

void gameShip::removeShipWeapon(gameWeapon* t)
{
	remove(sw.begin(), sw.end(), t);
}

void gameShip::setCaptain(gameCaptain* t)
{
	sc = t;
}

Attr gameShip::getAttr()
{
	Attr a;
	a = s.a;
	for (auto i:s.sw)
	{
		for (auto j:i.add)
		{
			a = a + j;
		}
	}
	return a;
}

gameCaptain::gameCaptain(captain t)
{
	c = t;
	ga = NULL;
	level = 1;
}

void gameCaptain::addShip(gameShip* t)
{
	gs.push_back(t);
}

void gameCaptain::removeShip(gameShip* t)
{
	remove(gs.begin(), gs.end(), t);
}

void gameCaptain::setLevel(int l)
{
	level = l;
}

int gameCaptain::getLevel()
{
	return level;
}

Attr gameCaptain::getAttr()
{
	Attr a;
	for (auto i:gs)
	{
		a = a + i->getAttr();
	}
	return a;
}

void gameCaptain::setArea(gameArea* t)
{
	ga = t;
}

gameArea::gameArea(area t)
{
	a = t;
	c = NULL;
}

void gameArea::addCaptain(gameCaptain* s)
{
	gc.push_back(s);
}

void gameArea::setCountry(gameCountry* s)
{
	c = s;
}

void gameArea::setBuilding(string str)
{
	building = str;
}

int gameArea::getMoney()
{
	return a.money;
}

string gameArea::getName()
{
	return a.name;
}

void gameCountry::addArea(gameArea* t)
{
	ga.push_back(t);
}

void gameCountry::addLibNum()
{
	LibNum++;
}

void gameCountry::removeLibNum()
{
	LibNum--;
}

void gameCountry::removeArea(gameArea* t)
{
	remove(ga.begin(), ga.end(), t);
}

gameArea* gameCountry::findArea(string name)
{
	for (auto i: ga)
	{
		if (i->getName() == name)
		{
			return i;
		}
	}
	return NULL;
}

void gameCountry::removeArea(string name)
{
	remove(ga.begin(), ga.end(), findArea(name));
}

bool gameScience::checkScience(string str)
{
	return s->sreachByName(str)->learned;
}

void gameScience::setScience(string str, bool b)
{
	s->sreachByName(str)->learned = b;
}

gameScience::gameScience(string str)
{
	SLG_XML_ReSource* t = SLG_XML_ReSource::Instance();
	s = t->getScienceByCountry(str);
}

science* gameScience::getScience()
{
	return s;
}

GamePlayer* GamePlayer::_instance = NULL;

GamePlayer* GamePlayer::Instance()
{
	if (_instance == NULL)
	{
		_instance = new GamePlayer();
	}
	return _instance;
}

gameScience* GamePlayer::getGameScience()
{
	return _gsc;
}

gameCountry* GamePlayer::getGameCountry(string str)
{
	return _gcm[str];
}

GamePlayer::GamePlayer()
{

}