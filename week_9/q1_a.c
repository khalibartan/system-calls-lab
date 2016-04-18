#include<stdio.h>
#include<pthread.h>
#include<signal.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<time.h>
pthread_t threads[3];
pthread_cond_t cond;
int turtle_move = 1;
int hare_move = 10;
int turtle_pos = 0;
int hare_pos = 0;
typedef enum{false, true} bool;
bool game_finish = false;
void move_turtle();
void run_hare();
int play = 1;
pthread_mutex_t lock;
void *Turtule(){
    pthread_mutex_lock(&lock);
    while(!play) { 
        pthread_cond_wait(&cond, &lock);
    }
    pthread_mutex_unlock(&lock);
    int local_turtle_pos = 0;
    int finish_pos = 100;
    
    while(local_turtle_pos <= finish_pos){
        move_turtle();
        pthread_mutex_lock(&lock);
        local_turtle_pos = turtle_pos;
        pthread_mutex_unlock(&lock);
    }
    pthread_mutex_lock(&lock);
    game_finish = true;
    pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
}
void move_turtle(){
    pthread_mutex_lock(&lock);
    turtle_pos += turtle_move;
    pthread_mutex_unlock(&lock);
    sleep(1);
}
void *Hare(){
    srand(time(NULL));
    pthread_mutex_lock(&lock);
    while(!play) { 
        pthread_cond_wait(&cond, &lock);
    }
    pthread_mutex_unlock(&lock);
    int local_hare_pos = 0;
    int finish_pos = 100;
    int pause_steps = random()%30;
    while(local_hare_pos <= finish_pos){
        if(random()%10>5)
        while(turtle_pos - pause_steps < local_hare_pos){
            sleep(1);
        }
        run_hare();
        pthread_mutex_lock(&lock);
        local_hare_pos = hare_pos ;
        pthread_mutex_unlock(&lock);
        srand(time(NULL));
        pause_steps = random()%40;
    }
    pthread_mutex_lock(&lock);
    game_finish = true;
    pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
}
void run_hare(){
    pthread_mutex_lock(&lock);
    hare_pos += hare_move ;
    pthread_mutex_unlock(&lock);
    usleep(500000);
}
void God(int sig){
    pthread_mutex_lock(&lock);
    signal(sig, SIG_IGN);
    printf("God called\nWhose position you want to change(t for turtle, h for hare): ");
    char c;
    scanf("%c",&c);
    printf("Enter the position: ");
    play = 0;
    if(c=='t'){
        scanf("%d",&turtle_pos);
    }
    else if(c=='h'){
        scanf("%d",&hare_pos);
    }
    play = 1;
    pthread_mutex_unlock(&lock);
    signal(sig, God);
    
}
void *Report(){
    bool local_game_finish = false;
    while(!local_game_finish){
        sleep(1);
        pthread_mutex_lock(&lock);
        while(!play) { 
            pthread_cond_wait(&cond, &lock);
        }
        printf("Turtule position is %d\nHare position is %d\n", turtle_pos, hare_pos);
        local_game_finish = game_finish;
        if(local_game_finish){
            if(turtle_pos >= 100){
                printf("Turtle won !!\n");
                exit(0);
            }
            else if(hare_pos>=100){
                 printf("Hare won!!\n");
                 exit(0);
            }
       }
        pthread_mutex_unlock(&lock);
    }
    pthread_exit(NULL);
}

int main(){
    signal(SIGINT, God);   
    printf("Use ctrl+c for calling god\n");
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);
    pthread_create(&threads[0], NULL, Turtule, NULL);
    pthread_create(&threads[1], NULL, Hare, NULL);
    pthread_create(&threads[3], NULL, Report, NULL);
    pthread_exit(NULL);
    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&lock);
    return 0;
}

