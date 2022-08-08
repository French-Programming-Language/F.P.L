#include "Parser.h"

namespace FPL {
    Parser::Parser() {
        mTypes["vide"] = Type("vide", VOID);
        mTypes["entier"] = Type("entier", INT);
        mTypes["decimal"] = Type("decimal", DOUBLE);
        mTypes["texte"] = Type("texte", STRING);
        mTypes["auto"] = Type("auto", AUTO);

        InstructionsList = {
                "envoyer",
                "appeler",
                "renvoyer",
                "definir",
                "variable",
                "changer",
                "saisir",
                "fonction",
                "globale",
                "entier",
                "decimal",
                "texte",
                "vide",
                "auto"
        };
    }

    void Parser::ManageVariableName(std::optional<FonctionDefinition>& fonction, std::string name) {
        if (isVariable(name)) {
            std::cerr << "Veuillez choisir un autre nom pour votre variable." << std::endl;
            exit(1);
        }

        if (std::find(InstructionsList.begin(), InstructionsList.end(), name) != InstructionsList.end()) {
            std::cerr << "Le nom doit etre different des types, des instructions." << std::endl;
            exit(1);
        }

        if (fonction != std::nullopt) {
            if (isArgument(fonction->FonctionName, name)) {
                std::cerr << "Le nom de la variable ne peut pas etre le meme que celui d'un argument de la fonction : " << fonction->FonctionName << "." << std::endl;
                exit(1);
            }
        }
    }

    void Parser::DefineVariable(std::optional<FonctionDefinition>& fonction, std::string& VarName, Type& VarType, std::string& VarValue, std::optional<Statement>& ContentVarValue, bool isGlobal, bool HasReturnV) {
        VariableDefinition variable;
        variable.VariableName = VarName;
        if (ContentVarValue.has_value() && ContentVarValue->StatementType.mType != AUTO) {
            variable.VariableType = Type(VarType.mName, VarType.mType);
        } else {
            if (ContentVarValue.has_value() && VarType.mType != ContentVarValue->StatementType.mType) {
                std::cerr << "Vous devez donner une valeur a la variable qui correspond au type." << std::endl;
                exit(1);
            }

            variable.VariableType = Type(ContentVarValue->StatementType.mName, ContentVarValue->StatementType.mType);
        }
        variable.IsGlobal = isGlobal;
        variable.HasReturnValue = HasReturnV;
        variable.InFonction = false;
        if (fonction.has_value()) {
            variable.InFonction = true;
        }
        if (ContentVarValue.has_value() && ContentVarValue->StatementType.mType == STRING) {
            std::replace(ContentVarValue->StatementName.begin(), ContentVarValue->StatementName.end(), '"', ' ');
        }
        variable.VariableValue = VarValue;
        mVariables[variable.VariableName] = variable;
    }

    bool Parser::AppelerInstruction() {
        auto PossibleFonctionName = CheckerIdentifiant();
        if (PossibleFonctionName.has_value()) {
            if (isFonction(PossibleFonctionName->mText)) {
                FonctionDefinition fonction = mFonctions[PossibleFonctionName->mText];

                if (fonction.HasReturn) {
                    std::cerr << "Vous devez utiliser une variable et non une appellation classique, il faut vous que vous recuperiez la valeur de retour." << std::endl;
                    exit(1);
                }

                if (!fonction.HasArgument) {
                    if (!CheckerOperateur(";").has_value()) {
                        std::cerr << "Vous devez mettre le symbole ';' pour mettre fin a l'instruction." << std::endl;
                        exit(1);
                    }
                }

                executeFonctionContent(fonction, PossibleFonctionName->mText);
                return true;
            }
        }
        return false;
    }

