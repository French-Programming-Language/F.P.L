#include "ErrorsCodeManagement.h"

void forgotType(FPL::Data::Data& data) {
    std::cerr << "Vous avez oublie de preciser le type, ligne "
    << data.current_token->TokenLineNumber << "." << std::endl;
    exit(1);
}

void forgotName(FPL::Data::Data& data) {
    std::cerr << "Vous avez oublie de donner un nom, ligne "
    << data.current_token->TokenLineNumber << "." << std::endl;
    exit(2);
}

void forgotEgalOperators(FPL::Data::Data& data) {
    std::cerr << "Vous avez oublie de placer les operateurs '->' pour donner une valeur, ligne "
    << data.current_token->TokenLineNumber << "." << std::endl;
    exit(3);
}

void forgotValue(FPL::Data::Data& data) {
    std::cerr << "Vous avez oublie de donner une valeur, ligne "
    << data.current_token->TokenLineNumber << "." << std::endl;
    exit(4);
}

void forgotEndInstructionOperator(FPL::Data::Data& data) {
    std::cerr << "Vous avez oublie de mettre l'operateur ';' pour mettre fin a l'instruction., ligne "
              << data.current_token->TokenLineNumber << "." << std::endl;
    exit(5);
}

void differentTypes(FPL::Data::Data& data) {
    std::cerr << "Vous avez declarer deux types differents dans une meme expression ce qui n'est pas possible, ligne "
    << data.current_token->TokenLineNumber << "." << std::endl;
    exit(6);
}

void variableAlreadyExist(FPL::Data::Data& data) {
    std::cerr << "Vous avez deja declare une variable avec ce nom, ligne "
              << data.current_token->TokenLineNumber << "." << std::endl;
    exit(7);
}

void variableDoesNotExist(FPL::Data::Data& data) {
    std::cerr << "La variable que vous cherchez n'existe pas, ligne "
              << data.current_token->TokenLineNumber << "." << std::endl;
    exit(8);
}

void BoolNotLikeValue(FPL::Data::Data& data) {
    std::cerr << "Pour utiliser le type bool vous devez pas mettre entre '\"' votre valeur mais marquer 'vrai' ou 'faux' simplement, ligne "
              << data.current_token->TokenLineNumber << "." << std::endl;
    exit(9);
}

void wrongTypeForBool(FPL::Data::Data& data) {
    std::cerr << "Pour utiliser un type bool vous devez mettre en argument 'boolean' ou 'bool', ligne "
              << data.current_token->TokenLineNumber << "." << std::endl;
    exit(10);
}

void needValueNextOperatorCondition(FPL::Data::Data& data) {
    std::cerr << "Apres votre operateur conditionnelle vous devez specifier une valeur, ligne "
              << data.current_token->TokenLineNumber << "." << std::endl;
    exit(11);
}

void inputTypeError(FPL::Data::Data& data) {
    std::cerr << "Votre reponse a l'entree clavier comporte un type non similaire a votre type preciser, ligne "
              << data.current_token->TokenLineNumber << "." << std::endl;
    exit(12);
}

void wrongType(FPL::Data::Data& data) {
    std::cerr << "Le type de la valeur preciser n'est pas valide, ligne "
              << data.current_token->TokenLineNumber << "." << std::endl;
    exit(13);
}

void CONVERSION_sameTypeVariable(FPL::Data::Data& data) {
    std::cerr << "Le type precise est le meme que le type de votre variable dans votre conversion donc aucun changement n'est necessaire, ligne "
              << data.current_token->TokenLineNumber << "." << std::endl;
    exit(14);
}

void CONVERSION_boolNumberFromInt(FPL::Data::Data& data) {
    std::cerr << "La variable doit etre de type 'entier' (int) et doit contenir 1 pour 'vrai' et 0 pour 'faux', ligne "
              << data.current_token->TokenLineNumber << "." << std::endl;
    exit(15);
}

void FONCTION_forgotfirstParenthese(FPL::Data::Data& data) {
    std::cerr << "Vous devez ouvrir les parentheses pour inserer des arguments si vous le souhaitez, ligne "
              << data.current_token->TokenLineNumber << "." << std::endl;
    exit(16);
}

void FONCTION_forgotargtype(FPL::Data::Data& data) {
    std::cerr << "Vous devez donner un le type de votre argument, ligne "
              << data.current_token->TokenLineNumber << "." << std::endl;
    exit(17);
}

