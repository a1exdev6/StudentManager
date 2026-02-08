#include <easyx.h>
#include <conio.h>
#include <graphics.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include"E:\StudentManager\StudentManager\StudentManager.h"
#include<stdio.h>
//申明全局链表，让整个文件都能使用
extern List studentList;
// 窗口常量
const int WIDTH = 1000;
const int HEIGHT = 618;
const int LEFT_WIDTH = 160;

// 图片缓冲区
IMAGE leftImg(LEFT_WIDTH, HEIGHT);
IMAGE rightImg(WIDTH - LEFT_WIDTH, HEIGHT);

// 左侧导航按钮结构体
typedef struct {
    int x, y;
    wchar_t text[20];
    int isSelected;  // 0-未选中 1-选中
} NavButton;

// 左侧导航按钮数组
NavButton navButtons[7] = {
    {5, 5, L"展示作品信息", 1},
    {5, 35, L"增加学生信息", 0},
    {5, 65, L"删除学生信息", 0},
    {5, 95, L"修改学生信息", 0},
    {5, 125, L"查询学生信息", 0},
    {5, 155, L"输出学生信息", 0},
    {5, 185, L"  退出程序", 0}
};

// 当前选中的导航索引
int currentNav = 0;
// 输出页面的当前页码
int currentPage = 1;
const int PAGE_SIZE = 12;

// 绘制单个导航按钮
void drawNavButton(NavButton btn) {
    setfillcolor(btn.isSelected ? RGB(204, 213, 240) : RGB(93, 107, 153));
    fillroundrect(btn.x, btn.y, btn.x + 120, btn.y + 20, 10, 10);
    setbkmode(TRANSPARENT);
    setcolor(RGB(255, 255, 255));
    setfont(20, 0, _T("微软雅黑"));
    outtextxy(btn.x + 15, btn.y , btn.text);
}

// 绘制左侧导航栏
void drawLeftNav() {
    SetWorkingImage(&leftImg);
    setbkcolor(RGB(93, 107, 153));
    cleardevice();
    for (int i = 0; i < 7; i++) {
        drawNavButton(navButtons[i]);
    }
    SetWorkingImage();
    putimage(0, 0, &leftImg);
}

// 绘制作品信息页面
void drawPage_WorkInfo() {
    SetWorkingImage(&rightImg);
    setbkcolor(RGB(247, 249, 254));
    cleardevice();
    setbkmode(TRANSPARENT);

    // 标题
    setcolor(RGB(0, 0, 139));
    // 标题文字
    TCHAR title[] = _T("学生成绩管理系统");
    settextstyle(60, 0, _T("微软雅黑"));

    // 直接计算右侧居中坐标
    int rightX = LEFT_WIDTH + ((getwidth() - LEFT_WIDTH) - textwidth(title)) / 3;
    int rightY = (getheight() - textheight(title)) / 3;

    // 绘制标题
    outtextxy(rightX, rightY, title);

    setfont(40, 0, _T("微软雅黑"));
    outtextxy(550, 320, _T("版本：V1.0"));

    SetWorkingImage();
    putimage(LEFT_WIDTH, 0, &rightImg);
}

// 绘制增加学生页面
void drawPage_AddStu() {
    SetWorkingImage(&rightImg);
    setbkcolor(RGB(247, 249, 254));
    cleardevice();
    setbkmode(TRANSPARENT);

    // 标题
    setcolor(RGB(0, 0, 139));
    setfont(38, 0, _T("微软雅黑"));
    outtextxy(300, 30, _T("学生信息增加页"));

    // 总人数
    char totalBuf[50];
    sprintf(totalBuf, "当前记录学生总人数为%d", studentList.size);
    wchar_t wBuf[50];
    MultiByteToWideChar(CP_ACP, 0, totalBuf, -1, wBuf, 50);
    setfont(30, 0, _T("微软雅黑"));
    outtextxy(50, 80, wBuf);

    // 输入区域背景
    setfillcolor(RGB(173, 216, 230));
    fillroundrect(250, 130, 650, 550, 10, 10);

    // 标签
    setcolor(RGB(0, 0, 0));
    setfont(25, 0, _T("微软雅黑"));
    outtextxy(300, 180, _T("学号"));
    outtextxy(300, 230, _T("姓名"));
    outtextxy(300, 280, _T("语文"));
    outtextxy(300, 330, _T("数学"));
    outtextxy(300, 380, _T("英语"));
    outtextxy(300, 430, _T("总分"));

    // 输入框
    setfillcolor(RGB(255, 255, 255));
    fillroundrect(400, 170, 580, 200, 5, 5);
    fillroundrect(400, 220, 580, 250, 5, 5);
    fillroundrect(400, 270, 580, 300, 5, 5);
    fillroundrect(400, 320, 580, 350, 5, 5);
    fillroundrect(400, 370, 580, 400, 5, 5);
    fillroundrect(400, 420, 580, 450, 5, 5);

    // 按钮
    setfillcolor(RGB(100, 149, 237));
    fillroundrect(600, 170, 680, 200, 5, 5);
    fillroundrect(600, 220, 680, 250, 5, 5);
    fillroundrect(600, 270, 680, 300, 5, 5);
    fillroundrect(600, 320, 680, 350, 5, 5);
    fillroundrect(600, 370, 680, 400, 5, 5);
    fillroundrect(600, 420, 680, 450, 5, 5);

    setcolor(RGB(255, 255, 255));
    outtextxy(615, 175, _T("添加"));
    outtextxy(615, 225, _T("添加"));
    outtextxy(615, 275, _T("添加"));
    outtextxy(615, 325, _T("添加"));
    outtextxy(615, 375, _T("添加"));
    outtextxy(615, 425, _T("保存"));

    // 默认值
    setcolor(RGB(0, 0, 0));
    outtextxy(410, 175, _T("0"));
    outtextxy(410, 225, _T("NULL"));
    outtextxy(410, 275, _T("0.0"));
    outtextxy(410, 325, _T("0.0"));
    outtextxy(410, 375, _T("0.0"));
    outtextxy(410, 425, _T("0.0"));

    SetWorkingImage();
    putimage(LEFT_WIDTH, 0, &rightImg);
}

