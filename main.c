#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
//#include <graphics.h>

#include "data.h"

extern void writeStudent(FILE *fp,struct Student stu);
extern void writeDataToFile() ;
extern void readDeleteStudent(struct Student stu,int index);
extern void readAllStudentFromFile();
extern void sortData(int subject,int isUpXU);
extern struct Student searchStudentById(char id[]);
extern void addStudent(struct Student stu);
extern void fm_Welcome();
extern void fm_MessageManager();
extern void searchStudentByStudentId();
extern void sortAll(int);
extern struct StudentDataSet getGuaKe(int);


void Menu();


/**
 * @brief 光标定位函数
 * 
 * @param x 
 * @param y 
 */
void gotoxy(int x,int y) {
	COORD p;//定义结构体变量p
	HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);//获取当前函数句柄
	p.X=x;p.Y=y;//将光标的目标移动位置传递给结构体
	SetConsoleCursorPosition(handle,p);//移动光标
}

/**
 * @brief 获取窗口中心坐标
 * 
 * @return 
 */
struct Position getWindowCenterPos() {
	HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);//获取当前函数句柄
	CONSOLE_SCREEN_BUFFER_INFO info ;
	GetConsoleScreenBufferInfo(handle,&info);
	int width = info.dwMaximumWindowSize.X;
	int height = info.dwMaximumWindowSize.Y;
	struct Position pos = {width/2,height/2};
	return pos;
};



/**
 * @brief 获取当前光标信息
 * 
 * @return 
 */
Position getCurrentIndexPosition() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coordScreen = {0, 0}; //光标位置
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	
	Position pos = {};
	
	if (GetConsoleScreenBufferInfo(hConsole, &csbi)){
		pos.x = csbi.dwCursorPosition.X;
		pos.y = csbi.dwCursorPosition.Y;
		//		printf("光标坐标:(%d,%d)\n",  csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y);
		return pos;
	}
	
}

/**
 * @brief 获取当前光标所属列
 * 
 * @return 
 */
int getCurrentIndexY() {
	Position pos = getCurrentIndexPosition();
	return pos.y;
}

/**
 * @brief 画一个框框，UI框架的基本重要函数
 * 
 * @param drawDir -1 仅绘制左边竖线 1右边绘制竖线 0完整绘制 2仅绘制竖线 3绘制竖线和顶部 4绘制竖线和底部
 * @param height 
 * @param startX 
 * @param startY 
 * @param width 注意实际宽度是传入的两倍，因为打了个空格。。。
 */
void paintWindow(int startX,int startY,int width,int height,int drawDir) {
	int i=0;
	
	if(drawDir==0 || drawDir==3){
		gotoxy(startX,startY); 
		printf("┏"); //左右各一个故-2
		for(i=0;i<width-2;i++)  {
			printf("━ ");
		}
		
		printf("┓");
	}
	
	
	if(drawDir==0||drawDir==-1||drawDir==2){
		for(i=1;i<=height-2;i++)  {
			gotoxy(startX,startY+i);
			printf("┃");    
		}
	}
	
	
	if(drawDir==0||drawDir==1||drawDir==2){
		for(i=1;i<=height-2;i++) {
			gotoxy(startX+width*2-3,startY+i);
			printf("┃");   
		}
	}
	
	if(drawDir==0 || drawDir == 4){
		gotoxy(startX,startY+height-1);
		printf("┗");
		for(i=0;i<width-2;i++) {
			printf("━ ");	
		}
		printf("┛");
	}
	
//	gotoxy(startX,startX+height);	
}

/**
 * @brief 在文本的水平方向居中显示
 * 
 * @param text 
 * @param y 显示的目标行号
 * 
 * @return 
 */
void showCenterText(char text[],int y) {
	struct Position cen = getWindowCenterPos();
	int startX = cen.x - strlen(text)/2;
	gotoxy(startX,y);
	printf("%s",text);
}

/**
 * @brief 同上，但手动填写字符串长度，用于看不见的字体也被算成字数了
 * 
 * @param text 字符串
 * @param len 长度
 * @param y 起始y
 */
void showCenterTextOffset(char text[],int y,int len) {
	struct Position cen = getWindowCenterPos();
	int startX = cen.x - len/2;
	gotoxy(startX,y);
	printf("%s",text);
}


