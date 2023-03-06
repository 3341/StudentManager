#include <stdio.h> 
#include <io.h>
#include <string.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int controller();
void Welcome();

struct StudentDataSet dataSet;

FILE* fp;

int main() {
	Welcome();
	int isSucceed = 0;
	do {
		isSucceed = login();
	} while(!isSucceed)
	return 0;
}


void Welcome()// 欢迎界面函数 
{
 system("title 程序设计课程设计"); //设置会话的窗口标题为“程序设计课程设计”
 system("color F4");  //设置背景色为亮白色，字体颜色为红色
 system("cls");	//清屏
 printf("\n\n\t\t|----------------------------------------|\n");
 printf("\t\t|----------------------------------------|\n");
 printf("\t\t|     《程序设计》课程设计             |\n");
 printf("\t\t|         ……………………………       |\n");
 printf("\t\t|----------------------------------------|\n");
 printf("\t\t|----------------------------------------|\n");
 printf("\n\t\t		……");
 printf("\n\t\t         ……\n");
 printf("\n\t\t         ……\n");
 printf("\n\t\t         ……\n");
 printf("\n\t\t         ……\n"); 
 printf("\n\t\t\t 	……\n");
 }
 
 void openFile(){
 	fp = fopen("student.txt","rw");
 }

 void loadList(){
    dataSet = listAllStudents();
 }
 
void login(){

    printf("Please login :\n");
    printf("Account>>");
    char account[];
    scanf("%s",account);

	for(int i=0;i<dataSet.size;i++) {
        struct Student stu = dataSet.datas[i];
        
        int res = strcmp(account,stu.id)
        if (res == 0)
        {
            printf("\nPassword>>");
            char pwd[];
            scanf("%s",pwd);
            if (strcmp(pwd,stu.password) == 0)
            {
                printf("Login Successful");
                controller();
            }
            
        }    
    }

    printf("Your Account not found");
}

int controller(){
	
}