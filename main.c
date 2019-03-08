
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct persoana{   //Structura pentru datele unui utilizator`

    char nume[20];
    char parola[20];
    char adresa[20];
    char numarTelefon[20];
    char email[30];

} Persoana;

struct {            //Structura pentru fisier
    FILE* fisier;
    char* path;
    int nr;
} global = {NULL,"text.txt"}; //cu fgets

int numarLinii()
{
    FILE *fp = fopen(global.path,"r");
  int ch=0;
  int lines=0;

  if (fp == NULL)
  return 0;

  lines++;
  while ((ch = fgetc(fp)) != EOF)
    {
      if (ch == '\n')
    lines++;
    }
  fclose(fp);
  return lines;
}
Persoana database[200]; //Un vector pentru utilizatori

void clearstdin(){
    while(getchar() != '\n'){
        continue;
    }
}

void Citire();
void instructiuni();  //Panoul de instructiuni
void inregistrare(); // Inregistrarea unui nou utilizator
int verificarePersoana(Persoana p); // Verifica daca exista o persoana cu acelasi nume de utilizator
void modificare(); // Modificarea unui utilizator
void ordonare();  //Ordonarea alfabetica a utilizatorilor

void cautare();   // Cautare11
int cautareNume();  //Cautare dupa nume
void salvare();  //Salvarea in fisier
void statistici();  //Statisticile bazei de date
void literaNume();  //Cautarea dupa o litera
void acelasiparola(); //Cati utilizatori au aceasi parola
void companie();  //Cati utilizatori sunt abonati la Vodafone/Orange/Cosmote
void emailGresit();//Cate adrese de email sunt corecte


int main() {
   global.nr=numarLinii();
   printf("%d",numarLinii());
    if(!(global.fisier = fopen(global.path, "r"))){
        if(!(global.fisier = fopen(global.path, "w"))){
            printf("                                   Fisierul nu s-a putut gasi!\n");      //Verifica daca fisierul s-a gasit
        }
    }
    Citire(); //Apelam functia de citire din fisier

    int optiune = -1;

    while (optiune!= 0) {      //Meniul bazei de date
        instructiuni();
        scanf("%d", &optiune);
        switch (optiune) {
            case 1:
                inregistrare();
                break;
            case 2:
                  cautare();
                break;
            case 3:
                ordonare();
                break;
            case 4:
                statistici();
                break;
            case 0:
                optiune = 0;
                salvare();   //0 pentru inchiderea bazei de date si salvarea datelor in fisier
                break;
            default:
                printf("\n                                          Alegerea dumneavoastra nu se incadreaza in meniu!\n");
                optiune=0;
                break;
        }
    }



    return 0;
}



void Citire(){               //Citirea datelor din fisier
    global.fisier = fopen(global.path, "r");
    if(global.fisier == NULL){
        printf("                                   Fisierul nu poate fi deschis!");
        exit(-1);
    }

   int i=0;
    while(!feof(global.fisier))
        {
       fscanf(global.fisier,"%s",&database[i].nume);
       fscanf(global.fisier,"%s",&database[i].parola);
       fscanf(global.fisier,"%s",&database[i].adresa);
       fscanf(global.fisier,"%s",&database[i].numarTelefon);
       fscanf(global.fisier,"%s",&database[i].email);
       i++;
        }

    fclose(global.fisier);
}

void instructiuni(){  //   Meniul bazei de date
    printf("                                *****************************************************************\n");
    printf("                                **                       Baza de date                          ** \n");
    printf("                                *****************************************************************\n");
    printf("                                ** 1) Inregistrare                                             **  \n  ");
    printf("                              ** 2) Logare                                                   **  \n  ");
    printf("                              ** 3) Pentru ordonarea alfabetica dupa nume si parola          **  \n   ");
    printf("                             ** 4) Pentru a va oferi statisticile                           **  \n    ");
    printf("                            ** 0) tastati 0 inchiderea programului si salvarea datelor     ** \n");

    printf("                                *****************************************************************\n\n\n");
      printf("                                                   Alegerea dumneavoastra :");

}

void inregistrare(){  //Inregistrarea unui nou utilizator
    Persoana contor;

    printf("\n                                                         Datele unei persoane\n");
    printf("                                   ---------------------------------------------------------------\n");
    clearstdin();
    printf("                                   nume: ");gets(contor.nume);
    printf("                                   parola: ");gets(contor.parola);
    printf("                                   adresa: ");gets(contor.adresa);
    printf("                                   Numar de telefon: ");gets(contor.numarTelefon);
    printf("                                   Email: ");gets(contor.email);

    if(!verificarePersoana(contor)){ //Verifica daca exista 2 utilizatori cu acelasi nume
        database[global.nr] = contor;
        global.nr++;
    }
}