    bool Parser::FonctionInstruction(auto parseStart) {
        auto PeutEtreNom = CheckerIdentifiant();

        if (std::find(InstructionsList.begin(), InstructionsList.end(), PeutEtreNom->mText) != InstructionsList.end()) {
            std::cerr << "Le nom doit etre different des types, des instructions." << std::endl;
            exit(1);
        }

        if (PeutEtreNom.has_value()) {
            if (CheckerOperateur("(").has_value()) {
                if (isFonction(PeutEtreNom->mText)) {
                    std::cerr << "Cette fonction est deja existante, donner un autre nom a cette derniere." << std::endl;
                    exit(1);
                }

                FonctionDefinition fonction;
                fonction.FonctionName = PeutEtreNom->mText;
                while (!CheckerOperateur(")").has_value()) {
                    auto type = CheckerType();

                    if (type->mType == VOID) { // Si aucun paramètre ou l'utilisateur a utilisé l'argument 'vide' ou juste fermer.
                        if (CheckerOperateur(")").has_value()) {
                            break;
                        } else {
                            std::cerr << "Vous devez fermer les parentheses de la fonction." << std::endl;
                            exit(1);
                        }
                    }

                    if (!type.has_value()) {
                        std::cerr << "Vous devez spécifier un type d'argument." << std::endl;
                        exit(1);
                    }

                    // Ajout de l'argument...
                    auto possibleArg = CheckerIdentifiant();
                    if (!possibleArg.has_value()) {
                        std::cerr << "Vous devez spécifier un nom unique a l'argument." << std::endl;
                        exit(1);
                    }
                    ArgumentDefinition param;
                    param.ArgType.mName = type->mName;
                    param.ArgType.mType = type->mType;
                    param.ArgName = possibleArg->mText;
                    fonction.HasArgument = true;
                    fonction.NumberArgument += 1;
                    fonction.ArgsFonction.push_back(param);

                    if (CheckerOperateur(")").has_value()) {
                        break;
                    }
                    if (!CheckerOperateur(",").has_value()) {
                        std::cerr << "Vous devez utiliser la ',' pour separer les arguments de la fonction." << std::endl;
                        exit(1);
                    }
                }

                // On récupère le code entre les {} :
                if (CheckerOperateur("{")) {
                    while (!CheckerOperateur("}").has_value()) {
                        if (mCurrentToken->mText == "renvoyer") {
                            ++mCurrentToken;
                            auto v = CheckerValue();
                            if (v.has_value()) {
                                if (CheckerOperateur(";").has_value()) {
                                    fonction.HasReturn = true;
                                    fonction.ReturnValue = v->StatementName;
                                    fonction.ReturnType = v->StatementType;

                                    if (CheckerIdentifiant().has_value() || CheckerValue().has_value() || CheckerType().has_value()) {
                                        std::cerr << "Vous ne pouvez plus rajouter d'instruction ou autre apres l'instruction 'renvoyer'." << std::endl;
                                        exit(1);
                                    }

                                    break;
                                } else {
                                    std::cerr << "Vous devez utiliser la ';' pour mettre fin a l'instruction." << std::endl;
                                    exit(1);
                                }
                            } else {
                                std::cerr << "Veuillez indiquer la valeur de retour de la fonction '" << fonction.FonctionName << "'." << std::endl;
                                exit(1);
                            }
                        }

                        if (mCurrentToken->mType == CHAINE_LITERAL) {
                            mCurrentToken->mText += "\"";
                        }

                        fonction.FonctionContent .push_back(mCurrentToken->mText);
                        ++mCurrentToken;

                        if (CheckerOperateur("}").has_value()) {
                            break;
                        }
                    }

                    if (fonction.HasReturn) {
                        if (!CheckerOperateur("}").has_value()) {
                            std::cerr << "Vous devez utiliser '}' pour mettre fin a la fonction." << std::endl;
                            exit(1);
                        }
                    }
                }

                mFonctions[fonction.FonctionName] = fonction;
                return true;
            } else {
                mCurrentToken = parseStart;
                std::cerr << "Vous devez ouvrir les parenthèses pour ajouter des paramètres si vous le souhaitez." << std::endl;
                exit(1);
            }
        } else {
            mCurrentToken = parseStart;
            std::cerr << "Vous devez donner un nom a votre fonction." << std::endl;
            exit(1);
        }
        return false;
    }

