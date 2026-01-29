#include "StudentManager.h"
#include<stdio.h>
#include<malloc.h>
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

void entryStudent(List* list)
{ 
	//创建节点
	Node* node = malloc(sizeof(Node));
	if(!node)
	{
		printf("malloc failed\n");
		return;
	}
	node->next = NULL;
	//输入学生信息
	printf("<-- 输入学生学号 -->\n");
	scanf("%llu", &node->stu.number);
	printf("<-- 输入学生姓名 -->\n");
	scanf("%s", node->stu.name);
	printf("<-- 输入学生语文成绩 -->\n");
	scanf("%f", &node->stu.chinese);
	printf("<-- 输入学生数学成绩 -->\n");
	scanf("%f", &node->stu.math);
	printf("<-- 输入学生英语成绩 -->\n");
	scanf("%f", &node->stu.english);
	//插入到链表中
	node->next = list->front;
	list->front = node;
	list->size++;
}

void printStudent(List* list) {
	printf("************************************\n");
	printf("*     欢迎使用高校成绩管理系统     *\n");
	printf("************************************\n");
	printf("*学号 * 姓名 * 语文 *  数学 *  英语*\n");
	printf("************************************\n");

	//遍历链表
	Node* curNode = list->front;
	while (curNode != NULL) {
		printf("* %llu * %s * %.1f *  %.1f *  %.1f *\n", curNode->stu.number,curNode->stu.name,
			curNode->stu.chinese,curNode->stu.math,curNode->stu.english);
		curNode = curNode->next;
	}
}