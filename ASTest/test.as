void test()
{
	Widget w;
	w.test();
	int i = 10;
	Print(i);
	BlackBoard a;
	Print(a.getListLength());
	systemEvent@ s = a.getSystemEventByIndex(kTrig_LeftClickUp);
	if (s is null )
	{
		Print("NULL");
	}
}

void test1(Widget@ i)
{
	Print(11);
}