#pragma once
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

