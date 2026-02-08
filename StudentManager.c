#include "StudentManager.h"
#include<stdio.h>
#include<malloc.h>
#include<string.h>

static Node* CreateNode()
{
	//创建节点
	Node* node = malloc(sizeof(Node));
	if (!node)
	{
		printf("malloc failed\n");
		return NULL;
	}
	node->stu.sum = 0;
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
	printf("*         8.新增学生信息           *\n");
	printf("*         9.删除学生信息           *\n");
	printf("*         0.退出系统               *\n");
	printf("************************************\n");
	printf("select>");
	int select = -1;
	scanf("%d", &select);
	return select;

}


//录入学生信息
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
	//计算总分
	node->stu.sum = node->stu.chinese + node->stu.math + node->stu.english;
	//插入到链表中
	node->next = list->front;
	list->front = node;
	list->size++;
}

// 按总成绩从高到低排序链表
void sortStudentBySum(List* list) {
	if (list->front == NULL || list->front->next == NULL) {
		return; // 空链表或只有一个节点时无需排序
	}

	int swapped;
	Node* ptr1;
	Node* lptr = NULL;

	// 冒泡排序核心逻辑
	do {
		swapped = 0;
		ptr1 = list->front;

		while (ptr1->next != lptr) {
			// 比较当前节点与下一个节点的总成绩
			if (ptr1->stu.sum < ptr1->next->stu.sum) {
				// 交换两个节点的学生数据
				Student temp = ptr1->stu;
				ptr1->stu = ptr1->next->stu;
				ptr1->next->stu = temp;
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	} while (swapped);
}


//打印学生信息
void printStudent(List* list) {
	//先按总成绩排序
	sortStudentBySum(list);
	//再打印表头
	printf("********************************************\n");
	printf("*        欢迎使用高校成绩管理系统          *\n");
	printf("********************************************\n");
	printf("*学号 * 姓名 * 语文 *  数学 *  英语 * 总分 *\n");
	printf("********************************************\n");

	//遍历链表
	Node* curNode = list->front;
	while (curNode != NULL) {
		printf("* %llu * %s * %.1f *  %.1f *  %.1f * %.1f\n", curNode->stu.number,curNode->stu.name,
			curNode->stu.chinese,curNode->stu.math,curNode->stu.english,curNode->stu.sum);
		curNode = curNode->next;
	}
}



//保存学生信息,以二进制的方式保存（打开后文件中的内容看不懂）
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

//以人类可读的方式保存学生信息
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
		fprintf(fp, "%llu %s %.1f %.1f %.1f %.1f\n",
			curNode->stu.number, curNode->stu.name,
			curNode->stu.chinese, curNode->stu.math, curNode->stu.english,curNode->stu.sum);
		curNode = curNode->next;
	};
	//关闭文件
	fclose(fp);
}
//读取学生信息,二进制方式读取
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

//以人类可读的方式读取学生信息
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
		if (6 != fscanf(fp, "%llu %s %f %f %f %f\n", &node->stu.number, node->stu.name,
			&node->stu.chinese, &node->stu.math, &node->stu.english,&node->stu.sum))
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

//统计学生人数
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

//查找学生信息
Node* findStudent(List* list)
{
	if (list->size == 0)
	{
		return NULL;
	}
	char buffer[32];
	printf("<-- 请输入要查找的学生学号/姓名 -->\n");
	scanf("%s", buffer);
	//尝试把buffer转成整型
	unsigned long long number=-1;
	sscanf(buffer, "%llu", &number);
	Node* curNode = list->front;
	while (curNode != NULL) {
		if (strcmp(curNode->stu.name, buffer) == 0||
			curNode->stu.number==number)
		{
			return curNode;
		}
		curNode = curNode->next;
	}
	return NULL;
}

//修改学生信息
void alterStudent(List* list)
{
	if (list->size == 0)
	{
		printf("当前无学生信息，无法修改！\n");
		return;
	}
	char buffer[32];
	printf("<-- 请输入要修改的学生学号/姓名 -->\n");
	scanf("%s", buffer);
	//尝试把buffer转成整型
	unsigned long long number = -1;
	sscanf(buffer, "%llu", &number);
	Node* curNode = list->front;
	while (curNode != NULL) {
		if (strcmp(curNode->stu.name, buffer) == 0 ||
			curNode->stu.number == number)
		{
			printf("请输入要修改的学生的成绩信息：\n");
			printf("<-- 语文成绩 -->\n");
			scanf("%f", &curNode->stu.chinese);
			printf("<-- 数学成绩 -->\n");
			scanf("%f", &curNode->stu.math);
			printf("<-- 英语成绩 -->\n");
			scanf("%f", &curNode->stu.english);
			//重新计算总分
			curNode->stu.sum = curNode->stu.chinese + curNode->stu.math + curNode->stu.english;
			printf("学生信息修改成功!!!\n");
			break;
		}
		curNode = curNode->next;
	}
	if(curNode==NULL)
		printf("未找到该学生信息，修改失败！\n");
}

//增加学生信息
void addStudent(List* list)
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
	//计算总分
	node->stu.sum = node->stu.chinese + node->stu.math + node->stu.english;
	//插入到链表中
	node->next = list->front;
	list->front = node;
	list->size++;
}

//删除学生信息
void removeStudent(List* list)
{
	if(list->size==0)
	{
		printf("当前无学生信息，无法删除！\n");
		return;
	}
	char buffer[32];
	printf("<-- 请输入要修改的学生学号/姓名 -->\n");
	scanf("%s", buffer);
	//尝试把buffer转成整型
	unsigned long long number = -1;
	sscanf(buffer, "%llu", &number);
	Node* curNode = list->front;
	Node* prevNode = NULL;
	while (curNode != NULL) {
		if (strcmp(curNode->stu.name, buffer) == 0 ||
			curNode->stu.number == number)
		{
			break;
		}
		prevNode = curNode;
		curNode = curNode->next;
	}
	//是否找到
	if(curNode)
	{
		//删除的是第一个节点
		if(prevNode==NULL)
		{
			list->front = curNode->next;
		}
		else {
			prevNode->next = curNode->next;
		}
		free(curNode);
		list->size--;
	}
}


