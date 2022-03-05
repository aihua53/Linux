/*
 * 
 * memtester version 1
 * 
 */
// #include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define __version__ "version: 1.0"
#define EXIT_FAIL_NONSTARTER    0x01

typedef unsigned long ul;
typedef unsigned long long ull;

static void usage(char* p) {
    printf("\nUsage: %s <mem>[B|K|M|G] [loops] [interval(ms)]\n", p);
    printf("example: memtester 10M 3 1\n");
    exit(EXIT_FAIL_NONSTARTER);
}

int memtester_pagesize(void) {
    int pagesize = sysconf(_SC_PAGE_SIZE);
    if (pagesize == -1) {
        perror("get page size failed");
        exit(EXIT_FAIL_NONSTARTER);
    }
    // printf("pagesize is %ld\n", (long) pagesize);
    return pagesize;
}

int main(int argc, char** argv){
    size_t pagesize, wantraw, wantmb, wantbytes, wantbytes_orig;
    char *memsuffix, *suffix;
    int memshift, loops = 0, interval = 2;
    void *buf = NULL;
    size_t maxbytes = -1; /* addressable memory, in bytes */
    size_t maxmb = (maxbytes >> 20) + 1; /* addressable memory, in MB */

    printf(__version__);
    printf("\n");

    pagesize = memtester_pagesize();

    if (argc == 1) {
        usage(argv[0]);
        return 0;
    }


    if (optind >= argc) {
        fprintf(stderr, "need memory argument, in MB\n");
        usage(argv[0]); /* doesn't return */
    }

    // printf("optind=%d\n",optind);
    errno = 0;
    wantraw = (size_t) strtoul(argv[optind], &memsuffix, 0);
    if (errno != 0) {
        fprintf(stderr, "failed to parse memory argument");
        usage(argv[0]); /* doesn't return */
    }

    switch (*memsuffix) {
        case 'G':
        case 'g':
            memshift = 30; /* GB */
            break;
        case 'M':
        case 'm':
            memshift = 20; /* MB */
            break;
        case 'K':
        case 'k':
            memshift = 10; /* KB */
            break;
        case 'B':
        case 'b':
            memshift = 0; /* bytes */
            break;
        case '\0':  /* no suffix */
            memshift = 20; /* megabytes */
            break;
        default:
            /* bad suffix */
            usage(argv[0]); /* doesn't return */
    }
    wantbytes_orig = wantbytes = ((size_t) wantraw << memshift);
    wantmb = (wantbytes_orig >> 20);
    optind++;

    if (wantmb > maxmb) {
        printf("wantmb > maxmb\n");
        fprintf(stderr, "This system can only address %llu MB.\n", (ull) maxmb);
        exit(EXIT_FAIL_NONSTARTER);
    }
    if (wantbytes < pagesize) {
        fprintf(stderr, "bytes %ld < pagesize %ld -- memory argument too small?\n",
                wantbytes, pagesize);
        exit(EXIT_FAIL_NONSTARTER);
    }

    if (optind >= argc) {
        loops = 0;
    } else {
        errno = 0;
        loops = strtoul(argv[optind], &suffix, 0);
        if (errno != 0) {
            fprintf(stderr, "failed to parse number of loops");
            usage(argv[0]); /* doesn't return */
        }
        if (*suffix != '\0') {
            fprintf(stderr, "loop suffix %c\n", *suffix);
            usage(argv[0]); /* doesn't return */
        }
    }
    optind++;
    
    if (optind >= argc) {
        interval = 2;
    } else {
        errno = 0;
        interval = strtoul(argv[optind], &suffix, 0);
        if (errno != 0) {
            fprintf(stderr, "failed to parse number of loops");
            usage(argv[0]); /* doesn't return */
        }
        if (*suffix != '\0') {
            fprintf(stderr, "loop suffix %c\n", *suffix);
            usage(argv[0]); /* doesn't return */
        }
    }
    printf("interval: %dms\n", interval);

    for(int loop=1; ((!loops) || loop <= loops); loop++) {
        printf("Loop %d\n", loop);
        buf = malloc(wantbytes);
        memset(buf,0,wantbytes);
        sleep(interval);   
    }
    printf("Done. Press any key to exit.\n");

    while(1){
        getchar();
        getchar();
        break;     
    }

    printf("Exit.\n");
    fflush(stdout);
    exit(0);
}