    void Parser::executeFonctionContent(FonctionDefinition& fonction, std::string fonctionName) {
        if (fonction.HasArgument) {
            if (CheckerOperateur(":").has_value()) {
                while (fonction.NumberArgument > 0) {
                    auto name = CheckerIdentifiant();
                    if (!name.has_value()) {
                        std::cerr << "Veuillez specifier le nom du parametre." << std::endl;
                        exit(1);
                    }

                    if (!isFonctionArgument(fonctionName, name->mText)) {
                        std::cerr << "Ce parametre n'existe pas dans la fonction " << fonctionName << "." << std::endl;
                        exit(1);
                    }

                    auto value = CheckerValue();
                    if (!value.has_value()) {
                        std::cerr << "Veuillez donner une valeur au parametre '" << name->mText << "'." << std::endl;
                        exit(1);
                    }

                    auto parametre = getArgument(fonctionName, name->mText);
                    if (parametre->ArgType.mType == value->StatementType.mType && parametre->ArgType.mType != AUTO) {
                        if (value->StatementType.mType == STRING) {
                            std::replace(value->StatementName.begin(), value->StatementName.end(), '"', ' ');
                        }
                        parametre->ArgValue = value->StatementName;
                    } else if (parametre->ArgType.mType == AUTO && parametre->ArgType.mType != value->StatementType.mType) {
                        parametre->ArgType = Type("auto", AUTO);
                        parametre->ArgValue = value->StatementName;
                    } else {
                        std::cerr << "Le type de votre valeur doit être identique a celui de l'argument." << std::endl;
                        exit(1);
                    }

                    ArgumentDefinition argument;
                    argument.ArgName = parametre->ArgName;
                    argument.ArgType = Type(parametre->ArgType.mName, parametre->ArgType.mType);
                    argument.ArgValue = parametre->ArgValue;
                    mArguments[fonction.FonctionName][argument.ArgName] = argument;

                    if (fonction.NumberArgument > 1 && !CheckerOperateur(",").has_value()) {
                        std::cerr << "Veuillez separer les different arguments par le symbole ','." << std::endl;
                        exit(1);
                    }
                    fonction.NumberArgument -= 1;
                }
                if (!CheckerOperateur(";").has_value()) {
                    std::cerr << "Vous devez mettre le symbole ';' pour mettre fin a l'instruction." << std::endl;
                    exit(1);
                }
            } else {
                std::cerr << "La fonction a des parametres, vous devez obligatoirement leur donner une valeur." << std::endl;
                exit(1);
            }
        }

        if (!fonction.FonctionContent.empty()) {
            std::string finalContent;
            for (auto const &a : fonction.FonctionContent) {
                finalContent.append(a).append(" ");
            }
            TokenBuilding t;
            std::cout << "" << std::endl; // IGNORE (finalContent) -> sans le print, cela ne marche plus.
            std::vector<Token> tokens = t.parseToken(finalContent);

            auto FCurrToken = tokens.begin();
            auto oldCurrentToken = mCurrentToken;
            std::optional<FonctionDefinition> f = fonction;
            parse(tokens, f);
            mCurrentToken = oldCurrentToken;

            std::vector<std::string> toErase;
            for(auto const &var: mVariables) {
                if(var.second.InFonction && !var.second.IsGlobal) {
                    toErase.push_back(var.first);
                }
            }
            for(auto const &it: toErase)
            {
                mVariables.erase(it);
            }
        }
    }

