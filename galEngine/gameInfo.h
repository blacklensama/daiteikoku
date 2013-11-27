#pragma once

#include "stdafx.h"

struct addInfo//�ӳ�
{
	string attr;//����
	int add;//�ӳ���ֵ
};

struct skill//�ᶽ����
{
	string info;//˵��
	string effect;//Ч��
};

struct shipAttr//�ᶽ��ֻ��λ˵��
{
	string info;//˵��
	vector<addInfo> add;//�ӳ�
};

struct Level
{
	int level;
	string headpicture;//����
	int	command;//ָ��ֵ
	vector<skill> s;//����
	string picture;//ȫ��CG
	vector<shipAttr> attr;//��ֻ��λ
};

struct captain//�ᶽ��Ϣ
{
	string country;//����
	string name;//�ᶽ����
	map<int, Level> level;
};

struct area//������Ϣ
{
	string picture;//ͼƬ
	string country;//����
	string name;//��������
	vector<string> builds;//���Խ���Ľ���
	int money;//����
};

struct Attr//��������
{
	Attr();
	int fire;//����
	int mission;//����
	int torperdo;//�׻�
	int airDef; //����
	int locked;//����
	int airAtt;//��Ϯ
	int def;//����
	int hp;//Ѫ��
	int attSS;//��Ǳ
	Attr operator+(const Attr& a);
	Attr operator+(const addInfo& a);
};

struct shipWeaponInfo//��ֻ��װ
{
	string info;//��װ˵��
	vector<addInfo> add;
};

struct ship//����
{
	string picture;//ͼƬ
	string sci;//����Ƽ�
	string country;//����
	string name;//����
	string level;//����
	string commond;//����ָ��ֵ
	Attr a;//��������
	vector<shipWeaponInfo> sw;//��������
};

struct shipWeapon//��ֻ����
{
	string picture;//ͼƬ
	string sci;//����Ƽ�
	string country;//����
	string kind;//��װ����
	int cost;//����
	string name;//����
	string info;//˵��
	vector<addInfo> add;//��������
};

struct science//�Ƽ�
{
	string country;//�Ƽ�
	string name;//����
	string picture;//ͼƬ
	string clickPicture;//�����Ժ��ͼƬ
	int cost;//����
	vector<science*> nodes;//�½ڵ�
	vector<science*> upnodes;//�Ͻڵ�
	bool learned;//�Ƿ�ѧϰ��
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