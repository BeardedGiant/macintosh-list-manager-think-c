#include "Lists.h"
#include "list.h"
#include <Types.h>
#include <string.h>

// Based on the work of Sean J. Crist (kurisuto).
// url: umich.edu/~archive/mac/development/source/simplelistmanager.txt

#define StandardList 0


short rowNum = 0;

ListHandle Create_List(WindowPtr _win, Rect _rect)
{
	ListHandle _list;
	Rect ViewRect;
	Rect DataBounds;
	short TempInteger; //just do a little math
	Point CellSize;
	Cell CellPoint;
	
	//Inset the box to make room for the scroll bar. Also inset it so we've got room for a border
	ViewRect = _rect;
	InsetRect(&ViewRect, 1, 1);
	ViewRect.right -= 15;
	

	CellSize.v = 15;
	CellSize.h = 50;
	
	
	
	//Now adjust the ViewRect to avoid cutting off the last visible cell
	TempInteger = (ViewRect.bottom-ViewRect.top) % CellSize.v;
	ViewRect.bottom = ViewRect.top + (TempInteger * CellSize.v);
	
	
	//Create the new List
	SetRect(&DataBounds, 0, 0, 1, 0);
	
	InsetRect(&ViewRect, -1, -1);
	FrameRect(&ViewRect);
	
	_list = LNew(&ViewRect, &DataBounds, CellSize, StandardList, GetWindowPointer(), TRUE, FALSE, FALSE, TRUE);
	
	UpdateList(_list);

	
	/*CellPoint.h = 0;
	CellPoint.v = 0;
	LAddRow(1, 0, _list);
	LSetCell("Testing 1", 9, CellPoint, _list);
	LDraw(CellPoint, _list);*/
	
	return _list;

}


//update the display of the list
void UpdateList(ListHandle _list)
{
	Rect ViewRect;
	RgnHandle ListUpdateRgn;
	
	SetPort( (**_list).port);
	
	//Get the list manager to update the list
	ViewRect = (**_list).rView;
	LDoDraw(TRUE, _list);
	ListUpdateRgn = NewRgn( );
	RectRgn(ListUpdateRgn, &ViewRect);
	LUpdate(ListUpdateRgn, _list);
	
	//Draw the border
	InsetRect(&ViewRect, -1, -1);
	FrameRect(&ViewRect);
	
	//Clean up after ourselves
	DisposeRgn(ListUpdateRgn);
}

short DoClick(ListHandle _list, Point _where)
{
	short result = 0;
	SetPort((**_list).port);
	LDoDraw(TRUE, _list);
	
	if(LClick(_where, 0, _list))
	{
		result = 1;
	}
	
	return result;	
}

void TurnOffSelection(ListHandle _list)
{
	Point ResultPoint;
	
	SetPt(&ResultPoint, 0, 0);
	if(LGetSelect(TRUE, &ResultPoint, _list))
	{
		LSetSelect(FALSE, ResultPoint, _list);	
	}
}

char* ListSelection(ListHandle _list)
{
	Point ResultPoint;
	char* ResultString;
	Ptr StringPointer;
	short StringLength;
	
	
	SetPt(&ResultPoint, 0, 0);
	if(LGetSelect(TRUE, &ResultPoint, _list))
	{	
		StringPointer = (Ptr)(*ResultString);
		StringLength = 255;
		LGetCell(&StringPointer, &StringLength, ResultPoint, _list);
		StringPointer = (Ptr)(*ResultString);
		*StringPointer = StringLength;
		return ResultString;
	}
	else 
	{
		return "";
	}
}

void AddRow(ListHandle _list, char* _newString)
{
	Cell CellPoint;
	
	CellPoint.h = 0;
	CellPoint.v = rowNum;
	LAddRow(1, rowNum, _list);
	LSetCell(_newString, strlen(_newString), CellPoint, _list);
	LDraw(CellPoint, _list);
	rowNum++;
	UpdateList(_list);

}

void DeleteRow(ListHandle _list, short _row)
{	
	Cell CellPoint;
	CellPoint.h = 0;
	CellPoint.v = _row;
	LDelRow(1, _row, _list);
	rowNum--;
}

void Activate(ListHandle _list)
{
	LActivate(TRUE, _list);
}

void DestroyList(ListHandle _list)
{
	LDispose(_list);
}

//Controls and stuff
ControlHandle GetVHandle(ListHandle _list)
{
	ControlHandle _myVHandle;
	
	_myVHandle=(**_list).vScroll;
	return _myVHandle;
}
