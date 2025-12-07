#include <iostream>
#include "Definitions.hpp"
#include "Scanner.hpp"


std::unordered_map<TokenType, std::string> desc
{
    {TokenType::ASSIGN_OP, "ASSIGN_OP"},
    {TokenType::COMP, "COMP"},
    {TokenType::END, "END"},
    {TokenType::For, "For"},
    {TokenType::LPAR, "LPAR"},
    {TokenType::NAME, "NAME"},
    {TokenType::NUM, "NUM"},
    {TokenType::Print, "Print"},
    {TokenType::QUOTE, "QUOTE"},
    {TokenType::RPAR, "RPAR"},
    {TokenType::SEMICOL, "SEMICOL"},
    {TokenType::UNARY_OP, "UNARY_OP"},
    {TokenType::UNDEF, "UNDEF"},
    {TokenType::WORD, "WORD"}
};

int main()
{
    std::cout << std::to_string('4') << std::endl;
    Scanner s;

    for (auto t = s.next(); t.first != TokenType::END; t = s.next())
    {
        std::cout << desc[t.first] << " " << t.second << std::endl;
    }
}