// 绘制删除学生页面
void drawPage_DelStu() {
    SetWorkingImage(&rightImg);
    setbkcolor(RGB(247, 249, 254));
    cleardevice();
    setbkmode(TRANSPARENT);

    // 标题
    setcolor(RGB(0, 0, 139));
    setfont(38, 0, _T("微软雅黑"));
    outtextxy(300, 30, _T("学生信息删除页"));

    // 总人数
    char totalBuf[50];
    sprintf(totalBuf, "当前记录学生总人数为%d", studentList.size);
    wchar_t wBuf[50];
    MultiByteToWideChar(CP_ACP, 0, totalBuf, -1, wBuf, 50);
    setfont(30, 0, _T("微软雅黑"));
    outtextxy(50, 80, wBuf);

    // 查询按钮
    setfillcolor(RGB(100, 149, 237));
    fillroundrect(200, 130, 400, 170, 10, 10);
    fillroundrect(450, 130, 650, 170, 10, 10);
    fillroundrect(700, 130, 800, 170, 10, 10);
    setcolor(RGB(255, 255, 255));
    setfont(24, 0, _T("微软雅黑"));
    outtextxy(240, 140, _T("以学号方式查询"));
    outtextxy(490, 140, _T("以姓名方式查询"));
    outtextxy(720, 140, _T(" 删除"));

    // 信息展示区
    setfillcolor(RGB(173, 216, 230));
    fillroundrect(200, 220, 650, 550, 10, 10);

    // 标签
    setcolor(RGB(0, 0, 0));
    setfont(25, 0, _T("微软雅黑"));
    outtextxy(250, 270, _T("学号"));
    outtextxy(250, 320, _T("姓名"));
    outtextxy(250, 370, _T("语文"));
    outtextxy(250, 420, _T("数学"));
    outtextxy(250, 470, _T("英语"));
    outtextxy(250, 520, _T("总分"));

    // 输入框
    setfillcolor(RGB(255, 255, 255));
    fillroundrect(350, 260, 550, 290, 5, 5);
    fillroundrect(350, 310, 550, 340, 5, 5);
    fillroundrect(350, 360, 550, 390, 5, 5);
    fillroundrect(350, 410, 550, 440, 5, 5);
    fillroundrect(350, 460, 550, 490, 5, 5);
    fillroundrect(350, 510, 550, 540, 5, 5);

    // 默认值
    setcolor(RGB(0, 0, 0));
    outtextxy(360, 265, _T("0"));
    outtextxy(360, 315, _T("NULL"));
    outtextxy(360, 365, _T("0.0"));
    outtextxy(360, 415, _T("0.0"));
    outtextxy(360, 465, _T("0.0"));
    outtextxy(360, 515, _T("0.0"));

    SetWorkingImage();
    putimage(LEFT_WIDTH, 0, &rightImg);
}

// 绘制修改学生页面
void drawPage_ModifyStu() {
    SetWorkingImage(&rightImg);
    setbkcolor(RGB(247, 249, 254));
    cleardevice();
    setbkmode(TRANSPARENT);

    // 标题
    setcolor(RGB(0, 0, 139));
    setfont(38, 0, _T("微软雅黑"));
    outtextxy(300, 30, _T("学生信息修改页"));

    // 总人数
    char totalBuf[50];
    sprintf(totalBuf, "当前记录学生总人数为%d", studentList.size);
    wchar_t wBuf[50];
    MultiByteToWideChar(CP_ACP, 0, totalBuf, -1, wBuf, 50);
    setfont(30, 0, _T("微软雅黑"));
    outtextxy(50, 80, wBuf);

    // 查询按钮
    setfillcolor(RGB(100, 149, 237));
    fillroundrect(500, 130, 700, 170, 10, 10);
    setcolor(RGB(255, 255, 255));
    outtextxy(540, 135, _T("查询学生学号"));

    // 信息展示区
    setfillcolor(RGB(173, 216, 230));
    fillroundrect(250, 220, 650, 550, 10, 10);

    // 标签
    setcolor(RGB(0, 0, 0));
    setfont(24, 0, _T("微软雅黑"));
    outtextxy(300, 270, _T("学号"));
    outtextxy(300, 320, _T("姓名"));
    outtextxy(300, 370, _T("语文"));
    outtextxy(300, 420, _T("数学"));
    outtextxy(300, 470, _T("英语"));
    outtextxy(300, 520, _T("总分"));

    // 输入框
    setfillcolor(RGB(255, 255, 255));
    fillroundrect(400, 260, 580, 290, 5, 5);
    fillroundrect(400, 310, 580, 340, 5, 5);
    fillroundrect(400, 360, 580, 390, 5, 5);
    fillroundrect(400, 410, 580, 440, 5, 5);
    fillroundrect(400, 460, 580, 490, 5, 5);
    fillroundrect(400, 510, 580, 540, 5, 5);

    // 按钮
    setfillcolor(RGB(100, 149, 237));
    fillroundrect(600, 260, 680, 290, 5, 5);
    fillroundrect(600, 310, 680, 340, 5, 5);
    fillroundrect(600, 360, 680, 390, 5, 5);
    fillroundrect(600, 410, 680, 440, 5, 5);
    fillroundrect(600, 460, 680, 490, 5, 5);
    fillroundrect(600, 510, 680, 540, 5, 5);

    setcolor(RGB(255, 255, 255));
    outtextxy(615, 265, _T("修改"));
    outtextxy(615, 315, _T("修改"));
    outtextxy(615, 365, _T("修改"));
    outtextxy(615, 415, _T("修改"));
    outtextxy(615, 465, _T("修改"));
    outtextxy(615, 515, _T("保存"));

    // 默认值
    setcolor(RGB(0, 0, 0));
    outtextxy(410, 265, _T("0"));
    outtextxy(410, 315, _T("NULL"));
    outtextxy(410, 365, _T("0.0"));
    outtextxy(410, 415, _T("0.0"));
    outtextxy(410, 465, _T("0.0"));
    outtextxy(410, 515, _T("0.0"));

    SetWorkingImage();
    putimage(LEFT_WIDTH, 0, &rightImg);
}

// 绘制查询学生页面
void drawPage_SearchStu() {
    SetWorkingImage(&rightImg);
    setbkcolor(RGB(247, 249, 254));
    cleardevice();
    setbkmode(TRANSPARENT);

    // 标题
    setcolor(RGB(0, 0, 139));
    setfont(38, 0, _T("微软雅黑"));
    outtextxy(300, 30, _T("学生信息查询页"));

    // 总人数
    char totalBuf[50];
    sprintf(totalBuf, "当前记录学生总人数为%d", studentList.size);
    wchar_t wBuf[50];
    MultiByteToWideChar(CP_ACP, 0, totalBuf, -1, wBuf, 50);
    setfont(30, 0, _T("微软雅黑"));
    outtextxy(50, 80, wBuf);

    // 查询按钮
    setfillcolor(RGB(100, 149, 237));
    fillroundrect(200, 130, 400, 170, 10, 10);
    fillroundrect(450, 130, 650, 170, 10, 10);
    setcolor(RGB(255, 255, 255));
    setfont(28, 0, _T("微软雅黑"));
    outtextxy(230, 139, _T("以学号方式查询"));
    outtextxy(465, 139, _T("以姓名方式查询"));

    // 信息展示区
    setfillcolor(RGB(173, 216, 230));
    fillroundrect(200, 220, 650, 550, 10, 10);

    // 标签
    setcolor(RGB(0, 0, 0));
    setfont(24, 0, _T("微软雅黑"));
    outtextxy(250, 270, _T("语文"));
    outtextxy(250, 320, _T("数学"));
    outtextxy(250, 370, _T("英语"));
    outtextxy(250, 420, _T("总分"));

    // 输入框
    setfillcolor(RGB(255, 255, 255));
    fillroundrect(350, 260, 550, 290, 5, 5);
    fillroundrect(350, 310, 550, 340, 5, 5);
    fillroundrect(350, 360, 550, 390, 5, 5);
    fillroundrect(350, 410, 550, 440, 5, 5);

    // 默认值
    setcolor(RGB(0, 0, 0));
    outtextxy(360, 265, _T("0.0"));
    outtextxy(360, 315, _T("0.0"));
    outtextxy(360, 365, _T("0.0"));
    outtextxy(360, 415, _T("0.0"));

    SetWorkingImage();
    putimage(LEFT_WIDTH, 0, &rightImg);
}

