#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define SIZE 30
#define CLASS 6 
int N;
int barriers=0;
typedef struct scj{
	char name[20],number[9];
	int grade[CLASS];
}form;
void exchange(form*,form*);
void openfile(void);
int check(form *, char*);
void inputcj(void);
form cj[SIZE];
void calculation(form*);
void rank(form []);
void no_rank(form []);
void search(form []);
void statistic(form []);
void outputcj(form*);
void writecj(form*);
FILE *fp = NULL;
void main(){
	N=11;
	memset(cj,0,sizeof(form)*SIZE);	
	while (N!=0) {
		printf("***************************************************\n");
		printf("1.读取文件数据\n");
		printf("2.手动录入\n");
		printf("3.计算每门课程的总分和平均分\n");
		printf("4.按学生总分由高到低排出名次\n");
		printf("5.按学号由小到大排出成绩表\n");
		printf("6.按姓名查询学生排名及其考试成绩\n");
		printf("7.统计\n");
		printf("8.输出\n");
		printf("9.写入文件\n");
		printf("0.退出系统\n");
		printf("***************************************************\n");
		scanf("%d",&N);
		if(barriers==1){
			switch(N){
				case 1:openfile();break;
				case 2:inputcj();break;
				case 3:calculation(cj);break;
				case 4:rank(cj);break;
				case 5:no_rank(cj);break;
				case 6:search(cj);break;
				case 7:statistic(cj);break;
				case 8:outputcj(cj);break;
				case 9:writecj(cj);break;
				case 0:break;
				default:printf("输入错误，重新输入\n"); 
			}
		}
		else
			switch(N){
				case 1:openfile();break;
				case 2:inputcj();break;
				case 0:break;
				default:
				printf("请先输入或读入数据!\n");
				while (getchar() != '\n'){ //防止非法输入出现无限循环的现象； 
            		;
    			}
			}	
	}
	if(fp!=NULL)
		fclose(fp); 
}
void exchange(form *cj1,form *cj2){
	form temp;
	memset(&temp,0,sizeof(form));
	temp=*cj1;
	*cj1=*cj2;
	*cj2=temp;
}
int check(form *checkf,char *exanumber){ //学号查重； 
	int i,flag=0;
	for(i=0;i<SIZE;i++)
		if(strcmp(checkf[i].name,exanumber)==0){	
			flag=1;break;
		}
return flag;
}

void openfile(void){
	char filename[40];
	int m,i=0,exm=0;
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
			else
				while(!feof(fp)!=0){			
					exm+=fread(&cj[i],sizeof(form),1,fp);
					i++;
				}
			break;
		case 2:fp=fopen(filename,"ab+");
			rewind(fp);
			while(!feof(fp)!=0){			
					exm+=fread(&cj[i],sizeof(form),1,fp);
					i++;
			}
			break;
		default:printf("error!");exit(1);
	}
	barriers=1;
	if(exm==i-1)
		printf("一共有%d名学生的成绩记录\n",i-1);
	else 
		printf("读入过程出错！"); 
}
void inputcj(void){
	int n=0,k=0,tempg;
	int i,j;
	char temp[9];
	printf("请输入录入学生人数（不超过30人）以及课程数（不超过6门）\n");
	scanf("%d%d",&n,&k);
	if ((n<0||n>30)||(k<0||k>6)){
		printf("输入数字错误！");
		return; 
	}
	else{		
		for(i=0;i<n;i++){
			printf("请输入学号：\n");
			scanf("%s",&temp);
			while(strcmp(temp,"00000000")<0||strcmp(temp,"99999999")>0||strlen(temp)!=8){		
				printf("学号输入不规范，请重新输入\n");
				scanf("%s",&temp);
			}
			while(check(cj,temp)){
				scanf("%s",&temp);
			}
			strcpy(cj[i].number,temp);
			printf("请输入姓名(拼音)：\n");
			scanf("%s",&cj[i].name);
			printf("请依次输入成绩(1~100):\n");
			for(j=0;j<k;j++){
				scanf("%d",&tempg);
				while(tempg<1||tempg>100){
					printf("请输入合理范围成绩\n");
					scanf("%d",&tempg);
				}
				cj[i].grade[j]=tempg;
				while (getchar() != '\n'){
            		;
    			}
			}			
		}	
	barriers=1;
	}	
		
}
void calculation(form *gradef){
	float sum[CLASS];
	float avg[CLASS];
	int i,j;
	int countn,countc;
	memset(sum,0,sizeof(float)*CLASS);
	for(i=0;strlen(gradef[i].number)!=0;i++)
		for(j=0;gradef[i].grade[j]!=0;j++){
			sum[j]+=gradef[i].grade[j];
		}		
	countn=i;
	countc=j;		
	for(j=0;j<countc;j++)
		avg[j]=sum[j]/i;
	printf("|----|总分|平均分|\n");
	for(j=0;j<countc;j++)
		printf("|课程%d:|%4.2f|%4.2f|\n",j+1,sum[j],avg[j]);
}
void rank(form *rankf){
	int i,j,sum[SIZE],line=1,temp;
	int flag=1;
	int countn=0,countc=0;
	memset(sum,0,sizeof(int)*SIZE);
	for(i=0;strlen(rankf[i].number)!=0;i++){
		for(j=0;rankf[i].grade[j]!=0;j++)
			sum[i]+=rankf[i].grade[j];
	}
	countn=i;
	countc=j;
	while(flag!=0){
		flag=0;
		for(i=0;i<countn-1;i++){		
			if(sum[i]<sum[i+1]){
				flag=1;
				exchange(&rankf[i],&rankf[i+1]);
				temp=sum[i];
				sum[i]=sum[i+1];
				sum[i+1]=temp;
			}
		}	
	}
	printf("排名  学号  姓名  ");
	for(j=0;j<countc;j++)
		printf("课程%d  ",j+1);
	printf("总分\n");
	for(i=0;i<countn;i++){
		printf("%d. ",line);line++;
		printf("No.%s  %s  ",rankf[i].number,rankf[i].name);
		for(j=0;j<countc;j++)
			printf("%d  ",rankf[i].grade[j]);
		printf("%d\n",sum[i]);
	}
}
void no_rank(form *no_rankf){
	int i,j;
	int countn;
	int flag=1;
	while(flag!=0){
		flag=0;
		for(i=1;strlen(no_rankf[i].number)!=0;i++){
			if(strcmp(no_rankf[i-1].number,no_rankf[i].number)>0){
				flag=1;
				exchange(&no_rankf[i-1],&no_rankf[i]);
			}
		}
	;
	}
	countn=i;
	printf("学号  姓名  ");
	for(j=0;no_rankf[0].grade[j]!=0;j++)
		printf("课程%d  ",j+1);
	printf("\n");
	for(i=0;i<countn;i++){
		printf("No.%s  %s  ",no_rankf[i].number,no_rankf[i].name);
		for(j=0;no_rankf[0].grade[j]!=0;j++)
			printf("%d  ",no_rankf[i].grade[j]);
		printf("\n");
	}
}
void search(form *searchf){
	char sname[20];
	int i,j=-1;
	rank(searchf);
	printf("请输入学生姓名（拼音）:\n");
	scanf("%s",sname);
	for(i=0;i<SIZE;i++)
		if(strcmp(searchf[i].name,sname)==0)
			j=i;
	if(j==-1)
		printf("没有该学生的记录");
	else
		printf("No.%s %s 排名是 %d\n",searchf[j].number,searchf[j].name,j+1);
		for(i=0;searchf[j].grade[i]!=0;i++)
			printf("课程%d成绩是%d",i+1,searchf[j].grade[i]);
		printf("\n"); 
}

