#pragma once
//学生结构
typedef struct Student
{
	unsigned long long number; //学号
	char name[32];			   //姓名
	float chinese;			   //语文成绩
	float math;				   //数学成绩
	float english;			   //英语成绩
}Student;

//学生链表节点结构
typedef struct Node
{
	Student stu;				 //学生信息
	struct Node* next;	         //指向下一个节点的指针

}Node;
//链表
typedef struct List
{
	Node* front; //指向第一个节点
	int size;   //链表中学生的数量
}List;
//菜单功能
typedef enum MenuOptions
{
	Entry = 1,      //录入学生信息 
	Print = 2,      //打印学生信息
	Save = 3,       //保存学生信息
	Read = 4,       //读取学生信息
	Statistics = 5, //统计学生人数
	Find = 6,       //查找学生信息
	Alter = 7,      //修改学生信息 
	Remove = 8,     //删除学生信息
	Quit = 0,       //退出系统
}MenuOptions;
//打印菜单并提示用户选择功能

int menu();

//录入学生信息
void entryStudent(List* list);

//打印学生信息
void printStudent(List* list);

//保存学生信息,以二进制的方式保存（打开后文件中的内容看不懂）
void saveStudent(List* list);
//以人类可读的方式保存学生信息
void saveStudentHuman(List* list);

