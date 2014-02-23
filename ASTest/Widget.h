#include "behavior_tree.h"
#include "Image.h"

class Widget
{
public:
	Widget();
	Widget(Image i);
	Widget(xml_node node);
	void draw();
	void draw(Point p);
	void draw(Point p, float c);
	void draw(float c);
	int isInUI(Point p);
	int isInUI(float x, float y);
	void Addref();
	void Release();
	void test();
protected:
	Image _image;
	int refCount;
private:
};

Widget* Widget_Factory();

//这个xml需要的格式为<newObj><Item bitmap="xxx.xxx" x="1" y="2" behaviour="xxx.xml"\>
class WidgetInfo
{
public:
	WidgetInfo();
	WidgetInfo(Widget w, string path);
	WidgetInfo(xml_node& node, WidgetInfo* parent = NULL);
	WidgetInfo(string path);
	void tick();
	~WidgetInfo();
protected:
private:
	Widget _w;
	BehaviorTreeObject _btree;
	WidgetInfo* _parent;
	vector<WidgetInfo*> _nextNode;
};

class WidgetMgr
{
public:
	static WidgetMgr* Instance();
	void tick();
	void loadFromXml(string path);
	void addWidget(WidgetInfo* info);
	void clearAll();
	void reloadXml(string path);
	static void Release();
protected:
	WidgetMgr();
	~WidgetMgr();
private:
	static WidgetMgr* _instance;
	vector<WidgetInfo*> _mgr;
};
