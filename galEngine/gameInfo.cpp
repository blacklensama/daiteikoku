#include "gameInfo.h"

science* science::sreachByName(string str)
{
	vector<science*> temp;
	temp.insert(temp.end(), nodes.begin(), nodes.end());
	for (auto i = temp.begin(); i != temp.end(); i++)
	{
		if ((*i)->name == str)
		{
			return *i;
		}
		temp.insert(temp.end(), (*i)->nodes.begin(), (*i)->nodes.end());
	}
	return NULL;
}

SLG_XML_ReSource* SLG_XML_ReSource::_instance = NULL;

SLG_XML_ReSource* SLG_XML_ReSource::Instance()
{
	if (_instance == NULL)
	{
		_instance = new SLG_XML_ReSource();
	}
	return _instance;
}

ship SLG_XML_ReSource::getShipByName(string name)
{
	for (auto i = shipGroup.begin(); i != shipGroup.end(); i++)
	{
		if (i->second.name == name)
		{
			return i->second;
		}
	}
}

vector<ship> SLG_XML_ReSource::getShipByCountry(string str)
{
	vector<ship> group;
	auto lower = shipGroup.lower_bound(str);
	auto upper = shipGroup.upper_bound(str);
	for (auto i = lower; i != upper; i++)
	{
		group.push_back(i->second);
	}
	return group;
}

captain SLG_XML_ReSource::getCaptainByName(string str)
{
	for (auto i = captainGroup.begin(); i != captainGroup.end(); i++)
	{
		if (i->second.name == str)
		{
			return i->second;
		}
	}
}

vector<captain> SLG_XML_ReSource::getCaptainByCountry(string str)
{
	vector<captain> group;
	auto lower = captainGroup.lower_bound(str);
	auto upper = captainGroup.upper_bound(str);
	for (auto i = lower; i != upper; i++)
	{
		group.push_back(i->second);
	}
	return group;
}

shipWeapon SLG_XML_ReSource::getWeaponByName(string str)
{
	for (auto i = weaponGroup.begin(); i != weaponGroup.end(); i++)
	{
		if (i->second.name == str)
		{
			return i->second;
		}
	}
}

vector<shipWeapon> SLG_XML_ReSource::getWeaponByCountry(string str)
{
	vector<shipWeapon> group;
	auto lower = weaponGroup.lower_bound(str);
	auto upper = weaponGroup.upper_bound(str);
	for (auto i = lower; i != upper; i++)
	{
		group.push_back(i->second);
	}
	return group;
}

SLG_XML_ReSource::SLG_XML_ReSource()
{
	loadShipIndex();
	loadCaptainIndex();
	loadAreaIndex();
	loadWeaponIndex();
	loadScienceIndex();
}

science* SLG_XML_ReSource::getScienceByCountry(string name)
{
	return sciGroup[name];
}

science* SLG_XML_ReSource::getScienceByName(science* sc, string name)
{
	return sc->sreachByName(name);
}

science* SLG_XML_ReSource::getScienceByName(string country, string name)
{
	return sciGroup[name]->sreachByName(name);
}

void SLG_XML_ReSource::loadShip(string filepath)
{
	xml_document doc;
	if (!doc.load_file(filepath.c_str()))
	{
		cout << "can't load the xml:" << filepath << endl;
	}
	xpath_node_set nodes = doc.select_nodes("//ship");
	for (auto i = nodes.begin(); i != nodes.end(); i++)
	{
		ship s;
		s.country = i->node().attribute("country").as_string();
		s.level = i->node().attribute("level").as_string();
		s.name = i->node().attribute("name").as_string();
		s.sci = i->node().attribute("science").as_string();
		s.commond = i->node().attribute("commond").as_int();
		auto att = i->node().select_nodes("descendant::att");
		s.a = loadAttr(att[0].node());
		auto wp = i->node().select_nodes("descendant::weapon");
		for (auto j:wp)
		{
			s.sw.push_back(loadShipWeapon(j.node()));
		}
		shipGroup.insert(make_pair(s.country, s));
	}
}

science* SLG_XML_ReSource::loadScience(science* sc, xml_node node)
{
	science* s = new science();
	sc->learned = false;
	s->picture = node.attribute("picture").as_string();
	s->clickPicture = node.attribute("clickPicture").as_string();
	s->upnodes.push_back(sc);
	s->country = node.attribute("country").as_string();
	s->name = node.attribute("name").as_string();
	s->cost = node.attribute("cost").as_int();
	s->x = node.attribute("x").as_float();
	s->y = node.attribute("y").as_float();
	auto n = node.select_nodes("child::science");//生成下面的节点
	for (auto i : n)
	{
		s->nodes.push_back(loadScience(sc, i.node()));
	}
	sciGroup.insert(make_pair(sc->country, sc));
	return s;
}