    bool Parser::VariableInstruction(std::optional<FonctionDefinition>& fonction) {
        auto VarType = CheckerType();
        if (VarType.has_value()) {
            auto VarName = CheckerIdentifiant();
            if (VarName.has_value()) {
                if (VarName->mText == "saisir") {
                    VarName = CheckerIdentifiant();
                    if (VarName.has_value()) {
                        ManageVariableName(fonction, VarName->mText);

                        if (CheckerOperateur("-").has_value()) {
                            if (CheckerOperateur(">").has_value()) {
                                if (executeInputs(fonction, VarName->mText, VarType.value(), "with")) {
                                    return true;
                                }
                                return false;
                            } else {
                                std::cerr << "Vous devez utiliser les symboles '->' pour donner une valeur." << std::endl;
                                exit(1);
                            }
                        } else {
                            if (executeInputs(fonction, VarName->mText, VarType.value(), "without")) {
                                return true;
                            }
                            std::cerr << "Vous devez utiliser les symboles '->' pour donner une valeur." << std::endl;
                            exit(1);
                        }
                    } else {
                        std::cerr << "Vous devez indiquer un nom a la variable." << std::endl;
                        exit(1);
                    }
                }
                else if (VarName->mText == "globale") {
                    VarName = CheckerIdentifiant();
                    if (VarName.has_value()) {
                        ManageVariableName(fonction, VarName->mText);

                        if (CheckerOperateur("-").has_value()) {
                            if (CheckerOperateur(">").has_value()) {
                                auto VarValue = CheckerValue();
                                if (VarValue.has_value()) {
                                    if (CheckerOperateur(";").has_value()) {
                                        DefineVariable(fonction, VarName->mText, VarType.value(), VarValue->StatementName, VarValue, true, false);
                                        return true;
                                    }
                                } else {
                                    auto name = CheckerIdentifiant();
                                    if (name.has_value()) {
                                       if (CheckerOperateur(";").has_value()) {
                                           VariableDefinition variable;
                                           variable.VariableName = VarName->mText;
                                           variable.IsGlobal = true;
                                           variable.HasReturnValue = false;
                                           variable.InFonction = false;
                                           if (VarType->mType != AUTO) {
                                               variable.VariableType = Type(VarType->mName, VarType->mType);
                                           }

                                           if (fonction.has_value() || fonction != std::nullopt) {
                                               variable.InFonction = true;
                                           }

                                           if (fonction != std::nullopt && isArgument(fonction->FonctionName, name->mText)) {
                                               variable.VariableValue = mArguments[fonction->FonctionName][name->mText].ArgValue;

                                               if (VarType->mType == AUTO) {
                                                   variable.VariableType = Type(mArguments[fonction->FonctionName][name->mText].ArgType.mName,
                                                                                mArguments[fonction->FonctionName][name->mText].ArgType.mType);
                                               } else if (VarType->mType != AUTO) {
                                                   if (VarType->mType != mArguments[fonction->FonctionName][name->mText].ArgType.mType) {
                                                       std::cerr << "Vous devez donner une valeur a la variable qui correspond au type." << std::endl;
                                                       exit(1);
                                                   }
                                               }
                                           } else if (isVariable(name->mText)) {
                                               variable.VariableValue = mVariables[name->mText].VariableValue;

                                               if (VarType->mType == AUTO) {
                                                   variable.VariableType = Type(mVariables[name->mText].VariableType.mName,
                                                                                mVariables[name->mText].VariableType.mType);
                                               } else if (VarType->mType != AUTO) {
                                                   if (VarType->mType != mVariables[name->mText].VariableType.mType) {
                                                       std::cerr << "Vous devez donner une valeur a la variable qui correspond au type." << std::endl;
                                                       exit(1);
                                                   }
                                               }
                                           }

                                           mVariables[variable.VariableName] = variable;
                                           return true;
                                       } else {
                                           std::cerr << "Merci de signifier la fin de la declaration de la variable avec ';'." << std::endl;
                                           exit(1);
                                       }
                                    }
                                    std::cerr << "Vous devez donner une valeur a votre variable." << std::endl;
                                    exit(1);
                                }
                            } else {
                                std::cerr << "Vous devez utiliser les symboles '->' pour donner une valeur." << std::endl;
                                exit(1);
                            }
                        } else {
                            std::cerr << "Vous devez utiliser les symboles '->' pour donner une valeur." << std::endl;
                            exit(1);
                        }
                    } else {
                        std::cerr << "Vous devez indiquer un nom a la variable." << std::endl;
                        exit(1);
                    }
                }
                else if (VarName->mText == "fonction") {
                    VarName = CheckerIdentifiant();
                    if (VarName.has_value()) {
                        ManageVariableName(fonction, VarName->mText);

                        if (CheckerOperateur("-").has_value()) {
                            if (CheckerOperateur(">").has_value()) {
                                auto PossibleFonction = CheckerIdentifiant();
                                if (PossibleFonction.has_value()) {
                                    if (isFonction(PossibleFonction->mText)) {
                                        FonctionDefinition f = mFonctions[PossibleFonction->mText];

                                        if (VarType->mType != f.ReturnType.mType && VarType->mType != AUTO) {
                                            std::cerr << "Vous devez utiliser le meme type que le type de retour de la fonction." << std::endl;
                                            exit(1);
                                        }

                                        if (!f.HasReturn) {
                                            std::cerr << "Vous devez utiliser une appellation classique." << std::endl;
                                            exit(1);
                                        }

                                        if (!f.HasArgument && !CheckerOperateur(";").has_value()) {
                                            std::cerr << "Vous devez mettre le symbole ';' pour mettre fin a l'instruction." << std::endl;
                                            exit(1);
                                        }

                                        executeFonctionContent(f, PossibleFonction->mText);

                                        DefineVariable(fonction, VarName->mText, VarType.value(), f.ReturnValue, (std::optional<Statement> &) std::nullopt, false, true);
                                        return true;
                                    } else if (isVariable(PossibleFonction->mText)) {
                                        VariableDefinition var = mVariables[PossibleFonction->mText];
                                        if (var.HasReturnValue) {
                                            if (CheckerOperateur(";").has_value()) {
                                                DefineVariable(fonction, VarName->mText, VarType.value(), var.VariableValue, (std::optional<Statement> &) std::nullopt, false, true);
                                                return true;
                                            } else {
                                                std::cerr << "Vous devez mettre le symbole ';' pour mettre fin a l'instruction." << std::endl;
                                                exit(1);
                                            }
                                        } else {
                                            std::cerr << "La variable doit avoir une valeur de retour." << std::endl;
                                            exit(1);
                                        }
                                    } else {
                                        std::cerr << "Cette fonction est inexistante." << std::endl;
                                        exit(1);
                                    }
                                } else {
                                    std::cerr << "Vous devez indiquer le nom de la fonction." << std::endl;
                                    exit(1);
                                }
                            } else {
                                std::cerr << "Vous devez utiliser les symboles '->' pour donner une valeur a la variable." << std::endl;
                                exit(1);
                            }
                        } else {
                            std::cerr << "Vous devez utiliser les symboles '->' pour donner une valeur a la variable." << std::endl;
                            exit(1);
                        }
                    }
                }
                else {
                    ManageVariableName(fonction, VarName->mText);

                    if (CheckerOperateur("-").has_value()) {
                        if (CheckerOperateur(">").has_value()) {
                            auto VarValue = CheckerValue();
                            if (VarValue.has_value()) {
                                if (CheckerOperateur(";").has_value()) {
                                    DefineVariable(fonction, VarName->mText, VarType.value(), VarValue->StatementName, VarValue, false, false);
                                    return true;
                                } else {
                                    std::cerr << "Merci de signifier la fin de la declaration de la variable avec ';'." << std::endl;
                                    exit(1);
                                }
                            } else if (CheckerIdentifiant().has_value()) {
                                --mCurrentToken;
                                auto PossibleVariable = CheckerIdentifiant();
                                if (PossibleVariable.has_value()) {
                                    if (CheckerOperateur(";").has_value()) {
                                        if (isVariable(PossibleVariable->mText)) {
                                            auto OldVariable = mVariables[PossibleVariable->mText];
                                            if (OldVariable.VariableType.mType == VarType->mType) {
                                                DefineVariable(fonction, VarName->mText, VarType.value(), OldVariable.VariableValue, (std::optional<Statement> &) std::nullopt, false, false);
                                                return true;
                                            } else {
                                                if (VarType->mType == AUTO) {
                                                    VariableDefinition variable;
                                                    variable.VariableName = VarName->mText;
                                                    variable.VariableType = Type(OldVariable.VariableType.mName, OldVariable.VariableType.mType);
                                                    variable.IsGlobal = false;
                                                    variable.HasReturnValue = false;
                                                    variable.InFonction = false;
                                                    if (fonction.has_value() || fonction != std::nullopt) {
                                                        variable.InFonction = true;
                                                    }
                                                    variable.VariableValue = OldVariable.VariableValue;

                                                    mVariables[variable.VariableName] = variable;
                                                    return true;
                                                }

                                                std::cerr << "Vous devez donner une valeur a la variable qui correspond au type." << std::endl;
                                                exit(1);
                                            }
                                        } else if (fonction.has_value() && isArgument(fonction->FonctionName, PossibleVariable->mText)) {
                                            VariableDefinition variable;
                                            variable.VariableName = VarName->mText;
                                            variable.IsGlobal = false;
                                            variable.HasReturnValue = false;
                                            variable.InFonction = false;

                                            if (fonction.has_value() || fonction != std::nullopt) {
                                                variable.InFonction = true;
                                            }

                                            if (VarType->mType == mArguments[fonction->FonctionName][PossibleVariable->mText].ArgType.mType) {
                                                variable.VariableType = Type(VarType->mName, VarType->mType);
                                            } else {
                                                std::cerr << "Vous devez donner une valeur a la variable qui correspond au type." << std::endl;
                                                exit(1);
                                            }

                                            if (VarType->mType == AUTO) {
                                                variable.VariableType = Type(mArguments[fonction->FonctionName][PossibleVariable->mText].ArgType.mName,
                                                                             mArguments[fonction->FonctionName][PossibleVariable->mText].ArgType.mType);
                                            }

                                            variable.VariableValue = mArguments[fonction->FonctionName][PossibleVariable->mText].ArgValue;

                                            mVariables[variable.VariableName] = variable;
                                            return true;
                                        }
                                    } else {
                                        std::cerr << "Merci de signifier la fin de la déclaration de la variable avec ';'." << std::endl;
                                        exit(1);
                                    }
                                }
                            } else {
                                std::cerr << "Vous devez donner une valeur a la variable qui correspond au type." << std::endl;
                                exit(1);
                            }
                        } else {
                            std::cerr << "Vous devez utiliser les symboles '->' pour donner une valeur a la variable." << std::endl;
                            exit(1);
                        }
                    } else {
                        std::cerr << "Vous devez utiliser les symboles '->' pour donner une valeur a la variable." << std::endl;
                        exit(1);
                    }
                }
            } else {
                std::cerr << "Vous devez indiquer un nom a la variable." << std::endl;
                exit(1);
            }
        }
        return false;
    }

