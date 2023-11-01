#include <stdio.h>

char* my_strcpy(char* dst, char* src) {
    if (dst == NULL || src == NULL) {
        return NULL;
    }
    char* s = dst;
    char* t = src;
    // 复制到终止字符 \0 为止
    while (*t != '\0') {
        *s = *t;
        s++;
        t++;
    }
    return dst;
}

// https://en.cppreference.com/w/cpp/string/byte/strncpy
char* my_strncpy(char* dst, char* src, int num) {
    if (src == NULL || dst == NULL) {
        return NULL;
    }
    char* s = dst;
    char* t = src;
    // 标记是否复制到了 t 的终止字符
    int src_terminate = 0;
    for (int i = 0; i < num; i++) {
        if (*t == '\0') {
            src_terminate = 1;
        }
        // 如果 src 已经复制完了，但没有到 num，那么后面赋值为 \0
        if (src_terminate) {
            *s = '\0';
            s++;
        } else {
            // 否则复制 src
            *s = *t;
            s++;
            t++;
        }
    }
    return dst;
}
