#include "lib.h"
#include <stdio.h>
#include <string.h>

int main() {
    char buf[8] = { 0 };
    char* p1 = "01234";
    char* p2 = "01234567890";
    // case 1:
    char* dst = my_strcpy(buf, p1);
    printf("case 1:\n%p: %s\n", dst, buf);
    // case 2: 缓冲区溢出，p2 超过 buf 长度
    // memset(buf, 0, sizeof(buf));
    // my_strcpy(buf, p2);
    // printf("%s\n", buf);
    // case 3: 限定长度复制
    memset(buf, 0, sizeof(buf));
    // 最后一位留给 \0
    dst = my_strncpy(buf, p2, sizeof(buf) - 1);
    printf("case 3:\n%p: %s\n", dst, buf);
    return 0;
}