// 绘制输出学生页面（适配链表）
void drawPage_OutputStu() {
    SetWorkingImage(&rightImg);
    setbkcolor(RGB(247, 249, 254));
    cleardevice();
    setbkmode(TRANSPARENT);

    // 标题
    setcolor(RGB(0, 0, 139));
    setfont(38, 0, _T("微软雅黑"));
    outtextxy(300, 30, _T("学生基本信息表"));

    // 分页信息
    int totalPage = (studentList.size + PAGE_SIZE - 1) / PAGE_SIZE;
    char pageBuf[100];
    sprintf(pageBuf, "当前记录学生总人数为%d 当前第%d/%d页", studentList.size, currentPage, totalPage);
    wchar_t wPageBuf[100];
    MultiByteToWideChar(CP_ACP, 0,pageBuf, -1, wPageBuf, 50);
    setfont(30, 0, _T("微软雅黑"));
    outtextxy(50, 80, wPageBuf);

    // 表头
    setcolor(RGB(0, 0, 0));
    setfont(24, 0, _T("微软雅黑"));
    int y = 120;
    outtextxy(100, y, _T("学号"));
    outtextxy(220, y, _T("姓名"));
    outtextxy(400, y, _T("语文"));
    outtextxy(480, y, _T("数学"));
    outtextxy(560, y, _T("英语"));
    outtextxy(640, y, _T("总分"));
    y += 20;

    // 遍历链表绘制当前页数据
    Node* p = studentList.front;
    int count = 0;
    int start = (currentPage - 1) * PAGE_SIZE;

    // 定位到当前页的起始节点
    while (p != NULL && count < start) {
        p = p->next;
        count++;
    }


    // 绘制当前页的12条数据
    count = 0;
    while (p != NULL && count < PAGE_SIZE) {
        char buf[50];
        wchar_t wBuf[50];

        // 学号
        sprintf(buf, "%llu", p->stu.number);
        MultiByteToWideChar(CP_ACP, 0, buf, -1, wBuf, 50);
        outtextxy(100, y, wBuf);

        // 姓名
        sprintf(buf, "%s", p->stu.name);
        MultiByteToWideChar(CP_ACP, 0, buf, -1, wBuf, 50);
        outtextxy(220, y, wBuf);

        // 语文
        sprintf(buf, "%.1f", p->stu.chinese);
        MultiByteToWideChar(CP_ACP, 0, buf, -1, wBuf, 50);
        outtextxy(400, y, wBuf);

        // 数学
        sprintf(buf, "%.1f", p->stu.math);
        MultiByteToWideChar(CP_ACP, 0, buf, -1, wBuf, 50);
        outtextxy(480, y, wBuf);

        // 英语
        sprintf(buf, "%.1f", p->stu.english);
        MultiByteToWideChar(CP_ACP, 0, buf, -1, wBuf, 50);
        outtextxy(560, y, wBuf);

        // 总分
        sprintf(buf, "%.1f", p->stu.sum);
        MultiByteToWideChar(CP_ACP, 0, buf, -1, wBuf, 50);
        outtextxy(640, y, wBuf);

        y += 20;
        p = p->next;
        count++;
    }


    // 分页按钮
    setfillcolor(RGB(100, 149, 237));
    fillroundrect(200, 550, 350, 590, 10, 10);
    fillroundrect(550, 550, 700, 590, 10, 10);
    setcolor(RGB(255, 255, 255));
    outtextxy(240, 560, _T("上一页"));
    outtextxy(590, 560, _T("下一页"));

    SetWorkingImage(NULL);
    putimage(LEFT_WIDTH, 0, &rightImg);
}

// 根据当前导航绘制右侧页面
void drawRightContent() {
    switch (currentNav) {
    case 0: drawPage_WorkInfo(); break;
    case 1: drawPage_AddStu(); break;
    case 2: drawPage_DelStu(); break;
    case 3: drawPage_ModifyStu(); break;
    case 4: drawPage_SearchStu(); break;
    case 5: drawPage_OutputStu(); break;
    case 6: closegraph(); exit(0); break;
    }
}

// 按学号查询学生（链表版）
void searchStuById_EasyX() {
    wchar_t inputId[20];
    // 使用系统输入框，兼容性更好
    if (GetDlgItemTextW(GetForegroundWindow(), NULL, inputId, _countof(inputId)) > 0) {
        unsigned long long id = _wtoll(inputId);
        // 遍历链表查询
        Node* p = studentList.front;
        while (p != NULL) {
            if (p->stu.number == id) {
                // 绘制查询结果
                SetWorkingImage(&rightImg);
                setfillcolor(RGB(173, 216, 230));
                fillroundrect(200, 220, 650, 550, 10, 10);
                setcolor(RGB(0, 0, 0));
                outtextxy(250, 270, _T("语文"));
                outtextxy(250, 320, _T("数学"));
                outtextxy(250, 370, _T("英语"));
                outtextxy(250, 420, _T("总分"));
                setfillcolor(RGB(255, 255, 255));
                fillroundrect(350, 260, 550, 290, 5, 5);
                fillroundrect(350, 310, 550, 340, 5, 5);
                fillroundrect(350, 360, 550, 390, 5, 5);
                fillroundrect(350, 410, 550, 440, 5, 5);
                char buf[50];
                wchar_t wBuf[50];

                // 语文
                sprintf(buf, "%.1f", p->stu.chinese);
                MultiByteToWideChar(CP_ACP, 0, buf, -1, wBuf, 50);
                outtextxy(360, 265, wBuf);

                // 数学
                sprintf(buf, "%.1f", p->stu.math);
                MultiByteToWideChar(CP_ACP, 0, buf, -1, wBuf, 50);
                outtextxy(360, 315, wBuf);

                // 英语
                sprintf(buf, "%.1f", p->stu.english);
                MultiByteToWideChar(CP_ACP, 0, buf, -1, wBuf, 50);
                outtextxy(360, 365, wBuf);

                // 总分
                sprintf(buf, "%.1f", p->stu.sum);
                MultiByteToWideChar(CP_ACP, 0, buf, -1, wBuf, 50);
                outtextxy(360, 415, wBuf);

                // 切换回默认绘图窗口
                SetWorkingImage(NULL);
                putimage(LEFT_WIDTH, 0, &rightImg);
                break;
            }
            p = p->next;
        }
    }
}