/**
 * @brief 用于接收选项输入
 * 
 * @param allowRetry 是否允许重试
 * @param ranageEnd 选择数字范围
 * @param ranageStart 选择数字范围，不能＜0
 * 
 * @return 为-1则是接收失败
 */
int receiveInput(int ranageStart,int ranageEnd,int allowRetry) {
	printf("\nPlease Select>>");
	int code;
	if(scanf("%d",&code) != 1) {
		//Error
		if(allowRetry){
			return receiveInput(ranageStart,ranageEnd,allowRetry);
		} else {
			return -1;
		}
	} else return code;
	//	int code = -1;
	//	to:
	//	char c = getch();
	//	if(c >= '0' && c<= '9'){
	//		int num = c - '0';
	//		if(num >= ranageStart && num <= ranageEnd){
	//			return num;
	//		} 
	//	}
	//	if(allowRetry){
	//		goto to;
	//	} else return -1;
}

void showTableWithColorField(char text[][20], int size,int startY,int linePram,int colorField) {
	int columnWidth = 20;
	int numColumns = size;
	Position cen = getWindowCenterPos();
	int totalWidth = columnWidth * numColumns / 2;
	int startX = cen.x - totalWidth;
	//	int startY = 5;
	int height = 3;
	
	// Draw table border
	int li = 0;
	switch (linePram) {
	case -1:
		li = 4;
		break;
	case 1:
		li = 3;
		break;
	default:
		li = 2;
		break;
	}
	paintWindow(startX, startY, totalWidth, height, li);
	
	// Draw column dividers
	for (int i = 0; i < numColumns; i++) {
		paintWindow(startX + columnWidth * i, startY, 3, height, -1);
	}
	
	// Draw table contents
	for (int j = 0; j < numColumns; j++) {
		gotoxy(startX + j * columnWidth + 2, startY + 1);
		if(j +1 == colorField){
			printf("\033[1;36;40m");
		}
		printf("%s", text[j]);
		if(j +1 == colorField){
			printf("\033[0m");
		}
	}
}

/**
 * @brief 显示表格,UI框架的重要函数
 * 
 * @param size 有多少个格子
 * @param text 每个格子的文字
 * @param linePram -1最后一行 1第一行 0中间行
 */
void showTable(char text[][20], int size,int startY,int linePram) {
	showTableWithColorField(text,size,startY,linePram,0);
}

/**
 * @brief 录入学生信息
 */
void Input() {
	system("cls");
	showCenterText("学生成绩录入",3);
	char arr[][20]={"学号","姓名","高数成绩","英语成绩","平均成绩","总成绩"};
	showTable(arr,6,5,1);
	char arra[6][20]={};
	showTable(arra,6,6,-1);
//	showTable(arra,6,7,-1);
	struct Student stu = {};
	int inputFieldCode = 0;
	input:
	char input[20];
	struct Position pop = {};
	getTablePos(inputFieldCode+1,6,6,&pop);
	gotoxy(pop.x,pop.y);
	
	switch (inputFieldCode) {
	case 0:
		t1:
		scanf("%s",stu.id);
		int len = strlen(stu.id);
		int exists = 0;
		for(int i=0;i<dataSet.length;i++){
			struct Student st = dataSet.datas[i];
			if(strcmp(st.id,stu.id) == 0){
				exists = 1;
			}
		}
		int isNum = 1;
		for(int i=0;i<len;i++){
			if(stu.id[i]<'0'||stu.id[i]>'9'){
				isNum=0;
			}
		}
		if(len<=2||len>12 || exists || !isNum){
			showCenterText("输入错误：必须为3-12位数字，且学号不能重复",getCurrentIndexY()+3);
			gotoxy(pop.x,pop.y);
			printf("                ");
			gotoxy(pop.x,pop.y);
			goto t1;
		}
		break;
		
	case 1:
		t2:
		scanf("%s",stu.name);
		int len1 = strlen(stu.name);
		if(len1<=0||len1>12){
			showCenterText("输入错误：必须为1-12位字符",getCurrentIndexY()+3);
			gotoxy(pop.x,pop.y);
			printf("          ");
			gotoxy(pop.x,pop.y);
			goto t2;
		}
		break;
				
	case 2:
		scanf("%d",&(stu.mathScore));
		
		break;
		
	case 3:
		scanf("%d",&(stu.englishScore));
		
		break;
		
	}
	
	inputFieldCode++;
	
	
	if(inputFieldCode <= 3){
		goto input;
	} else {
		float sum = stu.mathScore + stu.englishScore;
		getTablePos(5,6,6,&pop);
		gotoxy(pop.x,pop.y);
		printf("%.2f",sum/2);
		getTablePos(6,6,6,&pop);
		gotoxy(pop.x,pop.y);
		printf("%.2f",sum);
		
//		gotoxy(50,yOffset+6);
		//Gengerate Password
		stu.pwd[1] = stu.id[11];
		stu.pwd[0] = stu.id[10];
		stu.pwd[2] = '\0';
		addStudent(stu);
		writeDataToFile();
		
		Position pp = getCurrentIndexPosition();
		showCenterText("写入成功，任意键返回",pp.y+2);
//		printf("写入成功，任意键返回\n");
		getchar();
		getchar();
		Menu();
	}
}