    bool Parser::executeInputs(std::optional<FonctionDefinition>& fonction, std::string& VarName,  Type& VarType, std::string option) {
        if (option == "with") {
            auto VarValue = CheckerValue();

            if (VarValue->StatementType.mType == STRING) {
                std::replace(VarValue->StatementName.begin(), VarValue->StatementName.end(), '"', ' ');
            }

            if (VarValue.has_value()) {
                std::cout << VarValue->StatementName << std::endl;
            } else {
                auto PossibleArgument = CheckerIdentifiant();
                if (PossibleArgument.has_value() && fonction != std::nullopt) {
                    if (isArgument(fonction->FonctionName, PossibleArgument->mText)) {
                        std::cout << mArguments[fonction->FonctionName][PossibleArgument->mText].ArgValue << std::endl;
                    } else {
                        std::cerr << "L'argument " << PossibleArgument->mText <<" est inexistant ." << std::endl;
                        exit(1);
                    }
                }
            }
        }

        if (CheckerOperateur(";").has_value()) {
            std::string finalv;
            if (VarType.mType == INT) {
                int v;
                std::cin >> v;
                finalv = std::to_string(v);
            } else if (VarType.mType == DOUBLE) {
                double v;
                std::cin >> v;
                finalv = std::to_string(v);
            } else if (VarType.mType == STRING) {
                std::string v;
                std::cin >> v;
                finalv = v;
            }
            DefineVariable(fonction, VarName, VarType, finalv, (std::optional<Statement> &) std::nullopt, false, false);
            return true;
        } else {
            std::cerr << "Merci de signifier la fin de la declaration de la variable avec ';'." << std::endl;
            exit(1);
        }
        return false;
    }