void statistic(form *tj){
	int mark[CLASS][5];
	float markpct[CLASS][5]; 
	memset(mark,0,sizeof(int)*CLASS*5);
	memset(markpct,0,sizeof(float)*CLASS*5);
	int i,j,count=0;
	for(i=0;strlen(tj[i].number)!=0;i++){	
		for(j=0;tj[i].grade[j]!=0;j++){
			switch(tj[i].grade[j]/10){
				case 10:  case 9: mark[j][0]++;break;
				case 8: mark[j][1]++;break;
				case 7: mark[j][2]++;break;
				case 6: mark[j][3]++;break;
				default: mark[j][4]++;
			}
		}
		count++;
	}
	for(i=0;tj[0].grade[i]!=0;i++)
		for(j=0;j<5;j++)
			markpct[i][j]=(float)mark[i][j]/count;
	for(i=0;tj[0].grade[i]!=0;i++){
		printf("课程%d的分布情况为A:%d(%3.2f%%) B:%d(%3.2f%%) C:%d(%3.2f%%) D:%d(%3.2f%%) E:%d(%3.2f%%)\n",i+1,mark[i][0],markpct[i][0]*100,
		mark[i][1],markpct[i][1]*100,mark[i][2],markpct[i][2]*100,mark[i][3],markpct[i][3]*100,mark[i][4],markpct[i][4]*100);
	}
}	

void outputcj(form *output){
	int i,j,countc,countn;
	int sum[SIZE];
	float avg[SIZE];
	memset(sum,0,sizeof(int)*SIZE);
	for(i=0;strlen(output[i].number)!=0;i++){	
		for(j=0;output[i].grade[j]!=0;j++)
			sum[i]+=output[i].grade[j];	
	}
	countn=i;
	countc=j;
	for(i=0;i<countn;i++)
		avg[i]=(float)sum[i]/countc;
	printf("学号  姓名  ");
	for(j=0;j<countc;j++)
		printf("课程%d  ",j+1);
	printf("平均分  总分\n");
	for(i=0;i<countn;i++){
		printf("No.%s  %s  ",output[i].number,output[i].name);
		for(j=0;j<countc;j++)
			printf("%d  ",output[i].grade[j]);
		printf("%f  %d\n",avg[i],sum[i]);
	}
} 
void writecj(form *writef){
	char filename[20];
	FILE *nfp;
	int i=0,exm=0;
	printf("请输入文件名：\n");
	scanf("%s",filename);
	nfp=fopen(filename,"ab+");
	while(strlen(writef[i].number)!=0){
		exm+=fwrite(&writef[i],sizeof(form),1,nfp);
		i++;
	}
	if(exm==i)
		printf("文件写入成功\n");
	else
		printf("写入失败，请重新写入\n");
	fclose(nfp);
}
