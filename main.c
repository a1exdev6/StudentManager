#include<stdio.h>
#include<stdlib.h>
#include"StudentManager.h"


int main() {
	while (1) {
		MenuOptions m;
		switch (menu())
		{
		case Entry:
			break;
		case Print:
			break;
		case Save:
			break;
		case Read:
			break;
		case Statistics:
			break;
		case Find:
			break;
		case Alter:
			break;
		case Remove:
			break;
		case Quit:
			break;
		default:
			break;
		}
		
		//让程序暂停一下
		system("pause");
		//清屏重新出现菜单
		system("cls");
	}
	return 0;
}