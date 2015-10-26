#include <stdio.h>
#include <stdlib.h>

void detectComment();

int state = 0;
char ch;
char buf1;

int main(){
	FILE *fp;
	fp = fopen ("Filter.cpp", "r");
	if (fp == NULL){
		printf("Error with opening file!\n");
		exit(0);
	}
	while ((ch = fgetc(fp)) != EOF){
		detectComment();
		if(state == 0 || state == 5 || state == 6){
			printf("%c", ch);
		}else {
			printf("");
		}
	}

	fclose(fp);
	return 0;
}

void detectComment(){
	if (ch == '/' && state == 0){
		state = 1;
		buf1 = ch;
		
	}
	else if (state == 1 && ch == '/'){
		state = 2;
	}
	else if (state == 1 && ch == '*'){
		state = 3;
	}
	else if (state == 1 && ch != '/'){
		printf("%c", buf1);
		state = 0;
	}
	else if (state == 1 && ch != '*'){
		printf("%c", buf1);
		state = 0;
	}
	else if (ch == '"' && state == 0){
		state = 5;
	}
	else if (state == 2 && ch == '\n'){
		state = 0;
	}
	else if (state == 3 && ch == '*'){
		state = 4;
		buf1= ch;
	}
	else if (state == 4 && ch == '/'){
		state = 7;
	}
	else if (state == 4 && ch != '/'){
		state = 3;
		printf("%c", buf1);
	}
	else if (state == 7){
		state = 0;
	}
}

/* state 状态解释
0 正常读取字符
1 读取到一个／
2 连续读取到两个 ／ 开始删除
3 读取到／＊   开始删除
4 再次读取到 ＊ 
如果在state ＝ 4 时读取到 ／ state ＝ 0
5 读取到“ 进入字符串模式
此时遇到 \ 时进入state 6
如果在state ＝ 6 时读取到 ” state ＝ 5
如果在state ＝ 5 的时候读取到 ” 则state ＝ 0
*/