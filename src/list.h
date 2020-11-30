#ifndef _list_h
#define _list_h


ListHandle Create_List(WindowPtr _win, Rect _rect);
void UpdateList(ListHandle _list);
short DoClick(ListHandle _list, Point _where);
void TurnOffSelection(ListHandle _list);
char* ListSelection(ListHandle _list);
void AddRow(ListHandle _list, char* _newString);
void Activate(ListHandle _list);
void DeleteRow(ListHandle _list, short _row);
void DestroyList(ListHandle _list);


//Controls and stuff
ControlHandle GetVHandle(ListHandle _list);

#endif