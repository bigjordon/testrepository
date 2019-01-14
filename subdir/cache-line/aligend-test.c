struct test {
    char a;
    int b;
    char c;
    char d ;
}__attribute__((__aligned__(4096))); // sizeof(test) is 4096
struct test1 {
    char a;
    int b;
    char c;
    char d __attribute__((__aligned__(4096)));
};                                  // sizeof(test1) is 8192
int main()
{
    struct test ttt;
    struct test1 sss;
    return 0;
}
