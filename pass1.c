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

int main()
{
    printf("Name: Aditi Jaiswal\nRoll no.: 2016699\n");
    FILE *f = NULL, *o = NULL, *mdt = NULL, *mnt = NULL;
    char str[20];
    char str1[20];
    int mdtc = 1, mntc = 1, m = 0;

    f = fopen("input.txt", "r");
    if (f == NULL)
    {
        printf("Error in Input File");
        exit(1);
    }
    o = fopen("output.txt", "w");
    mdt = fopen("mdt.txt", "w");
    mnt = fopen("mnt.txt", "w");
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
    while (!feof(f))
    {

        readnext(f, str1);

        if (strcmp(str1, "MACRO") == 0)
        {
            m = 1;
            readnext(f, str1);
            fprintf(mnt, "%d. %s %d\n", mntc, str1, mdtc);
            mntc++;

            fprintf(mdt, "%d. %s\n", mdtc, str1);
            mdtc++;

            int y = -1, a = -1, m;
            char ala[20];
            while (str1[++y] != '\0')
            {
                if (str1[y] == ' ')
                {
                    while (str1[++y] != '\0')
                        if (str1[y] != '&')
                            ala[++a] = str1[y];
                }
            }
            ala[++a] = '\0';
            while (1)
            {
                int j = -1;
                char ch;
                readnext(f, str); // L 1,&x1,&x2
                if (strcmp(str, "MEND") == 0)
                {
                    fprintf(mdt, "%d. MEND\n", mdtc++);
                    break;
                }
                else
                    fprintf(mdt, "%d. ", mdtc);
                ch = str[++j];
                while (ch != '\0')
                {
                    if (ch != '&')
                        fputc(ch, mdt);
                    else
                    {
                        char u[5], v[5];
                        int u1 = -1, v1 = -1, i = -1;
                        u[++u1] = str[++j];
                        ch = str[++j];
                        while (ch != '\0' && ch != ',')
                        {
                            u[++u1] = ch; // x1
                            ch = str[++j];
                        }
                        u[++u1] = '\0';
                        char ch1;
                        int subs = 0;
                        while ((ch1 = ala[++i]) != '\0')
                        {
                            char v[5];
                            int v1 = -1;
                            while (ch1 != ',' && ch1 != '\0')
                            {
                                v[++v1] = ch1;
                                ch1 = ala[++i];
                            }
                            v[++v1] = '\0';
                            if (strcmp(u, v) == 0)
                            {
                                fprintf(mdt, "#%d", subs);
                                j = j - 1;
                                break;
                            }
                            else
                                subs++;
                        }
                    }
                    ch = str[++j];
                    if (ch == '\0')
                        break;
                }
                fprintf(mdt, "\n");
                mdtc++;
                if (strcmp(str, "MEND") == 0)
                    break;
            }
        }
        else
        {
            fprintf(o, "%s\n", str1);
        }
    }
    printf("Executed Pass 1");
    fclose(f);
    fclose(o);
    fclose(mdt);

    return 0;
}