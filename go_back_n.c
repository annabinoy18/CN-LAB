#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>

#define WINDOW_SIZE 4
#define TOTAL_PACKET 5
#define LOSS_PROB 20

int send_frame(int frame){
    printf("sending %d frame \n",frame);
    sleep(1);
    
    int rand_value=rand()%100;
    
    if(rand_value<LOSS_PROB){
        printf("%d frame lost..\n",frame);
        return 0;
    }
    printf("%d frame send successfully!\n",frame);
    return 1;
}

int ack_rec(int frame){
    printf("ack for %d frame receiveing\n",frame);
    sleep(1);
    
    int rand_value=rand()%100;
    
    if (rand_value<LOSS_PROB){
        printf("ack for %d lost...\n",frame);
        return 0;
    }
    printf("received ack of %d frame successfully!\n",frame);
    return 1;
}

void go_back_and_n(){
    int base=0,next_frame=0;
    
    while(base<TOTAL_PACKET){
        while(next_frame<base+WINDOW_SIZE && next_frame<TOTAL_PACKET){
            if(send_frame(next_frame)){
                next_frame++;
            }
            else{
                printf("frame %d will be retransmitted later.\n",next_frame);
                break;
            }
        }
        
        if(ack_rec(base)){
            printf("%d frame acknowledged.Sliding Window....\n",base);
            base++;
        }
        else{
            printf("ACK lost for frame %d. Go-Back-N retransmission from frame %d.\n\n", base, base);
            next_frame=base;
        }
    }
    printf("\n\nAll frames sent and ack successfully\n");
}

int main(){
    srand(time(0));
    printf("=== Go-Back-N ARQ Simulation ===\n\n");
    go_back_and_n();
    return 0;
}
