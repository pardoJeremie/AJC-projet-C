//
//  function.c
//  AJC projet C
//
//  Created by pardo jérémie on 12/05/2022.
//

#include "function.h"
#define Path_Size 50
#define Text_Size 101

int confirmation(void) {// Ask the user for a confirmation
    char c;
    
    printf("Êtes-vous sûr de vouloir effectuer cette action? [O/N] ");
    fflush(stdin);
    scanf("%c",&c);
    
    if(c == 'O' || c == 'o')
        return 1;
    return 0;
}

int encrypt_file (char*, char*);
int encrypt_string (char*, char*);
void decryt_to_printf (char*);
int decryt_to_file (char*, char*);
void change_parrot_phrase (char*);

int menu (void) {
    int reponse;//contains the value selectionned by the user.
    char path_a[Path_Size],path_b[Path_Size]// contains the values of a path to a file path
    , text[Text_Size];// contains the values of a path to a text
    
    printf("MENU DE SELECTION:\n 1. Encoder un fichier \n 2. Encoder une entrée texte \n 3. Decoder un fichier encoder dans la ligne de command \n 4. Decoder un fichier encoder dans un fichier texte\n 5. Changer la phrase perroquet\n 6. Quitter\n    votre choix: ");
    fflush(stdin);
    scanf("%d",&reponse);
    
    switch (reponse) {
        case 1:// encrypt a file
            printf("Ecriver le chemain du fichier à encrypter: ");
            fflush(stdin);
            fgets(path_a,Path_Size, stdin);
            
            
            printf("Ecriver le chemain du fichier crypter: ");
            fflush(stdin);
            fgets(path_b,Path_Size, stdin);
            
            if(encrypt_file (path_a,path_b))
                printf("Fichier encrypter.\n");
            break;
        case 2:// encrypt a text
            printf("Ecriver le chemain du fichier crypter: ");
            fflush(stdin);
            fgets(path_b,Path_Size, stdin);
            
            printf("\n Ecriver le texte (500 caractère max): ");
            fflush(stdin);
            fgets(text,Text_Size, stdin);
            
            if(encrypt_string (text,path_b))
                printf("Texte encrypter.\n");
            break;
        case 3:// decrypt a file into the command ligne
            printf("Ecriver le chemain du fichier crypter: ");
            fflush(stdin);
            fgets(path_b,Path_Size, stdin);
            
            decryt_to_printf(path_b);
            break;
        case 4:// decrypt a file into a new file
            printf("Ecriver le chemain du fichier crypter: ");
            fflush(stdin);
            fgets(path_b,Path_Size, stdin);
            
            printf("Ecriver le chemain du fichier à décrypter: ");
            fflush(stdin);
            fgets(path_a,Path_Size, stdin);
            
            if(decryt_to_file(path_a, path_b))
                printf("Texte decrypter.\n");
            break;
        case 5:// change parrot phrase
            printf("Attention, changer la phrase perroquet vous empêchera de lire l'ensemble des fichiers encrypter avec la phrase actuelle.\n");
            
            if(confirmation()) {
                printf("Ecriver la nouvelle phrase parrot (500 caractère max): ");
                fflush(stdin);
                fgets(text,Text_Size, stdin);
                
                change_parrot_phrase(text);
            }
            break;
        case 6:// quit program
            if(confirmation())
                return 0;//return 0 to indicate user want to quit the program
            break;
        default:
            printf("Mauvaise input!\n");
            break;
    }
    printf("\n");
    return 1;//return 1 to indicate user did not ask to quit the program
}

int encrypt_file (char* file_to_encrypt, char* new_crypted_file) {
    return 1;
}

int encrypt_string (char* text, char* new_crypted_file) {
    return 1;
}

void decryt_to_printf (char* crypted_file) {
    
}

int decryt_to_file (char* file_to_decrypt_to, char* crypted_file) {
    return 1;
}

void change_parrot_phrase (char* phrase) {
    
}
