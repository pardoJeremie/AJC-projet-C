//
//  function.c
//  AJC projet C
//
//  Created by pardo jérémie on 12/05/2022.
//

#include "function.h"

#define PATH_SIZE 500
#define TEXT_SIZE 1001

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
    int reponse = 0;//contains the value selectionned by the user.
    char path_a[PATH_SIZE],path_b[PATH_SIZE]// contains the values of a path to a file path
    , text[TEXT_SIZE];// contains the values of a path to a text
    
    printf("MENU DE SELECTION:\n 1. Encrypter un fichier \n 2. Encrypter une entrée texte \n 3. Décrypter un fichier crypté dans la ligne de command \n 4. Décrypter un fichier  crypté dans un fichier texte\n 5. Changer la phrase perroquet\n 6. Quitter\n    votre choix: ");
    fflush(stdin);
    scanf("%d",&reponse);
    
    switch (reponse) {
        case 1:// encrypt a file
            printf("Attention!\nCette action supprimera le fichier à encrypter.\n");
            if(confirmation()) {
                printf("Écrivez le chemin du fichier à encrypté (%d caractère max): ", TEXT_SIZE-1);
                fflush(stdin);
                fgets(path_a,PATH_SIZE, stdin);
            
                printf("Écrivez le chemin du fichier crypté: ");
                fflush(stdin);
                fgets(path_b,PATH_SIZE, stdin);
            
                path_a[strcspn(path_a, "\r\n")] = '\0'; //delet the '\n' character at the end of path_b introduced by fgets
                path_b[strcspn(path_b, "\r\n")] = '\0'; //delet the '\n' character at the end of path_b introduced by fgets
                if(encrypt_file (path_a,path_b))
                    printf("Fichier encrypté!\n");
            }
            break;
        case 2:// encrypt a text
            printf("\nÉcrivez le texte (%d caractère max): ", TEXT_SIZE-1);
            fflush(stdin);
            fgets(text,TEXT_SIZE, stdin);
            
            printf("Écrivez le chemin du fichier crypté: ");
            fflush(stdin);
            fgets(path_b,PATH_SIZE, stdin);
            
            text[strcspn(text, "\r\n")] = '\0'; //delet the '\n' character at the end of text introduced by fgets
            path_b[strcspn(path_b, "\r\n")] = '\0'; //delet the '\n' character at the end of path_b introduced by fgets
            if(encrypt_string (text,path_b))
                printf("Texte encrypté!\n");
            
            break;
        case 3:// decrypt a file into the command ligne
            printf("Écrivez le chemin du fichier crypté: ");
            fflush(stdin);
            fgets(path_b,PATH_SIZE, stdin);
            
            path_b[strcspn(path_b, "\r\n")] = '\0'; //delet the '\n' character at the end of path_b introduced by fgets
            if(decryt_to_printf(path_b))
                printf("Texte decrypte!\n");
            break;
        case 4:// decrypt a file into a new file
            printf("Écrivez le chemin du fichier crypté: ");
            fflush(stdin);
            fgets(path_b,PATH_SIZE, stdin);
            
            printf("Écrivez le chemin du fichier cible: ");
            fflush(stdin);
            fgets(path_a,PATH_SIZE, stdin);
            
            path_a[strcspn(path_a, "\r\n")] = '\0'; //delet the '\n' character at the end of path_b introduced by fgets
            path_b[strcspn(path_b, "\r\n")] = '\0'; //delet the '\n' character at the end of path_b introduced by fgets
            if(decryt_to_file(path_a, path_b))
                printf("Texte décrypté!\n");
            
            break;
        case 5:// change parrot phrase
            printf("Attention!\nChanger la phrase perroquet vous empêchera de lire l'ensemble des fichiers encryptés avec la phrase actuelle.\n");
            
            if(confirmation()) {
                printf("Écrivez la nouvelle phrase parrot (%d caractère max): ",TEXT_SIZE-1);
                fflush(stdin);
                fgets(text,TEXT_SIZE, stdin);
                
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
    char parrot[TEXT_SIZE],// contains the values of the parrot phrase
    text[TEXT_SIZE];// contains the text to decrypt or crypt
    unsigned long parrot_size = 0, text_size = 0;//size of parrot phrase
    FILE *f = NULL;
    
    //read parrot.def
    f = fopen("perroq.def","r");//open file
    if(f == NULL) {
        printf("file perroq.def did not open properly.\n Are you sure the file exists?\n");
        return 0;
    }
    
    fread(parrot,sizeof(parrot), 1, f);//read file
    parrot_size = strlen(parrot);
    
    if(fclose(f) == EOF) {//close file
        printf("file perroq.def was not closed properly.\n");
        exit(EXIT_FAILURE);
    }
    
    //read file to encrypt
    f = fopen(file_to_encrypt,"r");
    if(f == NULL) {//open file
        printf("file %s did not open properly.\n Are you sure the file exists?\n",file_to_encrypt);
        return 0;
    }
    
    fread(text,sizeof(text), 1, f);//read file
    text_size = strlen(text)+1;// +1 to encrypt '\0'
    
    if(fclose(f) == EOF){//close file
        printf("file %s was not closed properly.\n",file_to_encrypt);
        exit(EXIT_FAILURE);
    }
    
    //crypte text
    int j = 0;
    for (int i = 0; i < text_size; i++){
        text[i] -= parrot[j++];
        if (j >= parrot_size)
            j = 0;
    }
    
    
    //write crypted file
    f = fopen(new_crypted_file,"w+");//open file
    if(f == NULL) {
        printf("file %s did not open properly.\n",file_to_encrypt);
        exit(EXIT_FAILURE);
    }
    
    fwrite(text,sizeof(char), text_size, f);// write into the file
    
    if(fclose(f) == EOF){//close file
        printf("file %s was not closed properly.\n",file_to_encrypt);
        exit(EXIT_FAILURE);
    }
    
    //delet file to encrypt
    if (remove(file_to_encrypt) != 0) {//delet file
        printf("file %s did not deleted successfully\n",file_to_encrypt);
        return 0;
    }
    
    return 1;
}


int encrypt_string (char* text, char* new_crypted_file) {
    char parrot[TEXT_SIZE];// contains the values of the parrot phrase
    unsigned long parrot_size = 0,  text_size = 0;//size of parrot phrase
    FILE *f = NULL;
    
    //read parrot.def
    f = fopen("perroq.def","r");//open file
    if(f == NULL) {
        printf("file perroq.def did not open properly.\n Are you sure the file exists?\n");
        return 0;
    }
    
    fread(parrot,sizeof(parrot), 1, f);//read file
    parrot_size = strlen(parrot);
    
    if(fclose(f) == EOF){//close file
        printf("file perroq.def was not closed properly.\n");
        exit(EXIT_FAILURE);
    }
    
    // crypte text
    text_size = strlen (text)+1;// +1 to encrypt '\0'
    int j = 0;
    for (int i = 0; i < text_size; i++){
        text[i] -= parrot[j++];
        if (j >= parrot_size)
            j = 0;
    }
    
    //write crypted file
    f = fopen(new_crypted_file,"w+");//open file
    if(f == NULL) {
        printf("file %s did not open properly.\n",new_crypted_file);
        exit(EXIT_FAILURE);
    }
    
    fwrite(text,sizeof(char), text_size, f);// write into the file
    
    if(fclose(f) == EOF){//close file
        printf("file %s was not closed properly.\n",new_crypted_file);
        exit(EXIT_FAILURE);
    }
    
    return 1;
}

int decryt_to_printf (char* crypted_file) {
    char parrot[TEXT_SIZE],// contains the values of the parrot phrase
    text[TEXT_SIZE];// contains the text to decrypt or crypt
    unsigned long parrot_size = 0;//size of parrot phrase
    FILE *f = NULL;
    
    //read parrot.def
    f = fopen("perroq.def","r");//open file
    if(f == NULL) {
        printf("file perroq.def did not open properly.\n Are you sure the file exists?\n");
        return 0;
    }
    
    fread(parrot,sizeof(parrot), 1, f);//read file
    parrot_size = strlen(parrot);
    
    if(fclose(f) == EOF){//close file
        printf("file perroq.def was not closed properly.\n");
        exit(EXIT_FAILURE);
    }
    
    //read crypted file
    f = fopen(crypted_file,"r");//open file
    if(f == NULL) {
        printf("file %s did not open properly.\n Are you sure the file exists?\n",crypted_file);
        return 0;
    }
    
    fread(text,sizeof(text), 1, f);//read file
    
    if(fclose(f) == EOF){//close file
        printf("file %s was not closed properly.\n",crypted_file);
        exit(EXIT_FAILURE);
    }
    
    //decrypte text
    int j = 0;
    for (int i = 0; i < TEXT_SIZE; i++){
        text[i] += parrot[j++];
        if(text[i] == '\0')//if a '\0' character is decoded
            break;
        printf("%c",text[i]);//print decrypted char to command ligne
        if (j >= parrot_size)
            j = 0;
    }
    printf("\n");
    
    return 1;
}

int decryt_to_file (char* file_to_decrypt_to, char* crypted_file) {
    char parrot[TEXT_SIZE],// contains the values of the parrot phrase
    text[TEXT_SIZE];// contains the text to decrypt or crypt
    unsigned long parrot_size = 0;//size of parrot phrase
    FILE *f = NULL;
    
    //read parrot.def
    f = fopen("perroq.def","r");//open file
    if(f == NULL) {
        printf("file perroq.def did not open properly.\n Are you sure the file exists?\n");
        return 0;
    }
    
    fread(parrot,sizeof(parrot), 1, f);//read file
    parrot_size = strlen(parrot);
    
    if(fclose(f) == EOF){//close file
        printf("file perroq.def was not closed properly.\n");
        exit(EXIT_FAILURE);
    }
    
    //read crypted file
    f = fopen(crypted_file,"r");//open file
    if(f == NULL) {
        printf("file %s did not open properly.\n Are you sure the file exists?\n",crypted_file);
        return 0;
    }
    
    fread(text,sizeof(text), 1, f);//read file
    
    if(fclose(f) == EOF){//close file
        printf("file %s was not closed properly.\n",crypted_file);
        exit(EXIT_FAILURE);
    }
    
    //decrypte text
    int j = 0;
    for (int i = 0; i < TEXT_SIZE; i++){
        text[i] += parrot[j++];
        if(text[i] == '\0')//if a '\0' character is decoded
            break;
        if (j >= parrot_size)
            j = 0;
    }
    
    //write decrypted file
    f = fopen(file_to_decrypt_to,"w+");//open file
    if(f == NULL) {
        printf("file %s did not open properly.\n",file_to_decrypt_to);
        exit(EXIT_FAILURE);
    }
    
    fwrite(text,sizeof(char), strlen(text), f);// write into the file
    
    if(fclose(f) == EOF){//close file
        printf("file %s was not closed properly.\n",file_to_decrypt_to);
        exit(EXIT_FAILURE);
    }
    return 1;
}

void change_parrot_phrase (char* phrase) {
    //write the new parrot phrase
    FILE *f = NULL;
    f = fopen("perroq.def","w+");//open file
    if(f == NULL) {
        printf("file perroq.def did not open properly.\n");
        exit(EXIT_FAILURE);
    }
    
    fwrite(phrase,sizeof(char),strlen(phrase), f);// write into the file
    
    if(fclose(f) == EOF){//close file
        printf("file perroq.def was not closed properly.\n");
        exit(EXIT_FAILURE);
    }
}
