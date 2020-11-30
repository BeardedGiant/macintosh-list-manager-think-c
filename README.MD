This is a simple example of a list manager for the Macintosh, developed using Think-C.

A simple list manager that adds string entries into a list.
Comes with an example on how to use. It's barebones and simple enough
for you to start expanding it from here.

p.s. who ever decided to use .v(ertical) and .h(orizontal) instead of x/y 
or row, column got me to fill my swearjar over the past few days. I hate you person.

Important to remember if you're having problems:
* Cell is just a 2D Vector (Point).
* Internaly, the list tracks a cell's ID not by row/column but by "position" as a Point/Cell.
* This is what gave me headache's over the past 2-3 days. With a bit of bruteforcing I managed to port the code by Sean J. Crist over to C and understand how to use it!


Feel free to add the missing features as a pull request. Or keep it to yourself. Code is here
in case anyone else is looking for information and doesn't want to chase down emails from
services that are dead.

P.s. none of the Macintosh Think-C books I've read have any examples for a List Manager. if I 
wasn't looking through the Apple #Includes folder, I would have never, even, realized there's a 
control for that.

**Example on how to use it**:
    //The rect that the list will use
	Rect _listRect;
	int i = 0; //counter for how many entries
	
	_listRect.top = 0;
	_listRect.left = 0;
	_listRect.right = 200;
	_listRect.bottom = 300;
	
	_testList = Create_List(GetWindowPointer(), _listRect); //GetWindowPointer() is a function I'm using to
    //retrive the Window I want to attach the list to. Non standard, pass your own window.
	
    //Add 50 entries into the list to make sure it works
	for(i = 0; i < 50; i++)
	{	
		char* _stringID ="ID: ";
		sprintf(_stringID, "%d", i);
		AddRow(_testList, _stringID);
	
	}
    //Add one more.
	AddRow(_testList, "Test");

	//You can declare your own ControlHandle for the scrollBar (in this case _listVScroll) so you can use it to scroll through the list
	_listVScroll = GetVHandle(_testList);

From here on out, it should be easy to extend the code (and fix it up where it's b0rked) and use it in your projects.
