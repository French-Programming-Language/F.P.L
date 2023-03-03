#include "Fonction.h"

namespace FPL {
    bool FonctionDef::isArgument(std::string const& argument) {
        if (this->AllFonctionArguments.contains(argument)) { return true; }
        return false;
    }

    std::optional<FonctionArgumentDef> FonctionDef::getArgument(const std::string &argument) {
        if (this->isArgument(argument)) {
            return this->AllFonctionArguments[argument];
        }
        return std::nullopt;
    }

    void FonctionDef::updateValueOfArgument(FonctionArgumentDef argument, std::string_view value) {
        this->AllFonctionArguments[argument.ArgumentName].ArgumentValue = value;
    }

    std::ostream& operator<<(std::ostream &flux, FPL::FonctionDef const& f) {
        flux << "Nom de la fonction: " << f.FonctionName << ", type: " << f.FonctionType.Name << ", args: " << f.FonctionNumberArgument;
        return flux;
    }

    std::ostream& operator<<(std::ostream &flux, FPL::FonctionArgumentDef const& f) {
        flux << "Nom de l'argument: " << f.ArgumentName << ", type: " << f.ArgumentType.Name << ", value: " << f.ArgumentValue;
        return flux;
    }

    bool operator==(FonctionArgumentDef const& arg1, FonctionArgumentDef const& arg2) {
        return arg1.ArgumentName == arg2.ArgumentName;
    }

    bool operator==(const FonctionDef &v1, const FonctionDef &v2) {
        return v1.FonctionName == v2.FonctionName;
    }

    bool operator!=(const FonctionDef &v1, const FonctionDef &v2) {
        return v1.FonctionName != v2.FonctionName;
    }

    FonctionDef::FonctionDef(std::string name, Types::Types type, std::map<std::string, FonctionArgumentDef> allArgs,
                             std::vector<std::string> code, int nArgs, std::string returnV) {
        this->FonctionName = name;
        this->FonctionType = type;
        this->AllFonctionArguments = allArgs;
        this->FonctionContentCode = code;
        this->FonctionNumberArgument = nArgs;
        this->ReturnValue = returnV;
    }

    FonctionDef::FonctionDef() {}
}