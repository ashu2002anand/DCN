#include<unistd.h>
#include<stdio.h>
int main(void)
{
  int n;
  int fd[2];
  int pid;
  char line[20];
  if (pipe(fd)<0)
    printf("pipe error\n");
  else
    printf("pipe created\n");
  if((pid=fork())<0)
    printf("fork error\n");
  else
    printf("%d",pid);
  if (pid>0)
  {
    close (fd[0]);
    write (fd[1], "hello world\n", 12);
  }
  else
  {
    close (fd[1]);
    n = read (fd[0], line, 20);
    write (STDOUT_FILENO, line, n);
  }
}
