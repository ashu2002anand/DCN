#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main() {
    int packets[8], i, clk, b_size, o_rate, p_sz_rm = 0, p_sz, p_time;
    for(i = 0; i < 5; i++) {
        packets[i] = rand() % 10;
        if(packets[i] == 0) i--;
    }
    
    printf("Enter output rate: ");
    scanf("%d", &o_rate);
    printf("Enter bucket size: ");
    scanf("%d", &b_size);

    for(i = 0; i < 5; i++) {
        if((packets[i] + p_sz_rm) > b_size) {
            printf(packets[i] > b_size ? "\nIncoming packet size: %d greater than bucket capacity\n" : "Bucket size exceeded\n", packets[i]);
        } else {
            p_sz = packets[i];
            p_sz_rm += p_sz;
            printf("\nIncoming packet: %d\nTransmission left: %d\n", p_sz, p_sz_rm);
            p_time = rand() % 10;
            printf("Next packet will come at %d\n", p_time);

            for(clk = 0; clk < p_time && p_sz_rm > 0; clk++) {
                printf("Time left %d --- No packet to transmit!!\n", p_time - clk);
                sleep(1);
                p_sz_rm = p_sz_rm < o_rate ? 0 : p_sz_rm - o_rate;
                printf("Transmitted\nBytes remaining: %d\n", p_sz_rm);
            }
        }
    }
    return 0;
}
