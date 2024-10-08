#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <netdb.h>
#define BUFLEN 9000

int main(){
char buf[BUFLEN];
int flag=0, str;
struct sockaddr_in sin;
int sock_descriptor;
int temp_sock_descriptor;
int address_size;

sock_descriptor=socket(AF_INET, SOCK_STREAM, 0);
bzero(&sin, sizeof(sin));

sin.sin_family=AF_INET;
sin.sin_addr.s_addr=INADDR_ANY;
sin.sin_port=htons(8000);
bind(sock_descriptor,(struct sockaddr *)&sin, sizeof(sin));

listen(sock_descriptor,4);

temp_sock_descriptor=accept(sock_descriptor, NULL, NULL);

recv(temp_sock_descriptor, buf, sizeof(buf), 0);

printf("\n data received\n");
puts(buf);

printf("enter the data to be sent: \n");
fgets(buf, sizeof(buf), stdin);
send(temp_sock_descriptor, buf, sizeof(buf), 0);

close(temp_sock_descriptor);
exit(0);
}
