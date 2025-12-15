#include <iostream>
#include "Definitions.hpp"
#include "Parser.hpp"
#include "Interpreter.hpp"


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
    {TokenType::WORD, "WORD"}
};

std::unordered_map<NonTerm, std::string> nt_desc 
{
    {NonTerm::ACTION_STR, "action-str"},
    {NonTerm::CMD, "cmd"},
    {NonTerm::COND, "cond"},
    {NonTerm::FOR_EXPR, "for"},
    {NonTerm::INIT, "init"},
    {NonTerm::OPERAND, "operand"},
    {NonTerm::STAT, "stat"},
};

void print_tree(const std::unique_ptr<ParseNode> &p, int depth=0)
{
    auto align = std::string(depth, ' ');
    if (p->tok.index() == 0)  // NonTerm 
    {
        std::cout << align << nt_desc[std::get<0>(p->tok)] << std::endl;
        for (const auto &i: p->childs)
        {
            print_tree(i, depth+4);
        }
    }
    else  // Term
    {
        const auto& token = std::get<1>(p->tok);
        std::cout << align << desc[token.first] << " " << token.second << std::endl;
    }
}

int main(int argc, char **argv)
{
    if (argc > 2)
    {
        if (std::string(argv[1]) == "--help")
        {
            std::cout << "tranlator - простой транслятор for-выражений" << std::endl;
            std::cout << "При вызове без аргументов читает стандартный вывод" << std::endl;
            std::cout << "При вызове с аргументом, транслятор читает код из файла" << std::endl;

        }
    }

    Parser parser;
    Interpreter interpreter;
    auto i = parser.parse();
    i = interpreter.shrink(std::move(i));
    interpreter.addSymbols(i);
    interpreter.execute(i); 
}
