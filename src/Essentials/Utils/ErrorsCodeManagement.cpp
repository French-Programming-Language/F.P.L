#include "ErrorsCodeManagement.h"

#define CREATE_ERROR(functionName, error, exitType) \
	void functionName(FPL::Data::Data& data) { std::cerr << error << data.current_token->TokenLineNumber << "." << std::endl; exit(exitType); } 

CREATE_ERROR(forgotType, "Vous avez oublie de preciser le type, ligne ", 1);
CREATE_ERROR(forgotName, "Vous avez oublie de donner un nom, ligne ", 2);
CREATE_ERROR(forgotEgalOperators, "Vous avez oublie de placer les operateurs '->' pour donner une valeur, ligne ", 3);
CREATE_ERROR(forgotValue, "Vous avez oublie de donner une valeur, ligne ", 4);
CREATE_ERROR(forgotEndInstructionOperator, "Vous avez oublie de mettre l'operateur ';' pour mettre fin a l'instruction, ligne ", 5);
CREATE_ERROR(differentTypes, "Vous avez declare deux types differents dans une meme expression ce qui n'est pas possible, ligne ", 6);
CREATE_ERROR(variableAlreadyExist, "Vous avez deja declare une variable avec ce nom, ligne ", 7);
CREATE_ERROR(variableDoesNotExist, "La variable que vous cherchez n'existe pas, ligne ", 8);
CREATE_ERROR(BoolNotLikeValue, "Pour utiliser le type bool vous devez pas mettre entre '\"' votre valeur mais marquer 'vrai' ou 'faux' simplement, ligne ", 9);
CREATE_ERROR(wrongTypeForBool, "Pour utiliser un type bool vous devez mettre en argument 'boolean' ou 'bool', ligne ", 10);
CREATE_ERROR(needValueNextOperatorCondition, "Apres votre operateur conditionnelle vous devez specifier une valeur, ligne ", 11);
CREATE_ERROR(inputTypeError, "Votre reponse a l'entree clavier comporte un type non similaire a votre type preciser, ligne ", 12);
CREATE_ERROR(wrongType, "Le type de la valeur preciser n'est pas valide, ligne ", 13);
CREATE_ERROR(CONVERSION_sameTypeVariable, "Le type precise est le meme que le type de votre variable dans votre conversion donc aucun changement n'est necessaire, ligne ", 14);
CREATE_ERROR(CONVERSION_boolNumberFromInt, "La variable doit etre de type 'entier' (int) et doit contenir 1 pour 'vrai' et 0 pour 'faux', ligne ", 15);
CREATE_ERROR(FONCTION_forgotfirstParenthese, "Vous devez ouvrir les parentheses pour inserer des arguments si vous le souhaitez, ligne ", 16);
CREATE_ERROR(FONCTION_forgotargtype, "Vous devez donner un le type de votre argument, ligne ", 17);
CREATE_ERROR(FONCTION_forgotargname, "Vous devez donner un le nom de votre argument, ligne ", 18);
CREATE_ERROR(FONCTION_forgotaddarg, "Vous devez separer vos argument avec une ',', ligne ", 19);
CREATE_ERROR(FONCTION_forgotinsertcode, "Vous devez ouvrir et fermer avec '{' et '}' pour inserer votre code, ligne ", 20);
CREATE_ERROR(FONCTION_argumentexist, "L'argument existe deja, merci de donner un autre nom, ligne ", 21);
CREATE_ERROR(FONCTION_forgotnametocall, "Vous devez preciser le nom de la fonction que vous souhaitez appeler, ligne ", 22);
CREATE_ERROR(FONCTION_forgotargumenttogivevalue, "Vous devez donner un argument, ligne ", 23);
CREATE_ERROR(FONCTION_forgotargumentvalue, "Vous devez transmettre une valeur a votre argument, ligne ", 24);
CREATE_ERROR(FONCTION_argumentDoesNotExist, "Cet argument n'existe pas, ligne ", 25);
CREATE_ERROR(FONCTION_noneedargs, "La fonction ne demande pas des arguments donc veuillez retirer ':' et mettre directement ';' a la fin de l'instruction, ligne ", 26);
CREATE_ERROR(FONCTION_didnotfindarg, "L'argument est introuvable, veuillez reessayer ou contacter l'equipe de developpement, ligne ", 27);
CREATE_ERROR(VAR_wrongparameter, "Vous devez preciser un parametre pour votre variable qui existe : 'globale', 'fonction', ligne ", 28);
CREATE_ERROR(VAR_closeparameter, "Vous devez fermer les parenthese si vous avez voulu introduire un parametre pour votre variable, ligne ", 29);
CREATE_ERROR(FONCTION_doesnotexist, "La fonction n'existe pas, ligne ", 30);
CREATE_ERROR(RETURN_noinfonction, "Vous ne devez pas utiliser 'renvoyer' en dehors d'une fonction, ligne ", 31);
CREATE_ERROR(RETURN_novariablefound, "Vous devez declarer une variable sous ce format : 'variable TYPE_DE_RETOUR fonction NOM -> FONCTION;', ligne ", 32);
CREATE_ERROR(RETURN_noreturn, "Aucune instruction 'renvoyer' n'a ete trouve, ligne ", 33);
CREATE_ERROR(RETURN_wrongtype, "Les types doivent etre les meme et non differents, ligne ", 34);
CREATE_ERROR(IMPORT_needfilename, "Vous devez donner le nom du fichier entre guillements : '\"', ligne ", 35);
CREATE_ERROR(PAQUET_forgotname, "Vous devez donner a nom a votre paquet, ligne ", 36);
CREATE_ERROR(PAQUET_open, "Vous devez ouvrir les '{' pour mettre votre code, ligne ", 37);
CREATE_ERROR(PAQUET_close, "Vous devez fermer l'introduction du code avec '}' pour mettre votre code, ligne ", 38);
CREATE_ERROR(FICHIER_fileunknow, "Fichier non trouve, ligne ", 39);
CREATE_ERROR(FICHIER_varunknow, "Variable non trouve, ligne ", 40);
CREATE_ERROR(FICHIER_wrongargument, "Mauvais argument pour utiliser 'fichier' en instruction : 'lire' ou 'ecrire', ligne ", 41);
CREATE_ERROR(FICHIER_stringtypetogetfile, "Pour recuperer le fichier vous devez le mettre entre '\"' donc de type 'texte' (string), ligne ", 42);
CREATE_ERROR(FICHIER_needvariable, "Precisez le nom d'une variable existante ou non, ligne ", 42);
