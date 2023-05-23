#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"


void writeStudent(FILE *fp,struct Student stu) {
	fprintf(fp,format,stu.name,stu.pwd,stu.id,stu.mathScore,stu.englishScore);
}

extern void showCenterText(char text[],int y);



void writeDataToFile() {
	FILE *fp = fopen(file_name,"wt");
	for(int i=0;i<dataSet.length;i++){
		if(dataSet.datas[i].isAdmin){
			//TODO
		} else writeStudent(fp,dataSet.datas[i]);
	}
	
	fflush(fp);
}


void readDeleteStudent(struct Student stu,int index) {
	for(int i=index;i<dataSet.length-1;i++){
		dataSet.datas[i] = dataSet.datas[i+1];
	}
	dataSet.length--;
	writeDataToFile();
}

void readAllStudentFromFile() {
	FILE *fp = fopen(file_name,"r");
	int code = 0;
	do{
		struct Student stu = {};
		code = fscanf(fp,format,stu.name,stu.pwd,stu.id,&(stu.mathScore),&(stu.englishScore));
		if(code != EOF){
			dataSet.datas[dataSet.length++]=stu;
		}
	}while(code != EOF);
	
	//添加管理员账户
	//	struct Student admin = {"admin","01","0",0,0,1,0};
	//	dataSet.datas[dataSet.length++] = admin;
}


void fm_Welcome(){        //欢迎封面
	printf ("\t     -------------------******************学生管理系统*********************--------------------\n\n");
	printf ("\t --------------------****************账号只允许由12位数字组成*******************-------------------\n");
	printf ("\n\t\t\t\t\t欢迎使用学生管理系统，请先登录！\n");
	printf("\n");
	printf("\n");
	printf("\t\t                   (^ - ^)                            (^ - ^) \n");
	printf("\t\t                   (@^o^@) 欢迎使用学生信息管理系统   (⌒:⌒)\n");
	printf("\t\t                   (~):(~)                            (~)v(~) \n");
	printf("\t\t                   *****************************************\n");
	printf("\t\t  *           *    *                                       *  *           *    \n");
	printf("\t\t  * *       * *    *                菜   单                *  * *       * *    \n");
	printf("\t\t  *   *   *   *    *                                       *  *   *   *   *    \n");
	printf("\t\t  *     *     *    *                \033[5;32;40m[1]：登录\033[0m              *  *     *     *    \n");
	printf("\t\t  *     *     *    *                                       *  *     *     *    \n");
	printf("\t\t  *     *     *    *            专业：软件工程             *  *     *     *    \n");
	printf("\t\t  *     *     *    *                                       *  *     *     *    \n");
	printf("\t\t  *     *     *    *            班级：222                  *  *     *     *    \n");
	printf("\t\t  *     *     *    *                                       *  *     *     *    \n");
	printf("\t\t  *     *     *    *	        学号：202212900201         *  *     *     *    \n");
	printf("\t\t  *     *     *    *                                       *  *     *     *    \n");
	printf("\t\t  *     *     *    *            姓名：包远钦、陈佳豪       *  *     *     *    \n");
	printf("\t\t   *    *    *     *                                       *   *    *    *     \n");
	printf("\t\t    *   *   *      *            时间：2023年3月8日         *    *   *   *      \n");
	printf("\t\t      * * *        *****************************************      * * *        \n");
	printf("\n\t\t                                请输入您的操作！");
}


void fm_MessageManager(){    //成绩信息封面
	printf ("\n\n\n");
	printf ("\t  -------------------******************学生成绩信息菜单*********************--------------------\n\n\n");
	printf ("\t\t\t     * [1]  录入学生成绩             * [2] 删除学生成绩\n\n");
	printf ("\t\t\t     * [3]  修改学生信息             * [4] 以学号查询学生成绩\n\n");
	printf ("\t\t\t     * [5]  以姓名查询学生成绩       * [6] 学生成绩报告\n\n");
	printf ("\t\t\t     * [7]  学生信息显示             * [8] 清空数据库\n\n");
	printf ("\t\t\t     * [9]  总成绩排名               * [0] 退出程序\n\n");
	printf ("\t  -------------------**********************欢迎使用*************************--------------------\n");
//	printf ("请您输入菜单上的按键--\n");
}



extern void writeDataToFile();

/**
 * @brief 通过学号查找学生
 * 
 * @param id 学号
 * 
 * @return 结构体指针，因为可能找不到，所以有可能是null，记得做空指针判断
 * @deprecated 方法已弃用
 */
struct Student searchStudentById(char id[]) {
	for(int i=0;i<=dataSet.length;i++){
		struct Student stu = dataSet.datas[i];
		//		printf("%s = %s ? %d\n",stu.id,id,strcmp(stu.id,id));
		if(strcmp(stu.id,id)==0){
			//			printf("Found : %s",stu.name);
			return stu;
		}
	}
	
	struct Student re = {"","","",0,0,0,1};
	return re;
};

void addStudent(struct Student stu) {
	dataSet.datas[dataSet.length++] = stu;
	writeDataToFile();
}

