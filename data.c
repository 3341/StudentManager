#include "data.h"
#include <stdio.h>
#include <string.h>

//FILE *fp = NULL;
struct StudentDataSet dataSet ; 

const char file_name[]  = "student.txt";
const char format[] = "%s %s %s %d %d\n";
const char titleArray[][20]={"学号","姓名","高数成绩","英语成绩","平均成绩","总成绩"};
const char emptyArray[6][20]={};
const char subjectName[][20] = {"高数","英语"};
