/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** StringManager
*/

#include "../../../includes/StringManager.hpp"

namespace String {
    /**
     * @brief Split a string into a vector of strings
     *
     * @param str_to_cut  The string to cut
     * @param delimiters  The delimiters
     * @return std::vector<std::string>  The vector of strings
     */
    std::vector<std::string> string_to_string_vector(const std::string &str_to_cut, const std::string &delimiters) {
        std::vector<std::string> words;
        std::string current_word;

        for (const char &c : str_to_cut) {
            if (delimiters.find(c) != std::string::npos) {
                if (!current_word.empty()) {
                    words.push_back(current_word);
                    current_word.clear();
                }
            } else {
                current_word += c;
            }
        }

        // Add the last word if it is not empty
        if (!current_word.empty()) {
            words.push_back(current_word);
        }

        return words;
    }

    /**
     * @brief Compare two strings ignoring the case of the letters
     *
     * @param str1  The first string
     * @param str2  The second string
     * @return true  If the strings are the same
     * @return false  If the strings are different
     */
    bool compareStringsIgnoreCase(const std::string &str1, const std::string &str2) {
        if (str1.length() != str2.length()) {
            return false;
        }

        for (size_t i = 0; i < str1.length(); ++i) {
            if (std::tolower(str1[i]) != std::tolower(str2[i])) {
                return false;
            }
        }
        return true;
    }

    /**
     * @brief Find the occurrences of two substrings in a string
     *
     * @param str  The string to search in
     * @param target1  The first substring
     * @param target2  The second substring
     * @return std::vector<unsigned>  The occurrences of the substrings
     * @example :
     * str: "FooBarFooBarFoo"
     * target1: "Foo"
     * target2: "Bar"
     * return: {3, 2}
     */
    std::vector<unsigned> find_two_substrings_occurs(const std::string &str, const std::string &target1, const std::string &target2) {
        std::string::size_type pos = 0;
        std::string::size_type pos1 = 0;
        std::string::size_type pos2 = 0;
        unsigned occurrences_1 = 0;
        unsigned occurrences_2 = 0;
        while ((pos1 = str.find(target1, pos )) != std::string::npos || (pos2 = str.find(target2, pos )) != std::string::npos) {
            if (pos1 != std::string::npos || pos1 < pos2) {
                occurrences_1++;
                pos = pos1 + target1.length();
            } else if (pos2 != std::string::npos || pos2 < pos1) {
                occurrences_2++;
                pos = pos2 + target2.length();
            }
        }
        return {occurrences_1, occurrences_2};
    }
} // namespace String
