#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <assert.h>
#include <time.h>

#include <array>

#define MAX_BUFFER_SIZE 256

void processDigit(char *buf, size_t& idx, int *i) {
    switch (*buf) {
        case '1': case '2': case '3': case '4': case '5': case '6': 
        case '7': case '8': case '9':
            *i = *buf - '0';
            idx++;
            break;
        case 'o':
            if(*(buf + 1) == 'n' && *(buf + 2) == 'e') {
                *i = 1;
                idx += 3;
            } 
            break;
        case 't':
            if (*(buf + 1) == 'w' && *(buf + 2) == 'o') {
                *i = 2;
                idx += 3;
            } else if(strncmp(buf + 1, "hree", 4) == 0) {
                *i = 3;
                idx += 5;
            }
            break;
        case 'f':
            if(strncmp(buf + 1, "our", 3) == 0) {
                *i = 4;
                idx += 4;
            } else if(strncmp(buf + 1, "ive", 3) == 0) {
                *i = 5;
                idx += 4;
            }
            break;
        case 's':
            if(*(buf + 1) == 'i' && *(buf + 2) == 'x') {
                *i = 6;
                idx += 3;
            } else if(strncmp(buf + 1, "even", 4) == 0) {
                *i = 7;
                idx += 5;
            }
            break;
        case 'e':
            if(strncmp(buf + 1, "ight", 4) == 0) {
                *i = 8;
                idx += 5;    
            }
            break;
        case 'n':
            if(strncmp(buf + 1, "ine", 3) == 0) {
                *i = 9;
                idx += 4;    
            }
            break;
        default:
            break;
    }
}

static inline size_t get1stDigit(char *buf, int *i) {
    size_t idx = 0;
    *i = -1;
    while(*buf) {
        processDigit(buf, idx, i);
        if(*i > 0 && *i <= 9) break;
        buf++;
        idx++;
    }
    return idx;
}


int main (void) {
    char buffer[MAX_BUFFER_SIZE];
    FILE *f = fopen("challenge_1.txt", "r");
    assert(f);
    int i;
    while (fgets(buffer, MAX_BUFFER_SIZE, f)) {
        get1stDigit(buffer, &i);
        printf("buffer: %s -> 1st digit: %d\n", i);
    }
    fclose(f);
    return EXIT_SUCCESS;
}