    bool Parser::SaisirInstruction(std::optional<FonctionDefinition>& fonction) {
        auto VarType = CheckerType();

        if (VarType.has_value()) {
            auto VarName = CheckerIdentifiant();
            if (VarName.has_value()) {
                ManageVariableName(fonction, VarName->mText);

                if (CheckerOperateur("-").has_value()) {
                    if (CheckerOperateur(">").has_value()) {
                        if (executeInputs(fonction, VarName->mText, VarType.value(), "with")) {
                            return true;
                        }
                    } else {
                        std::cerr << "Vous devez utiliser les symboles '->' pour donner une valeur." << std::endl;
                        exit(1);
                    }
                } else {
                    if (executeInputs(fonction, VarName->mText, VarType.value(), "without")) {
                        return true;
                    }
                    std::cerr << "Vous devez utiliser les symboles '->' pour donner une valeur." << std::endl;
                    exit(1);
                }
            } else {
                std::cerr << "Veuillez indiquer le nom de la variable." << std::endl;
                exit(1);
            }
        } else {
            std::cerr << "Veuillez donner le type de votre variable." << std::endl;
            exit(1);
        }
        return false;
    }

    bool Parser::ChangerInstruction(std::optional<FonctionDefinition>& fonction) {
        auto VarName = CheckerIdentifiant();
        if (VarName.has_value()) {
            if (isVariable(VarName->mText)) {
                auto VarType = mVariables[VarName->mText].VariableType;
                if (CheckerOperateur("-").has_value()) {
                    if (CheckerOperateur(">").has_value()) {
                        auto Value = CheckerValue();
                        if (Value.has_value()) {
                            if (Value->StatementType.mType == VarType.mType) {
                                if (CheckerOperateur(";").has_value()) {
                                    mVariables[VarName->mText].VariableValue = Value->StatementName;
                                    return true;
                                } else {
                                    std::cerr << "Vous devez mettre le symbole ';' pour mettre fin a l'instruction." << std::endl;
                                    exit(1);
                                }
                            } else {
                                std::cerr << "Veuillez donner une valeur en rapport avec le type de la variable." << std::endl;
                                exit(1);
                            }
                        } else {
                            auto PossibleVar = CheckerIdentifiant();
                            if (PossibleVar.has_value()) {
                                if (CheckerOperateur(";").has_value()) {
                                    if (isVariable(PossibleVar->mText)) {
                                        if (mVariables[PossibleVar->mText].VariableType.mType == mVariables[VarName->mText].VariableType.mType) {
                                            mVariables[VarName->mText].VariableValue = mVariables[PossibleVar->mText].VariableValue;
                                            return true;
                                        } else {
                                            std::cerr << "Le type de la variable n'est pas le même que celui de la variable que vous voulez modifier." << std::endl;
                                            exit(1);
                                        }
                                    } else if (fonction != std::nullopt) {
                                        if (isArgument(fonction->FonctionName, PossibleVar->mText)) {
                                            mVariables[VarName->mText].VariableValue = mArguments[fonction->FonctionName][PossibleVar->mText].ArgValue;
                                            return true;
                                        } else {
                                            std::cerr << "L'argument de la fonction ' " << fonction->FonctionName << " est inexistant." << std::endl;
                                            exit(1);
                                        }
                                    } else {
                                        std::cerr << "La variable n'existe pas." << std::endl;
                                        exit(1);
                                    }
                                } else {
                                    std::cerr << "Vous devez mettre le symbole ';' pour mettre fin a l'instruction." << std::endl;
                                    exit(1);
                                }
                            }
                            std::cerr << "Veuillez preciser la nouvelle valeur de la variable." << std::endl;
                            exit(1);
                        }
                    } else {
                        std::cerr << "Vous devez utiliser les symboles '->' pour donner une valeur a la variable." << std::endl;
                        exit(1);
                    }
                } else {
                    std::cerr << "Vous devez utiliser les symboles '->' pour donner une valeur a la variable." << std::endl;
                    exit(1);
                }
            } else {
                std::cerr << "Cette variable n'existe pas." << std::endl;
                exit(1);
            }
        } else {
            std::cerr << "Vous devez spécifier le nom de votre variable." << std::endl;
            exit(1);
        }
        return false;
    }

