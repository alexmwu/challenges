#include <cstdlib>
#include <ctime>
#include <cstdio>

int main() {
  srand(time(NULL));
  printf("%d\n", rand()%2 == 0 ? (rand()%1700 + 100):(rand()%3000+ 10000));
}