Student tempStu = { 0 }; // 定义全局临时学生变量用于存储输入内容
//增加学生信息页面的点击输入操作
void handleRightClick(int rx, int ry)
{
    // 仅在【增加学生信息页】生效
    if (currentNav == 1)
    {
        // 定义临时变量存储输入内容
        TCHAR inputContent[20] = { 0 };
        // 标记当前操作类型（0-无操作 1-学号 2-姓名 3-语文 4-数学 5-英语 6-保存）
        int opType = 0;

        // 1. 先获取输入内容并更新临时学生信息
        if (rx >= 600 && rx <= 680 && ry >= 170 && ry <= 200)
        {
            if (InputBox(inputContent, 20, _T("请输入学生学号"), _T("学号输入"))) {
                tempStu.number = _wtoll(inputContent); // 保存学号到临时变量
                opType = 1;
            }
        }
        else if (rx >= 600 && rx <= 680 && ry >= 220 && ry <= 250)
        {
            if (InputBox(inputContent, 20, _T("请输入学生姓名"), _T("姓名输入"))) {
                // 转换宽字符到多字节并保存姓名
                char nameBuf[20] = { 0 };
                WideCharToMultiByte(CP_ACP, 0, inputContent, -1, nameBuf, sizeof(nameBuf), NULL, NULL);
                strcpy(tempStu.name, nameBuf);
                opType = 2;
            }
        }
        else if (rx >= 600 && rx <= 680 && ry >= 270 && ry <= 300)
        {
            if (InputBox(inputContent, 20, _T("请输入语文成绩"), _T("语文输入"))) {
                tempStu.chinese = (float)_wtof(inputContent); // 保存语文成绩
                tempStu.sum = tempStu.chinese + tempStu.math + tempStu.english; // 计算总分
                opType = 3;
            }
        }
        else if (rx >= 600 && rx <= 680 && ry >= 320 && ry <= 350)
        {
            if (InputBox(inputContent, 20, _T("请输入数学成绩"), _T("数学输入"))) {
                tempStu.math = (float)_wtof(inputContent); // 保存数学成绩
                tempStu.sum = tempStu.chinese + tempStu.math + tempStu.english; // 计算总分
                opType = 4;
            }
        }
        else if (rx >= 600 && rx <= 680 && ry >= 370 && ry <= 400)
        {
            if (InputBox(inputContent, 20, _T("请输入英语成绩"), _T("英语输入"))) {
                tempStu.english = (float)_wtof(inputContent); // 保存英语成绩
                tempStu.sum = tempStu.chinese + tempStu.math + tempStu.english; // 计算总分
                opType = 5;
            }
        }
        else if (rx >= 600 && rx <= 680 && ry >= 420 && ry <= 450)
        {
            // 保存学生信息到链表和文件
            addStudentToList(&studentList, tempStu);
            saveStudentsToFile(&studentList);
            MessageBox(GetHWnd(), _T("学生信息已保存！"), _T("提示"), MB_OK);
            // 重置临时变量，清空输入框
            memset(&tempStu, 0, sizeof(Student));
            opType = 6;
        }

        // 2. 重绘整个增加学生页面（清除残影）
        drawPage_AddStu();

        // 3. 切换到右侧缓冲区绘制所有已输入的内容
        SetWorkingImage(&rightImg);
        setbkmode(TRANSPARENT);
        setcolor(BLACK);
        setfillcolor(WHITE);
        setlinecolor(LIGHTGRAY);

        // 定义临时缓冲区用于格式转换
        char buf[50];
        wchar_t wBuf[50] = { 0 };

        // 绘制学号（如果已输入）
        if (tempStu.number != 0) {
            fillroundrect(400, 170, 580, 200, 5, 5);
            roundrect(400, 170, 580, 200, 5, 5);
            sprintf(buf, "%llu", tempStu.number);
            MultiByteToWideChar(CP_ACP, 0, buf, -1, wBuf, sizeof(wBuf) / sizeof(wBuf[0]));
            outtextxy(410, 175, wBuf);
        }

        // 绘制姓名（如果已输入）
        if (strcmp(tempStu.name, "") != 0) {
            fillroundrect(400, 220, 580, 250, 5, 5);
            roundrect(400, 220, 580, 250, 5, 5);
            MultiByteToWideChar(CP_ACP, 0, tempStu.name, -1, wBuf, sizeof(wBuf) / sizeof(wBuf[0]));
            outtextxy(410, 225, wBuf);
        }

        // 绘制语文成绩（如果已输入）
        if (tempStu.chinese != 0) {
            fillroundrect(400, 270, 580, 300, 5, 5);
            roundrect(400, 270, 580, 300, 5, 5);
            sprintf(buf, "%.1f", tempStu.chinese);
            MultiByteToWideChar(CP_ACP, 0, buf, -1, wBuf, sizeof(wBuf) / sizeof(wBuf[0]));
            outtextxy(410, 275, wBuf);
        }

        // 绘制数学成绩（如果已输入）
        if (tempStu.math != 0) {
            fillroundrect(400, 320, 580, 350, 5, 5);
            roundrect(400, 320, 580, 350, 5, 5);
            sprintf(buf, "%.1f", tempStu.math);
            MultiByteToWideChar(CP_ACP, 0, buf, -1, wBuf, sizeof(wBuf) / sizeof(wBuf[0]));
            outtextxy(410, 325, wBuf);
        }

        // 绘制英语成绩（如果已输入）
        if (tempStu.english != 0) {
            fillroundrect(400, 370, 580, 400, 5, 5);
            roundrect(400, 370, 580, 400, 5, 5);
            sprintf(buf, "%.1f", tempStu.english);
            MultiByteToWideChar(CP_ACP, 0, buf, -1, wBuf, sizeof(wBuf) / sizeof(wBuf[0]));
            outtextxy(410, 375, wBuf);
        }

        // 绘制总分（如果有成绩）
        if (tempStu.sum != 0) {
            fillroundrect(400, 420, 580, 450, 5, 5);
            roundrect(400, 420, 580, 450, 5, 5);
            sprintf(buf, "%.1f", tempStu.sum);
            MultiByteToWideChar(CP_ACP, 0, buf, -1, wBuf, sizeof(wBuf) / sizeof(wBuf[0]));
            outtextxy(410, 425, wBuf);
        }

        // 4. 切回默认窗口并更新显示
        SetWorkingImage();
        putimage(LEFT_WIDTH, 0, &rightImg);
    }
}


