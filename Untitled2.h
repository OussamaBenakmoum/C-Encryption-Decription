#ifndef UNTITLED2_H_INCLUDED
#define UNTITLED2_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>



#define MAX_CARAC 40
#define TRAME 10
#define MIN_B 0
#define MAX_B 4
#define MIN_H 5
#define MAX_H 9

FILE *src_file ,*crypted_file , *final_file;
unsigned char crypted_string[9] ,src_char , final_char;
unsigned char src_file_name[25] ,crypted_file_name[25], final_file_name[25] ,password[25] ;
unsigned char huns ,tens ,units ,res1 ,res2 ,res3 ,par1 ,par2 ,par3 ;
unsigned char password_lenght ,end_file ,choice ,letter = 0 ;
int comp_select = 0;


void initialisation(void);
void ouverture_des_fichiers (void);
void choix_crypt ();
void set_password (void);
void crypt(void);
void decrypt(void);
void get_char(void) ;
void code(void) ;
void decode(void) ;
void print_code(void) ;
void get_code(void);
void print_char(void);
void display_menu();
void esi_logo();




#endif // UNTITLED2_H_INCLUDED
