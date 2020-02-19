#include <stdio.h>
#include <stdlib.h>
#include "conio.c"
#include "Untitled1.h"

void initialisation(void){ //initialiser les chaine de caracteres
    char lenght;
	for (lenght=0;lenght<25;lenght++)
        {
    	src_file_name[lenght] = 0;
        crypted_file_name[lenght] = 0;
        password[lenght] = 0;
        }
    letter = 0;
    //system ("CLS");
}


void open_files(void) //ouverture des fichiers
{

    system("CLS");
    info();
    textcolor(LIGHTMAGENTA);
    gotoxy(6, 1);
    printf("Welcome to the Encryption <-> Decryption Program ******** BENAKMOUM/BENAZIZA");
    textcolor(WHITE);
    gotoxy(11, 3); textcolor(GREEN);printf("Write source file name : ") ;textcolor(WHITE);
    scanf("%40s",&src_file_name) ;
    gotoxy(2, 4); textcolor(RED);  printf("Write the destination file name : ");textcolor(WHITE);
    scanf("%40s",&crypted_file_name) ;
    src_file = fopen(src_file_name ,"rt");
    if (src_file == NULL)
    {
        gotoxy(5, 7); textcolor(RED);printf("NO source file");textcolor(WHITE);
    }

    crypted_file = fopen(crypted_file_name ,"wt") ;
    if (crypted_file == NULL)
    {
        gotoxy(5, 7); textcolor(RED);printf("NO Result file");textcolor(WHITE);
    }
    system("CLS");

}

void choix_crypt (void)
{
    system("CLS");


    gotoxy(4, 3);printf("Select the option :");
    gotoxy(2, 5); textcolor(BLUE);printf("\n1-   ");textcolor(WHITE);
    printf("Encrypt a file(c)");
    gotoxy(2, 6); textcolor(BLUE);printf("\n2-   ");textcolor(WHITE);
    printf("Decrypt a file(d)");
    textcolor(RED);
    gotoxy(4, 8);
    printf("(c/d):");
    textcolor(WHITE);

do {
        choice = getch();
        rewind(stdin);
    }while (choice != 'c' && choice !='d');

    printf("%c",choice);

    system("CLS");
    set_password();

    int stop = 0;
        if (choice == 'c')
            crypt();
              if (choice == 'd')
                  {
                        decrypt();
                        display_compare();
                        //compare();
                  }

}

void set_password(void)//lire  password .
{
    int i = 0;
    char ch;
    char pwd[25];
    char lenght ;
    gotoxy(10, 10);
    textcolor(LIGHTCYAN);
    printf("Would you please enter your password : ");
    textcolor(LIGHTRED);


    while(1)
    {
        ch = getch();

        if (ch == 13/*ENTER */|| ch == 9 /*tab */){
            pwd[i] = '\0';
            break;
        }else if(ch == 8/*Back space */){
            if (i>0){
                i--;
                printf("\b \b");
            }
            }else{
            pwd[i++] = ch;
            printf("* \b");

            }





        //password = pwd;
    }
    textcolor(WHITE);
 printf("\n\n\n\n\nPassword:%s Length %d", pwd, i);

        strcpy(password,pwd);




   // fgets(password,sizeof password ,stdin);
    password_lenght = strlen(password);
    for (lenght=0 ;lenght<password_lenght ;lenght++) password[lenght] = 255 - password[lenght] ;

}

void get_char(void)  /**recuperer un caractere du fichier source*/
{
    src_char = fgetc(src_file);
    end_file = src_char ;
}

void crypt(void)
{
    do
    {
        get_char();
        if (end_file != 255)
        {
            code();
            //printf("%d",crypted_string);
            print_code();

        }
    }while (end_file != 255);
    fclose(crypted_file);
    textcolor(GREEN);printf("\n*********DONE*********\n");textcolor(WHITE);
}

void code(void)
{
    src_char = src_char ^ password[letter];     /**faire un XOR on obtiendra un ascii de trois positions maximum*/
    letter++;
    if (letter == password_lenght) {letter = 0;}        /**initialser l'indice du mot de passe*/
    huns = src_char / 100 ;     /**recupere les centeines*/
    tens = (src_char - (100 * huns)) / 10;      /**recupere les dizaines*/
    units = src_char - (100 * huns)  - (10 * tens);     /**recuperer les unit�s*/
        /**former trois nouveaux variables*/
    res1 = huns + tens ;
    res2 = tens + units ;
    res3 = huns + units ;
        /**pour verifier la parit� des res(i)*/
    if ((res1 % 2) == 0) par1 = 0;
    else                 par1 = 5;
    if ((res2 % 2) == 0) par2 = 0;
    else                 par2 = 5;
    if ((res3 % 2) == 0) par3 = 0;
    else                 par3 = 5;

    /**pour assurer que les res(i) ont une seule position */

    res1 = res1 / 2 ;
    res2 = res2 /2 ;
    res3 = res3 /2 ;
    crypted_string[0] = par1 ; crypted_string[1] = par2 ; crypted_string[2] = par3 ;
    crypted_string[3] = rand()%10 ; crypted_string[4] = rand()%10 ; crypted_string[5] = rand()%10 ;     /**pour rendre plus defficile le decodage*/
    crypted_string[6] = res1 ; crypted_string[7] = res2 ; crypted_string[8] = res3 ;
}