void FONCTION_forgotargname(FPL::Data::Data& data) {
    std::cerr << "Vous devez donner un le nom de votre argument, ligne "
              << data.current_token->TokenLineNumber << "." << std::endl;
    exit(18);
}

void FONCTION_forgotaddarg(FPL::Data::Data& data) {
    std::cerr << "Vous devez separer vos argument avec une ',', ligne "
              << data.current_token->TokenLineNumber << "." << std::endl;
    exit(19);
}

void FONCTION_forgotinsertcode(FPL::Data::Data& data) {
    std::cerr << "Vous devez ouvrir et fermer avec '{' et '}' pour inserer votre code, ligne "
              << data.current_token->TokenLineNumber << "." << std::endl;
    exit(20);
}

void FONCTION_argumentexist(FPL::Data::Data& data) {
    std::cerr << "L'argument existe deja, merci de donner un autre nom, ligne "
              << data.current_token->TokenLineNumber << "." << std::endl;
    exit(21);
}

void FONCTION_forgotnametocall(FPL::Data::Data& data){
    std::cerr << "Vous devez preciser le nom de la fonction que vous souhaitez appeler, ligne "
              << data.current_token->TokenLineNumber << "." << std::endl;
    exit(22);
}

void FONCTION_forgotargumenttogivevalue(FPL::Data::Data& data) {
    std::cerr << "Vous devez donner un argument, ligne "
              << data.current_token->TokenLineNumber << "." << std::endl;
    exit(23);
}

void FONCTION_forgotargumentvalue(FPL::Data::Data& data) {
    std::cerr << "Vous devez transmettre une valeur a votre argument, ligne "
              << data.current_token->TokenLineNumber << "." << std::endl;
    exit(24);
}

void FONCTION_argumentDoesNotExist(FPL::Data::Data& data) {
    std::cerr << "Cet argument n'existe pas, ligne "
              << data.current_token->TokenLineNumber << "." << std::endl;
    exit(25);
}

void FONCTION_noneedargs(FPL::Data::Data& data) {
    std::cerr << "La fonction ne demande pas des arguments donc veuillez retirer ':' et mettre directement ';' à la fin de l'instruction, ligne "
              << data.current_token->TokenLineNumber << "." << std::endl;
    exit(26);
}

void FONCTION_didnotfindarg(FPL::Data::Data& data) {
    std::cerr << "L'argument est introuvable, veuillez reessayer ou contacter l'equipe de developpement, ligne "
              << data.current_token->TokenLineNumber << "." << std::endl;
    exit(27);
}

void VAR_wrongparameter(FPL::Data::Data& data) {
    std::cerr << "Vous devez preciser un parametre pour votre variable qui existe : 'globale', 'fonction', ligne "
              << data.current_token->TokenLineNumber << "." << std::endl;
    exit(28);
}

void VAR_closeparameter(FPL::Data::Data& data) {
    std::cerr << "Vous devez fermer les parenthese si vous avez voulu introduire un parametre pour votre variable, ligne "
              << data.current_token->TokenLineNumber << "." << std::endl;
    exit(29);
}

void FONCTION_doesnotexist(FPL::Data::Data& data) {
    std::cerr << "La fonction n'existe pas, ligne "
              << data.current_token->TokenLineNumber << "." << std::endl;
    exit(30);
}

void RETURN_noinfonction(FPL::Data::Data& data) {
    std::cerr << "Vous ne devez pas utiliser 'renvoyer' en dehors d'une fonction, ligne "
              << data.current_token->TokenLineNumber << "." << std::endl;
    exit(31);
}

void RETURN_novariablefound(FPL::Data::Data& data) {
    std::cerr << "Vous devez declarer une variable sous ce format : 'variable TYPE_DE_RETOUR fonction NOM -> FONCTION;', ligne "
              << data.current_token->TokenLineNumber << "." << std::endl;
    exit(32);
}

void RETURN_noreturn(FPL::Data::Data& data) {
    std::cerr << "Aucune instruction 'renvoyer' n'a ete trouve, ligne "
              << data.current_token->TokenLineNumber << "." << std::endl;
    exit(33);
}

void RETURN_wrongtype(FPL::Data::Data& data) {
    std::cerr << "Les types doivent etre les meme et non differents, ligne "
              << data.current_token->TokenLineNumber << "." << std::endl;
    exit(33);
}

void IMPORT_needfilename(FPL::Data::Data& data) {
    std::cerr << "Vous devez donner le nom du fichier entre guillements : '\"', ligne "
              << data.current_token->TokenLineNumber << "." << std::endl;
    exit(33);
}