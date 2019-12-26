#include <stdio.h>

#include <sys/time.h>
#include <time.h>

// get current time
char* get_current_time() {

  static char fmt[27];
  static char buff[20];

  struct timeval tv;
  gettimeofday(&tv, NULL);
  struct tm *tm = localtime(&tv.tv_sec);

  strftime(buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", tm);
  snprintf(fmt, sizeof(fmt), "%s.%06ld", buff, tv.tv_usec);

  return fmt;
}


int main() {

  for (int i=0; i<20; ++i) {
    printf("%s\n", get_current_time());
  }

  return 0;
}
