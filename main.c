#include<stdio.h>
#include<stdlib.h>
#include"StudentManager.h"
#include<string.h>

int main() {
	//创建链表
	List list = { 0 };
	//内存设置
	memset(&list, 0, sizeof(List));
	while (1) {
		MenuOptions m;
		switch (menu())
		{
		case Entry:
			entryStudent(&list);
			break;
		case Print:
			printStudent(&list);
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