#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>

#define TIMEOUT  3 
#define TOTAL_PACKETS 5

int simulate_ack(){
    return rand()%10 < 7;
}

int main(){
    int packet=1;
    int ack;
    srand(time(0));
    while(packet<=TOTAL_PACKETS){
        printf("sender: sending packet %d\n",packet);
        sleep(1);
        
        ack=simulate_ack();
        
        if(ack){
            printf("Reciever: Ack for packet %d received.\n",packet);
            packet++;
        }
        else{
            printf("Reciever: Ack for packet %d lost....retransmitting\n",packet);
            sleep(TIMEOUT);
        }
    }
    printf("All packets send successfully!\n");
    
    return 0;
}
