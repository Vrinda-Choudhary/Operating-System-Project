#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <Windows.h>

volatile  dist_turtle=0,dist_hare=0,end=5;
int  full=0,empty=1,mutex=1;
int MAX_HARE_SPEED=3;
bool game_over;

void wait(int *s){  //LOCKING
	while(*s<=0);
	*s=*s-1;
}
void post(int *s){  //UNLOCKING
	*s=*s+1;
}

void *report(void *vargp){
    //sleep(1);
    while(!game_over){
        printf("%s%d%s%d\n","Turtle-> ",dist_turtle," ,Hare-> ",dist_hare);
        Sleep(1000);
    }
    return NULL;
}

void *turtle(void *vargp){
	while(dist_turtle<end && ! game_over){
		wait(&empty);
		wait(&mutex);
		dist_turtle=dist_turtle+1;
        //pthread_t Temp;
        //pthread_create(&Temp,NULL,report,NULL);
        //pthread_join(Temp,NULL);
        //printf("%d %d\n",x,y);
		post(&mutex);
		post(&full);
		Sleep(1000);
	}
    if(!game_over){
        printf("Turtle wins\n");
        game_over=true;
    }
    return NULL;
}
void *hare(void *vargp){
	while(dist_hare<end && !game_over){
		wait(&full);
		wait(&mutex);
		if(dist_hare>dist_turtle + 2){
            //do nothing
		}
		else{
                int temp=rand()%MAX_HARE_SPEED;
                dist_hare=dist_hare+temp;
        }
        //pthread_t Temp;
        //pthread_create(&Temp,NULL,report,NULL);
        //pthread_join(Temp,NULL);
        //printf("%d %d\n",dist_hare,dist);
		post(&mutex);
		post(&empty);
        Sleep(1000);
    }
    if(!game_over){
        printf("Hare wins\n");
        game_over=true;
    }
    return NULL;

}
void *relocate(void *vargp){
    //sleep(1);
    while(true && !game_over){
        char ch;
        int temp;
        scanf("%c%d",&ch,&temp);
        if(ch=='T'){
            dist_turtle=temp;
        }
        if(ch=='H'){
            dist_hare=temp;
        }
    }
    return NULL;
}

int main()
{
    game_over=false;
    pthread_t TURTLE,HARE,RELOCATE,REPORT;

    pthread_create(&TURTLE, NULL, turtle, NULL);
    pthread_create(&HARE,NULL, hare, NULL);
    pthread_create(&RELOCATE, NULL, relocate, NULL);
    pthread_create(&REPORT, NULL, report, NULL);

    pthread_join(TURTLE, NULL);
    pthread_join(HARE, NULL);
    pthread_join(RELOCATE, NULL);
    pthread_join(REPORT,NULL);

    printf("%s\n","Race Finished..");
    exit(0);
}