void print_code(void)       /**insere le caractere crypt� dans le fichier resultat*/
{
   char lenght ;
   for (lenght=0 ;lenght<9 ;lenght++)
       fprintf(crypted_file,"%d",crypted_string[lenght]);
}

void get_code(void)     /**recuper 9 caracteres quie represente un caractere crypt�*/
{
    int length;
    for (length=0 ; length<9;length++)
    {
        crypted_string[length] = fgetc(src_file);
        if (crypted_string[length] != 255)
            crypted_string[length] = crypted_string[length] & 0x0F  ;
    }
    end_file = crypted_string[0] ;      /**indique la fin de fichier*/

}

void decrypt(void)
{
    letter = 0;
    while (end_file != 255)
    {
        get_code();
        if (end_file != 255)
       {
            decode();
            print_char();
        }
    }

fclose(crypted_file);
fclose(src_file);
textcolor(GREEN);printf("\n*********DONE*********\n");textcolor(WHITE);


}

void decode(void)
{
    /**recuperer les informations necessaires pour le decodage*/
    par1 = crypted_string[0] ;par2 = crypted_string[1] ; par3 = crypted_string[2] ;
    res1 = crypted_string[6] ; res2 = crypted_string[7] ; res3 = crypted_string[8] ;

    /**faire l'operation inverse*/
    if (par1 < 5 ) res1 = res1 * 2 ;
    else res1 = (res1 * 2) + 1 ;

    if (par2 < 5) res2 = res2 * 2 ;
    else res2 = (res2 * 2) + 1 ;

    if (par3 < 5) res3 = res3 * 2 ;
    else res3 = (res3 * 2) + 1 ;

    /**resoudre equation trois inconnues*/
    huns = (int) (res1 - res2 + res3) / 2 ;
    tens = (int) (res1 + res2 - res3) / 2 ;
    units = (int) (res2 + res3 - res1) / 2 ;

    /**former le source char*/
    src_char = (100 * huns) + (10 * tens ) + units ;
    /**faire un XOR pour trouver le resultat initiale*/
    src_char = password[letter] ^ src_char  ;
    letter = letter + 1 ;
    if (letter == password_lenght) {letter = 0 ;}
}

void print_char(void)       /**insere le texte decrypte*/
{
    //printf("\nje vais eire : %d\n",src_char);
    fputc(src_char,crypted_file);
}

void compare(void)
{
    int test = 1;
    char car1 = 0, car2 = 0;
    src_file = fopen("s.txt", "rt");
    final_file = fopen("sss.txt", "rt");
    while ((car1 != EOF) && (car2 != EOF) && (test== 1)) 
    {
        car1 = fgetc(src_file);
        car2 = fgetc(final_file);
            if ( car1 != car2)
            {
                printf("\nERROR");
                test = 0;
            }
    }
    if (test == 1){

            textcolor(GREEN);
            printf("\nYour files are similar\n");
            textcolor(WHITE);

    }else
    {

            textcolor(RED);
            printf("\nYour files are not similar\n");
            textcolor(WHITE);
    }
}


void recommencer (void)
    {
    printf ("\n\nwould you play it again  (o/n) : ",130,130);
    do  {
        choice = getch();
        }while(choice != 'o' && choice != 'n');
    }


void info()
{
    gotoxy(5, 8);
    textcolor(RED);
    printf("IMPORTANT !");
    textcolor(LIGHTCYAN);
    gotoxy(4, 10);
    printf("(i) if you want to use our files in this work then:");
    gotoxy(4, 11);
    printf(" we have used a file named [s.txt] as a source file");
    gotoxy(4, 12);
    printf("                          [ss.txt] as a crypted file");
    gotoxy(4, 13);
    printf("                         [sss.txt] as a final file for decryption ");
    gotoxy(5, 14);textcolor(RED);
    printf("If you want to use your text GO EDIT [s.txt]");
    textcolor(WHITE);

}


void display_compare(void)
{
    char choice2;


    textcolor(LIGHTBLUE); printf("\nDo you wanna compare the files\n");
    textcolor(WHITE);
    printf("(y/n)\n\n");

    do {
        choice2 = getch();
        rewind(stdin);
    }while (choice2 != 'y' && choice2 != 'n');

    printf("%c",choice2);
    if (choice2 == 'y')
    {
        compare();
    }else
    {
        printf("QUIT");
    }
}
