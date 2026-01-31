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
			//saveStudent(&list);
			saveStudentHuman(&list);
			break;
		case Read:
			//readStudent(&list);
			readStudentHuman(&list);
			break;
		case Statistics:
			statisticsStudentCount(&list);
			break;
		case Find:
		{
			Node* node = findStudent(&list);
			if(!node)
				printf("未找到该学生信息\n");
			else {
				printf("学号：%llu\n", node->stu.number);
				printf("姓名：%s\n", node->stu.name);
				printf("语文成绩：%.2f\n", node->stu.chinese);
				printf("数学成绩：%.2f\n", node->stu.math);
				printf("英语成绩：%.2f\n", node->stu.english);
			}
			break;
		}
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