//新增删除页面的点击处理函数
void handleDeletePageClick(int rx, int ry) {
    if (currentNav == 2) { // 仅在删除页面生效
        TCHAR inputBuf[50] = { 0 };
        Node* foundNode = NULL;

        // 1. 以学号方式查询
        if (rx >= 200 && rx <= 400 && ry >= 130 && ry <= 170) {
            if (InputBox(inputBuf, 50, _T("请输入要查询的学号"), _T("学号查询"))) {
                unsigned long long id = _wtoll(inputBuf);
                // 遍历链表查找
                Node* p = studentList.front;
                while (p != NULL) {
                    if (p->stu.number == id) {
                        foundNode = p;
                        break;
                    }
                    p = p->next;
                }
                if (foundNode) {
                    // 重绘页面并显示查询结果
                    drawPage_DelStu();
                    SetWorkingImage(&rightImg);
                    char buf[50];
                    wchar_t wBuf[50];

                    // 学号
                    sprintf(buf, "%llu", foundNode->stu.number);
                    MultiByteToWideChar(CP_ACP, 0, buf, -1, wBuf, 50);
                    setfillcolor(WHITE);
                    fillroundrect(350, 260, 550, 290, 5, 5);
                    setcolor(BLACK);
                    outtextxy(360, 265, wBuf);

                    // 姓名
                    sprintf(buf, "%s", foundNode->stu.name);
                    MultiByteToWideChar(CP_ACP, 0, buf, -1, wBuf, 50);
                    fillroundrect(350, 310, 550, 340, 5, 5);
                    outtextxy(360, 315, wBuf);

                    // 语文
                    sprintf(buf, "%.1f", foundNode->stu.chinese);
                    MultiByteToWideChar(CP_ACP, 0, buf, -1, wBuf, 50);
                    fillroundrect(350, 360, 550, 390, 5, 5);
                    outtextxy(360, 365, wBuf);

                    // 数学
                    sprintf(buf, "%.1f", foundNode->stu.math);
                    MultiByteToWideChar(CP_ACP, 0, buf, -1, wBuf, 50);
                    fillroundrect(350, 410, 550, 440, 5, 5);
                    outtextxy(360, 415, wBuf);

                    // 英语
                    sprintf(buf, "%.1f", foundNode->stu.english);
                    MultiByteToWideChar(CP_ACP, 0, buf, -1, wBuf, 50);
                    fillroundrect(350, 460, 550, 490, 5, 5);
                    outtextxy(360, 465, wBuf);

                    // 总分
                    sprintf(buf, "%.1f", foundNode->stu.sum);
                    MultiByteToWideChar(CP_ACP, 0, buf, -1, wBuf, 50);
                    fillroundrect(350, 510, 550, 540, 5, 5);
                    outtextxy(360, 515, wBuf);

                    SetWorkingImage();
                    putimage(LEFT_WIDTH, 0, &rightImg);
                }
                else {
                    MessageBox(GetHWnd(), _T("未找到该学号的学生！"), _T("提示"), MB_OK);
                }
            }
        }
        // 2. 以姓名方式查询
        else if (rx >= 450 && rx <= 650 && ry >= 130 && ry <= 170) {
            if (InputBox(inputBuf, 50, _T("请输入要查询的姓名"), _T("姓名查询"))) {
                char nameBuf[50];
                WideCharToMultiByte(CP_ACP, 0, inputBuf, -1, nameBuf, 50, NULL, NULL);
                // 遍历链表查找
                Node* p = studentList.front;
                while (p != NULL) {
                    if (strcmp(p->stu.name, nameBuf) == 0) {
                        foundNode = p;
                        break;
                    }
                    p = p->next;
                }
                if (foundNode) {
                    // 重绘页面并显示查询结果
                    drawPage_DelStu();
                    SetWorkingImage(&rightImg);
                    char buf[50];
                    wchar_t wBuf[50];

                    // 学号
                    sprintf(buf, "%llu", foundNode->stu.number);
                    MultiByteToWideChar(CP_ACP, 0, buf, -1, wBuf, 50);
                    setfillcolor(WHITE);
                    fillroundrect(350, 260, 550, 290, 5, 5);
                    setcolor(BLACK);
                    outtextxy(360, 265, wBuf);

                    // 姓名
                    sprintf(buf, "%s", foundNode->stu.name);
                    MultiByteToWideChar(CP_ACP, 0, buf, -1, wBuf, 50);
                    fillroundrect(350, 310, 550, 340, 5, 5);
                    outtextxy(360, 315, wBuf);

                    // 语文
                    sprintf(buf, "%.1f", foundNode->stu.chinese);
                    MultiByteToWideChar(CP_ACP, 0, buf, -1, wBuf, 50);
                    fillroundrect(350, 360, 550, 390, 5, 5);
                    outtextxy(360, 365, wBuf);

                    // 数学
                    sprintf(buf, "%.1f", foundNode->stu.math);
                    MultiByteToWideChar(CP_ACP, 0, buf, -1, wBuf, 50);
                    fillroundrect(350, 410, 550, 440, 5, 5);
                    outtextxy(360, 415, wBuf);

                    // 英语
                    sprintf(buf, "%.1f", foundNode->stu.english);
                    MultiByteToWideChar(CP_ACP, 0, buf, -1, wBuf, 50);
                    fillroundrect(350, 460, 550, 490, 5, 5);
                    outtextxy(360, 465, wBuf);

                    // 总分
                    sprintf(buf, "%.1f", foundNode->stu.sum);
                    MultiByteToWideChar(CP_ACP, 0, buf, -1, wBuf, 50);
                    fillroundrect(350, 510, 550, 540, 5, 5);
                    outtextxy(360, 515, wBuf);

                    SetWorkingImage();
                    putimage(LEFT_WIDTH, 0, &rightImg);
                }
                else {
                    MessageBox(GetHWnd(), _T("未找到该姓名的学生！"), _T("提示"), MB_OK);
                }
            }
        }
        // 3. 删除按钮
        else if (rx >= 700 && rx <= 800 && ry >= 130 && ry <= 170) {
            if (InputBox(inputBuf, 50, _T("请输入要删除的学号"), _T("删除确认"))) {
                unsigned long long id = _wtoll(inputBuf);
                Node* p = studentList.front;
                Node* prev = NULL;
                int deleted = 0;

                while (p != NULL) {
                    if (p->stu.number == id) {
                        if (prev == NULL) { // 删除头节点
                            studentList.front = p->next;
                        }
                        else { // 删除中间或尾节点
                            prev->next = p->next;
                        }
                        free(p);
                        studentList.size--;
                        deleted = 1;
                        break;
                    }
                    prev = p;
                    p = p->next;
                }

                if (deleted) {
                    MessageBox(GetHWnd(), _T("删除成功！"), _T("提示"), MB_OK);
                    // 删除后重绘页面，更新总人数
                    drawPage_DelStu();
                }
                else {
                    MessageBox(GetHWnd(), _T("未找到该学号的学生，删除失败！"), _T("提示"), MB_OK);
                }
            }
        }
    }
}


