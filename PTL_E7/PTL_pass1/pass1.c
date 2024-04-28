#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int find_opcode(FILE *fp, char *opcode)
{
    char mnemonic[10];
    rewind(fp);
    while (fscanf(fp, "%s", mnemonic) != EOF)
    {
        if (!strcmp(opcode, mnemonic))
        {
            return 4;
        }
    }
    return 0;
}

int main()
{
    char label[10], opcode[10], operand[10];
    int locctr = 0;
    FILE *fp1 = fopen("input.txt", "r");
    FILE *fp2 = fopen("mot.txt", "r");
    FILE *fp3 = fopen("output.txt", "w");
    FILE *fp4 = fopen("st.txt", "w");

    while (fscanf(fp1, "%s %s %s", label, opcode, operand) != EOF)
    {
        if (!strcmp(opcode, "END"))
        {
            fprintf(fp3, "%d %s %s %s\n", locctr, label, opcode, operand);
            break;
        }
        if (!strcmp(opcode, "DC") || !strcmp(opcode, "DS"))
        {
            fprintf(fp4, "%s %d\n", label, locctr);
            fprintf(fp3, "%d %s %s %s\n", locctr, label, opcode, operand);
            locctr += 4;
        }
        else
        {
            fprintf(fp3, "%d %s %s %s\n", locctr, label, opcode, operand);
            locctr += find_opcode(fp2, opcode);
        }
    }

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    return 0;
}