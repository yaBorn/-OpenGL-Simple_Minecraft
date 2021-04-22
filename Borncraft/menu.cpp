#include "menu.h"

//�����˵�
void menu_Creat(HWND hWnd)
{
	HMENU hMenu = CreateMenu();
	HMENU hMenu1 = CreatePopupMenu();
	HMENU hMenu2 = CreatePopupMenu();
	HMENU hSubi = CreatePopupMenu();
	//g_menu = hMenu1;
	AppendMenu(hMenu, MF_POPUP, (UINT)hMenu1, "�˵�1");
	AppendMenu(hMenu1, MF_STRING | MF_CHECKED, 1001, "��ѡ");
	AppendMenu(hMenu1, MF_POPUP, (UINT)hSubi, "�Ӳ˵�");
	AppendMenu(hSubi, MF_STRING, 1002, "��Ϣ2");
	AppendMenu(hSubi, MF_SEPARATOR, 0, "");
	AppendMenu(hSubi, MF_STRING, 1003, "��Ϣ3");
	AppendMenu(hMenu, MF_POPUP, (UINT)hMenu2, "�˵�2");
	AppendMenu(hMenu2, MF_STRING, 1004, "��Ϣ4");
	AppendMenu(hMenu2, MF_SEPARATOR, 0, "");
	AppendMenu(hMenu2, MF_STRING, 1005, "��Ϣ5");
	SetMenu(hWnd, hMenu);
}

//��Ӧ�˵�
void menu_Command(HWND hWnd, WPARAM wParam)
{
	static int g_state = 0;//��־��
	switch (LOWORD(wParam))
	{
	case 1002:
		MessageBox(hWnd, "��Ϣ2", "��Ϣ", MB_OK);
		break;
	case 1003:
		MessageBox(hWnd, "��Ϣ3", "��Ϣ", MB_OK);
		break;
	case 1004:
		MessageBox(hWnd, "��Ϣ4", "��Ϣ", MB_OK);
		break;
	case 1005:
		MessageBox(hWnd, "��Ϣ5", "��Ϣ", MB_OK);
		break;
	}
}

// �ص�����
LRESULT CALLBACK WndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam)
{
	switch (msgID)
	{
	case WM_COMMAND:
		menu_Command(hWnd, wParam);
		break;
	case WM_CREATE:
		menu_Creat(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, msgID, wParam, lParam);
}