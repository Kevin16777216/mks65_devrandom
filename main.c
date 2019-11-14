#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

void print_arr(int *arr, size_t len) {
  int i = -1;
  while(++i < len) {
    printf("\trandom %d: %d\n", i, *arr++);
  }
  printf("\n");
}

int myOpen(char *filename, int flag) {
  int output = open(filename, flag);
  if(output < 0) printf("error %d: %s\n", errno, strerror(errno));
  return output;
}

int myNewOpen(char *filename, int flag, int permissions) {
  int ans = open(filename, flag, permissions);
  if(ans < 0) ans = my_open(filename, O_WRONLY);
  return ans;
}

int my_read(int file, int *buffer, int size) {
  int ans = read(file, buffer, size);
  if(ans < 0) printf("error %d: %s\n", errno, strerror(errno));
  return ans;
}

int my_write(int file, int *buffer, int size) {
  int ans = write(file, buffer, size);
  if(ans < 0) printf("error %d: %s\n", errno, strerror(errno));
  return ans;
}

int main() {
  int devrandom = my_open("/dev/random", O_RDONLY);
  int newfile = my_new_file_open("newRand", O_CREAT | O_EXCL | O_WRONLY, 0644);
  int newfile_read = my_open("newRand", O_RDONLY);
  int rand1[10];
  int rand2[10];
  
  printf("Generating random numbers:\n");
  my_read(devrandom, rand1, 10 * sizeof(int));
  print_arr(randarr1, 10);

  printf("Writing numbers to file...\n\n");
  my_write(newfile, rand1, 10 * sizeof(int));

  printf("Checking written values:\n");
  my_read(newfile_read, rand2, 10 * sizeof(int));
  print_arr(randarr2, 10);

  close(devrandom);
  close(newfile);
  close(newfile_read);
  return 0;
}
