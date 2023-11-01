
## Case 1

以下是 `strcpy` 的实现。

```c
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
```

这段代码需要首先判断目标地址和源地址是否是空指针，如果是的话就退出。

随后用双指针在目标地址和源地址上遍历，依次复制，直到源地址指针指向终止字符就停下来。

Case 1 即在缓冲区长度大于等于源字符串长度（含终止字符）时，这段代码可以正常运作。

## Case 2

Case 2 即缓冲区长度小于源字符串长度，但依然使用不带长度保护的 `strcpy`。例如：

```c
    char buf[8] = { 0 };
    char* p2 = "01234567890";
    // case 2: 缓冲区溢出，p2 超过 buf 长度
    memset(buf, 0, sizeof(buf));
    my_strcpy(buf, p2);
    printf("%s\n", buf);
```

导致运行结果为：

```
01234567890E���S�fIm
fish: Job 1, './demo' terminated by signal SIGABRT (Abort)
```

由于把源字符串复制到目标地址时，长度超过了缓冲区，覆盖了 `\0` 的位置，输出无法正确停止，且报错缓冲区溢出。

## Case 3

考虑在执行函数时传入一个长度上限 `num`，若源字符串复制完了，循环变量还没有到 `num` 则后面部分填写 `\0`，否则最多复制 `num` 次。调用该函数传入 `sizeof(dst) - 1` 即目标地址缓冲区长度减 $1$（最后一位留给终止字符）。

```c
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
```

```c
    char buf[8] = { 0 };
    char* p2 = "01234567890";
    // case 3: 限定长度复制
    // 最后一位留给 \0
    dst = my_strncpy(buf, p2, sizeof(buf) - 1);
    printf("case 3:\n%p: %s\n", dst, buf);
```

运行结果为：

```
case 3:
0x16d846420: 0123456
```