    bool Parser::PrintInstruction(auto parseStart, std::optional<FonctionDefinition>& fonction) {
        auto Value = CheckerValue();
        if (Value.has_value()) {
            --mCurrentToken;
            while (!CheckerOperateur(";").has_value()) {
                Value = CheckerValue();
                if (Value.has_value()) {
                    if (Value->StatementType.mType == STRING) {
                        std::replace(Value->StatementName.begin(), Value->StatementName.end(), '"', ' ');
                    }

                    std::cout << Value->StatementName;
                    std::cout << " ";
                }
                else if (CheckerOperateur("[").has_value()) {
                    auto var = CheckerIdentifiant();
                    if (isVariable(var->mText)) {
                        if (CheckerOperateur("]").has_value()) {
                            auto finalMsg = mVariables[var->mText].VariableValue;
                            if (mVariables[var->mText].VariableType.mType == STRING) {
                                std::replace(finalMsg.begin(), finalMsg.end(), '"', ' ');
                            }
                            std::cout << finalMsg;
                        } else{
                            std::cerr << "Ces operateurs sont utilises dans cette instruction pour introduire une variable, merci de cloturer l'insertion avec ']'." << std::endl;
                            exit(1);
                        }
                    } else if (isArgument(fonction->FonctionName, var->mText)) {
                        if (CheckerOperateur("]").has_value()) {
                            auto finalMsg = mArguments[fonction->FonctionName][var->mText].ArgValue;
                            if (mArguments[fonction->FonctionName][var->mText].ArgType.mType == STRING) {
                                std::replace(finalMsg.begin(), finalMsg.end(), '"', ' ');
                            }
                            std::cout << finalMsg;
                        } else{
                            std::cerr << "Ces operateurs sont utilises dans cette instruction pour introduire une variable, merci de cloturer l'insertion avec ']'." << std::endl;
                            exit(1);
                        }
                    }
                } else {
                    std::cerr << "Vous devez mettre le symbole ';' pour mettre fin a l'instruction." << std::endl;
                    exit(1);
                }

                if (CheckerOperateur(";").has_value()) {
                    break;
                }
            }
            std::cout << std::endl;
            return true;
        } else {
            mCurrentToken = parseStart;
            ++mCurrentToken;
            auto value = CheckerIdentifiant();
            if (value.has_value()) {
                if (CheckerOperateur(";").has_value()) {
                    if (isVariable(value->mText)) {
                        std::cout << mVariables[value->mText].VariableValue << std::endl;
                        return true;
                    } else if (fonction != std::nullopt) {
                        if (isArgument(fonction->FonctionName, value->mText)) {
                            std::cout << mArguments[fonction->FonctionName][value->mText].ArgValue << std::endl;
                            return true;
                        }
                    }
                    std::cerr << "Vous devez specifier une argument d'une fonction ou une variable." << std::endl;
                    exit(1);
                } else {
                    std::cerr << "Vous devez mettre le symbole ';' pour mettre fin a l'instruction." << std::endl;
                }
            }
            std::cerr << "Vous devez ouvrir les guillemets pour transmettre une chaine de caracteres ou le nom de votre variable sous ce format : 'envoyer [variable];'." << std::endl;
        }
        return false;
    }

    bool Parser::ManagerInstruction(std::optional<FonctionDefinition>& fonction) {
        auto parseStart = mCurrentToken; // std::vector<Token>::iterator
        auto PeutEtreInstruction = CheckerIdentifiant();
        if (PeutEtreInstruction.has_value()) {
            if (PeutEtreInstruction->mText == "envoyer") {
                if (PrintInstruction(parseStart, fonction)) { return true; } else { return false; }
            } else if (PeutEtreInstruction->mText == "variable") {
                if (VariableInstruction(fonction)) { return true; } else { return false; }
            } else if (PeutEtreInstruction->mText == "changer") {
                if (ChangerInstruction(fonction)) { return true; } else { return false; }
            } else if (PeutEtreInstruction->mText == "definir") {
                if (FonctionInstruction(parseStart)) {return true;} else {return false;}
            } else if (PeutEtreInstruction->mText == "appeler") {
               if (AppelerInstruction()) { return true; } else {return false;}
            } else if (PeutEtreInstruction->mText == "saisir") {
                if (SaisirInstruction(fonction)) { return true; } else { return false; }
            }
            else {
                mCurrentToken = parseStart;
            }
        }
        return false;
    }