/**
 * 显示学生数组信息，但是某个字段高亮
 * @param highField 需要高亮的字段
 */
void showStudentsInfoWithHightLight(struct Student stus[],int size,int startY,int highField) {
	showTableWithColorField(titleArray,6,startY,1,highField);
	for(int i=0;i<size;i++){
		struct Student st = stus[i];
		char data[6][20] = {};
		strcpy(data[0],st.id);
		strcpy(data[1],st.name);
		sprintf(data[2],"%d",st.mathScore);
		sprintf(data[3],"%d",st.englishScore);
		float sum = st.mathScore + st.englishScore;
		sprintf(data[4],"%.2f",sum/2);
		sprintf(data[5],"%.2f",sum);
		showTableWithColorField(data,6,startY+i+1,i==size-1?-1:0,highField);
	}
}

/**
 * @brief 显示学生数组信息，以表格输出
 * 
 * @param size 数组大小
 * @param startY 开始的行数
 * 
 * @return 
 */
void showStudentsInfo(struct Student stu[],int size,int startY) {
	showStudentsInfoWithHightLight(stu,size,startY,0);
}


/**
 * @brief 显示单个学生信息
 * 
 * @param st 
 * @param startY 
 */
void showStudentInfo(struct Student st,int startY) {
	struct Student stt[] = {st};
	showStudentsInfo(stt,1,startY);
}


/**
 * @brief 获取表格的每个列的坐标，因为每一列是固定大小的所以可以计算
 * 
 * @param count 第几列
 * @param pos 位置指针，用来返回位置
 * @param size 一共有几列
 * @param startY 开始行数
 */
void getTablePos(int count,int size,int startY,struct Position *pos) {
	int columnWidth = 20;
//	int numColumns = size;
	Position cen = getWindowCenterPos();
	int totalWidth = columnWidth * size / 2;
	int startX = cen.x - totalWidth;
	//	int startY = 5;
	int height = 3;
//	struct Position pos = {};
	pos->x=startX + (count-1) * columnWidth + 2, pos->y=startY + 1;
}

/**
 * @brief 列出所有学生
 */
void StudentListShow() {
	system("cls");
	showCenterText("学生列表",3);
	showStudentsInfo(dataSet.datas,dataSet.length,5);
	showCenterText("[0]返回",getCurrentIndexY()+3);
	while(getch() != '0');
	Menu();
}

/**
 * @brief 用方框来输入一个字段
 * 
 * @param content 目标输入值，输入会存到这里
 * @param startY 行数
 * @param text 字段名
 * 
 * @return 
 */
void inputFieldForChars(char text[],char content[],int startY) {
	startY-=2;
	int yOffset = startY;
	Position cen = getWindowCenterPos();
	int width = 20;
	int startX = cen.x-width;
	paintWindow(startX,yOffset+2,width,3,0);
	gotoxy(startX+3,yOffset+3);
	printf("%s",text);
	paintWindow(startX,yOffset+2,5,1,1);
	gotoxy(startX+10,yOffset+3);
	
	scanf("%s",content);
}



/**
 * @brief 旧版修改功能的内部实现（已废弃）
 * 
 * @param st 学生信息指针
 * @param subject 科目：0是高数 1是英语
 * @deprecated
 */
