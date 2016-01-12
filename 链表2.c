//
//  main.c
//  Grade
//
//  Created by 史征宇 on 16/1/11.
//  Copyright © 2016年 SKY. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE sizeof(struct Node)
struct Node {
    long num;
    float grade;
    float mathGrade;
    float engGrade; //Two Subject Currently
    // float
    char name[10];
    struct Node *next;
    struct Node *prev;
};

struct Node * createLinkList ();
void outputLinkList(struct Node * headp);
struct Node * deleteNode(struct Node * headp, long numkey);
struct Node * insertNode(struct Node * headp, struct Node * insert);
void searchNode(struct Node * headp, long numkey);
void sortLinkList(struct Node * headp);
void bubble( struct Node *headp, struct Node *tailp );
void findTop(struct Node * headp);
int numOfNode (struct Node * headp);

int numOfNode (struct Node * headp){
    struct Node * check;
    check = headp;
    int sum = 0;
    while (check != NULL) {
        sum ++;
        check = check ->next;
    }
    return sum;
}

struct Node * createLinkList() {
    int k = 0;
    long nn;
    struct Node * headp , * newp , * tailp = NULL;
    headp = NULL;
    printf("请输入要添加的学生的学号.（输入0以停止输入）\n");
    scanf("%ld", &nn);
    while ( nn != 0L ) {
        k++;
        newp = (struct Node *)malloc(SIZE);
        newp->num = nn;
        printf("请输入学号为%ld的学生的名字\n", newp->num);
        scanf("%s", &newp->name);//Maybe memory overflow
        printf("请输入学号为%ld的学生的数学成绩\n", newp->num);
        scanf("%f", &newp->mathGrade);
        printf("请输入学号为%ld的学生的英语成绩\n", newp->num);
        scanf("%f", &newp->engGrade);
        newp->grade = newp->mathGrade + newp-> engGrade;
        if ( k == 1 ) {
            headp = newp;
            newp->prev = NULL;
        }else {
            tailp->next = newp;
            newp->prev = tailp;
        }
        tailp = newp;
        printf("请输入要添加的学生的学号.（输入0以停止输入）\n");
        scanf("%ld", &nn);
    }
    tailp->next = NULL;
    return (headp);
}

void outputLinkList(struct Node * headp) {
    struct Node * p;
    if (headp == NULL) {
        printf("列表为空\n");
        return;
    }
    p = headp;
    while ( p != NULL ) {
        printf("学号：%9ld 姓名：%s 数学成绩：%10.1f 英语成绩：%10.1f 总分：%10.1f \n",
               p->num, p->name, p->mathGrade, p->engGrade, p->grade);
        p = p->next;
    }
}

struct Node * deleteNode(struct Node * headp, long numkey) {
    struct Node * check, * last;
    int didDeleteNode = 0;
    check = last = headp;
    while ( check != NULL ) {
        if ( check->num == numkey ) {
            if ( check ==  headp ) {
                headp = check->next;
                free(check);
                printf("已删除学号为%ld的同学的信息\n", numkey);
                didDeleteNode = 1;
                break;
            }else {
                last->next = check->next;
                free(check);
                printf("已删除学号为%ld的同学的信息\n", numkey);
                didDeleteNode = 1;
                break;
            }
        }else {
            last = check;
            check = check->next;//Move the point to next Node
        }
    }
    if (didDeleteNode == 0) {
        printf("未找到学号为%ld的同学\n", numkey);
        return headp;
    }else {
        return headp;
    }
    
}

void searchNode(struct Node * headp, long numkey) {
    struct Node * check;
    check = headp;
    while ( check != NULL ) {
        if ( check->num == numkey )
            break;
        check = check->next;
    }
    if ( check != NULL ) {
        printf("学号为%ld的同学的总成绩为%g，数学成绩为：%g，英语成绩为：%g\n",
               check->num, check->grade, check->mathGrade, check->engGrade);
    }else {
        printf("未找到学号为%ld的同学\n", numkey);
    }
}

struct Node * insertNode(struct Node * headp, struct Node * insert) {
    struct Node * check, * last;
    
    if ( headp == NULL ) {
        insert->next = NULL;
        return insert;
    }
    
    check = last = headp ;
    
    while( check != NULL ) {
        if ( check->num == insert->num )
            break;
        last = check;
        check = check->next;
    }
    insert->next = check;
    
    if ( check != headp ) {
        last->next = insert;
    }else {
        headp = insert;
    }
    return (headp);
}

void sortLinkList(struct Node * headp){
    struct Node * check;
    check = headp;
    int i = 0;
    int sum = numOfNode(headp);
    float scoreList[sum];
    char nameList[sum][10];
    while (check != NULL) {
        scoreList[i] = check->grade;
        strcpy(nameList[i], check->name);
        i++;
        check = check->next;
    }
    i = 0;
    int k , temp;
    char tempChar[10];
    for( k = 0 ; k < sum ; k ++ ){
        for( i = k+1 ; i < sum ; i ++ )
            if( scoreList[k] < scoreList[i]){
                temp = scoreList[k];
                strcpy(tempChar, nameList[k]);
                scoreList[k] = scoreList[i];
                strcpy(nameList[k], nameList[i]);
                scoreList[i] = temp;
                strcpy(nameList[i], tempChar);
            }
    }
    i = 0;
    while ( i < sum ) {
        printf("姓名：%s，成绩：%g，排名：%d\n",nameList[i], scoreList[i], i + 1);
        i++;
    }
}

