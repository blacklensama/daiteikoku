#pragma once
#include "stdafx.h"
#include "gameInfo.h"

class gameShip;
class gameWeapon;
class gameCaptain;
class gameCountry;
class gameArea;
class gameScience;

class gameWeapon
{
public:
	gameWeapon(shipWeapon t);
	void setShip(gameShip* t);
	vector<addInfo> getAddInfo();
protected:
private:
	shipWeapon sw;
	gameShip* s;
};

class gameShip
{
public:
	gameShip(ship t);
	void setCaptain(gameCaptain* t);
	void addShipWeapon(gameWeapon* t);
	void removeShipWeapon(gameWeapon* t);
	Attr getAttr();
protected:
private:
	ship s;
	vector<gameWeapon*> sw;
	gameCaptain* sc;
};

class gameCaptain
{
public:
	gameCaptain(captain t);
	void addShip(gameShip* t);
	void removeShip(gameShip* t);
	void setLevel(int l);
	int getLevel();
	Attr getAttr();
	void setArea(gameArea* t);
protected:
private:
	captain c;
	int level;
	vector<gameShip*> gs;
	gameArea* ga;
};

class gameArea
{
public:
	gameArea(area t);
	void addCaptain(gameCaptain* s);
	void setBuilding(string str);
	void setCountry(gameCountry* s);
	int getMoney();
	string getName();
protected:
private:
	vector<gameCaptain*> gc;
	area a;
	string building;
	gameCountry* c;
};

class gameScience
{
public:
	gameScience(string str);
	bool checkScience(string str);
	void setScience(string str, bool b);
protected:
private:
	science* s;
};

class gameCountry
{
public:
	void addArea(gameArea* t);
	void removeArea(gameArea* t);
	void removeArea(string name);
	void addLibNum();
	void removeLibNum();
	gameArea* findArea(string name);
protected:
private:
	vector<gameArea*> ga;
	int LibNum;
	int money;
};