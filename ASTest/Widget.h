#include "behavior_tree.h"
#include "Image.h"

class Widget
{
public:
	Widget();
	void update();
	void draw();
	void draw(Point p);
	void draw(Point p, float c);
	void draw(float c);
protected:
	Image i;
	BehaviorTreeObject btree;
private:
};