//新增修改页面的点击处理函数
// 全局变量：记录当前正在修改的学生节点
Node* currentModifyNode = NULL;

void handleModifyPageClick(int rx, int ry) {
    if (currentNav == 3) { // 仅在修改页面生效
        TCHAR inputBuf[50] = { 0 };

        // 1. 查询学生学号
        if (rx >= 500 && rx <= 700 && ry >= 130 && ry <= 170) {
            if (InputBox(inputBuf, 50, _T("请输入要修改的学生学号"), _T("学号查询"))) {
                unsigned long long id = _wtoll(inputBuf);
                // 遍历链表查找
                Node* p = studentList.front;
                while (p != NULL) {
                    if (p->stu.number == id) {
                        currentModifyNode = p;
                        break;
                    }
                    p = p->next;
                }
                if (currentModifyNode) {
                    // 重绘页面并显示查询结果
                    drawPage_ModifyStu();
                    SetWorkingImage(&rightImg);
                    char buf[50];
                    wchar_t wBuf[50];

                    // 学号
                    sprintf(buf, "%llu", currentModifyNode->stu.number);
                    MultiByteToWideChar(CP_ACP, 0, buf, -1, wBuf, 50);
                    setfillcolor(WHITE);
                    fillroundrect(400, 260, 580, 290, 5, 5);
                    setcolor(BLACK);
                    outtextxy(410, 265, wBuf);

                    // 姓名
                    sprintf(buf, "%s", currentModifyNode->stu.name);
                    MultiByteToWideChar(CP_ACP, 0, buf, -1, wBuf, 50);
                    fillroundrect(400, 310, 580, 340, 5, 5);
                    outtextxy(410, 315, wBuf);

                    // 语文
                    sprintf(buf, "%.1f", currentModifyNode->stu.chinese);
                    MultiByteToWideChar(CP_ACP, 0, buf, -1, wBuf, 50);
                    fillroundrect(400, 360, 580, 390, 5, 5);
                    outtextxy(410, 365, wBuf);

                    // 数学
                    sprintf(buf, "%.1f", currentModifyNode->stu.math);
                    MultiByteToWideChar(CP_ACP, 0, buf, -1, wBuf, 50);
                    fillroundrect(400, 410, 580, 440, 5, 5);
                    outtextxy(410, 415, wBuf);

                    // 英语
                    sprintf(buf, "%.1f", currentModifyNode->stu.english);
                    MultiByteToWideChar(CP_ACP, 0, buf, -1, wBuf, 50);
                    fillroundrect(400, 460, 580, 490, 5, 5);
                    outtextxy(410, 465, wBuf);

                    // 总分
                    sprintf(buf, "%.1f", currentModifyNode->stu.sum);
                    MultiByteToWideChar(CP_ACP, 0, buf, -1, wBuf, 50);
                    fillroundrect(400, 510, 580, 540, 5, 5);
                    outtextxy(410, 515, wBuf);

                    SetWorkingImage();
                    putimage(LEFT_WIDTH, 0, &rightImg);
                }
                else {
                    MessageBox(GetHWnd(), _T("未找到该学号的学生！"), _T("提示"), MB_OK);
                }
            }
        }
        // 2. 学号修改按钮
        else if (rx >= 600 && rx <= 680 && ry >= 260 && ry <= 290) {
            if (currentModifyNode == NULL) {
                MessageBox(GetHWnd(), _T("请先查询要修改的学生！"), _T("提示"), MB_OK);
                return;
            }
            if (InputBox(inputBuf, 50, _T("请输入新的学号"), _T("学号修改"))) {
                unsigned long long newId = _wtoll(inputBuf);
                currentModifyNode->stu.number = newId;
                // 重绘并更新显示
                drawPage_ModifyStu();
                SetWorkingImage(&rightImg);
                char buf[50];
                wchar_t wBuf[50];
                sprintf(buf, "%llu", currentModifyNode->stu.number);
                MultiByteToWideChar(CP_ACP, 0, buf, -1, wBuf, 50);
                setfillcolor(WHITE);
                fillroundrect(400, 260, 580, 290, 5, 5);
                setcolor(BLACK);
                outtextxy(410, 265, wBuf);
                SetWorkingImage();
                putimage(LEFT_WIDTH, 0, &rightImg);
            }
        }
        // 3. 姓名修改按钮
        else if (rx >= 600 && rx <= 680 && ry >= 310 && ry <= 340) {
            if (currentModifyNode == NULL) {
                MessageBox(GetHWnd(), _T("请先查询要修改的学生！"), _T("提示"), MB_OK);
                return;
            }
            if (InputBox(inputBuf, 50, _T("请输入新的姓名"), _T("姓名修改"))) {
                char nameBuf[50];
                WideCharToMultiByte(CP_ACP, 0, inputBuf, -1, nameBuf, 50, NULL, NULL);
                strcpy(currentModifyNode->stu.name, nameBuf);
                // 重绘并更新显示
                drawPage_ModifyStu();
                SetWorkingImage(&rightImg);
                char buf[50];
                wchar_t wBuf[50];
                sprintf(buf, "%s", currentModifyNode->stu.name);
                MultiByteToWideChar(CP_ACP, 0, buf, -1, wBuf, 50);
                setfillcolor(WHITE);
                fillroundrect(400, 310, 580, 340, 5, 5);
                setcolor(BLACK);
                outtextxy(410, 315, wBuf);
                SetWorkingImage();
                putimage(LEFT_WIDTH, 0, &rightImg);
            }
        }
        // 4. 语文修改按钮
        else if (rx >= 600 && rx <= 680 && ry >= 360 && ry <= 390) {
            if (currentModifyNode == NULL) {
                MessageBox(GetHWnd(), _T("请先查询要修改的学生！"), _T("提示"), MB_OK);
                return;
            }
            if (InputBox(inputBuf, 50, _T("请输入新的语文成绩"), _T("语文修改"))) {
                float newScore = (float)_wtof(inputBuf);
                currentModifyNode->stu.chinese = newScore;
                currentModifyNode->stu.sum = currentModifyNode->stu.chinese + currentModifyNode->stu.math + currentModifyNode->stu.english;
                // 重绘并更新显示
                drawPage_ModifyStu();
                SetWorkingImage(&rightImg);
                char buf[50];
                wchar_t wBuf[50];
                sprintf(buf, "%.1f", currentModifyNode->stu.chinese);
                MultiByteToWideChar(CP_ACP, 0, buf, -1, wBuf, 50);
                setfillcolor(WHITE);
                fillroundrect(400, 360, 580, 390, 5, 5);
                setcolor(BLACK);
                outtextxy(410, 365, wBuf);
                // 更新总分
                sprintf(buf, "%.1f", currentModifyNode->stu.sum);
                MultiByteToWideChar(CP_ACP, 0, buf, -1, wBuf, 50);
                fillroundrect(400, 510, 580, 540, 5, 5);
                outtextxy(410, 515, wBuf);
                SetWorkingImage();
                putimage(LEFT_WIDTH, 0, &rightImg);
            }
        }
        // 5. 数学修改按钮
        else if (rx >= 600 && rx <= 680 && ry >= 410 && ry <= 440) {
            if (currentModifyNode == NULL) {
                MessageBox(GetHWnd(), _T("请先查询要修改的学生！"), _T("提示"), MB_OK);
                return;
            }
            if (InputBox(inputBuf, 50, _T("请输入新的数学成绩"), _T("数学修改"))) {
                float newScore = (float)_wtof(inputBuf);
                currentModifyNode->stu.math = newScore;
                currentModifyNode->stu.sum = currentModifyNode->stu.chinese + currentModifyNode->stu.math + currentModifyNode->stu.english;
                // 重绘并更新显示
                drawPage_ModifyStu();
                SetWorkingImage(&rightImg);
                char buf[50];
                wchar_t wBuf[50];
                sprintf(buf, "%.1f", currentModifyNode->stu.math);
                MultiByteToWideChar(CP_ACP, 0, buf, -1, wBuf, 50);
                setfillcolor(WHITE);
                fillroundrect(400, 410, 580, 440, 5, 5);
                setcolor(BLACK);
                outtextxy(410, 415, wBuf);
                // 更新总分
                sprintf(buf, "%.1f", currentModifyNode->stu.sum);
                MultiByteToWideChar(CP_ACP, 0, buf, -1, wBuf, 50);
                fillroundrect(400, 510, 580, 540, 5, 5);
                outtextxy(410, 515, wBuf);
                SetWorkingImage();
                putimage(LEFT_WIDTH, 0, &rightImg);
            }
        }
        // 6. 英语修改按钮
        else if (rx >= 600 && rx <= 680 && ry >= 460 && ry <= 490) {
            if (currentModifyNode == NULL) {
                MessageBox(GetHWnd(), _T("请先查询要修改的学生！"), _T("提示"), MB_OK);
                return;
            }
            if (InputBox(inputBuf, 50, _T("请输入新的英语成绩"), _T("英语修改"))) {
                float newScore = (float)_wtof(inputBuf);
                currentModifyNode->stu.english = newScore;
                currentModifyNode->stu.sum = currentModifyNode->stu.chinese + currentModifyNode->stu.math + currentModifyNode->stu.english;
                // 重绘并更新显示
                drawPage_ModifyStu();
                SetWorkingImage(&rightImg);
                char buf[50];
                wchar_t wBuf[50];
                sprintf(buf, "%.1f", currentModifyNode->stu.english);
                MultiByteToWideChar(CP_ACP, 0, buf, -1, wBuf, 50);
                setfillcolor(WHITE);
                fillroundrect(400, 460, 580, 490, 5, 5);
                setcolor(BLACK);
                outtextxy(410, 465, wBuf);
                // 更新总分
                sprintf(buf, "%.1f", currentModifyNode->stu.sum);
                MultiByteToWideChar(CP_ACP, 0, buf, -1, wBuf, 50);
                fillroundrect(400, 510, 580, 540, 5, 5);
                outtextxy(410, 515, wBuf);
                SetWorkingImage();
                putimage(LEFT_WIDTH, 0, &rightImg);
            }
        }
        // 7. 保存按钮
        else if (rx >= 600 && rx <= 680 && ry >= 510 && ry <= 540) {
            if (currentModifyNode == NULL) {
                MessageBox(GetHWnd(), _T("请先查询要修改的学生！"), _T("提示"), MB_OK);
                return;
            }
            MessageBox(GetHWnd(), _T("学生信息修改已保存！"), _T("提示"), MB_OK);
            // 重置当前修改节点
            currentModifyNode = NULL;
            // 重绘页面
            drawPage_ModifyStu();
        }
    }
}