void ModifyImpl(struct Student *st, int subject) {
	system("cls");
	showCenterText("修改学生成绩",3);
	showTable(titleArray,6,5,1);
	char data[6][20] = {};
	strcpy(data[0],st->id);
	strcpy(data[1],st->name);
	if(subject!=0){
		sprintf(data[2],"%d",st->mathScore);
	}
	if(subject!=1){
		sprintf(data[3],"%d",st->englishScore);
	}
	float sum = st->mathScore + st->englishScore;
	sprintf(data[4],"%.2f",sum/2);
	sprintf(data[5],"%.2f",sum);
	showTable(data,6,6,-1);
	
	Position pos = {};
	getTablePos(subject == 0? 3 : 4,6,6,&pos);
	gotoxy(pos.x,pos.y);
	int score = 0;
	scanf("%d",&score);
	if(subject == 0){
		st->mathScore = score;
	} else {
		st->englishScore = score;
	}
}


/**
 * @brief 修改功能的内部实现
 * 
 * @param st 学生信息指针
 * @param field 要修改的字段列数，范围1-4，后面的是计算出来的不可修改
 */
void ModifyImplc(struct Student *st, int field) {
	system("cls");
	showCenterText("修改学生成绩",3);
	showTable(titleArray,6,5,1);
	char data[6][20] = {};
	if(field!=1){
		strcpy(data[0],st->id);
	}
	if(field!=2){
		strcpy(data[1],st->name);
	}
	
	if(field!=3){
		sprintf(data[2],"%d",st->mathScore);
	}
	if(field!=4){
		sprintf(data[3],"%d",st->englishScore);
	}
	float sum = st->mathScore + st->englishScore;
	sprintf(data[4],"%.2f",sum/2);
	sprintf(data[5],"%.2f",sum);
	showTable(data,6,6,-1);
	
	Position pos = {};
	getTablePos(field,6,6,&pos);
	gotoxy(pos.x,pos.y);
	switch (field) {
	case 1:
		char id[20];
		scanf("%s",id);
		int exists;
		for(int i=0;i<=dataSet.length;i++){
			struct Student stt = dataSet.datas[i];
			if(strcmp(stt.id,id)==0){
				exists = 1;
			}
		}
		if(exists){
			showCenterText("错误：学号已存在 [0] 返回",getCurrentIndexY()+3);
			while(getch()!='0');
			return;
		} else {
			strcpy(st->id,id);
		}
		break;
	case 2:
		scanf("%s",st->name);
		break;
		
	case 3:
		scanf("%d",&(st->mathScore));
		break;
		
	case 4:
		scanf("%d",&(st->englishScore));
		break;
	}
}

/**
 * @brief 修改功能
 */
void Modify() {
	system("cls");
	showCenterText("修改学生成绩",3);
	char id[20] = {};
	inputFieldForChars("学号",id,5);
	
	for(int i=0;i<dataSet.length;i++){
		struct Student st = dataSet.datas[i];
		if(strcmp(st.id,id)==0){
			show:
			system("cls");
			showCenterText("修改学生成绩",3);
			showStudentInfo(st,5);
			showCenterText("[1]修改高数成绩",getCurrentIndexY()+2);
			showCenterText("[2]修改英语成绩",getCurrentIndexY()+1);
			showCenterText("[3]修改姓名",getCurrentIndexY()+1);
			showCenterText("[4]修改学号",getCurrentIndexY()+1);
			showCenterText("[0]返回",getCurrentIndexY()+1);
			select:
			char c = getch();
			int sel[] = {3,4,2,1};
			
			int selection = c - '0';
			if(selection>=1&&selection<=4){
				ModifyImplc(&dataSet.datas[i],sel[selection-1]);
				writeDataToFile();
				st = dataSet.datas[i];
				goto show;
			} else if(selection == 0){
				Menu();
			} else {
				goto select;
			}
			
			
		}
	}
	
	showCenterText("错误：未找到，[0] 返回",getCurrentIndexY()+2);
	while(getch()!='0');
	Menu();
}

/**
 * @brief 通过姓名查找学生
 */
