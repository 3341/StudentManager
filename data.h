export const int MAX_STROAGE_SIZE = 10086;

struct Student {
	char name[];
	char id[]; //学号 
	int hasManagerPermission; //是否有更改其他学生的权限 
	int score; //分数 
	char password[]; //登录密码 
	
};

struct StudentDataSet {
    int size;
    struct Student datas[MAX_STROAGE_SIZE];

};