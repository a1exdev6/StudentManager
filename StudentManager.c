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

void saveStudent(List* list)
{
	//打开文件
	FILE* fp = fopen("students.data", "wb");
	if(!fp){
		perror("file open failed\n");
		return;
	}
	//写入学生信息
	Node* curNode = list->front;
	while (curNode != NULL) {
		fwrite(&curNode->stu, sizeof(Student), 1, fp);
		curNode = curNode->next;
	};
	//关闭文件
	fclose(fp);
}

void saveStudentHuman(List* list)
{
	//打开文件
	FILE* fp = fopen("students.txt", "w");
	if (!fp) {
		perror("file open failed\n");
		return;
	}
	//写入学生信息
	Node* curNode = list->front;
	while (curNode != NULL) {
		fprintf(fp, "学号:%llu 姓名:%s 语文:%.1f 数学:%.1f 英语:%.1f\n",
			curNode->stu.number, curNode->stu.name,
			curNode->stu.chinese, curNode->stu.math, curNode->stu.english);
		curNode = curNode->next;
	};
	//关闭文件
	fclose(fp);
}
