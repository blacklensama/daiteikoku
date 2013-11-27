#pragma once

#include "stdafx.h"

struct addInfo//加成
{
	string attr;//属性
	int add;//加成数值
};

struct skill//提督技能
{
	string info;//说明
	string effect;//效果
};

struct shipAttr//提督船只槽位说明
{
	string info;//说明
	vector<addInfo> add;//加成
};

struct Level
{
	int level;
	string headpicture;//立绘
	int	command;//指挥值
	vector<skill> s;//技能
	string picture;//全身CG
	vector<shipAttr> attr;//船只槽位
};

struct captain//提督信息
{
	string country;//国家
	string name;//提督名字
	map<int, Level> level;
};

struct area//地区信息
{
	string picture;//图片
	string country;//国家
	string name;//地区名字
	vector<string> builds;//可以建造的建筑
	int money;//产出
};

struct Attr//舰船属性
{
	Attr();
	int fire;//火力
	int mission;//导弹
	int torperdo;//雷击
	int airDef; //防空
	int locked;//锁敌
	int airAtt;//空袭
	int def;//防御
	int hp;//血量
	int attSS;//反潜
	Attr operator+(const Attr& a);
	Attr operator+(const addInfo& a);
};

struct shipWeaponInfo//船只武装
{
	string info;//武装说明
	vector<addInfo> add;
};

struct ship//舰船
{
	string picture;//图片
	string sci;//需求科技
	string country;//国家
	string name;//名字
	string level;//种类
	string commond;//需求指挥值
	Attr a;//舰船属性
	vector<shipWeaponInfo> sw;//舰船武器
};

struct shipWeapon//船只武器
{
	string picture;//图片
	string sci;//需求科技
	string country;//国家
	string kind;//武装归属
	int cost;//花费
	string name;//名字
	string info;//说明
	vector<addInfo> add;//增加属性
};

struct science//科技
{
	string country;//科技
	string name;//名字
	string picture;//图片
	string clickPicture;//点亮以后的图片
	int cost;//消耗
	vector<science*> nodes;//下节点
	vector<science*> upnodes;//上节点
	bool learned;//是否学习了
	science* sreachByName(string name);
};

class SLG_XML_ReSource
{
public:
	static SLG_XML_ReSource* Instance();
	vector<captain> getCaptainByCountry(string str);
	vector<ship> getShipByCountry(string str);
	vector<shipWeapon> getWeaponByCountry(string str);
	captain getCaptainByName(string str);
	ship getShipByName(string str);
	shipWeapon getWeaponByName(string str);
	science* getScienceByCountry(string name);
	science* getScienceByName(string country, string name);
	science* getScienceByName(science* sc, string name);
	void loadCaptainIndex();
	void loadShipIndex();
	void loadWeaponIndex();
	void loadAreaIndex();
	void loadScienceIndex();
	void loadCaptain(string filepath);
	void loadShip(string filepath);
	void loadWeapon(string filepath);
	void loadScience(string filepath);
	void loadArea(string filepath);
	science* loadScience(science* sc, xml_node node);
	Level loadLevel(xml_node node);
	Attr loadAttr(xml_node node);
	skill loadSkill(xml_node node);
	shipAttr loadShipAttr(xml_node node);
	addInfo loadAddInfo(xml_node node);
	shipWeaponInfo loadShipWeapon(xml_node node);
protected:
	SLG_XML_ReSource();
private:
	static SLG_XML_ReSource* _instance;
	multimap<string, captain> captainGroup;
	multimap<string, ship> shipGroup;
	multimap<string, shipWeapon> weaponGroup;
	multimap<string, area> areaGroup;
	map<string, science*> sciGroup;
};