//新增查询页面的点击处理函数
void handleSearchPageClick(int rx, int ry) {
    if (currentNav == 4) { // 仅在查询页面生效
        TCHAR inputBuf[50] = { 0 };
        Node* foundNode = NULL;

        // 1. 以学号方式查询
        if (rx >= 200 && rx <= 400 && ry >= 130 && ry <= 170) {
            if (InputBox(inputBuf, 50, _T("请输入要查询的学号"), _T("学号查询"))) {
                unsigned long long id = _wtoll(inputBuf);
                // 遍历链表查找
                Node* p = studentList.front;
                while (p != NULL) {
                    if (p->stu.number == id) {
                        foundNode = p;
                        break;
                    }
                    p = p->next;
                }
                if (foundNode) {
                    // 重绘页面并显示查询结果
                    drawPage_SearchStu();
                    SetWorkingImage(&rightImg);
                    char buf[50];
                    wchar_t wBuf[50];

                    // 语文
                    sprintf(buf, "%.1f", foundNode->stu.chinese);
                    MultiByteToWideChar(CP_ACP, 0, buf, -1, wBuf, 50);
                    setfillcolor(WHITE);
                    fillroundrect(350, 260, 550, 290, 5, 5);
                    setcolor(BLACK);
                    outtextxy(360, 265, wBuf);

                    // 数学
                    sprintf(buf, "%.1f", foundNode->stu.math);
                    MultiByteToWideChar(CP_ACP, 0, buf, -1, wBuf, 50);
                    fillroundrect(350, 310, 550, 340, 5, 5);
                    outtextxy(360, 315, wBuf);

                    // 英语
                    sprintf(buf, "%.1f", foundNode->stu.english);
                    MultiByteToWideChar(CP_ACP, 0, buf, -1, wBuf, 50);
                    fillroundrect(350, 360, 550, 390, 5, 5);
                    outtextxy(360, 365, wBuf);

                    // 总分
                    sprintf(buf, "%.1f", foundNode->stu.sum);
                    MultiByteToWideChar(CP_ACP, 0, buf, -1, wBuf, 50);
                    fillroundrect(350, 410, 550, 440, 5, 5);
                    outtextxy(360, 415, wBuf);

                    SetWorkingImage();
                    putimage(LEFT_WIDTH, 0, &rightImg);
                }
                else {
                    MessageBox(GetHWnd(), _T("未找到该学号的学生！"), _T("提示"), MB_OK);
                }
            }
        }
        // 2. 以姓名方式查询
        else if (rx >= 450 && rx <= 650 && ry >= 130 && ry <= 170) {
            if (InputBox(inputBuf, 50, _T("请输入要查询的姓名"), _T("姓名查询"))) {
                char nameBuf[50];
                WideCharToMultiByte(CP_ACP, 0, inputBuf, -1, nameBuf, 50, NULL, NULL);
                // 遍历链表查找
                Node* p = studentList.front;
                while (p != NULL) {
                    if (strcmp(p->stu.name, nameBuf) == 0) {
                        foundNode = p;
                        break;
                    }
                    p = p->next;
                }
                if (foundNode) {
                    // 重绘页面并显示查询结果
                    drawPage_SearchStu();
                    SetWorkingImage(&rightImg);
                    char buf[50];
                    wchar_t wBuf[50];

                    // 语文
                    sprintf(buf, "%.1f", foundNode->stu.chinese);
                    MultiByteToWideChar(CP_ACP, 0, buf, -1, wBuf, 50);
                    setfillcolor(WHITE);
                    fillroundrect(350, 260, 550, 290, 5, 5);
                    setcolor(BLACK);
                    outtextxy(360, 265, wBuf);

                    // 数学
                    sprintf(buf, "%.1f", foundNode->stu.math);
                    MultiByteToWideChar(CP_ACP, 0, buf, -1, wBuf, 50);
                    fillroundrect(350, 310, 550, 340, 5, 5);
                    outtextxy(360, 315, wBuf);

                    // 英语
                    sprintf(buf, "%.1f", foundNode->stu.english);
                    MultiByteToWideChar(CP_ACP, 0, buf, -1, wBuf, 50);
                    fillroundrect(350, 360, 550, 390, 5, 5);
                    outtextxy(360, 365, wBuf);

                    // 总分
                    sprintf(buf, "%.1f", foundNode->stu.sum);
                    MultiByteToWideChar(CP_ACP, 0, buf, -1, wBuf, 50);
                    fillroundrect(350, 410, 550, 440, 5, 5);
                    outtextxy(360, 415, wBuf);

                    SetWorkingImage();
                    putimage(LEFT_WIDTH, 0, &rightImg);
                }
                else {
                    MessageBox(GetHWnd(), _T("未找到该姓名的学生！"), _T("提示"), MB_OK);
                }
            }
        }
    }
}