void searchStudentByName() {
	system("cls");
	showCenterText("姓名查找学生",3);
	char name[20];
	inputFieldForChars("姓名",name,5);
	struct StudentDataSet result = {};
	
	for(int i=0;i<dataSet.length;i++){
		struct Student st = dataSet.datas[i];
		if(strstr(st.name,name)!=NULL){
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
 * @brief 删除学生功能
 */
void deleteStudentByStudentId() {
	system("cls");
	showCenterText("删除学生",3);
	char id[20];
	inputFieldForChars("学号",id,5);
	struct StudentDataSet result = {};
	
	int searchedIndex = -1;
	for(int i=0;i<dataSet.length;i++){
		struct Student st = dataSet.datas[i];
		if(strcmp(st.id,id)==0){
			result.datas[result.length++] = st;
			searchedIndex = i;
		}
	}
	
	if(result.length == 0){
		showCenterText("[1]没找到,扣1重找",getCurrentIndexY()+2);
		getchar();
	} else {
		showStudentsInfo(result.datas,result.length,getCurrentIndexY()+2);
		showCenterText("确认删除请在框中填入yes",getCurrentIndexY()+2);
		char yes[20];
		inputFieldForChars("删除",yes,getCurrentIndexY()+2);
		if(strcmp(yes,"yes") == 0){
			readDeleteStudent(result.datas[0],searchedIndex);
			showCenterText("删除完毕，[0]返回",getCurrentIndexY()+2);
		} else {
			showCenterText("删除撤销，[0]返回",getCurrentIndexY()+2);
		}
		while(getch()!='0');
		Menu();
	}
	
	showCenterText("[0]返回",getCurrentIndexY()+2);
	
	select:
	char c = getch();
	if(c == '0'){
		Menu();
	} else if(result.length == 0) {
		deleteStudentByStudentId();
	} else {
		goto select;
	}
}


/**
 * @brief 显示学生总成绩排名
 */
void showStudentPaiMing() {
	system("cls");
	showCenterText("总成绩排名",3);
	char titleArray[][20]={"学号","姓名","高数成绩","英语成绩","排名","总成绩"};
	showTable(titleArray,6,5,1);
	sortAll(0);
	for(int i=0;i<dataSet.length;i++){
		struct Student st = dataSet.datas[i];
		char data[6][20] = {};
		strcpy(data[0],st.id);
		strcpy(data[1],st.name);
		sprintf(data[2],"%d",st.mathScore);
		sprintf(data[3],"%d",st.englishScore);
		float sum = st.mathScore + st.englishScore;
		sprintf(data[4],"%d",i+1);
		sprintf(data[5],"%.2f",sum);
		showTable(data,6,6+i,i==dataSet.length-1?-1:0);
	}
	
	showCenterText("[0] 返回",getCurrentIndexY()+2);
	while(getch()!='0');
	Menu();
}


/**
 * @brief 显示统计信息：最大值之类的
 * 
 * @param subject 0是高数 1是英语
 */
void showStatisticInformation(int subject) {
	showCenterText("统计信息",getCurrentIndexY()+2);
	int max = 0;
	int min = 0;
	float sum = 0;
	float gua = 0;
	for(int i=0;i<dataSet.length;i++){
		struct Student stu = dataSet.datas[i];
		int score = 0;
		switch (subject) {
		case 0:
			score = stu.mathScore;
			break;
			case 1:
			score = stu.englishScore;
			break;
		}
		
		if(i == 0){
			max = score,min = score;
		}
		
		if(max < score){
			max = score;
		}
		
		if(min > score){
			min = score;
		}
		
		sum += score;
		
		if(score < 60){
			gua++;
		}
	}
	
	char title[][20] = {"最高分","最低分","平均分","挂科率"};
	showTable(title,4,getCurrentIndexY()+2,1);
	char data[][20] = {};
	sprintf(data[0],"%d",max);
	sprintf(data[1],"%d",min);
	sprintf(data[2],"%.2f",sum/dataSet.length);
	sprintf(data[3],"%.2f%%",(gua/dataSet.length)*100);
	showTable(data,4,getCurrentIndexY(),-1);
}

/**
 * @brief 显示排序结果
 * 
 * @param isUpXu 是否是升序
 * @param subject 科目信息 0高数 1英语
 */
void showSort(int subject, int isUpXu) {
	sortData(subject,isUpXu);
	showCenterText("成绩排序",getCurrentIndexY()+2);
	showStudentsInfoWithHightLight(dataSet.datas,dataSet.length,getCurrentIndexY()+2,subject?4:3);
}

void showGuaKeStudents(int subject) {
	char name[20];
	system("cls");
	sprintf(name,"%s挂科情况",subjectName[subject]);
	showCenterText(name,3);
	char title[][20] = {"挂科人数","挂科率"};
	showTable(title,2,getCurrentIndexY()+2,1);
	struct StudentDataSet set = getGuaKe(subject);
	char data[6][20] = {};
	int size = set.length;
	sprintf(data[0],"%d",size);
	//奇怪的bug，sprintf后set.length会改变，非常奇怪
	set.length = size;
	sprintf(data[1],"%.2f%%",set.length/(float)dataSet.length*100);
	showTable(data,2,getCurrentIndexY(),-1);
	
	showCenterText("挂科名单",getCurrentIndexY()+2);
	showStudentsInfoWithHightLight(set.datas,set.length,getCurrentIndexY()+2,subject?4:3);
	showCenterText("[0] 返回",getCurrentIndexY()+2);
	while(getch()!='0');
	return;
}

/**
 * @brief 统计功能内部实现
 * 
 * @param isupxu 是否升序
 * @param subject 科目
 */
void StatisticImpl(int subject,int isupxu) {
	show:
	system("cls");
	char title[20];
	sprintf(title,"\033[1;36;40m%s成绩统计\033[0m",subjectName[subject]);
	showCenterTextOffset(title,0,6);
	showStatisticInformation(subject);
	showSort(subject,isupxu);
	
	showCenterText("[左右] 切换科目",getCurrentIndexY()+2); 
	char updown[20];
	char colors[] = "\033[1;37;42m";
	sprintf(updown,"[上下] 切换%s升序\033[0m / %s降序\033[0m",isupxu?colors:"",isupxu?"":colors);
	showCenterTextOffset(updown,getCurrentIndexY()+1,12);
	showCenterText("[1]显示挂科情况",getCurrentIndexY()+1);
	showCenterText("[0]返回",getCurrentIndexY()+1);
	
	select:
	char c = getch();
	if(c == '0'){
		Menu();
	} else if(c == '1') {
		showGuaKeStudents(subject);
		goto show;
	} else if(c == -32) { //72、80、75、77 上下左右
		c=getch();
		switch (c) {
		case 72:
			StatisticImpl(subject,!isupxu);
			break;
		case 80:
			StatisticImpl(subject,!isupxu);
			break;
		case 75:
			StatisticImpl(!subject,isupxu);
			break;
			
		case 77:
			StatisticImpl(!subject,isupxu);
			break;
		}
		
		goto show;
	} else {
		goto select;
	}
}

/**
 * @brief 统计功能
 */
void Statistic() {
	int subject = 0;
	int isup = 0;
	
	
	StatisticImpl(subject,isup);
}

/**
 * @brief 清空数据库功能
 */
void clearDatas() {
	system("cls");
	showCenterText("清空数据库",3);
	char in[20];
	showCenterText("输入yes开始清空数据库",5);
	showStudentsInfo(dataSet.datas,dataSet.length,13);
	inputFieldForChars("清空",in,7);
	if(strcmp(in,"yes")==0){
		dataSet.length=0;
		writeDataToFile();
		showCenterText("清空成功 [0]返回",11);
	} else showCenterText("清空撤销 [0]返回",11);
	while(getch()!='0');
	Menu();
}

/**
 * @brief 菜单
 */
void Menu() {
	system("cls");
	fm_MessageManager();
//	int code = receiveInput(1,8,1);
	select:
	char c = getch();
	int code = -1;
	if(c<'0'||c>'9'){
		goto select;
	} else {
		code = c-'0';
	}
	switch (code) {
	case 1:
		Input();
		break;
		
	case 4:
		searchStudentByStudentId();
		break;
		
	case 5:
		searchStudentByName();
		break;
		
	case 0:
		exit;
		break;
		
	case 3:
		Modify();
//		ModifyBeta();
		break;
		
	case 6:
		Statistic();
		break;
		
	case 2:
		deleteStudentByStudentId();
		break;
		
	case 8:
		clearDatas();
		break;
		
	case 9:
		showStudentPaiMing();
		
		break;
		
	case 7:
		
		StudentListShow();
		break;
	}
}

/**
 * @brief 登录实现
 */
void login() {
	system("cls");
//	showCenterText("+-----学号-----+-----姓名-----+---高数成绩----+-----英语成绩-----+--------平均成绩-------+总成绩(平均成绩)+\n",1);
	showCenterText("登录",3);
	
	int yOffset = 3;
	Position cen = getWindowCenterPos();
	int width = 20;
	int startX = cen.x-width;
	paintWindow(startX,yOffset+2,width,3,0);
	gotoxy(startX+3,yOffset+3);
	printf("账号");
	paintWindow(startX,yOffset+2,5,1,1);
	
	yOffset = 7;
	paintWindow(startX,yOffset+2,width,3,0);
	gotoxy(startX+3,yOffset+3);
	printf("密码");
	paintWindow(startX,yOffset+2,5,1,1);
	
	showCenterText("默认密码01",13);
	
	gotoxy(startX+10,6);
	printf("管理员账号"); //TODO:后续实现其他学生登录
	inPwd:
	gotoxy(startX+10,10);
	char pwd[20];
	scanf("%s",pwd);
	
	if(strcmp(pwd,"01") == 0){
		Menu();
	} else {
		showCenterText("密码错误",15);
		gotoxy(startX+10,10);
		printf("                         ");
		goto inPwd;
	}
	
}

/**
 * @brief 弃用的函数
 * @deprecated
 */
void inputStudent() {
	
	struct Student stu = {};
	
	gotoxy(8,2);
	printf ("                                             录入学生                                                      \n\n");
	
	int yOffset = 3;
	
	gotoxy(8,yOffset+1);
	printf ("+-----学号-----+-----姓名-----+---高数成绩----+-----英语成绩-----+--------平均成绩-------+总成绩(平均成绩)+\n");
	gotoxy(8,yOffset+2);
	printf ("+              +              +               +                  +                       +                +\n");
	gotoxy(8,yOffset+3);
	printf ("+              +              +               +                  +                       +                +\n");
	gotoxy(8,yOffset+4);
	printf ("+--------------+--------------+---------------+------------------+-----------------------+----------------+\n");
	
	int inputFieldCode = 0;
	input:
	char input[20];
	int spaceArray[] = {0,15,31,47};
	gotoxy(8+spaceArray[inputFieldCode]+2,yOffset+3);
	
	switch (inputFieldCode) {
	case 0:
		scanf("%s",stu.id);
		
		break;
		
		case 1:
		scanf("%s",stu.name);
		break;
		
		case 2:
		scanf("%d",&(stu.mathScore));
		
		break;
		
		case 3:
		scanf("%d",&(stu.englishScore));
		
		break;
		
	}
	
	inputFieldCode++;
	

	if(inputFieldCode <= 3){
		goto input;
	} else {
		float sum = stu.mathScore + stu.englishScore;
		gotoxy(75,yOffset+3);
		printf("%.2f",sum/2);
		gotoxy(98,yOffset+3);
		printf("%.2f",sum);
		
		gotoxy(50,yOffset+6);
		printf("写入成功\n");
	}
}

/**
 * @brief 弃用的函数
 * @deprecated
 */
void changeWindowToCenter() {
	HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);//获取当前函数句柄
	CONSOLE_SCREEN_BUFFER_INFO info ;
	GetConsoleScreenBufferInfo(handle,&info);
	int width = info.dwMaximumWindowSize.X;
	int height = info.dwMaximumWindowSize.Y;
	
	int sWid = GetSystemMetrics(SM_CXFULLSCREEN);
	int sHei = GetSystemMetrics(SM_CYFULLSCREEN);
	MoveWindow(handle,sWid/2-width/2,sHei/2-height/2,width,height,1);

}


/**
 * @brief 主函数
 * 
 * @return 
 */
int main() {
	SetConsoleOutputCP(65001); //更改为utf-8
	
	system("cls");
	
	readAllStudentFromFile();
	
	fm_Welcome();
//	welSelection:
//	if(getch()=='1'){
//		login();
//	} else {
//		goto welSelection;
//	}
	getch();
	login();
	return 0;
}
