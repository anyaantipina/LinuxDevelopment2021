#define _GNU_SOURCE
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <dlfcn.h>

typedef int (*remove_type)(const char* file_name);

int remove(const char* file_name) {
    remove_type orig_remove;
    orig_remove = (remove_type)dlsym(RTLD_NEXT,"remove");
    if (strstr(file_name, "PROTECT") != NULL) {
        errno = 111;
        return -1;
    }
    return orig_remove(file_name);
 }