//新增输出页面的点击处理函数
void handleOutputPageClick(int rx, int ry) {
    if (currentNav == 5) { // 仅在输出页面生效
        int totalPage = (studentList.size + PAGE_SIZE - 1) / PAGE_SIZE;

        // 上一页按钮
        if (rx >= 200 && rx <= 350 && ry >= 550 && ry <= 590) {
            if (currentPage > 1) {
                currentPage--;
                drawPage_OutputStu(); // 重绘页面，显示上一页数据
            }
            else {
                MessageBox(GetHWnd(), _T("已经是第一页了！"), _T("提示"), MB_OK);
            }
        }
        // 下一页按钮
        else if (rx >= 550 && rx <= 700 && ry >= 550 && ry <= 590) {
            if (currentPage < totalPage) {
                currentPage++;
                drawPage_OutputStu(); // 重绘页面，显示下一页数据
            }
            else {
                MessageBox(GetHWnd(), _T("已经是最后一页了！"), _T("提示"), MB_OK);
            }
        }
    }
}
                
        
List studentList;
// 主函数
int main() {
    initgraph(WIDTH, HEIGHT);
    // 让图形窗口置顶，避免被控制台挡住
    HWND hwnd = GetHWnd();
    SetForegroundWindow(hwnd);
    List studentList;
    studentList.front = NULL;
    studentList.size = 0;
    readStudentHuman(&studentList);
    drawLeftNav();
    drawRightContent();
    MOUSEMSG m;
    while (1) {
        m = GetMouseMsg();
        if (m.uMsg == WM_LBUTTONDOWN) {
            // 点击左侧导航
            if (m.x >= 0 && m.x <= LEFT_WIDTH) {
                for (int i = 0; i < 7; i++) {
                    if (m.x >= navButtons[i].x && m.x <= navButtons[i].x + 120 &&
                        m.y >= navButtons[i].y && m.y <= navButtons[i].y + 20) {
                        // 更新选中状态
                        for (int j = 0; j < 7; j++) navButtons[j].isSelected = 0;
                        navButtons[i].isSelected = 1;
                        currentNav = i;
                        drawLeftNav();
                        drawRightContent();
                        break;
                    }
                }
            }
            // 点击右侧内容区
            else {
                int rx = m.x - LEFT_WIDTH;
                int ry = m.y;
                if (currentNav == 1) {
                    handleRightClick(rx, ry); // 增加页面处理
                }
                else if (currentNav == 2) {
                    handleDeletePageClick(rx, ry); // 删除页面处理
                }
                else if (currentNav == 3) {
                    handleModifyPageClick(rx, ry); // 修改页面处理
                }
                else if (currentNav == 4) {
                    handleSearchPageClick(rx, ry); // 查询页面处理
                }
                else if (currentNav == 5) {
                    handleOutputPageClick(rx, ry); // 输出页面处理
                }
                
            }
        }
    }

    closegraph();
    return 0;
}


static Node* CreateNode()
{
    //创建节点
    Node* node = (Node*)malloc(sizeof(Node));
    if (!node)
    {
        printf("malloc failed\n");
        return NULL;
    }
    node->stu.sum = 0;
    node->next = NULL;
    return node;
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
        if (!node)
            break;
        if (6 != fscanf(fp, "%llu %s %f %f %f %f\n", &node->stu.number, node->stu.name,
            &node->stu.chinese, &node->stu.math, &node->stu.english, &node->stu.sum))
        {
            free(node);
            break;
        }
        //插入链表
        node->next = list->front;
        list->front = node;
        list->size++;
    }
}

// 添加学生到链表（重命名后）
void addStudentToList(List* list, Student stu) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        MessageBox(GetHWnd(), _T("内存分配失败，添加学生失败！"), _T("错误"), MB_OK | MB_ICONERROR);
        return;
    }
    newNode->stu = stu;
    newNode->next = list->front;
    list->front = newNode;
    list->size++;
}

// 保存学生信息到文件
void saveStudentsToFile(List* list) {
    FILE* fp = fopen("students.txt", "w");
    if (!fp) {
        MessageBox(GetHWnd(), _T("保存文件失败！"), _T("错误"), MB_OK | MB_ICONERROR);
        return;
    }
    Node* p = list->front;
    while (p != NULL) {
        fprintf(fp, "%llu %s %.1f %.1f %.1f %.1f\n",
            p->stu.number, p->stu.name,
            p->stu.chinese, p->stu.math, p->stu.english, p->stu.sum);
        p = p->next;
    }
    fclose(fp);
}