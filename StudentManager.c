#include "StudentManager.h"
#include<stdio.h>
int menu() {
	printf("************************************\n");
	printf("*     欢迎使用高校成绩管理系统     *\n");
	printf("************************************\n");
	printf("*           请选择功能             *\n");
	printf("************************************\n");
	printf("*         1.录入学生信息           *\n");
	printf("*         2.打印学生信息           *\n");
	printf("*         3.保存学生信息           *\n");
	printf("*         4.读取学生信息           *\n");
	printf("*         5.统计学生人数           *\n");
	printf("*         6.查找学生信息           *\n");
	printf("*         7.修改学生信息           *\n");
	printf("*         8.删除学生信息           *\n");
	printf("*         0.退出系统               *\n");
	printf("************************************\n");
	printf("select>");
	int select = -1;
	scanf("%d", &select);
	return select;

}