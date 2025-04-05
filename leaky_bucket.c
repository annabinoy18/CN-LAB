#include<stdio.h>
#include<stdlib.h>

void leaky_bucket(int bucket_capacity,int leak_rate,int num_packets,int packet[]){
    int bucket=0;
    printf("Time\tPacket\tBucket\t\tLeaked\tReamaining\n");
    
    for (int i=0;i<num_packets;i++){
        printf("%d\t%d\t",i+1,packet[i]);
        
        bucket+=packet[i];
        if(bucket>bucket_capacity){
            printf("%d (Dropped %d)\t",bucket_capacity,(bucket-bucket_capacity));
            bucket=bucket_capacity;
        }
        else{
            printf("%d\t\t",bucket);
        }
        
        
        int leaked=(bucket>leak_rate)?leak_rate:bucket;
        printf("%d\t%d\n",leaked,bucket-leaked);
        bucket-=leaked;
    }
    
    int times=num_packets+1;
    while(bucket>0){
        int leaked=(bucket>leak_rate)?leak_rate:bucket;
        printf("%d\t%d\t%d\t\t%d\t%d\n",times,0,bucket,leaked,bucket-leaked);
        bucket-=leaked;
        times++;
    }
}

int main(){
    int bucket_capacity,leak_rate,num_packets;
    
    printf("enter the bucket_capacity\n");
    scanf("%d",&bucket_capacity);
    
    printf("enter the leak_rate\n");
    scanf("%d",&leak_rate);
    
    printf("emter the total no of packets\n");
    scanf("%d",&num_packets);
    
    int packets[num_packets];
    printf("enter the packets\n");
    for(int i=0;i<num_packets;i++){
        scanf("%d",&packets[i]);
    }
    
    leaky_bucket(bucket_capacity,leak_rate,num_packets,packets);
    
    return 0;
}
