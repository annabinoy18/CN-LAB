#include<stdio.h>

#define MAXSIZE 10
#define INFINITY 9999

int cost[MAXSIZE][MAXSIZE], dist[MAXSIZE][MAXSIZE], nexthop[MAXSIZE][MAXSIZE];
int nodes;

void initialize(){
    for(int i=0;i<nodes;i++){
        for (int j=0;j<nodes;j++){
            dist[i][j]=cost[i][j];
            nexthop[i][j]=j;
        }
    }
}

void update(){
    int updated;
    do{
        updated=0;
        for(int i=0;i<nodes;i++){
            for(int j=0;j<nodes;j++){
                for(int k=0;k<nodes;k++){
                    if (dist[i][j]>dist[i][k]+dist[k][j]){
                        dist[i][j]=dist[i][k]+dist[k][j];
                        nexthop[i][j]=nexthop[i][k];
                        updated=1;
                    }
                }
            }
        }
    }while(updated);
}

void display(){
    for (int i=0;i<nodes;i++){
        printf("Router %d's routing table:\n",i);
        printf("Distance\t\tcost\t\tnexthop\n");
        for(int j=0;j<nodes;j++){
            printf("%d\t\t%d\t\t%d\n",j+1,dist[i][j],nexthop[i][j]+1);
        }
    }
}

int main(){
    printf("enter the no of routers\n");
    scanf("%d",&nodes);
    
    printf("enter the cost matrix(enter 9999 if there is no direct connection)");
    for(int i=0;i<nodes;i++){
        for(int j=0;j<nodes;j++){
            scanf("%d",&cost[i][j]);
            if(i==j){
                cost[i][j]=0;
            }
        }
    }
    
    initialize();
    update();
    display();
    
    return 0;
}