    void Parser::parse(std::vector<Token> &tokens, std::optional<FonctionDefinition>& fonction) {
        mEndToken = tokens.end();
        mCurrentToken = tokens.begin();

        while (mCurrentToken != mEndToken) { // Tant que tout le fichier n'est pas parcouru et qu'on n'a pas analysé tous les éléments.
            if (ManagerInstruction(fonction)) {

            } else {
                if (mCurrentToken->mText.empty() || mCurrentToken->mType == ESPACEVIDE ) {
                    continue;
                }

                std::cerr << "Identifier inconnu : " << mCurrentToken->mText << " : " << mCurrentToken->mLineNumber << std::endl;
                ++mCurrentToken;
            }
        }
    }

    std::optional<Token> Parser::CheckerIdentifiant(std::string_view name) {
        if (mCurrentToken == mEndToken) { return std::nullopt; }
        if (mCurrentToken->mType != IDENTIFIANT) { return std::nullopt; }
        if (!name.empty() && mCurrentToken->mText != name) { return std::nullopt; }

        auto returnToken = mCurrentToken;
        ++mCurrentToken;
        return *returnToken;
    }

    std::optional<Token> Parser::CheckerOperateur(std::string_view name) {
        if (mCurrentToken == mEndToken) { return std::nullopt; }
        if (mCurrentToken->mType != OPERATEUR) { return std::nullopt; }
        if (mCurrentToken->mText != name && !name.empty()) { return std::nullopt; }
        // On vérifie s'il est présent, si c'est un OPERATEUR et que c'est le bon nom.

        auto returnToken = mCurrentToken; // std::vector<Token>::iterator
        ++mCurrentToken;
        return *returnToken; // On donne l'opérateur
    }

    std::optional<Type> Parser::CheckerType() {
        auto possibleType = CheckerIdentifiant();
        if (!possibleType.has_value()) { return std::nullopt; }

        auto foundType = mTypes.find(possibleType->mText);
        if (foundType == mTypes.end()) {
            --mCurrentToken;
            return std::nullopt;
        }

        return foundType->second;
    }

    std::optional<Statement> Parser::CheckerValue()
    {
        std::optional<Statement> res;
        if (mCurrentToken->mType == DECIMAL_LITERAL)
        {
            Statement doubleLitteralStatement (StatementKind::LITTERAL, mCurrentToken->mText, Type("decimal", DOUBLE));
            res = doubleLitteralStatement;
        }
        else if (mCurrentToken->mType == ENTIER_LITERAL)
        {
            Statement integerLitteralStatement(StatementKind::LITTERAL, mCurrentToken->mText, Type("entier", INT));
            res = integerLitteralStatement;
        }
        else if (mCurrentToken->mType == CHAINE_LITERAL)
        {
            Statement stringLitteralStatement(StatementKind::LITTERAL, mCurrentToken->mText, Type("text", STRING));
            res = stringLitteralStatement;

        } else {
            return std::nullopt;
        }

        ++mCurrentToken;
        return res;
    }

    bool Parser::isVariable(std::string &name) const {
        if (mVariables.contains(name)) { return true; }
        return false;
    }

    bool Parser::isFonction( std::string &name) const {
        if (mFonctions.contains(name)) { return true; }
        return false;
    }

    bool Parser::isArgument(std::string& fonction, std::string &name) const {
        const auto it = mArguments.find(fonction);
        if (it != mArguments.end())
        {
            return it->second.contains(name);
        }
        return false;
    }

    bool Parser::isFonctionArgument(std::string &fonction, std::string &argument) {
        if (isFonction(fonction)) {
            FonctionDefinition f = mFonctions[fonction];
            if (f.HasArgument) {
                for (auto const& a : f.ArgsFonction) {
                    if (a.ArgName == argument) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    std::optional<FonctionDefinition> Parser::getFonction(std::string& fonction) {
        if (isFonction(fonction)) {
            return mFonctions[fonction];
        }
        return std::nullopt;
    }

    std::optional<ArgumentDefinition> Parser::getArgument(std::string &fonction, std::string &name) {
        if (isFonctionArgument(fonction, name)) {
            auto f = getFonction(fonction);
            for (auto const &arg : f->ArgsFonction) {
                if (arg.ArgName == name) {
                    return arg;
                }
            }
        }
        return std::nullopt;
    }

    [[maybe_unused]] void Parser::DebugPrint() const {
        for (auto &funcPair: mFonctions) {
            for (auto &e: funcPair.second.FonctionContent) {
                std::cout << e << std::endl;
            }
        }
    }
}