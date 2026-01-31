#include "StudentManager.h"
#include<stdio.h>
#include<malloc.h>

static Node* CreateNode()
{
	//创建节点
	Node* node = malloc(sizeof(Node));
	if (!node)
	{
		printf("malloc failed\n");
		return NULL;
	}
	node->next = NULL;
	return node;
}
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
	Node* node = CreateNode();
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
		fprintf(fp, "%llu %s %.1f %.1f %.1f\n",
			curNode->stu.number, curNode->stu.name,
			curNode->stu.chinese, curNode->stu.math, curNode->stu.english);
		curNode = curNode->next;
	};
	//关闭文件
	fclose(fp);
}

void readStudent(List* list)
{
	//打开文件
	FILE* fp = fopen("students.data", "rb");
	if (!fp) {
		perror("file open failed\n");
		return;
	}
	//读取学生信息
	while(!feof(fp))
	{
		Node* node = CreateNode();
		if (!node)
			break;
		size_t len = fread(&node->stu, sizeof(Student), 1, fp);
		if (len == 0)
		{
			free(node);
			break;
		}
		//插入到链表中
		node->next = list->front;
		list->front = node;
		list->size++;
	}
	//关闭文件
	fclose(fp);
}

void readStudentHuman(List* list)
{
	//打开文件
	FILE* fp = fopen("students.txt", "r");
	if (!fp) {
		perror("file open failed\n");
		return;
	}
	//读取学生文件
	while (!feof(fp))
	{
		Node* node = CreateNode();
		if(!node)
			break;
		if (5 != fscanf(fp, "%llu %s %f %f %f\n", &node->stu.number, node->stu.name,
			&node->stu.chinese, &node->stu.math, &node->stu.english))
		{
			free(node);
			break;
		}
		//插入链表
		node->next = list->front;
		list->front = node;
		list->size++;
	}
	//关闭文件
	fclose(fp);
}

void statisticsStudentCount(List* list)
{
	//printf("学生总人数为：%d\n", list->size);
	int count = 0;
	Node* curNode = list->front;
	while (curNode != NULL) {
		count++;
		curNode = curNode->next;
	}
	printf("学生总人数为：%d\n", count);
}
