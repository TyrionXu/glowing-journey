#include "stdio.h"
#include "stdlib.h"
#define SIZE 200 
int n;
void exchange();
void openfile();
void inputcj();
typedef struct scj{
	char name[20],number[9];
	int grade1,grade2,grade3;
}form;	
void calculation();
void rank();
void no_rank();
void search(); 
void outputcj();
FILE *fp = NULL;
void main(){
	n=1;
	while (n!=0) {
		printf("\n\n1.读取文件数据\n");
		printf("2.手动录入\n");
		printf("3.计算每门课程的总分和平均分\n");
		printf("4.按学生总分由高到低排出名次\n");
		printf("5.按学号由小到大排出成绩表\n");
		printf("6.按姓名查询学生排名及其考试成绩\n");
		printf("7.统计\n");
		printf("8.输出\n");
		printf("9.写入文件\n");
		printf("0.退出系统\n");
		scanf("%d",&n);
		switch(n){
			case 1:openfile();break;
			case 2:inputcj();break;
			case 3:calculation();break;
			case 4:rank(n);break;
			case 5:no_rank();break;
			case 6:search()
			case 8:outputcj();break;
		}
	}
	fp=NULL; 
}
void exchange(form *cj1,form *cj2){
	form *temp;
	temp->number=cj1->number;
	cj1->number=cj2->number;
	cj2->number=temp->number;
	temp->name=cj1->name;
	cj1->name=cj2->name;
	cj2->name=temp->name;
	temp->grade1=cj1->grade1;
	cj1->grade1=cj2->grade1;
	cj2->grade1=temp->grade1;
	temp->grade2=cj1->grade2;
	cj1->grade2=cj2->grade2;
	cj2->grade2=temp->grade2;
	temp->grade3=cj1->grade3;
	cj1->grade3=cj2->grade3;
	cj2->grade3=temp->grade3;
}
void openfile(void){
	char filename[40];
	int m;
	printf("请输入文件名：");
	scanf("%s",filename);
	printf("选择打开方式：1.只读 2.可读写(输入1或2)");
	scanf("%d",&m);
	switch(m){
		case 1:fp=fopen(filename,"rb");
			if(fopen(filename,"rb")== NULL) {
			printf("文件不存在或数据为空！\n");
			return;
			}
			break;
		case 2:fp=fopen(filename,"ab+");break;
		default:printf("error!");exit(1);
	}
}
void calculation(){
	int sum1=0,sum2=0,sum3=0;
	int avg1,avg2,avg3,i=0;
	form grade;
	rewind(fp);
	while(!feof(fp)==0){
		fread(&grade,sizeof(form),1,fp);
		sum1+=grade.grade1;
		sum2+=grade.grade2;
		sum3+=grade.grade3;
		i++;
	}
	avg1=sum1/i;
	avg2=sum2/i;
	avg3=sum3/i;
	printf("|----|总分|平均分|\n");
	printf("|课程1|%4d|%4d|\n");
	printf("|课程2|%4d|%4d|\n");
	printf("|课程3|%4d|%4d|\n");
}
void rank(int n){
	int i,sum[n],line=1;
	int flag=0;
	form rankf[n];
	rewind(fp);
	for(i=0;i<n;i++){
		fread(&rank[i],sizeof(form),1,fp);
		sum[i]=rankf[i].grade1+rankf[i].grade2+rankf[i].grade3;
	}
	while(flag!=0){
		for(i=0;i<n-1;i++){		
			if(sum[i]<sum[i+1]){
				flag=1;
				exchange(&rankf[i],&rankf[i+1]);
			}
		}	
	}
	for(i=0;i<n;i++){
		printf("rank:No.  name  grade1 grade2 grade3 sum\n");
		printf("%d.",line);line++;
		printf("No.%s %s:%4d %4d %4d %4d\n",rankf[i].number,rankf[i].name,rankf[i].grade1,rankf[i].grade2,rankf[i].grade3,sum[i]);
	}
}
void no_rank(){
	int i;
	int flag=0;
	form no_rankf[n];
	rewind(fp);
	for(i=0;i<n;i++)
		fread(&no_rank[i],sizeof(form),1,fp);
	while(flag!=0){
		for(i=0;i<n-1;i++){		
			if(strcmp(no_rankf[i].number,no_rankf[i+1].number)>0){
				flag=1;
				exchange(&rankf[i],&rankf[i+1]);
			}
		}	
	}
	for(i=0;i<n;i++){
		printf("No.  name  grade1 grade2 grade3 \n");
		printf("No.%s %s:%4d %4d %4d \n",no_rankf[i].number,no_rankf[i].name,no_rankf[i].grade1,no_rankf[i].grade2,no_rankf[i].grade3);
	}
}
void search(){
	form lsit[5];
	int i,j;
	rank();
	printf("请输入学生姓名（拼音）:\n");
	for(i=0;i<n;i++){
		 
	}
}
void inputcj(form cj[SIZE],int flag){
/*	
*/
	int i;
	flag=1;
	if (fp == NULL){
		printf("请选择指定文件或自行创建文件！");
		return;
	}
	else{
		
		for(i=0;flag==1;i++){
			printf("请输入学号：\n");
			scanf("%s",&cj[i].number);
			while (getchar() != '\n') /* clear the input buffer */
           {
            	;//loop
    		}
			printf("请输入姓名(拼音)：\n");
			scanf("%s",&cj[i].name);
			while (getchar() != '\n') /* clear the input buffer */
           {
            	;//loop
    		}
			printf("请依次输入成绩:\n");
			scanf("%d%d%d",&cj[i].grade1,&cj[i].grade2,&cj[i].grade3);
			flag=0;
			while (getchar() != '\n') /* clear the input buffer */
           {
            	;//loop
    		}
			printf("继续输入请按1\n");
			scanf("%d",&flag); 
			
		}	
		fwrite(cj,sizeof(form),i,fp); /*实时储存  指针问题*/ 
		if(fwrite(cj,sizeof(form),i,fp)==i)
			printf("数据录入成功\n\n");
		else
			printf("数据录入失败\n\n");
		fclose(fp);
		fp=NULL; 
	}	
		
}
void outputcj(){
	openfile();
	form outcj[SIZE];
	fread(&outcj[0],sizeof(form),1,fp);
	printf("No.%s %s grade1 %3d grade2 %3d grade3 %3d\n",outcj[0].number,outcj[0].name,outcj[0].grade1,outcj[0].grade2,outcj[0].grade3);
} 
/* 用二级制说明原因
学号输入时重复问题检查
末尾数据追加问题*/ 
