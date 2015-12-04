#include <stdio.h>
#include <stdlib.h>
struct Node {
	long num;
	float grade;
	struct Node *next;
	struct Node *prev;
};
#define SIZE sizeof(struct Node)

struct Node * createLinkList ();
void outputLinkList(struct Node * headp);
struct Node * deleteNode(struct Node * headp, long numkey);
struct Node * insertNode(struct Node * headp, struct Node * insert);
void searchNode(struct Node * headp, long numkey);
struct Node * revertLinkList(struct Node * headp);
void sortLinkList(struct Node * headp);
void bubble( struct Node *headp, struct Node *tailp );

struct Node * createLinkList() {
	int k = 0;
	long nn;
	struct Node * headp , * newp , * tailp;
	headp = NULL;
	printf("Input num of a student.(Input 0 for stop)\n");
	scanf("%ld", &nn);
	while ( nn != 0L ) {
		k++;
		newp = (struct Node *)malloc(SIZE);
		newp->num = nn;
		printf("Input grade of this student.\n");
		scanf("%f", &newp->grade);
		if ( k == 1 ) {
			headp = newp;
			newp->prev = NULL;
		}else {
			tailp->next = newp;
			newp->prev = tailp;
		}
		tailp = newp;
		printf("Input num of a student.(Input 0 for stop)\n");
		scanf("%ld", &nn);
	}
	tailp->next = NULL;
	return (headp);
}

void outputLinkList(struct Node * headp) {
	struct Node * p;
	if (headp == NULL) {
		printf("Empty LinkList\n");
		return;
	}
	p = headp;
	while ( p != NULL ) {
		printf("%9ld %10.1f\n",p->num, p->grade);
		p = p->next;
	}
}

struct Node * deleteNode(struct Node * headp, long numkey) {
	struct Node * check, * last;
	check = last = headp;
	while ( check != NULL ) {
		if ( check->num == numkey ) {
			break;
		}
		last = check;
		check = check ->next;
	}
	if ( check->num == numkey ) {
		if ( check == headp ) {
			headp = check->next;
		}else {
			last->next = check->next;
		}
		free (check);
		printf("已删除学号为%ld的同学的信息\n", numkey);
	}else {
		printf("未找到学号为%ld的同学\n", numkey);
	}
	return headp;
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
		printf("学号为%ld的同学的成绩为%f\n", check->num, check->grade);
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

struct Node * revertLinkList(struct Node * headp) {
	struct Node * tailp, * check;
	check = headp;
	if (check == NULL)
		return (headp);
	struct Node * linklist2;
	while (check != NULL) {
		if (check->next == NULL){
			tailp = check;
			linklist2 = tailp;
		}
		check = check->next;
	}//将tailp指向最后一个
	while (tailp != NULL) {
		check = tailp->next;
		tailp->next = tailp->prev;
		tailp->prev = check;
		tailp = tailp->next;
		// if (tailp->prev == NULL
	}
	return (linklist2);
}

void sortLinkList(struct Node * headp){
	struct Node *tmp = NULL;
	for ( tmp = headp ; tmp->next != NULL ; ) {
		tmp = tmp->next;
	}
	for ( ; tmp != NULL; tmp = tmp->prev ) {
		bubble(headp, tmp);
	}
}

void bubble( struct Node *headp, struct Node *tailp ) {
	struct Node *tmp, *p;
	long nn;
	float grade1;
	for ( tmp = headp ; tmp != tailp ; tmp = tmp->next ) {
		if ( tmp->next == NULL )
			break;
		if ( tmp->num > tmp->next->num) {
			nn = tmp->num;
			grade1 = tmp->grade;
			tmp->num = tmp->next->num;
			tmp->grade = tmp->next->grade;
			tmp->next->num = nn;
			tmp->next->grade = grade1;
		}
	}
}


int main() {
	struct Node * linklist1;
	struct Node * stu;

	linklist1 = NULL;
	int mode;
	long nn1;
	printf("请输入需要进行的操作 1为建立新的链表，2为查看链表的数据，3为删除指定学号的学生信息，4为插入一项纪录，5为查找指定学号的学生成绩，6为倒转链表，7为排序(默认以学号排序)，0为退出程序\n");
	scanf("%d", &mode);
	while ( mode != 0 ) {
		switch (mode) {
			case 1: linklist1 = createLinkList();
					printf("请输入需要进行的操作 1为建立新的链表，2为查看链表的数据，3为删除指定学号的学生信息，4为插入一项纪录，5为查找指定学号的学生成绩，6为倒转链表，7为排序，0为退出程序\n");
					scanf("%d", &mode);
					break;
			case 2: outputLinkList(linklist1);
					printf("请输入需要进行的操作 1为建立新的链表，2为查看链表的数据，3为删除指定学号的学生信息，4为插入一项纪录，5为查找指定学号的学生成绩，6为倒转链表，7为排序，0为退出程序\n");
					scanf("%d", &mode);
					break;
			case 3: printf("请输入要删除的学生的学号\n");
					scanf("%ld", &nn1);
					deleteNode(linklist1, nn1);
					printf("请输入需要进行的操作 1为建立新的链表，2为查看链表的数据，3为删除指定学号的学生信息，4为插入一项纪录，5为查找指定学号的学生成绩，6为倒转链表，7为排序，0为退出程序\n");
					scanf("%d", &mode);
					break;
			case 4: stu = (struct Node *) malloc(SIZE);
					printf("请输入要添加的学生的学号+成绩，以空格分开\n");
					scanf("%ld%f", &stu->num, &stu->grade);
					linklist1 = insertNode(linklist1, stu);
					outputLinkList(linklist1);
					printf("请输入需要进行的操作 1为建立新的链表，2为查看链表的数据，3为删除指定学号的学生信息，4为插入一项纪录，5为查找指定学号的学生成绩，6为倒转链表，7为排序，0为退出程序\n");
					scanf("%d", &mode);
					break;
			case 5: printf("请输入要查找的学号\n");
					scanf("%ld", &nn1);
					searchNode(linklist1, nn1);
					printf("请输入需要进行的操作 1为建立新的链表，2为查看链表的数据，3为删除指定学号的学生信息，4为插入一项纪录，5为查找指定学号的学生成绩，6为倒转链表，7为排序，0为退出程序\n");
					scanf("%d", &mode);
					break;
			case 6: linklist1 = revertLinkList(linklist1);
					printf("请输入需要进行的操作 1为建立新的链表，2为查看链表的数据，3为删除指定学号的学生信息，4为插入一项纪录，5为查找指定学号的学生成绩，6为倒转链表，7为排序，0为退出程序\n");
					scanf("%d", &mode);
					break;
			case 7: sortLinkList(linklist1);
					printf("请输入需要进行的操作 1为建立新的链表，2为查看链表的数据，3为删除指定学号的学生信息，4为插入一项纪录，5为查找指定学号的学生成绩，6为倒转链表，7为排序，0为退出程序\n");
					scanf("%d", &mode);
					break;


			default: return 0;
					break;
		}
	}	
	return 0;
}
