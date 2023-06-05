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
} // namespace String
