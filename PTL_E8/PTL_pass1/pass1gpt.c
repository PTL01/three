#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char label[10], opcode[10], operand[10];
    int mntc = 1, mdtc = 1;

    FILE *fp1 = fopen("input.txt", "r"), //input
         *fp2 = fopen("mnt.txt", "w"),
         *fp3 = fopen("mdt.txt", "w"),
         *fp4 = fopen("copyfile.txt", "w");

    while (fscanf(fp1, "%s %s %s", label, opcode, operand) != EOF)
    {
        if (!strcmp(opcode, "END"))
        {
            fprintf(fp4, "%s %s %s\n", label, opcode, operand);
            break;
        }
        if (!strcmp(opcode, "MACRO"))
        {
            fscanf(fp1, "%s %s %s", label, opcode, operand);
            fprintf(fp2, "%d %s %d\n", mntc++, opcode, mdtc);
            while (strcmp(opcode, "MEND"))
            {
                fprintf(fp3, "%d %s %s %s\n", mdtc++, label, opcode, operand);
                fscanf(fp1, "%s %s %s", label, opcode, operand);
            }
            fprintf(fp3, "%d %s %s %s\n", mdtc++, label, opcode, operand);
        }
        else
        {
            fprintf(fp4, "%s %s %s\n", label, opcode, operand);
        }
    }

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);

    return 0;
}
