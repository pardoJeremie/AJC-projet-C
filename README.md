# AJC-projet-C

**PROJET : CRYPTAGE**

On souhaite réaliser un programme d'encryptage et décryptage d’un fichier texte. Pour cela, nous utiliserons l'algorithme du « perroquet ». Cet algorithme repose sur un mot (le perroquet) qui permet de crypter en calculant la différence ASCII caractère par caractère.

*Exemple :*
| :---------------:|:---------------|
| Texte à crypter | Olivier |
| Perroquet | abcd | 
| Résultat en calcul ascii | (‘O’-‘a’)(‘l’-‘b’)(‘i’-‘c’)(‘v’-‘d’)(‘i’-‘a’)(‘e’-‘b’)(‘r’-‘c’) |
| Résultat | Concaténation des codes ASCII | 

Le programme utilisera trois fichiers:
* « peroq.def », fichier contenant le mot (ou la phrase) du « perroquet ».
* « fichier.txt », fichier contenant le texte à crypté. Ce fichier devra être supprimé après la réalisation de l'opération de cryptage.
* « dest.crt », fichier contenant le texte crypté.

Il faudra réaliser une fonction encryptage, une fonction décryptage avec option d'affichage dans la ligne de commande ou dans un fichier texte et un menu de sélection (option, réaliser une fonction permettant de changer le mot/phrase « perroquet » ).
