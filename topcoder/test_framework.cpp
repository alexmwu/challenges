//A test framework I found online

//
// Copyright (c) 2010 Tuomas Pelkonen, tuomaspelkonen.com
//
// Permission is hereby granted, free of charge, to any person
// obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without
// restriction, including without limitation the rights to use,
// copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following
// conditions:
//
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
// OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
//

#include <pthread.h>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

vector <string> test(int N,
                     vector<string> &tiles,
                     double time_multiplier,
                     double *elapsed);

#define NUM_THREADS 2
static pthread_t threads[NUM_THREADS];
static pthread_mutex_t mutex;

static int last_test;
static int next_test;
static double scores[1000];
static double total = 0;
static int scores_count = 0;
static int scores_printed = 0;
static bool scores_available[1000];
static double elapsed[1000];

#define SQUARE(x) ((x) * (x))
#define ABS(x) ((x) < 0 ? -(x) : (x))
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define PI 3.14159265358979

static unsigned int low = 0;
static unsigned int high = 0;

unsigned int my_random()
{
  high = (high << 16) + (high >> 16);
  high += low;
  low += high;

  return high;
}

void my_srandom(unsigned int seed)
{
  high = seed;
  low = high ^ 0x49616E42;
}

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

void generate(int test_number, int *n, vector<string> &tiles)
{
  my_srandom((test_number + 1) * 7919);

  int c = my_random() % 21 + 10;
  *n = my_random() % 13 + 8;
  int board[400][4];

  for (int i = 0; i < *n; i++)
    {
      for (int j = 0; j < *n; j++)
        {
          for (int k = 0; k < 4; k++)
            {
              board[i * *n + j][k] = my_random() % c;
            }

          if (i > 0)
            board[i * *n + j][NORTH] = board[(i - 1) * *n + j][SOUTH];
          if (j > 0)
            board[i * *n + j][WEST] = board[i * *n + j - 1][EAST];
        }
    }

  bool used[400];
  memset(used, 0, sizeof(used));

  for (int i = 0; i < *n * *n; i++)
    {
      char temp[32];

      int piece = my_random() % (*n * *n);
      while (used[piece])
        piece = my_random() % (*n * *n);

      int rot = my_random() % 4;

      used[piece] = true;
      snprintf(temp, 32, "%d %d %d %d",
               board[piece][(NORTH + rot) % 4],
               board[piece][(EAST + rot) % 4],
               board[piece][(SOUTH + rot) % 4],
               board[piece][(WEST + rot) % 4]);
      tiles.push_back(temp);
    }
}

double get_score(int n, vector<string> &tiles, vector<string> &ret)
{
  int board[400][4];
  int index[400];
  int rotation[400];

  for (int i = 0; i < n * n; i++)
    {
      sscanf(tiles[i].c_str(), "%d %d %d %d", &board[i][0], &board[i][1],
             &board[i][2], &board[i][3]);
      sscanf(ret[i].c_str(), "%d %d", &index[i], &rotation[i]);
    }

  int matches = 0;
  for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
        {
          if (j < n - 1)
            {
              int col1 = board[index[i * n + j]]
                [(EAST + (4 - rotation[i * n + j])) % 4];
              int col2 = board[index[i * n + j + 1]]
                [(WEST + (4 - rotation[i * n + j + 1])) % 4];

              if (col1 == col2)
                matches++;
            }

          if (i < n - 1)
            {
              int col1 = board[index[i * n + j]]
                [(SOUTH + (4 - rotation[i * n + j])) % 4];
              int col2 = board[index[(i + 1) * n + j]]
                [(NORTH + (4 - rotation[(i + 1) * n + j])) % 4];

              if (col1 == col2)
                matches++;
            }
        }
    }

  return (double)matches / ((n - 1) * n * 2);
}

void *worker_thread_cb(void *arg)
{
  while (true)
    {
      pthread_mutex_lock(&mutex);

      int test_number = next_test;
      next_test++;
      if (test_number > last_test)
        {
          pthread_mutex_unlock(&mutex);
          break;
        }

      vector<string> tiles;
      int n = 0;
      generate(test_number, &n, tiles);
      pthread_mutex_unlock(&mutex);
      vector<string> ret = test(n, tiles, 1.0,
                                &elapsed[test_number]);

      pthread_mutex_lock(&mutex);
      scores[test_number] = get_score(n, tiles, ret);

      if (scores[test_number] < 0.0)
        {
          fprintf(stderr, "FAIL\n");
          exit(0);
        }

      scores_available[test_number] = true;

      for (int i = scores_printed; i < next_test; i++)
        {
          if (!scores_available[i])
            break;

          scores_printed++;

          total += scores[i];
          scores_count++;

          printf("%4d %4d %.3f %5.4f %.2f\n",
                 i, scores_count, scores[i], total / scores_count, elapsed[i]);
        }

      pthread_mutex_unlock(&mutex);
    }  

  return NULL;
}

void run_visualizer()
{
  int n;

  char temp[32];
  fgets(temp, 32, stdin);
  vector<string> tiles;

  n = atoi(temp);

  for (int i = 0; i < n * n; i++)
    {
      fgets(temp, 32, stdin);
      tiles.push_back(temp);
    }
  fprintf(stderr, "N %d\n", n);

  double elapsed;
  vector<string> ret = test(n, tiles, 1.0, &elapsed);

  for (int i = 0; i < (int)ret.size(); i++)
    {
      printf("%s\n", ret[i].c_str());
    }
  fflush(NULL);
}

//extern bool output_debug;

int main(int argc, char **argv)
{
  memset(scores_available, 0, sizeof(scores_available));

  if (argc == 1)
    {
      last_test = 119;
      next_test = 0;
    }
  else if (argc == 2)
    {
      if (strcmp(argv[1], "vis") == 0)
        {
          run_visualizer();
          return 0;
        }

      next_test = atoi(argv[1]);
      last_test = next_test;
    }
  else if (argc >= 3)
    {
      next_test = atoi(argv[1]);
      last_test = atoi(argv[2]);
#if 0
      if (argc >= 4)
        output_debug = false;
#endif
    }

  scores_printed = next_test;

  pthread_mutex_init(&mutex, NULL);

  for (int i = 0; i < NUM_THREADS; i++)
    {
      pthread_create(&threads[i], NULL, worker_thread_cb, (void *)i);
    }

  for (int i = 0; i < NUM_THREADS; i++)
    {
      pthread_join(threads[i], NULL);
    }

  return 0;
}