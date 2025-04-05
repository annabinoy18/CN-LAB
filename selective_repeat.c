#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>

#define WINDOW_SIZE 4 
#define TOTAL_FRAME 10
#define LOSS_PROB 20

int send_frame(int frame){
    printf("sending %d frame....\n",frame);
    sleep(1);
    
    int rand_value=rand()%100;
    if(rand_value<LOSS_PROB){
        printf("%d frame lost.\n",frame);
        return 0;
    }
    printf("%d frame send successfully.\n",frame);
    return 1;
}

int ack_received(int frame){
    printf("Recieving ack 0f %d frame...\n",frame);
    sleep(1);
    
    int rand_value=rand()%100;
    if(rand_value<LOSS_PROB){
        printf("ack of %d frame lost\n",frame);
        return 0;
    }
    printf("Ack of %d recieved sucessfully.\n",frame);
    return 1;
}

void selective_repeat(){
    int send_frames[TOTAL_FRAME]={0};
    int ack_rec[TOTAL_FRAME]={0};
    int base=0;
    
    while(base<TOTAL_FRAME){
        for(int i=base;i<base+WINDOW_SIZE && i<TOTAL_FRAME;i++){
            if(!send_frames[i]){
                send_frames[i]=send_frame(i);
            }
        }
        
        for(int i=base;i<base+WINDOW_SIZE && i<TOTAL_FRAME;i++){
            if(send_frames[i] && !ack_rec[i]){
                ack_rec[i]=ack_received(i);
            }
        }
        
        while(base<TOTAL_FRAME && ack_rec[base]){
            printf("Sliding window forward. Frame %d fully acknowledged.\n", base);
            base++;
        }
    }
    printf("\n\nall frames sent succussfully\n");
}

int main(){
    srand(time(0));
    printf("===========selective repeat arq============\n");
    selective_repeat();
    return 0;
}
