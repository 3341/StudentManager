#ifndef _DATA_H
#define _DATA_H

#include <stdio.h>

//extern FILE *fp ; //全局文件指针


extern const char file_name[] ;
extern const char format[] ;
extern const char titleArray[][20];
extern const char emptyArray[6][20];
extern const char subjectName[][20];

struct Student {
	char name[19];
	char pwd[20];
	char id[20];
	int mathScore;
	int englishScore;
	int isAdmin; //注意，这个永远在文件里不能被设置成1，文件也不应该保存这个字段
	int isNotFound; //无效的Student 
};

struct Position {
	int x;
	int y;
};

typedef struct Position Position;


struct StudentDataSet {
	int length;
	struct Student datas[100];
};

extern struct StudentDataSet dataSet ; //全局数据

#endif
