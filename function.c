//
//  function.c
//  AJC projet C
//
//  Created by pardo jérémie on 12/05/2022.
//

#include <stdlib.h>
#include <string.h>
#include "function.h"

#define Path_Size 500
#define Text_Size 1001
// /Users/pardojeremie/Desktop/AJC Formation pour Thales/formation cours/C/program/AJC projet C/AJC projet C/function.txt


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
int decryt_to_printf (char*);
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
            
            path_a[strcspn(path_a, "\r\n")] = '\0'; //delet the '\n' character at the end of path_b introduced by fgets
            path_b[strcspn(path_b, "\r\n")] = '\0'; //delet the '\n' character at the end of path_b introduced by fgets
            if(encrypt_file (path_a,path_b))
                printf("Fichier encrypter.\n");
            
            break;
        case 2:// encrypt a text
            printf("Ecriver le chemain du fichier crypter: ");
            fflush(stdin);
            fgets(path_b,Path_Size, stdin);
            
            printf("\n Ecriver le texte (%d caractère max): ", Text_Size-1);
            fflush(stdin);
            fgets(text,Text_Size, stdin);
            
            text[strcspn(text, "\r\n")] = '\0'; //delet the '\n' character at the end of text introduced by fgets
            path_b[strcspn(path_b, "\r\n")] = '\0'; //delet the '\n' character at the end of path_b introduced by fgets
            if(encrypt_string (text,path_b))
                printf("Texte encrypter.\n");
            
            break;
        case 3:// decrypt a file into the command ligne
            printf("Ecriver le chemain du fichier crypter: ");
            fflush(stdin);
            fgets(path_b,Path_Size, stdin);
            
            path_b[strcspn(path_b, "\r\n")] = '\0'; //delet the '\n' character at the end of path_b introduced by fgets
            if(decryt_to_printf(path_b))
                printf("Texte decrypter.\n");
            break;
        case 4:// decrypt a file into a new file
            printf("Ecriver le chemain du fichier crypter: ");
            fflush(stdin);
            fgets(path_b,Path_Size, stdin);
            
            printf("Ecriver le chemain du fichier à décrypter: ");
            fflush(stdin);
            fgets(path_a,Path_Size, stdin);
            
            path_a[strcspn(path_a, "\r\n")] = '\0'; //delet the '\n' character at the end of path_b introduced by fgets
            path_b[strcspn(path_b, "\r\n")] = '\0'; //delet the '\n' character at the end of path_b introduced by fgets
            if(decryt_to_file(path_a, path_b))
                printf("Texte decrypter.\n");
            
            break;
        case 5:// change parrot phrase
            printf("Attention, changer la phrase perroquet vous empêchera de lire l'ensemble des fichiers encrypter avec la phrase actuelle.\n");
            
            if(confirmation()) {
                printf("Ecriver la nouvelle phrase parrot (%d caractère max): ",Text_Size-1);
                fflush(stdin);
                fgets(text,Text_Size, stdin);
                
                text[strcspn(text, "\r\n")] = '\0'; //delet the '\n' character at the end of text introduced by fgets
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
    //read file to encrypt
    FILE *f = NULL;
    
    f = fopen(file_to_encrypt,"r");
        
    if(f == NULL) {
        printf("file %s did not open properly.\n Are you sure the file exists?\n",file_to_encrypt);
        return 0;
    }
    
    if(fclose(f) == EOF){
        printf("file %s was not closed properly.\n",file_to_encrypt);
        exit(EXIT_FAILURE);
    }
    
    //read parrot.def
    f = fopen("perroq.def","r");
        
    if(f == NULL) {
        printf("file perroq.def did not open properly.\n Are you sure the file exists?\n");
        return 0;
    }
    
    
    if(fclose(f) == EOF){
        printf("file perroq.def was not closed properly.\n");
        exit(EXIT_FAILURE);
    }
    
    //write crypted file
    f = fopen(new_crypted_file,"w+");
        
    if(f == NULL) {
        printf("file %s did not open properly.\n",file_to_encrypt);
        exit(EXIT_FAILURE);
    }
    
    
    if(fclose(f) == EOF){
        printf("file %s was not closed properly.\n",file_to_encrypt);
        exit(EXIT_FAILURE);
    }
    return 1;
}


int encrypt_string (char* text, char* new_crypted_file) {
    
    //read parrot.def
    FILE *f = NULL;
    f = fopen("perroq.def","r");
        
    if(f == NULL) {
        printf("file perroq.def did not open properly.\n Are you sure the file exists?\n");
        return 0;
    }
    
    
    if(fclose(f) == EOF){
        printf("file perroq.def was not closed properly.\n");
        exit(EXIT_FAILURE);
    }
    
    //write crypted file
    f = fopen(new_crypted_file,"w+");
        
    if(f == NULL) {
        printf("file %s did not open properly.\n",new_crypted_file);
        exit(EXIT_FAILURE);
    }
    
    
    if(fclose(f) == EOF){
        printf("file %s was not closed properly.\n",new_crypted_file);
        exit(EXIT_FAILURE);
    }
    
    return 1;
}

int decryt_to_printf (char* crypted_file) {
    //read parrot.def
    FILE *f = NULL;
    f = fopen("perroq.def","r");
        
    if(f == NULL) {
        printf("file perroq.def did not open properly.\n Are you sure the file exists?\n");
        return 0;
    }
    
    
    if(fclose(f) == EOF){
        printf("file perroq.def was not closed properly.\n");
        exit(EXIT_FAILURE);
    }
    
    //read crypted file
    f = fopen(crypted_file,"r");
        
    if(f == NULL) {
        printf("file %s did not open properly.\n Are you sure the file exists?\n",crypted_file);
        return 0;
    }
    
    if(fclose(f) == EOF){
        printf("file %s was not closed properly.\n",crypted_file);
        exit(EXIT_FAILURE);
    }
    return 1;
    
}

int decryt_to_file (char* file_to_decrypt_to, char* crypted_file) {
    //read parrot.def
    FILE *f = NULL;
    f = fopen("perroq.def","r");
        
    if(f == NULL) {
        printf("file perroq.def did not open properly.\n Are you sure the file exists?\n");
        return 0;
    }
    
    
    if(fclose(f) == EOF){
        printf("file perroq.def was not closed properly.\n");
        exit(EXIT_FAILURE);
    }
    
    //read crypted file
    f = fopen(crypted_file,"r");
        
    if(f == NULL) {
        printf("file %s did not open properly.\n Are you sure the file exists?\n",crypted_file);
        return 0;
    }
    
    if(fclose(f) == EOF){
        printf("file %s was not closed properly.\n",crypted_file);
        exit(EXIT_FAILURE);
    }
    
    //write decrypted file
    f = fopen(file_to_decrypt_to,"w+");
        
    if(f == NULL) {
        printf("file %s did not open properly.\n",file_to_decrypt_to);
        exit(EXIT_FAILURE);
    }
    
    
    if(fclose(f) == EOF){
        printf("file %s was not closed properly.\n",file_to_decrypt_to);
        exit(EXIT_FAILURE);
    }
    return 1;
}

void change_parrot_phrase (char* phrase) {
    //write the new parrot phrase
    FILE *f = NULL;
    f = fopen("perroq.def","w+");
        
    if(f == NULL) {
        printf("file perroq.def did not open properly.\n");
        exit(EXIT_FAILURE);
    }
    
    fwrite(phrase,sizeof(phrase), 1, f);// write into the file
    
    if(fclose(f) == EOF){
        printf("file perroq.def was not closed properly.\n");
        exit(EXIT_FAILURE);
    }
}