int verificarePersoana(Persoana p){ //Verificarea dupa nume
    int i;

    for(i = 0; i < global.nr; i++){
        if(strcmp(p.nume, database[i].nume) == 0){
            printf("                                   -----------------------------------------------------------"
                   "                                   ----\n");
            printf("                                              Aceasta persoana exista in baza de date !\n");
            printf("                                   -----------------------------------------------------------"
                   "                                   ----\n");
            return 1;
        }
    }

    return 0;

}

void modificare(){ //Modificarea datelor unui utilizator
    Persoana p;
    int ok = 0;
   int i,j;
    printf("                             Din motive de securitate va rog sa introduceti datele de utilizator.\n");
    clearstdin();
    printf("                                   nume: ");gets(p.nume);
    printf("                                   parola: ");gets(p.parola);

    for( i = 0; i < global.nr; i++){
        for(j = 0; j < strlen(database[i].nume); j++){
            if(database[i].nume[j] >= 65 && database[i].nume[j] <= 90){
                database[i].nume[j] = database[i].nume[j] + 32;
            }
        }

        for(j = 0; j < strlen(database[i].parola); j++){
            if(database[i].parola[j] >= 65 && database[i].parola[j] <= 90){
                database[i].parola[j] = database[i].parola[j] + 32;
            }
        }
    }

    for( i = 0; i < strlen(p.nume); i++){
        if(p.nume[i] >= 65 && p.nume[i] <= 90){
            p.nume[i] = p.nume[i] + 32;
        }
    }
    for(i = 0; i < strlen(p.parola); i++){
        if(p.parola[i] >= 65 && p.parola[i] <= 90){
            p.parola[i] = p.parola[i] + 32;
        }
    }

    for(i = 0; i < global.nr; i++){
        if(strcmp(p.nume, database[i].nume)==0 &&
           strcmp(p.parola, database[i].parola) == 0){
            printf("                      Persoana a fost gasita.Va rog sa modificati datele utilizatorului !.\n");
            printf("              nume: ");gets(database[i].nume);
            printf("              parola: ");gets(database[i].parola);
            printf("              adresa: ");gets(database[i].adresa);
            printf("              numarTelefon: ");gets(database[i].numarTelefon);
            printf("              Email-i: ");gets(database[i].email);

            ok++;
        }
    }
      printf("                                   Modificarile au fost facute ! Va rog sa tastati 0 pentru a va intoare in meniu.");

    if(ok == 0){
        printf("                                   -------------------------------------------------------------------\n");
        printf("                                          Aceasta persoana nu exista in baza de date.\n");
        printf("                                   -------------------------------------------------------------------\n");

    }

}


void ordonare(){    //Ordonarea dupa nume
    int i,j;
    for(i = 0; i < global.nr; i++){
        for( j = 0; j < strlen(database[i].nume); j++){
            if(database[i].nume[j] >= 65 && database[i].nume[j] <= 90){
                database[i].nume[j] = database[i].nume[j] + 32;
            }
        }

        for( j = 0; j < strlen(database[i].parola); j++){
            if(database[i].parola[j] >= 65 && database[i].parola[j] <= 90){
                database[i].parola[j] = database[i].parola[j] + 32;
            }
        }
    }


    for(i = 0; i <= global.nr; i++){
        for(j = i+1; j < global.nr; j++){
            if((strcmp(database[j].nume, database[i].nume)<0)){
                Persoana temp = database[i];
                database[i] = database[j];
                database[j] = temp;
            }
        }
    }
    printf("                                   ---------------------------------------------------------------------------------\n");
    printf("                                   nume           parola              adresa              numar              email\n");
    printf("                                   ---------------------------------------------------------------------------------\n");

    for(i = 0; i < global.nr; i++){
        printf("%s\t\t%s\t\t%s\t\t%s\t%s\n", database[i].nume,
               database[i].parola, database[i].adresa, database[i].numarTelefon,
               database[i].email);
    }

}



void cautare(){
    int k = 0;

    printf("                                -------------------------------------------------------------------\n");

            if(Logare() == -1){
                printf("\n                                   Persoana nu a fost gasita.\n");
            }
            else
            printf("                                   Alegerea nu este in meniu!\n");


    printf("-------------------------------------------------------------------\n");
}
void optiuniLogare() //Meniul pentru logarea unui  utilizator
{
               printf("\n                           1)Date utilizator");
               printf("\n                           2)Modificare date utilizator");
               printf("\n                           3)Stergere utilizator");
               printf("\n                           0)Deconectare ");
               printf("\n                            Alegerea dumneavoastr : ");
}
void dateUtilizator(int i) // Afisarea datelor personale ale unui utilizator
{
    printf("                                   ---------------------------------------------------------------------------------\n");
    printf("                                   nume           parola              adresa               numar               email\n");
    printf("                                   ---------------------------------------------------------------------------------\n");


        printf("%s\t\t%s\t\t%s\t\t%s\t%s\n", database[i].nume,
               database[i].parola, database[i].adresa, database[i].numarTelefon,
               database[i].email);

               optiuniLogare();
}
int Logare(){ //Verificarea numelui si a parolei pentru logare
     Persoana p;
    int i,nr;
    printf("                                        Va rog sa dati datele de utilizator.\n");
    clearstdin();
    printf("                                nume: "); gets(p.nume);
    printf("                                parola: ");gets(p.parola);

    for( i = 0; i < global.nr; i++){
        if(strcmp(p.nume, database[i].nume) == 0 &&
           strcmp(p.parola, database[i].parola) == 0)
            {printf("\n                         V-ati logat cu succes .Acum aveti acces la date de utilizator !!\n");
               optiuniLogare();
               int optiune;
                while (optiune!= 0) {
                scanf("%d", &optiune);
                switch (optiune) {
            case 1:
                dateUtilizator(i);
                break;
            case 2:
                modificare();
                break;
            case 3:

                break;
            case 0:
                optiune = 0;
                salvare();
                break;
            default:
                printf("\n                          Alegerea dumneavoastra nu se incadreaza in meniu!!\n");
                optiune=0;
                break;
        }
    }


            return i;

            }

    }
    return -1;
}


