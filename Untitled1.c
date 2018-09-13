#include <windows.h>
#include <stdio.h>
#include <commctrl.h>
#include <graphics.h>
#include "fuck_conio.h"
#include "resources.h"
#define reserve 1
#define available 2
#define remove 3
#define display 4
#define search 5
#define exit 6

HMENU menu;
HWND name,a,b,c,d,e,f;

void addmenu(HWND handle){
    HMENU FILE_MENU = CreateMenu();

    AppendMenu(FILE_MENU,MF_STRING,reserve,"reserve");
    AppendMenu(FILE_MENU,MF_STRING,available,"available rooms");
    AppendMenu(FILE_MENU,MF_STRING,remove,"remove reservation");
    AppendMenu(FILE_MENU,MF_STRING,display,"display reservations");
    AppendMenu(FILE_MENU,MF_STRING,search,"search");
    AppendMenu(FILE_MENU,MF_SEPARATOR,0,NULL);
    AppendMenu(FILE_MENU,MF_STRING,exit,"exit");

    menu = CreateMenu();

    AppendMenu(menu,MF_POPUP,(UINT_PTR)FILE_MENU,"hotel");
    SetMenu(handle,menu);
}
void addcontrols(HWND handle){
    int x,y,xcenter/*ycenter*/;
    x=GetSystemMetrics(SM_CXFULLSCREEN);
    RECT windowsize={0};
    y=GetSystemMetrics(SM_CYFULLSCREEN);
    GetWindowRect(handle,&windowsize);
    printf("%d %d %d %d",(int)windowsize.top,(int)windowsize.left,(int)windowsize.right,(int)windowsize.bottom);
    if(windowsize.left<0)
        windowsize.left*=-1;
    int xreserve=200;
    xcenter=x/2;
    //ycenter=y/2;

    a=CreateWindowEx(0,"button","reserve",WS_VISIBLE | WS_CHILD  | BS_CENTER,(windowsize.right-windowsize.left)/2-(xreserve/2),20,xreserve,25,handle,NULL,NULL,NULL);
    b=CreateWindowEx(0,"button","available rooms",WS_VISIBLE | WS_CHILD | BS_CENTER,(windowsize.right-windowsize.left)/2-(xreserve/2),47,xreserve,25,handle,NULL,NULL,NULL);
    c=CreateWindowEx(0,"button","remove reservation",WS_VISIBLE | WS_CHILD | BS_CENTER,(windowsize.right-windowsize.left)/2-(xreserve/2),74,xreserve,25,handle,NULL,NULL,NULL);
    d=CreateWindowEx(0,"button","display reservations",WS_VISIBLE | WS_CHILD | BS_CENTER,(windowsize.right-windowsize.left)/2-(xreserve/2),101,xreserve,25,handle,NULL,NULL,NULL);
    e=CreateWindowEx(0,"button","search for a client",WS_VISIBLE | WS_CHILD | BS_CENTER,(windowsize.right-windowsize.left)/2-(xreserve/2),128,xreserve,25,handle,NULL,NULL,NULL);

    name = CreateWindowEx(0,"edit","...",WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_MULTILINE,(windowsize.right-windowsize.left)/2-(xreserve/2),156,100,50,handle,NULL,NULL,NULL);
    f=CreateWindowEx(0,"button","test",WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,(windowsize.right-windowsize.left)/2-(xreserve/2),208,100,25,handle,(HMENU)reserve,NULL,NULL);
}

LRESULT CALLBACK WindowProcedure(HWND handler,UINT msg,WPARAM wparam,LPARAM lparam){

 switch (msg){
 case WM_COMMAND :
     switch (wparam){
     case reserve:
         MessageBeep(MB_ICONERROR);
         char NAME[25];
         GetWindowText(name,NAME,25);
         SetWindowText(handler,NAME);
         break;
     case exit:
         DestroyWindow(handler);
         break;
     }
     break;

    case WM_SIZE:
         switch (wparam){
         case SIZE_MAXIMIZED:
             printf("A");
             DestroyWindow(a);
             DestroyWindow(b);
             DestroyWindow(c);
             DestroyWindow(d);
             DestroyWindow(e);
             DestroyWindow(name);
             DestroyWindow(f);
             addcontrols(handler);
             //name=CreateWindowEx(0,"edit","...",WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_MULTILINE,300,156,100,50,handler,NULL,NULL,NULL);
             break;
         case SIZE_RESTORED:
             printf("a\n");
             DestroyWindow(a);
             DestroyWindow(b);
             DestroyWindow(c);
             DestroyWindow(d);
             DestroyWindow(e);
             DestroyWindow(name);
             DestroyWindow(f);
             addcontrols(handler);
            MessageBeep(MB_ICONERROR);
            break;
         }
          //PostQuitMessage(0);
         break;

 case WM_CREATE:

     //a=GetSystemMetrics(SM_CXVIRTUALSCREEN);
     printf("d\n");
     addmenu(handler);
     //addcontrols(handler);

     break;
 case WM_DESTROY:
    PostQuitMessage(0);
    break;
 default:
    return DefWindowProc(handler,msg,wparam,lparam);

 }
 return 0;
}


int WINAPI WinMain(HINSTANCE hInst,HINSTANCE hPrev,LPSTR args,int cmdln){

 WNDCLASSEX mywindow = { 0 };
 mywindow.style = CS_DBLCLKS;
 mywindow.cbSize = sizeof(WNDCLASSEX);

 mywindow.hbrBackground = (HBRUSH)COLOR_WINDOW;
 mywindow.hCursor = LoadCursor(NULL,IDC_ARROW);
 mywindow.hInstance = hInst;
 mywindow.lpszClassName = "hotel";
 mywindow.lpfnWndProc = WindowProcedure;
 mywindow.hIconSm = (HICON)LoadImage(GetModuleHandle(NULL),MAKEINTRESOURCE(IDI_ICON),IMAGE_ICON,16,16,0);
 mywindow.hIcon = (HICON)LoadImage(GetModuleHandle(NULL),MAKEINTRESOURCE(IDI_ICON),IMAGE_ICON,128,128,0);

 if (!RegisterClassEx(&mywindow))
  return -1;

 CreateWindowEx(0,"hotel","ROOMLUX",WS_OVERLAPPEDWINDOW | WS_VISIBLE,100,100,500,500,HWND_DESKTOP,NULL,hInst,NULL);
 MSG msg = { 0 };

 while (GetMessage(&msg,NULL,0,0)){
        while(1){
            SYSTEMTIME time;
     GetLocalTime(&time);
     printf("\nDATE:%d/%d/%d TIME:%d:%d:%d.%d %d\n",time.wYear,time.wMonth,time.wDay,time.wHour,time.wMinute,time.wSecond,time.wMilliseconds,time.wDay);
       clrscr();break;
        }
  TranslateMessage(&msg);
  DispatchMessage(&msg);
 }

 return 0;
}
