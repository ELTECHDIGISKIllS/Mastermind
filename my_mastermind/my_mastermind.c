#include "my_mastermind.h"

void commenceOp();
int assessSpec(char *Ident_a, char *Ident_b, int *num_point);
int EqualCust(char *Sympoint_a, char *Sympoint_b);
char *DupliAlt(char *Datum_1, char *Datum_2);
void scrutinizeSynt(char *Snipseq, int *refval);
void getRand(int *refval);
int ascertEffort(int *refval);
void confirmTrials(int *Strives, int *Circuits);
int scanMemory(int *DigitsAddr);
int inspectUnit(int *DigitsAddr, int *refval);

void commenceOp() 
{ 
    printf("Will you find the secret code?\n");  
    printf("Please enter a valid guess\n");
}

int assessSpec(char *Ident_a, char *Ident_b, int *num_point)  
{ 
    char Snipseq[KEY_LENGTH];   
    if (!EqualCust("-c", Ident_a))  
    { 
        DupliAlt(Snipseq, Ident_b);   
        scrutinizeSynt(Snipseq, num_point);   
        return 0;
    }
    else if (!EqualCust("-t", Ident_a)) 
    {
        Strives = atoi(Ident_b);
    }
    else
    {
        getRand(num_point); 
    }
    return 1;
}

int EqualCust(char *Sympoint_a, char *Sympoint_b)
{
    int count1, count2 = 0;
    for (int k = 0; Sympoint_a[k]; k++) count1 += Sympoint_a[k];
    for (int k = 0; Sympoint_b[k]; k++) count2 += Sympoint_b[k];
    if (Sympoint_a[0] == Sympoint_b[0] && Sympoint_a[1] == Sympoint_b[1] &&
        Sympoint_a[2] == Sympoint_b[2])
        return 0;
     if (count1 > count2)
        return -1;
    else if (count1 < count2)
        return 1;
    else
        return 0;
}

char *DupliAlt(char *Datum_1, char *Datum_2)
{ 
    int k = 0;
    int len = strlen(Datum_2);
    while (k < len)
    { 
        Datum_1[k] = Datum_2[k];
        k++;
    }
    return Datum_1;
}

void scrutinizeSynt(char *Snipseq,  int *refval)  
{
    for (int k = 0; k < KEY_LENGTH; k++)
    {
        if ((Snipseq[k] >= '0' && Snipseq[k] <= '8') || (Snipseq[k] >= 'a' && Snipseq[k] <= 'z') || (Snipseq[k] >= 'A' && Snipseq[k] <= 'Z'))
        { 
            if (Snipseq[k] != '0')  
                refval[k] = Snipseq[k] - '0'; 
            else
                refval[k] = 0;
        } 
        else 
        {
            printf("Wrong input\n");
            break;
        }
    }
}

void getRand(int *refval)  
{
    for (int k = 0; k < KEY_LENGTH; k++) 
        refval[k] = rand() % 8;
}

int ascertEffort(int *refval)
{
    int DigitsAddr[KEY_LENGTH] = {0};  
    while (Strives) 
    {
        printf("Round %d\n", Circuits);
        confirmTrials(&Strives, &Circuits); 
        int check = scanMemory(DigitsAddr);
        if (check == -1)  
        { return 0; }
        else if (inspectUnit(DigitsAddr, refval) == 1)  
            return 0;
            }
    return 1;
}
void confirmTrials(int *Strives, int *Circuits)
{
    *Strives -= 1;  
    *Circuits += 1;
}

int scanMemory(int *DigitsAddr)  
{  char j;
    int k = 0, ret, seq_quant = 0;
    while ((ret = read(0, &j, 1)) == 1 &&  k < KEY_LENGTH)  
    { if ((j >= '0' && j <= '8') || !isalpha(j)) 
        { if (j != '0') 
                DigitsAddr[k++] = j - '0';  
            else
                DigitsAddr[k++] = 0;
            seq_quant++;
        }
        else 
        {printf("Invalid input\n");
            while (j != '\n' && ret == 1) {
                ret = read(0, &j, 1);}
            return -1;  } }
    if (seq_quant < 4 || k != 4)
    { printf("Invalid input\n"); return -1; }
    return 1;
}



int inspectUnit(int *DigitsAddr, int *refval)
{ 
    int Incorrectitems = 0;  int Sound = 0;
    for (int k = 0; k < 4; k++)
    { 
        if (DigitsAddr[k] == refval[k])
            Sound++;
        else if (DigitsAddr[k] != refval[k] && (DigitsAddr[k] == refval[(k + 1) % 4] ||DigitsAddr[k] == refval[(k + 2) % 4] ||  DigitsAddr[k] == refval[(k + 3) % 4]))
            Incorrectitems++;
    }
    if (Sound == 4)  
    { printf("Congratz! You did it!\n");return 1; } 
    else
    {printf("Well placed pieces: %d\nMisplaced pieces: %d\n", Sound, Incorrectitems);
        return 0;} 
        }

int main(int paramCount, char **paramArg)
{    
    int refval[KEY_LENGTH] = {0};  
    commenceOp();  
    if (paramCount == 0) return 0;  
    for (int k = 0, j = -1; paramArg[k] && j != 0; k++)  
        j = assessSpec(paramArg[k], paramArg[k + 1], refval);
    ascertEffort(refval);
    return EXIT_SUCCESS;
}