void SLG_XML_ReSource::loadScience(string filepath)
{
	xml_document doc;
	if (!doc.load_file(filepath.c_str()))
	{
		cout << "can't load the xml:" <<filepath << endl;
	}
	xpath_node_set nodes = doc.select_nodes("/newObj/science");
	for (auto i : nodes)
	{
		science* sc = new science();
		sc->learned = false;
		sc->picture = i.node().attribute("picture").as_string();
		sc->clickPicture = i.node().attribute("clickPicture").as_string();
		sc->country = i.node().attribute("country").as_string();
		sc->cost = i.node().attribute("cost").as_int();
		sc->name = i.node().attribute("name").as_string();
		sc->x = i.node().attribute("x").as_float();
		sc->y = i.node().attribute("y").as_float();
		auto node = i.node().select_nodes("child::science");
		//生成自己的节点
		for (auto j : node)
		{
			sc->nodes.push_back(loadScience(sc, j.node()));
		}
		sciGroup.insert(make_pair(sc->country, sc));
	}
}

void SLG_XML_ReSource::loadArea(string filepath)
{
	xml_document doc;
	if (!doc.load_file(filepath.c_str()))
	{
		cout << "can't load the xml:" << filepath << endl;
	}
	xpath_node_set nodes = doc.select_nodes("//area");
	for (auto i : nodes)
	{
		area a;
		a.picture = i.node().attribute("country").as_string();
		a.money = i.node().attribute("money").as_int();
		a.name = i.node().attribute("name").as_string();
		a.country = i.node().attribute("country").as_string();
		auto node = i.node().select_nodes("descendant::building");
		//生成可建造列表
		for (auto j:node)
		{
			a.builds.push_back(j.node().attribute("building").as_string());
		}
		areaGroup.insert(make_pair(a.country, a));
	}
}

void SLG_XML_ReSource::loadWeapon(string filepath)
{
	xml_document doc;
	if (!doc.load_file(filepath.c_str()))
	{
		cout << "can't load the xml:" << filepath << endl;
	}
	xpath_node_set nodes = doc.select_nodes("/newObj/weapon");
	for (auto i = nodes.begin(); i != nodes.end(); i++)
	{
		shipWeapon sw;
		sw.picture = i->node().attribute("picture").as_string();
		sw.sci = i->node().attribute("science").as_string();
		sw.name = i->node().attribute("name").as_string();
		sw.country = i->node().attribute("country").as_string();
		sw.info = i->node().attribute("info").as_string();
		sw.cost = i->node().attribute("cost").as_int();
		sw.kind = i->node().attribute("kind").as_string();
		auto addInfo = i->node().select_nodes("descendant::addInfo");
		for (auto j:addInfo)
		{
			sw.add.push_back(loadAddInfo(j.node()));
		}
		weaponGroup.insert(make_pair(sw.country, sw));
	}
}

void SLG_XML_ReSource::loadCaptain(string filepath)
{
	xml_document doc;
	if(!doc.load_file(filepath.c_str()))
	{
		cout << "can't load the xml" << endl;
	}
	xpath_node_set nodes = doc.select_nodes("//captain");
	for (auto i = nodes.begin(); i != nodes.end(); i++)
	{
		captain c;
		c.name = i->node().attribute("name").as_string();
		c.country = i->node().attribute("country").as_string();
		auto levelNode = i->node().select_nodes("descendant::level");
		for (auto j:levelNode)
		{
			Level l = loadLevel(j.node());
			c.level.insert(make_pair(l.level, l));
		}
		captainGroup.insert(make_pair(c.country, c));
	}
}

shipWeaponInfo SLG_XML_ReSource::loadShipWeapon(xml_node node)
{
	shipWeaponInfo swi;
	swi.info = node.attribute("info").as_string();
	auto nodes = node.select_nodes("descendant::addInfo");
	for (auto i:nodes)
	{
		swi.add.push_back(loadAddInfo(i.node()));
	}
	return swi;
}