extern void inputFieldForChars(char text[],char content[],int startY);
extern void showStudentsInfo(struct Student stu[],int size,int startY);
extern int getCurrentIndexY();
extern void Menu();

void searchStudentByStudentId() {
	system("cls");
	showCenterText("学号查找学生",3);
	char id[20] = {};
	inputFieldForChars("学号",id,5);
	
	struct StudentDataSet result = {};
	
	for(int i=0;i<dataSet.length;i++){
		struct Student st = dataSet.datas[i];
		if(strcmp(st.id,id)==0){
			result.datas[result.length++] = st;
		}
	}
	
	if(result.length == 0){
		showCenterText("[1]没找到,扣1重找",getCurrentIndexY()+2);
		getchar();
	} else {
		showStudentsInfo(result.datas,result.length,getCurrentIndexY()+2);
	}
	
	showCenterText("[0]返回",getCurrentIndexY()+2);
	
	select:
	char c = getch();
	if(c == '0'){
		Menu();
	} else if(result.length == 0) {
		searchStudentByStudentId();
	} else {
		goto select;
	}
}

/**
 * @brief 获取挂科学生
 * 
 * @return 数据集合
 */
struct StudentDataSet getGuaKe(int subject) {
	
	struct StudentDataSet result = {};
	for(int i=0;i<dataSet.length;i++){
		struct Student st = dataSet.datas[i];
		int score = 0;
		if(subject == 0){
			score = st.mathScore;
		} else {
			score = st.englishScore;
		}
		if(score<60){
			result.datas[result.length++] = st;
		}
	}
	
	return result;
};

/**
 * @brief 获得学生的总分
 * 
 * @param stu 
 * 
 * @return 
 */
int getSumScore(struct Student stu) {
	return stu.mathScore + stu.englishScore;
}

/**
 * @brief 对总成绩进行排序
 */
void sortAll(int isUpXU) {
	if(isUpXU == 1){ //升序
		for(int i=0;i<dataSet.length-1;i++){
			int t = i;
			for(int j=i+1;j<dataSet.length;j++){
				if(getSumScore( dataSet.datas[j]) < getSumScore( dataSet.datas[t])){
					t = j;
				}//TODO
			}
			if(i != t){
				struct Student temp = dataSet.datas[i];
				dataSet.datas[i] = dataSet.datas[t];
				dataSet.datas[t] = temp;
			}
			//TODO
		}
	}else{  //降序
		for(int i=0;i<dataSet.length-1;i++){
			int t = i;
			for(int j=i+1;j<dataSet.length;j++){
				if(getSumScore( dataSet.datas[j]) > getSumScore( dataSet.datas[t])){
					t = j;
				}//TODO
			}
			if(i != t){
				struct Student temp = dataSet.datas[i];
				dataSet.datas[i] = dataSet.datas[t];
				dataSet.datas[t] = temp;
			}
		}
	}
}

/**
 * @brief 排序数据
 * 
 * @param isUpXU 是否是升序
 */
void sortData(int subject,int isUpXU) {
	int i,j;
	if(subject == 0) {  //高数排序
		if(isUpXU == 1){ //升序
			for(int i=0;i<dataSet.length-1;i++){
				int t = i;
				for(int j=i+1;j<dataSet.length;j++){
					if(dataSet.datas[j].mathScore < dataSet.datas[t].mathScore){
						t = j;
					}//TODO
				}
				if(i != t){
					struct Student temp = dataSet.datas[i];
					dataSet.datas[i] = dataSet.datas[t];
					dataSet.datas[t] = temp;
				}
				//TODO
			}
		}else{  //降序
			for(int i=0;i<dataSet.length-1;i++){
				int t = i;
				for(int j=i+1;j<dataSet.length;j++){
					if(dataSet.datas[j].mathScore > dataSet.datas[t].mathScore){
						t = j;
					}//TODO
				}
				if(i != t){
					struct Student temp = dataSet.datas[i];
					dataSet.datas[i] = dataSet.datas[t];
					dataSet.datas[t] = temp;
				}
			}
		}
	}else if(subject == 1) {  //英语排序
		if(isUpXU == 1){ //升序
			for(int i=0;i<dataSet.length-1;i++){
				int t = i;
				for(int j=i+1;j<dataSet.length;j++){
					if(dataSet.datas[j].englishScore < dataSet.datas[t].englishScore){
						t = j;
					}//TODO
				}
				if(i != t){
					struct Student temp = dataSet.datas[i];
					dataSet.datas[i] = dataSet.datas[t];
					dataSet.datas[t] = temp;
				}
			}
		}else{  //降序
			for(int i=0;i<dataSet.length-1;i++){
				int t = i;
				for(int j=i+1;j<dataSet.length;j++){
					if(dataSet.datas[j].englishScore > dataSet.datas[t].englishScore){
						t = j;
					}//TODO
				}
				if(i != t){
					struct Student temp = dataSet.datas[i];
					dataSet.datas[i] = dataSet.datas[t];
					dataSet.datas[t] = temp;
				}
			}
		}
	}//TODO
}
