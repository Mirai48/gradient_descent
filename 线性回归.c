#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct{
    int x;
    float y;
}Point;

typedef struct{
    float cost;
    float k;
    float a;
}Cost;

float get_gradient_a(Point *sample, int l, float k, float a);
float get_gradient_k(Point *sample, int l, float k, float a);
float get_sum_a(Point *sample, int l, float k, float a);
float get_sum_k(Point *sample, int l, float k, float a);
void creat_data(Point *sample, int l);
float cost_function(Point *sample, int l, float k, float a);
int gradient_descent(Point *sample, int l, float *k, float *a, float alpha, Cost *max3, int i);
void max3_increase(Point *sample, int l, float *k, float *a, Cost *max3);
void max3_initialization(Cost *max3, int a);
int max3_if_end(Cost *max3);



float get_gradient_a(Point *sample,int l, float k, float a){//在递归计算a的梯度变化量
     float sum,x,y,p;
     sum = 0;
    for (int i = 0; i < l; i++)
    {
        x = sample->x;
        y = sample->y;
        sample++;
        p = x * k + a - y;
        sum = sum+p;
    }
    sum = sum/l;
    return sum;
}

float get_gradient_k(Point *sample,int l, float k, float a){//在递归计算k的梯度变化量
    float sum,x,y,p;
    sum = 0;
    for (int i = 0; i < l; i++)
    {
        x = sample->x;
        y = sample->y;
        sample++;
        p = x * k + a - y;
        p = p * x;
        sum = sum+p;
    }
    sum = sum/l;
    return sum;
}

float get_sum_a(Point *sample,int l, float k, float a){
    float sum,x,y,p;
    sum = 0;
    for (int i = 0; i < l; i++){
        x = sample->x;
        y = sample->y;
        sample++;
        p = x * k + a - y;
        //p = p * x;
        sum = sum+p;
    }
    sum = sum/l;
    return sum;
}

float get_sum_k(Point *sample,int l, float k, float a){
    float sum,x,y,p;
    sum = 0;
    for (int i = 0; i < l; i++){
        x = sample->x;
        y = sample->y;
        sample++;
        p = x * k + a - y;
        p = p * x;
        sum = sum+p;
    }
    sum = sum/l;
    return sum;
}

void creat_data(Point *sample, int l){ //传入Point数组首位指针，需要的位数，自动生成线性回归样本
    srand((unsigned)time(NULL));
    float k;
    int a;
    k = (rand() % 10) / 5.0;
    a = rand() % 10;
    for (int i = 0; i < l; i++) {
       // srand((unsigned)time(NULL));
        sample->x = i;
        sample->y = i * k + (rand()%10)/5.0+a;
        sample++;
        //没有判断是否溢出
    }
}

float cost_function(Point *sample,int l, float k, float a){
    float sum,x,y,p;
    sum = 0;
    for (int i = 0; i < l; i++)
    {
        x = sample->x;
        y = sample->y;
        sample++;
        p = x * k + a - y;
        sum = sum + p * p;
    }
    sum = sum/2/l;
    return sum;
}

int gradient_descent(Point *sample,int l, float *k, float *a,float alpha,Cost *max3,int i){ 
    if(i>5000){    //递归1w次，函数停止
        return 0;
    }
    i++;
    float k2, a2;//临时储存迭代后的k和a
    printf("%2f", *a);
    a2 = *a-alpha*get_gradient_a(sample, l, *k, *a);
    k2 = *k-alpha*get_gradient_k(sample, l, *k, *a);
    *a = a2;
    *k = k2;
    //利用max3_increase更新
    max3_increase(sample,l,k,a,max3);
    if (max3_if_end(max3)){    //存储最近的3次的数据，计算它们的cost，如果最老的数据（cost3)最小，函数停止
        return 1;
    }
    gradient_descent(sample, l, k, a, alpha, max3, i);
    return 1;
}

void max3_increase(Point *sample, int l,float *k, float *a,Cost *max3){
    Cost *max3_t;
    max3_t = max3 + 2;
    max3 = max3 + 1;
    max3_t->a = max3->a;
    max3_t->k = max3->k;
    max3_t->cost = max3->cost;

    max3_t --;
    max3 --;
    max3_t->a = max3->a;
    max3_t->k = max3->k;
    max3_t->cost = max3->cost;

    max3->a = *a;
    max3->k = *k;
    max3->cost = cost_function(sample, l, *k, *a);

}

void max3_initialization(Cost *max3,int a){
    for (int i = 0; i < a; i++)
    {
        max3->a = 0;
        max3->k = 0;
        max3->cost = 99999;//大数防止提前终止
        max3++;
    }
}

int max3_if_end(Cost *max3){
    if (max3->cost<(max3+1)->cost&&(max3+1)->cost<(max3+2)->cost)
    {
        return 1;
    }else{
        return 0;
    }   
}





int main(){
    Point sample[9];
    Point *s;
    s = &sample[0];
    creat_data(s,10);
/*     for (int i = 0; i < 10; i++)
    {
        printf("%d",sample[i].x);
        printf("|%f",sample[i].y);
        printf("\n");
    } */
    //初始化max3结构体
    Cost max3[3];
    Cost *stc;
    max3_initialization(stc,3);
    int i = 0;
    int l=10;
    float a = 0;
    float k = 1;
    float alpha=0.1;
    if( gradient_descent(s, l, &k, &a, alpha, max3, i)){
        printf("y=%3fx+%3f cost=%3f",max3->k, max3->a, max3->cost);
    }else
    {
        printf("you stupid code");
    }

    printf("I dont knwo waht happen!");
    return 0;
}