Level SLG_XML_ReSource::loadLevel(xml_node node)
{
	Level l;
	l.level = node.attribute("level").as_int();
	l.picture = node.attribute("picture").as_string();
	l.headpicture = node.attribute("headpicture").as_string();
	l.command = node.attribute("command").as_int();
	auto skillnode = node.select_nodes("descendant::skill");
	for (auto j:skillnode)
	{
		l.s.push_back(loadSkill(j.node()));
	}
	auto shipAttr = node.select_nodes("descendant::shipAttr");
	for (auto j:shipAttr)
	{
		l.attr.push_back(loadShipAttr(j.node()));
	}
	return l;
}

Attr SLG_XML_ReSource::loadAttr(xml_node node)
{
	Attr a;
	a.airAtt = node.attribute("airAtt").as_int();
	a.airDef = node.attribute("airDef").as_int();
	a.attSS = node.attribute("attSS").as_int();
	a.def = node.attribute("def").as_int();
	a.fire = node.attribute("fire").as_int();
	a.hp = node.attribute("hp").as_int();
	a.locked = node.attribute("locked").as_int();
	a.mission = node.attribute("mission").as_int();
	a.torperdo = node.attribute("torperdo").as_int();
	return a;
}

skill SLG_XML_ReSource::loadSkill(xml_node node)
{
	skill s;
	s.effect = node.attribute("effect").as_string();
	s.info = node.attribute("info").as_string();
	return s;
}

addInfo SLG_XML_ReSource::loadAddInfo(xml_node node)
{
	addInfo ai;
	ai.attr = node.attribute("attr").as_string();
	ai.add = node.attribute("add").as_int();
	return ai;
}

shipAttr SLG_XML_ReSource::loadShipAttr(xml_node node)
{
	shipAttr sa;
	sa.info = node.attribute("info").as_string();
	auto nodes = node.select_nodes("descendant::addInfo");
	for (auto i:nodes)
	{
		sa.add.push_back(loadAddInfo(i.node()));
	}
	return sa;
}

void SLG_XML_ReSource::loadAreaIndex()
{
	string str;
	ifstream infile;
	infile.open("area/areaIndex.txt");
	while (getline(infile, str))
	{
		loadArea(str);
	}
}

void SLG_XML_ReSource::loadCaptainIndex()
{
	string str;
	ifstream infile;
	infile.open("captain/captainIndex.txt");
	while (getline(infile, str))
	{
		loadCaptain(str);
	}
}

void SLG_XML_ReSource::loadShipIndex()
{
	string str;
	ifstream infile;
	infile.open("ship/shipIndex.txt");
	while (getline(infile, str))
	{
		loadShip(str);
	}
}

void SLG_XML_ReSource::loadWeaponIndex()
{
	string str;
	ifstream infile;
	infile.open("weapon/weaponIndex.txt");
	while (getline(infile, str))
	{
		loadWeapon(str);
	}
}

void SLG_XML_ReSource::loadScienceIndex()
{
	string str;
	ifstream infile;
	infile.open("science/scienceIndex.txt");
	while (getline(infile, str))
	{
		loadScience(str);
	}
}

Attr::Attr()
{
	airAtt = airDef = attSS = def = fire = hp = locked = mission = torperdo = 0;
}

Attr Attr::operator+(const Attr& a)
{
	Attr b;
	b.airAtt = a.airAtt + airAtt;
	b.airDef = a.airDef + airDef;
	b.attSS = a.attSS + attSS;
	b.def = a.def + def;
	b.fire = a.fire + fire;
	b.hp = a.hp + hp;
	b.locked = a.locked + locked;
	b.mission = a.mission + mission;
	b.torperdo = a.torperdo + torperdo;
	return b;
}

Attr Attr::operator+(const addInfo& a)
{
	Attr b = *this;
	if (a.attr == "airAtt")
	{
		b.airAtt*=a.add;
	}else if (a.attr == "airDef")
	{
		b.airDef*=a.add;
	}else if (a.attr == "attSS")
	{
		b.attSS*=a.add;
	}else if (a.attr == "def")
	{
		b.def*=a.add;
	}else if (a.attr == "fire")
	{
		b.fire*=a.add;
	}else if (a.attr == "hp")
	{
		b.hp*=a.add;
	}else if (a.attr == "locked")
	{
		b.locked*=a.add;
	}else if (a.attr == "mission")
	{
		b.mission*=a.add;
	}else if (a.attr == "torperdo")
	{
		b.torperdo*=a.add;
	}
	return b;
}