//
//  function.c
//  AJC projet C
//
//  Created by pardo jérémie on 12/05/2022.
//

#include "function.h"

void scanf_buffer_flush(void) {
    int ch;
    while ((ch=getchar()) != EOF && ch != '\n');// clean the buffer of all caracters
}

void encrypt_file (char*);
void decryt_to_printf (void);
void decryt_to_file (char*);
                   
int menu (void) {
    int reponse;//contains the value selectionned by the user.
    
    printf("MENU DE SELECTION:\n 1. Encoder un fichier \n 2. Lire un fichier encoder\n 3. Changer la phrase perroquet\n 4. Quitter\n    votre choix:");
    scanf_buffer_flush();
    scanf("%d",&reponse);
            
    switch (reponse) {
        case 1:// encrypt a file
            break;
        case 2:// decrypt a file
            break;
        case 3:// change parrot phrase
            break;
        case 4:// quit program
            return 0;//return 0 to indicate user want to quit the program
        default:
            printf("Mauvaise input!\n");
            break;
    }
    return 1;//return 1 to indicate user did not ask to quit the program
}

void encrypt_file (char* file_to_encrypt) {
    
}

void decryt_to_printf (void) {
    
}

void decryt_to_file (char* file_to_decrypt) {
    
}

void change_parrot_phrase (void) {
    
}
