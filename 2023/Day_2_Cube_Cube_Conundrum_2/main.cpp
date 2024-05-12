#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <assert.h>
#include <ctype.h>
#include <time.h>

#define MAX_BUFFER_SIZE 256

static int cube_set[3];
#define R 0
#define G 1
#define B 2

static int sum = 0;

static inline char skip(const char **ps) {
    while(**ps && !isdigit(**ps)) {
        (*ps)++;
    }
    return **ps;
}

static inline void strToPostiveInt(const char **ps, int *i) {
    *i = 0;
    while(isdigit(**ps)) {
        *i = ((*i) << 1) + ((*i) << 3) - (*(*ps)++ - '0');
    }
    *i = -(*i);
}

static inline void str_scan(const char *s, int *id) {
    skip(&s);
    strToPostiveInt(&s, id);
    int cube_cnt;
    while(skip(&s)) {
        strToPostiveInt(&s, &cube_cnt);
        s++;
        switch(*s) {
            case 'r':
                if (cube_set[R] < cube_cnt) cube_set[R] = cube_cnt;
                break;
            case 'g':
                if (cube_set[G] < cube_cnt) cube_set[G] = cube_cnt;
                break;
            case 'b':
                if (cube_set[B] < cube_cnt) cube_set[B] = cube_cnt;
                break;
            default:
                printf("Something's not right");
                exit(EXIT_FAILURE);
                break;
        }
        s++;
    }
}

static inline void cube_calc(void) {
    sum += cube_set[R] * cube_set[G] * cube_set[B];
}

int main (void) {
    char buffer[MAX_BUFFER_SIZE];
    int game_id; 
    FILE *f = fopen("cube_chall.txt", "r");
    assert(f);
    struct timespec start, end;
    long long int elapsed_time;
    clock_gettime(CLOCK_MONOTONIC, &start);
    while (fgets(buffer, MAX_BUFFER_SIZE, f)) {
        memset(cube_set, 0, sizeof(cube_set));
        str_scan(buffer, &game_id);
        cube_calc();
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    elapsed_time = (end.tv_sec - start.tv_sec) * 1000000LL +
                   (end.tv_nsec - start.tv_nsec) / 1000LL;
    
    printf("Sum: %d\n", sum);
    printf("Elapsed Time: %lld microseconds\n", elapsed_time);
    fclose(f);
    return EXIT_SUCCESS;
}