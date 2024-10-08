#include<stdio.h>
#include<conio.h>
#include<ctype.h>

#define numOfNodes 10
#define permanent 1
#define tentative 0

struct node{
    unsigned int weight;
    int prev;
    int state;
};

void main(){
    int table[numOfNodes][numOfNodes]={
        {0,1,0,0,0,4,0,0,0,0},
        {1,0,4,0,0,0,0,1,0,0},
        {0,4,0,3,2,0,0,0,3,0},
        {0,0,3,0,1,0,0,0,0,0},
        {0,0,2,1,0,3,0,0,0,1},
        {4,0,0,0,3,0,1,0,0,0},
        {0,0,0,0,0,1,0,2,0,2},
        {0,1,0,0,0,0,2,0,1,0},
        {0,0,3,0,0,0,0,1,0,2},
        {0,0,0,0,1,0,2,0,2,0}
    };
    int src,dest,i,working_node;
    unsigned int min;

    struct node nodes[numOfNodes];
    for( i=0;i<numOfNodes;i++){
	nodes[i].state =tentative;
	nodes[i].weight = -1;
    }

    printf("\nEnter Source:");
    src = getche();
    working_node = src = toupper(src)-'A';
    nodes[src].prev = -1;
    nodes[src].weight =0;
    printf("\nEnter Destination:");
    dest = toupper(getche())-'A';

    do{
	nodes[working_node].state = permanent;
	for( i=0;i<numOfNodes;i++){
	    if(table[working_node][i]!=0 && nodes[i].state==tentative){
		if(nodes[working_node].weight+table[working_node][i]< nodes[i].weight){
		    nodes[i].weight = nodes[working_node].weight + table[working_node][i];
		    nodes[i].prev = working_node;
		}
	    }
	}
	min=-1;
	for(i=0;i<numOfNodes;i++){
	    if(nodes[i].state==tentative && nodes[i].weight<min){
		min = nodes[i].weight;
		working_node=i;
	    }
	}
    } while (working_node!=dest);

    printf("\nShortest Path got--->\n%c",dest+65);
    do{
	working_node = nodes[working_node].prev;
	printf("<-%c",working_node+65);
    } while (nodes[working_node].prev!=-1);

    printf("\nAt a total weight of:%d",nodes[dest].weight);
}