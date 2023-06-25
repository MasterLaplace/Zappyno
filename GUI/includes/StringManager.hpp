/*
** EPITECH PROJECT, 2023
** B-YEP-400-REN-4-1-zappy
** File description:
** StringManager
*/

#ifndef STRINGMANAGER_HPP_
    #define STRINGMANAGER_HPP_
    #include <vector>
    #include <string>

namespace String {
    std::vector<std::string> string_to_string_vector(const std::string &str_to_cut, const std::string &delimiters);
    bool compareStringsIgnoreCase(const std::string &str1, const std::string &str2);
    std::vector<unsigned> find_two_substrings_occurs(const std::string &str, const std::string &target1, const std::string &target2);
} // namespace String

#endif /* !STRINGMANAGER_HPP_ */
