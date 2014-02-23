#include "Widget.h"

Widget::Widget()
{
	refCount = 1;
}

Widget::Widget(Image i)
{
	refCount = 1;
	_image = i;
}

Widget::Widget(xml_node node):_image(node)
{
	refCount = 1;
}

void Widget::draw()
{
	DrawMode::DrawImage(&_image);
}

void Widget::draw(float c)
{
	DrawMode::DrawImage(&_image, c);
}

void Widget::draw(Point p)
{
	DrawMode::DrawImage(&_image, p);
}

void Widget::draw(Point p, float c)
{
	DrawMode::DrawImage(&_image, p, c);
}

int Widget::isInUI(Point p)
{
	return p.IsInRange(_image.getPoint(), _image.getPoint()+_image.getImageInfo());
}

int Widget::isInUI(float x, float y)
{
	return isInUI(Point(x,y));
}

void Widget::Addref()
{
	refCount++;
}

void Widget::Release()
{
	if (--refCount == 0)
	{
		delete this;
	}
}

void Widget::test()
{
	cout << "this is Widget test" << endl;
}

Widget* Widget_Factory()
{
	return new Widget();
}

WidgetInfo::WidgetInfo()
{
}

WidgetInfo::WidgetInfo(Widget w, string path)
{
	_w = w;
	_btree.reload(path);
}

WidgetInfo::WidgetInfo(xml_node& nodes, WidgetInfo* parent):
	_w(nodes),_btree(nodes.attribute("behaviour").as_string()),_parent(parent)
{
	auto i = nodes.children();
	for (auto node : nodes)
	{
		_nextNode.push_back(new WidgetInfo(node, this));
	}
}

WidgetInfo::WidgetInfo(string path)
{
	xml_document doc;
	doc.load_file(path.c_str());assert(doc);
	xml_node node = doc.root().first_child().first_child();
	_w = Widget(node);
	_btree.reload(node.attribute("behaviour").as_string());
	_parent = NULL;
}

void WidgetInfo::tick()
{
	_btree.Update(&_w);
	for (auto i : _nextNode)
	{
		i->tick();
	}
}

WidgetInfo::~WidgetInfo()
{
	for (auto i : _nextNode)
	{
		delete i;
	}
	_nextNode.swap(vector<WidgetInfo*>());
}

WidgetMgr* WidgetMgr::_instance = NULL;

WidgetMgr* WidgetMgr::Instance()
{
	if (_instance == NULL)
	{
		_instance = new WidgetMgr();
	}
	return _instance;
}

void WidgetMgr::Release()
{
	delete _instance;
}

WidgetMgr::WidgetMgr()
{

}

void WidgetMgr::tick()
{
	for (auto i:_mgr)
	{
		i->tick();
	}
}

void WidgetMgr::addWidget(WidgetInfo* info)
{
	_mgr.push_back(info);
}

void WidgetMgr::clearAll()
{
	for (auto i : _mgr)
	{
		delete i;
	}
	_mgr.swap(vector<WidgetInfo*>());
}

void WidgetMgr::loadFromXml(string path)
{
	xml_document doc;
	doc.load_file(path.c_str());
	xml_node root = doc.first_child();
	for (xml_node node : root.children())
	{
		_mgr.push_back(new WidgetInfo(node, NULL));
	}
}

void WidgetMgr::reloadXml(string path)
{
	clearAll();
	loadFromXml(path);
}

WidgetMgr::~WidgetMgr()
{
	clearAll();
}