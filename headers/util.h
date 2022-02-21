#ifndef UTIL_H_
#define UTIL_H_

#define BBLK "\e[1;90m"
#define BRED "\e[1;31m"
#define reset "\e[0m"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

typedef enum {
  false,
  true
} bool;

void *mallocSafe(size_t);

#endif