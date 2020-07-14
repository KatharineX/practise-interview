#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define num int
#define str char *
#define strs char **

// check arg
#define argc(b, a) \
    while (b < 3)  \
        return 1;  \
    ;

// check 2ch
#define ch2c(a) \
    slen(a) if (len < 10) return len & 1;

// len
#define slen(s)                            \
    len = 0;                               \
    while (*(s + len++) && len < (1 << 8)) \
        ;

// allocate space
#define smelloc(a, b, c) \
    malloc(*(*a + b) + *(*a + c));

// copy memory
#define place(p, a, b, c, bs, cs)                          \
    memcpy(p, (*(a + b)), *(*a + bs));                     \
    memcpy(p + *(*a + bs), (*(a + c)), *(*a + cs));        \
    // memcpy(p + *(*a + bs) + *(*a + cs), (*a + cs), '\0'); \
    ;

// concatenate two strings
int main(num len, strs a)
{
    argc(len, a);
    ch2c((*a))

    slen((*(a + 1))) *
    (*a + 0) = len - 1;

    slen((*(a + 2))) * (*a + 1) = len - 1;

    void *p = (char *)smelloc(a, 0, 1);
    place(p, a, 1, 2, 0, 1);
    *a = (char *)p;
    int length = strlen(*a)+1;
    char * new;
    new = (new, *a);
    new[length] = '\0';
    printf("%s\n", new);
    // printf("%s\n", *a);
    free(*a);

    // char * str2 = "hel\\lll";
    // int length = sizeof(str2)/sizeof(str2[0]);
    // while(*str2){
    //     printf("%c", *str2++);

    // }
    // printf("\n");

    // unsigned char * s = "hello00000000000000" + 5;
    // int y = 24;
    // printf("%c: %c\n", (15)[s + 10], *(s -20 + 5));
    // if(10[15+s] == (-10)[s-10]+5){
    //     printf("hello");
    // }

    // int i[50];int h[50];
  
    // for(int j = 0; j< 50; j++){
    //     i[j] = 0;
    //     h[j] = 0;

    // }
    // ((&(i[0])) + 5)[5] = 20;
    // // (h + 7)[3] = 20;
    // &(h-10)[5] = 20;

    // for (int j = 0; j < 50; j++)
    // {
    //    printf("i = %d, h = %d \n", i[j], h[j]);
    // }
    // (&(h-10))[5] = 20;

    return 0;
}
