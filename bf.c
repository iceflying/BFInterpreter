#define LEN 50000

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    FILE *input = fopen(argv[1], "r");
	char source[LEN] = {0};
	char runtime[LEN] = {0};
    char *sptr, *wptr;
    int pos = 0;
    int wflag = 0;
    int line = 1, col = 0, wline, wcol;
    sptr = source;
    while (wflag || EOF!=fscanf(input, "%c", sptr))
    {
        if (!wflag)
            ++col;
        else
            ++wcol;
        switch (*sptr)
        {
            case '>' :
                ++pos;
                break;
            case '<' :
                if (--pos <0)
                {
                    printf("%d : %d : ERROR: Illegal pointer value\n", line, col);
                    return 1;
                }
                break;
            case '+' :
                ++runtime[pos];
                if (runtime[pos] < 0 || runtime[pos] > 255)
                {
                    if (!wflag)
                        printf("%d : %d : ERROR: Illegal value\n", line, col);
                    else
                        printf("%d : %d : ERROR: Illegal value\n", wline, wcol);
                    return 1;
                }
                break;
            case '-' :
                --runtime[pos];
                if (runtime[pos] < 0 || runtime[pos] > 255)
                {
                    if (!wflag)
                        printf("%d : %d : ERROR: Illegal value\n", line, col);
                    else
                        printf("%d : %d : ERROR: Illegal value\n", wline, wcol);
                    return 0;
                }
                break;
            case '.' :
                putchar(runtime[pos]);
                break;
            case ',' :
                runtime[pos]=getchar();
                break;
            case '[' :
                if (runtime[pos])
                    wptr = sptr-1;
                else
                    wflag = 0;
                wline = line;
                wcol = col;
                break;
            case ']' :
                sptr = wptr;
                wflag = 1;
                line = wline;
                col = wcol;
                break;
            case '\n' :
                if (!wflag)
                {
                    ++line;
                    col = 0;
                }
                else
                {
                    ++wline;
                    wcol = 0;
                }
                break;
        }
        ++sptr;
    }
    fclose(input);
    return 0;
}
