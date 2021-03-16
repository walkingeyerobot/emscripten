#include <stdio.h>
#include <pthread.h>

int get_side_tls();
int* get_side_tls_address();

static __thread int main_tls = 10;

int get_main_tls() {
  return main_tls;
}

int* get_main_tls_address() {
  return &main_tls;
}

void report_tls() {
  //printf("side_tls address: %p\n", get_side_tls_address());
  printf("side_tls value  : %d\n", get_side_tls());
  //printf("main_tls address: %p\n", get_main_tls_address());
  printf("main_tls value  : %d\n", get_main_tls());
}

void test_tls(int inc) {
  report_tls();
  int* m = get_main_tls_address();
  int* s = get_side_tls_address();
  *m = *m + inc;
  *s = *s + inc;
  printf("increment done\n");
  report_tls();
}

void* thread_main(void* arg) {
  printf("thread_main\n");
  test_tls(10);
  return NULL;
}

int main() {
  printf("main\n");
  test_tls(20);

  // Now do the same on a second thread
  pthread_t t;
  pthread_create(&t, NULL, thread_main, NULL);
  pthread_join(t, NULL);

  printf("success\n");
}
