#include <windows.h>
#include <stdio.h>
#include <commctrl.h>
#include "resources.h"

#define reserve 1
#define available 2
#define remove 3
#define display 4
#define search 5
#define exit 6

int dim = 16;

HMENU menu;
HBITMAP menuicon = (HBITMAP)LoadImage(NULL,"r.bmp",IMAGE_BITMAP,dim,dim,LR_LOADFROMFILE);
HBITMAP exiticon = (HBITMAP)LoadImage(NULL,"exit.bmp",IMAGE_BITMAP,dim,dim,LR_LOADFROMFILE);
HBITMAP searchicon = (HBITMAP)LoadImage(NULL,"search.bmp",IMAGE_BITMAP,dim,dim,LR_LOADFROMFILE);
HBITMAP displayicon = (HBITMAP)LoadImage(NULL,"display.bmp",IMAGE_BITMAP,dim,dim,LR_LOADFROMFILE);
HBITMAP removeicon = (HBITMAP)LoadImage(NULL,"remove.bmp",IMAGE_BITMAP,dim,dim,LR_LOADFROMFILE);
HBITMAP availableicon = (HBITMAP)LoadImage(NULL,"a.bmp",IMAGE_BITMAP,dim,dim,LR_LOADFROMFILE);
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

    AppendMenu(menu, MF_POPUP, (UINT_PTR)FILE_MENU, "hotel");
    SetMenu(handle,menu);
    SetMenuItemBitmaps(menu,1,MF_BYCOMMAND,menuicon,NULL);
    SetMenuItemBitmaps(menu,6,MF_BYCOMMAND,exiticon,NULL);
    SetMenuItemBitmaps(menu,4,MF_BYCOMMAND,displayicon,NULL);
    SetMenuItemBitmaps(menu,3,MF_BYCOMMAND,removeicon,NULL);
    SetMenuItemBitmaps(menu,5,MF_BYCOMMAND,searchicon,NULL);
    SetMenuItemBitmaps(menu,2,MF_BYCOMMAND,availableicon,NULL);
}
void addcontrols(HWND handle){
    int xtest;
    //x=GetSystemMetrics(SM_CXFULLSCREEN);
    RECT windowsize={0};
    //y=GetSystemMetrics(SM_CYFULLSCREEN);
    GetWindowRect(handle,&windowsize);
    printf("%d %d %d %d\n",(int)windowsize.top,(int)windowsize.left,(int)windowsize.right,(int)windowsize.bottom);
    if(windowsize.left<0){
        windowsize.left*=-1;
    }
    int xreserve=200;
    //xcenter=x/2;
    xtest=100;
    //ycenter=y/2;

    a=CreateWindowEx(0,"button","reserve",WS_VISIBLE | WS_CHILD  | BS_CENTER,(windowsize.right-windowsize.left)/2-(xreserve/2),20,xreserve,25,handle,(HMENU)reserve,NULL,NULL);
    b=CreateWindowEx(0,"button","available rooms",WS_VISIBLE | WS_CHILD | BS_CENTER,(windowsize.right-windowsize.left)/2-(xreserve/2),47,xreserve,25,handle,NULL,NULL,NULL);
    c=CreateWindowEx(0,"button","remove reservation",WS_VISIBLE | WS_CHILD | BS_CENTER,(windowsize.right-windowsize.left)/2-(xreserve/2),74,xreserve,25,handle,NULL,NULL,NULL);
    d=CreateWindowEx(0,"button","display reservations",WS_VISIBLE | WS_CHILD | BS_CENTER,(windowsize.right-windowsize.left)/2-(xreserve/2),101,xreserve,25,handle,NULL,NULL,NULL);
    e=CreateWindowEx(0,"button","search for a client",WS_VISIBLE | WS_CHILD | BS_CENTER,(windowsize.right-windowsize.left)/2-(xreserve/2),128,xreserve,25,handle,NULL,NULL,NULL);

    name = CreateWindowEx(WS_EX_TRANSPARENT,"edit","...",WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_MULTILINE,(windowsize.right-windowsize.left)/2-(xtest/2),156,xtest,50,handle,NULL,NULL,NULL);
    f=CreateWindowEx(0,"button","test",WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,(windowsize.right-windowsize.left)/2-(xtest/2),208,xtest,25,handle,(HMENU)reserve,NULL,NULL);
}

LRESULT CALLBACK WindowProcedure(HWND handler,UINT msg,WPARAM wparam,LPARAM lparam){
int val;
 switch (msg){

 case WM_COMMAND :
     switch (wparam){
     case reserve:
         //MessageBeep(MB_ICONERROR);
         char NAME[25];
         GetWindowText(name,NAME,25);
         SetWindowText(handler,NAME);
         break;
     case exit:
         val = MessageBoxEx(handler,"are you sure?","sure?",MB_YESNO | MB_ICONINFORMATION,0);
         if(val==IDYES){
         DestroyWindow(handler);
         }
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
             printf("size\n");
             DestroyWindow(a);
             DestroyWindow(b);
             DestroyWindow(c);
             DestroyWindow(d);
             DestroyWindow(e);
             DestroyWindow(name);
             DestroyWindow(f);
             addcontrols(handler);
            //MessageBeep(MB_ICONERROR);
            break;
         }
          //PostQuitMessage(0);
         break;

 case WM_CREATE:

     //a=GetSystemMetrics(SM_CXVIRTUALSCREEN);
     printf("wm_create\n");
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
 mywindow.hCursor = (HCURSOR)LoadImage(GetModuleHandle(NULL),MAKEINTRESOURCE(IDI_ICON),IMAGE_ICON,16,16,0);
 mywindow.hInstance = hInst;
 mywindow.lpszClassName = "hotel";
 mywindow.lpfnWndProc = WindowProcedure;
 mywindow.hIconSm = (HICON)LoadImage(GetModuleHandle(NULL),MAKEINTRESOURCE(IDI_ICON),IMAGE_ICON,16,16,0);
 mywindow.hIcon = (HICON)LoadImage(GetModuleHandle(NULL),MAKEINTRESOURCE(IDI_ICON2),IMAGE_ICON,300,300,0);

 if (!RegisterClassEx(&mywindow)){
  return -1;
 }

 CreateWindowEx(WS_EX_TRANSPARENT ,"hotel","ROOMLUX",WS_OVERLAPPEDWINDOW | WS_VISIBLE,100,100,600,500,HWND_DESKTOP,NULL,hInst,NULL);
 MSG msg = { 0 };

 while (GetMessage(&msg,NULL,0,0)){
  TranslateMessage(&msg);
  DispatchMessage(&msg);
 }

 return 0;
}
