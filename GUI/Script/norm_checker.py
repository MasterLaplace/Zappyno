#!/usr/bin/env python3
import os
import re

class CheckNorm:
    def __init__(self):
        self.nb_errors = 0

    def check_End_Of_File(self, file_name, content):
        """_summary_
        * The file must end with a new line
        * The EOF must be alone on its line
        """
        lines = content.split('\n')

        last_line = lines[-1]
        if last_line.strip() != '':
            raise AssertionError(f"Le fichier \"{file_name}\" ne se termine pas par une ligne vide.")


    def check_structure_name(self, file_name, content):
        """_summary_
        * All the structure names must start with a capital letter and end with _s
        """
        pattern = r'struct\s+(\w+)\s*{'
        incorrect_structures = []

        matches = re.findall(pattern, content)
        for struct_name in matches:
            if not struct_name[0].isupper() or not struct_name.endswith('_s'):
                incorrect_structures.append(struct_name)

        if incorrect_structures:
            print(f"Incorrect structure names found in file '{file_name}':")
            for struct_name in incorrect_structures:
                print(struct_name)
            raise AssertionError(f"Le fichier \"{file_name}\" contient des structures avec un nom incorrect")

    def check_namespace_name(self, file_name, content):
        """_summary_
        * All the namespace names must start with a capital letter
        """
        pattern = r'namespace\s+(\w+)\s*{'
        incorrect_namespaces = []

        matches = re.findall(pattern, content)
        for struct_name in matches:
            if not struct_name[0].isupper():
                incorrect_namespaces.append(struct_name)

        if incorrect_namespaces:
            print(f"Incorrect namespace names found in file '{file_name}':")
            for struct_name in incorrect_namespaces:
                print(struct_name)
            raise AssertionError(f"Le fichier \"{file_name}\" contient des namespaces avec un nom incorrect")

    def check_tab_size(self, file_name, content):
        """_summary_
        * All the lines must be indented with 4 spaces
        """
        lignes_incorrectes = []

        for i, ligne in enumerate(content.split('\n')):
            # Vérification si la ligne est une documentation Doxygen
            if ligne.strip().startswith('/**') or ligne.strip().startswith('*') or ligne.strip().startswith('*/'):
                continue

            # Vérification si la ligne contient des commentaires
            if ligne.strip().startswith('#') or ligne.strip().startswith('//'):
                continue

            # Vérification de l'indentation de la ligne
            indentation = len(ligne) - len(ligne.lstrip())
            if indentation % 4 != 0:
                lignes_incorrectes.append(i + 1)

        if lignes_incorrectes:
            raise AssertionError(f"Le fichier \"{file_name}\" contient des lignes avec une indentation incorrecte aux lignes:", lignes_incorrectes)

    def call_all_checks(self, file_name, content):
        self.check_tab_size(file_name, content)
        self.check_structure_name(file_name, content)
        self.check_namespace_name(file_name, content)
        self.check_End_Of_File(file_name, content)


DOSSIER_SRC = 'GUI/src/'
DOSSIER_INCLUDE = 'GUI/includes/'

def main():
    check_norm = CheckNorm()

    for repertoire, sous_repertoires, fichiers in os.walk(DOSSIER_SRC):
        for fichier in fichiers:
            chemin_fichier = os.path.join(repertoire, fichier)

            try:
                # On ne s'intéresse qu'aux fichiers C++
                if chemin_fichier.endswith('.cpp'):
                    if fichier != 'main.cpp' and not fichier[0].isupper() or fichier[0].isdigit():
                        raise AssertionError("The name of the file \"" + chemin_fichier + "\" does not start with a capital letter")
                    with open(chemin_fichier, 'r', encoding='latin-1') as f:
                        contenu = f.read()
                        check_norm.call_all_checks(chemin_fichier, contenu)
                elif chemin_fichier.endswith('.h') or chemin_fichier.endswith('.hpp'):
                    raise AssertionError("Header file detected in src: " + chemin_fichier)
            except AssertionError as e:
                check_norm.nb_errors += 1
                print(e)


    for repertoire, sous_repertoires, fichiers in os.walk(DOSSIER_INCLUDE):
        for fichier in fichiers:
            chemin_fichier = os.path.join(repertoire, fichier)

            try:
                # On ne s'intéresse qu'aux fichiers Header C++
                if chemin_fichier.endswith('.hpp'):
                    if not fichier[0].isupper() or fichier[0].isdigit():
                        raise AssertionError("The name of the file \"" + chemin_fichier + "\" does not start with a capital letter")
                    with open(chemin_fichier, 'r', encoding='latin-1') as f:
                        contenu = f.read()
                        check_norm.call_all_checks(chemin_fichier, contenu)
                elif chemin_fichier.endswith('.c') or chemin_fichier.endswith('.cpp'):
                    raise AssertionError("C/C++ file detected in include(s): " + chemin_fichier)
            except AssertionError as e:
                check_norm.nb_errors += 1
                print(e)

    if check_norm.nb_errors > 0:
        raise AssertionError(f"\033[1;31mIl y a {check_norm.nb_errors} erreur(s) dans le code source\033[0m")
    else:
        print("\033[1;32m► Le code source est conforme aux normes de codage C++ !\033[0m")

if __name__ == '__main__':
    main()
