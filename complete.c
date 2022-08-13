#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *readnext(FILE *f, char st[])
{
    char ch, i = -1;
    ch = getc(f);
    while (ch != '\n' && ch != EOF)
    {
        st[++i] = ch;
        ch = getc(f);
    }
    st[++i] = '\0';

    return st;
}

void read(int *n, int *sp, int s[], FILE *f, FILE *mdt, char st[])
{
    // st[] = {0};
    if (*sp == -1)
        st = readnext(f, st);
    else
    {
        s[*sp + 1] = s[*sp + 1] + 1;
        // incomplete
    }
}

int chk_mnt(char st[], FILE *mnt)
{
    printf("In already MNT");

    char ch;
    rewind(mnt);
    int g = -1, f1 = -1;
    ch = fgetc(mnt);
    while (!(feof(mnt)))
    {
        char mn[30], md[20];
        ch = fgetc(mnt);
        printf("%c", ch);
        while (ch != ' ')
            ch = fgetc(mnt);
        ch = fgetc(mnt);
        while (ch != ' ')
        {
            mn[++g] = ch;
            ch = fgetc(mnt);
        }
        mn[++g] = '\0';
        ch = fgetc(mnt);
        while (ch != ' ')
        {
            md[++f1] = ch;
            ch = fgetc(mnt);
        }
        md[++f1] = '\0';

        puts(mn);
        puts(md);
        strcat(mn, " ");
        strcat(mn, md);
        puts(mn);
        while (ch != EOF)
        {
            ch = fgetc(mnt);
        }
        printf("%c", ch);
        if (strcmp(st, mn) == 0)
            return 1;
    }
    return 0;
}

int chk_com(char st[])
{
    int y = 0;
    while (st[y] != '\0')
    {
        if (st[y] == '&')
            y++;
    }
    return y;
}

int main()
{
    int mdlc = 0, n = 0, sp = -1, s[20];
    FILE *f = NULL, *o = NULL, *mdt = NULL, *mnt = NULL;
    int mdtc = 1, mntc = 1;
    int h;

    f = fopen("input1.txt", "r");
    if (f == NULL)
    {
        printf("Error in Input File");
        exit(1);
    }
    o = fopen("output1.txt", "w+");
    mdt = fopen("mdt1.txt", "w+");
    mnt = fopen("mnt1.txt", "w+");

    if (o == NULL)
    {
        printf("Error in Output File");
        exit(1);
    }
    if (mdt == NULL)
    {
        printf("Error in MDT File");
        exit(1);
    }
    h = -1;
    while (!(feof(f)))
    {
        char st[20];
        read(&n, &sp, s, f, mdt, st);
        printf("0.For ");
        puts(st);
        printf("\n");
        if (strcmp(st, "END") == 0)
            break;
        // check in mnt
        printf("In MNT");
        h = chk_mnt(st, mnt);

        printf("chk_mnt:%d\n", h);
        if (h == 0)
        {
            if (strcmp(st, "MACRO") == 0)
            {
                read(&n, &sp, s, f, mdt, st);
                printf("1.For ");
                puts(st);
                fprintf(mnt, "%d. %s %d\n", mntc, st, mdtc);
                fprintf(mdt, "%d. %s\n", mdtc, st);
                mntc++;
                mdtc++;
                int y = -1, a = -1, m;
                char ala[20];
                while (st[++y] != '\0')
                {
                    if (st[y] == ' ')
                    {
                        while (st[++y] != EOF)
                            if (st[y] != '&')
                                ala[++a] = st[y];
                    }
                }
                ala[++a] = '\0';
                printf("ALA ");
                puts(ala);
                mdlc = mdlc + 1;
                while (mdlc != 0) // error
                {
                    char st1[10];
                    read(&n, &sp, s, f, mdt, st1);
                    printf("\n2.For ");
                    puts(st1);
                    if (strcmp(st1, "MACRO") == 0)
                    {
                        mdlc = mdlc + 1;
                    }
                    else if (strcmp(st1, "MEND") == 0)
                    {
                        mdlc = mdlc - 1;
                        printf("Value of mdlc:%d\n", mdlc);
                    }
                    else
                    {

                        printf("\n");
                        fprintf(mdt, "%d. ", mdtc++);
                        m = -1;
                        printf("Sub Read\n");
                        while ((st1[++m] != '\0'))
                        {
                            char t[10];
                            int t1 = -1;
                            if (st1[m] == '&')
                            {
                                int b = m + 1;
                                while (st1[b] != ',' && st1[b] != EOF)
                                    t[++t1] = st1[b++];
                                int i, j = -1;
                                for (i = 0; i <= a; i++)
                                {
                                    char ta[5];
                                    int ta1 = -1, f = 0;
                                    while (ala[i] != ',' && ala[i] != EOF)
                                    {
                                        f = 1;
                                        ta[++ta1] = ala[i++];
                                    }
                                    if (f == 1)
                                        j++;
                                    if (strcmp(ta, t) == 0)
                                        break;
                                }
                                fprintf(mdt, "#%d", j);
                                m = m + t1;
                            }
                            else
                                fprintf(mdt, "%c", st1[m]);
                            printf("%c", st1[m]);
                        }
                    }
                }
            }
            else
            {
                fprintf(o, "%s", st);
                read(&n, &sp, s, f, mdt, st);
                if (strcmp(st, "MEND") == 0)
                    break;
            }
        }
        else
        {
            // stack;
        }
    }
    fclose(f);
    fclose(o);
    fclose(mnt);
    fclose(mdt);
    printf("Executed");
    return 0;
}