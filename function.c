//
//  function.c
//  AJC projet C
//
//  Created by pardo jérémie on 12/05/2022.
//

#include "function.h"

void scanf_buffer_flush(void) {
    int ch;
    while ((ch=getchar()) != EOF && ch != '\n');
}

void encrypt_file (char*);
void decryt_to_printf (void);
void decryt_to_file (char*);
                   
int menu (void) {
    int reponse;
    
    printf("MENU DE SELECTION:\n 1. Encoder un fichier \n 2. Lire un fichier encoder\n 3. Changer la phrase perroquet\n 4. Quitter\n    votre choix:");
    scanf_buffer_flush();
    scanf("%d",&reponse);
            
    switch (reponse) {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            return 0;
        default:
            printf("Mauvaise input!\n");
            break;
    }
    return 1;
}

void encrypt_file (char* file_to_encrypt) {
    
}

void decryt_to_printf (void) {
    
}

void decryt_to_file (char* file_to_decrypt) {
    
}

void change_parrot_phrase (void) {
    
}
