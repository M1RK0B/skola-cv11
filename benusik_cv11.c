#include <stdio.h>
#include <stdlib.h>

typedef struct student
{
    char priezvisko_meno[100];
    int rocnik;
    float priemer;
    struct student *dalsi;
    }STUDENT;


STUDENT *nacitajSpajany(char *subor)
{
    FILE *fr;
    int pocet = 0, a = 0;
    STUDENT *p_prv, *p_akt;

    if ((fr = fopen(subor, "r")) == NULL)
    {
        printf("nepodarilo sa otvorit subor\n");
        return 0;
    }

    fscanf(fr, "%d", &pocet);
    a = fgetc(fr);

    if((p_prv = (STUDENT *) malloc(sizeof(STUDENT))) == NULL)
    {
        printf("Malo pamate.\n");
        return 0;
    }

    fgets(p_prv->priezvisko_meno, 100, fr);
    fscanf(fr,"%d\n", &p_prv->rocnik);
    fscanf(fr,"%f\n", &p_prv->priemer);
    p_prv->priezvisko_meno[strlen(p_prv->priezvisko_meno)-1] = '\0';
    p_akt = p_prv;

    for(int i = 2; i <= pocet; i++)
    {
        if((p_akt->dalsi = (STUDENT *) malloc(sizeof(STUDENT))) == NULL)
        {
            printf("Malo pamate.\n");
            break;
        }
        p_akt = p_akt->dalsi;
        fgets(p_akt->priezvisko_meno, 100, fr);
        p_akt->priezvisko_meno[strlen(p_akt->priezvisko_meno)-1] = '\0';
        fscanf(fr,"%d\n", &p_akt->rocnik);
        fscanf(fr,"%f\n", &p_akt->priemer);
    }
    if(fclose(fr) == EOF){
       printf("Subor sa nepodarilo zatvorit.\n");
    }
    p_akt->dalsi = NULL;
    return p_prv;
    p_akt = p_prv;
 }


void vypisSpajany(STUDENT *studenti)
{
    while(studenti != NULL)
    {
        printf("%s;%d;%.2f\n", studenti->priezvisko_meno, studenti->rocnik, studenti->priemer);
        studenti = studenti->dalsi;
    }
}



void uvolniSpajany (STUDENT *studenti)
{
    STUDENT *akt;
    while(studenti != NULL){
        free(studenti);
    }
    free(studenti->dalsi);
}


int main()
{
    STUDENT *spajany, *naj;
    spajany = nacitajSpajany("vstup.txt");
    if (spajany== NULL)
        {
            printf("nepodarilo sa nacitat a naplnit zoznam");
            return -1;
        }
    vypisSpajany(spajany);
    uvolniSpajany(spajany);
    return 0;
}