void salvare(){ //Salvarea in fisier
     global.fisier = fopen(global.path, "a");

       fprintf(global.fisier,"%s ",database[global.nr-1].nume);
       fprintf(global.fisier,"%s ",database[global.nr-1].parola);
       fprintf(global.fisier,"%s ",database[global.nr-1].adresa);
       fprintf(global.fisier,"%s ",database[global.nr-1].numarTelefon);
       fprintf(global.fisier,"%s ",database[global.nr-1].email);
       fprintf(global.fisier,"\n");


    fclose(global.fisier);
}

void statistici(){ //Meniu pentru statistici
    int optiune = -1;
    printf("                                    -------------------------------------------------------------------\n");
    printf("                                   Alegeti criteriul.\n");
    printf("                                   1) Cate persoane sunt in baza de date.\n");
    printf("                                   2) Cata memorie ocupa baza de date.\n");
    printf("                                   3) Cate persoane au prima litera a numelui /\n");
    printf("                                   4) Cate persoane au aceeasi parola.\n");
    printf("                                   5) Cati clienti sunt la Vodafone/Orange/Cosmote\n");
    printf("                                   6) Cate adrese de email sunt incorecte.\n");
    printf("                                   Alegerea dumneavoastra: ");scanf("%d", &optiune);
    printf("                                   -------------------------------------------------------------------\n");
    switch (optiune) {
        case 1:
            printf("\n                                   Momentan sunt %d persoane %c inregistrate in baza de date.\n",
                   global.nr, (global.nr==1)?:'s');
            break;
        case 2:
            printf("\n                                   Baza de date ocupa %d bytes.\n",
                   sizeof(Persoana)*global.nr);
            break;
        case 3:
            literaNume();
            break;
        case 4:
            acelasiparola();
            break;
        case 5:
            companie();
            break;
        case 6:
            emailGresit();
            break;
        default:
            break;
    }



    printf("                                   -------------------------------------------------------------------\n");
}

void literaNume(){//Cautarea in baza de date a unui nume dupa o litera
    char g;
    int contor = 0,i;
    printf("Dati litera : ");
    clearstdin();
    scanf("%c", &g);

    for( i = 0; i < global.nr; i++){
        if(database[i].nume[0] == g){
            printf("%s\n", database[i].nume);
            contor++;
        }
    }

    if(contor == 0){
        printf("\n                                   Nici un nume nu incepe cu aceasta litera ! \n");
    }
}

void acelasiparola(){ // Cate parole sunt la fel
    printf("\n");
    int i,j;
    for(i = 0; i < global.nr; i++){
        for(j = i+1; j < global.nr; j++){
            if(strcmp(database[i].parola, database[j].parola)==0)
                printf("%s %s---%s %s\n", database[i].parola, database[i].nume,
                       database[j].parola, database[j].nume);
        }
    }
}

void companie(){ //Ce fel de numar de telefon
    char* vod = "072", *tkom="074", *eag="076";
    int v=0, t=0, e=0;
    int i;
    for( i = 0; i < global.nr; i++){
        if(strncmp(database[i].numarTelefon, vod, 3) == 0){
            v++;
        }else if(strncmp(database[i].numarTelefon, tkom, 3) == 0){
            t++;
        }else if(strncmp(database[i].numarTelefon, eag, 3) == 0)
            e++;
    }

    printf("                                   In baza de date se afla un total de:\n");
    printf("%d                                    Numere de \"Vodafone\".\n", v);
    printf("%d                                    Numere de \"Orange\".\n", t);
    printf("%d                                    Numere de \"Cosmote\".\n", e);
}


void emailGresit(){ //Cate email-uri sunt gresite
    int ok = 0;
    char c = '@';
    int i;
    for(i = 0; i < global.nr; i++){
        if(!strchr(database[i].email, c))
            ok++;
    }

    printf("\n                                   Sunt un total de  %d adrese de email care nu sunt in formatul corespunzator"
                                              " (Nu contin caracterul  \'@\')\n", ok);

}








