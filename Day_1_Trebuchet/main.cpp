#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <assert.h>
#include <time.h>

#define MAX_BUFFER_SIZE 256

static const char *accept = "0123456789";

int main (void) {
    char buffer[MAX_BUFFER_SIZE];
    FILE *f = fopen("challenge_1.txt", "r");
    assert(f);
    struct timespec start, end;
    long long int elapsed_time;
    int sum = 0, tmpInt;
    size_t idx;
    char char_num[3], *temp;
    char_num[2] = '\0';
    clock_gettime(CLOCK_MONOTONIC, &start);
    while (fgets(buffer, MAX_BUFFER_SIZE, f)) {
        idx = strcspn(buffer, accept);
        temp = buffer+idx;
        char_num[0] = char_num[1] = *temp;
        while(*temp) {
            if('0' <= *temp && *temp <= '9') char_num[1] = *temp;
            temp++;
        }
        tmpInt = char_num[0] - '0';
        sum +=  (tmpInt << 1) + (tmpInt << 3) + (char_num[1] - '0');
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("SUM: %d\n", sum);
    elapsed_time = (end.tv_sec - start.tv_sec) * 1000000LL +
                   (end.tv_nsec - start.tv_nsec) / 1000LL;
    printf("Elapsed Time: %lld microseconds\n", elapsed_time);
    fclose(f);
    return EXIT_SUCCESS;
}