void findTop(struct Node * headp) {
    struct Node *check;
    float maxMath, maxEng;
    char maxEngStu[10], maxMathStu[10];
    check = headp;
    if (headp == NULL) {
        printf("列表为空\n");
        return;
    }
    maxEng = check ->engGrade;
    strcpy(maxEngStu, check ->name);
    maxMath = check ->mathGrade;
    strcpy(maxMathStu, check ->name);
    while (check != NULL) {
        if (check-> mathGrade > maxMath) {
            maxMath = check ->mathGrade;
            strcpy(maxMathStu, check ->name);
        }
        if (check-> engGrade > maxEng) {
            maxEng = check ->engGrade;
            strcpy(maxEngStu, check ->name);
        }
        check = check ->next;
    }
    printf("数学成绩最高的同学为：%s，%g分\n 英语成绩最高的同学为：%s，%g分\n", maxMathStu, maxMath, maxEngStu, maxEng);
}


int main() {
    struct Node * linklist1;
    struct Node * stu;
    
    linklist1 = NULL;
    int mode;
    long nn1;
    printf("请输入需要进行的操作 1为建立新的链表，2为查看链表的数据，3为删除指定学号的学生信息，4为插入一项纪录，5为查找指定学号的学生成绩，7为排序(默认以学号排序)，8为查找各科目最高分的学生，0为退出程序\n");
    scanf("%d", &mode);
    while ( mode != 0 ) {
        switch (mode) {
            case 1:
                linklist1 = createLinkList();
                printf("请输入需要进行的操作 1为建立新的链表，2为查看链表的数据，3为删除指定学号的学生信息，4为插入一项纪录，5为查找指定学号的学生成绩，7为排序，8为查找各科目最高分的学生，0为退出程序\n");
                scanf("%d", &mode);
                break;
            case 2:
                outputLinkList(linklist1);
                printf("请输入需要进行的操作 1为建立新的链表，2为查看链表的数据，3为删除指定学号的学生信息，4为插入一项纪录，5为查找指定学号的学生成绩，7为排序，8为查找各科目最高分的学生，0为退出程序\n");
                scanf("%d", &mode);
                break;
            case 3:
                printf("请输入要删除的学生的学号\n");
                scanf("%ld", &nn1);
                deleteNode(linklist1, nn1);
                printf("请输入需要进行的操作 1为建立新的链表，2为查看链表的数据，3为删除指定学号的学生信息，4为插入一项纪录，5为查找指定学号的学生成绩，7为排序，8为查找各科目最高分的学生，0为退出程序\n");
                scanf("%d", &mode);
                break;
            case 4:
                stu = (struct Node *) malloc(SIZE);
                printf("请输入要添加的学生的学号+姓名+数学成绩+英语成绩，以空格分开\n");
                scanf("%ld %s %f %f", &stu->num, &stu->name, &stu->mathGrade, &stu->engGrade);
                stu-> grade = stu->mathGrade + stu->engGrade;
                linklist1 = insertNode(linklist1, stu);
                outputLinkList(linklist1);
                printf("请输入需要进行的操作 1为建立新的链表，2为查看链表的数据，3为删除指定学号的学生信息，4为插入一项纪录，5为查找指定学号的学生成绩，7为排序，8为查找各科目最高分的学生，0为退出程序\n");
                scanf("%d", &mode);
                break;
            case 5:
                printf("请输入要查找的学号\n");
                scanf("%ld", &nn1);
                searchNode(linklist1, nn1);
                printf("请输入需要进行的操作 1为建立新的链表，2为查看链表的数据，3为删除指定学号的学生信息，4为插入一项纪录，5为查找指定学号的学生成绩，7为排序，8为查找各科目最高分的学生，0为退出程序\n");
                scanf("%d", &mode);
                break;
            case 7:
                sortLinkList(linklist1);
                printf("请输入需要进行的操作 1为建立新的链表，2为查看链表的数据，3为删除指定学号的学生信息，4为插入一项纪录，5为查找指定学号的学生成绩，7为排序，8为查找各科目最高分的学生，0为退出程序\n");
                scanf("%d", &mode);
                break;
            case 8:
                findTop(linklist1);
                printf("请输入需要进行的操作 1为建立新的链表，2为查看链表的数据，3为删除指定学号的学生信息，4为插入一项纪录，5为查找指定学号的学生成绩，7为排序，8为查找各科目最高分的学生，0为退出程序\n");
                scanf("%d", &mode);
                break;
            default: return 0;
                break;
        }
    }
    return 0;
}
