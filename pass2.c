#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int chk_mnt(char st[], FILE *mnt)
{
    char str[20], f;
    int rt = -1, t2 = -1;

    f = st[++rt];
    while (f != ' ' && f != '\0')
    {
        str[++t2] = st[rt];
        f = st[++rt];
    }
    str[++t2] = ' ';

    f = st[++rt];
    while (f != ' ' && f != '\0')
    {
        if (f == ',')
            str[++t2] = f;
        f = st[++rt];
    }
    str[++t2] = '\0';

    rewind(mnt);
    int f1 = -1;
    while (!(feof(mnt)))
    {
        char ch;
        char mn[30], md[5];
        int g = -1, h = -1;
        ch = fgetc(mnt);
        while (ch != ' ' && ch != EOF && ch != '\n')
        {
            ch = fgetc(mnt);
        }
        ch = fgetc(mnt);
        while (ch != ' ' && ch != '\n' && ch != EOF)
        {
            mn[++g] = ch;
            ch = fgetc(mnt);
        }
        mn[++g] = ' ';

        ch = fgetc(mnt);
        while (ch != ' ' && ch != EOF && ch != '\n')
        {
            if (ch == ',')
                mn[++g] = ch;
            ch = fgetc(mnt);
        }
        mn[++g] = '\0';
        while (ch != '\n' && ch != EOF)
        {

            ch = fgetc(mnt);
            md[++h] = ch;
        }
        int o = atoi(md);
        if (strcmp(str, mn) == 0)

            return o;
    }
    return 0;
}

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

int main()
{
    printf("Name: Aditi Jaiswal\nRoll no.: 2016699\n");
    FILE *in = NULL, *mnt = NULL, *mdt = NULL, *exp = NULL;
    int h;
    char str[20];
    in = fopen("output.txt", "r");
    mnt = fopen("mnt.txt", "r");
    mdt = fopen("mdt.txt", "r");
    exp = fopen("expanded.txt", "w");
    while (!(feof(in)))
    {
        readnext(in, str);
        if (strcmp(str, "END") == 0)
        {
            fprintf(exp, "END");
            break;
        }
        h = chk_mnt(str, mnt); // to search mnt for match with operation code
        if (h == 0)
            fprintf(exp, "%s\n", str);
        else
        { // substitution
            rewind(mdt);
            int mdtp = h + 1, k = 1;
            char t1[50];
            char t[50], up;
            int rt = -1, p4 = -1;
            while (k != mdtp)
            {
                fgets(t1, 40, mdt);
                k++;
            }
            fgets(t1, 40, mdt);
            up = t1[++rt];
            while (up != ' ' && up != '\0')
                up = t1[++rt];
            up = t1[++rt];
            while (up != '\0' && up != '\n')
            {
                t[++p4] = up;
                up = t1[++rt];
            }
            t[++p4] = '\0';
            while (strcmp(t, "MEND") != 0)
            {
                int l = -1;
                char cv = t[++l];
                while (cv != '\0' && cv != '\n')
                {
                    while (cv != '#' && cv != '\n' && cv != '\0')
                    {
                        fputc(cv, exp);
                        cv = t[++l];
                    }
                    char sub[5];
                    int y = -1, u, act = -1, i;
                    cv = t[++l];
                    while (cv != ',' && cv != '\n' && cv != '\0')
                    {
                        sub[++y] = cv;
                        cv = t[++l];
                    }
                    sub[++y] = '\0';
                    u = atoi(sub);
                    for (i = 0; str[i] != '\0'; i++)
                    {
                        if (str[i] == ',' || str[i] == '\n')
                            act++;
                        if (act == u)
                            break;
                    }
                    char fg[5], kl;
                    int s = -1;
                    kl = str[--i];
                    while (kl != ' ' && kl != ',')
                    {
                        fg[++s] = str[i];
                        kl = str[--i];
                    }
                    fg[++s] = '\0';
                    fprintf(exp, "%s", strrev(fg));
                }
                fprintf(exp, "\n");
                fgets(t1, 40, mdt);
                rt = -1;
                p4 = -1;
                up = t1[++rt];
                while (up != ' ' && up != '\0')
                    up = t1[++rt];
                up = t1[++rt];
                t[0] = '\0';
                while (up != '\0' && up != '\n')
                {
                    t[++p4] = up;
                    up = t1[++rt];
                }
                t[++p4] = '\0';
                if (strcmp(t, "MEND") == 0)
                    break;
            }
        }
    }

    printf("Executed Pass 2");
    fclose(in);
    fclose(exp);
    fclose(mdt);
    fclose(mnt);

    return 0;
}