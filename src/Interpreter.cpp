#include "Interpreter.hpp"
#include "Definitions.hpp"
#include <algorithm>
#include <stdexcept>

template<typename T>
void erase_idx(std::vector<T> &arr, std::size_t s)
{
    if (arr.size() > s)
    {
        auto it = arr.begin() + s;
        arr.erase(it);
    }
}

std::unique_ptr<ParseNode> Interpreter::shrink(std::unique_ptr<ParseNode> tree)
{
    auto shrink_for = [](std::unique_ptr<ParseNode> for_expr){
        auto begin = for_expr->childs.begin();
        auto end = for_expr->childs.end();
        auto is_term = [](const std::unique_ptr<ParseNode>& ch)
        {
            return ch->tok.index() == 1; // is terminal
        };

        for_expr->childs.erase(std::remove_if(begin, end, is_term), end);
        erase_idx(
            for_expr->childs[0]->childs, 1); // remove ASSIGN_OP if it's there
        return for_expr;
    };

    auto get_name_from_cmd = [](std::unique_ptr<ParseNode> cmd)
    {
        if (cmd->tok.index() != 0
            && std::get<NonTerm>(cmd->tok) != NonTerm::CMD)
        {
            throw std::runtime_error("bad usage of get_name_from_cmd");
        }

        auto out = std::move(cmd->childs[3]);
        cmd->childs.clear();
        return out;
    };

    tree->childs[0] = shrink_for(std::move(tree->childs[0]));     
    if (std::get<NonTerm>(tree->childs[1]->tok) == NonTerm::STAT)
    {
        tree->childs[1] = shrink(std::move(tree->childs[1])); 
    }
    else // this is cmd
    {
        erase_idx(tree->childs, 2); // remove semicolon
        tree->childs[1] = get_name_from_cmd(std::move(tree->childs[1]));
    }

    return tree;
}

void Interpreter::addSymbols(const std::unique_ptr<ParseNode> &tree) 
{
    static int scope = 0; 
    static int ind = 0;

    // stat -> for -> init
    const auto& init = tree->childs[0]->childs[0];

    if (init->childs.size() > 0)
    {
        auto a = std::get<Token>(init->childs[0]->tok);
        auto b = std::get<Token>(init->childs[1]->tok);
        symbolTable[a.second].ind = ind++;
        symbolTable[a.second].scope = scope++;
        symbolTable[a.second].init = b;
        _memory.push_back(0);
    }

    if (tree->childs[1]->tok.index() == 0) // i. e. == NonTerm::STAT
    {
        addSymbols(tree->childs[1]);
    }
    else // == NonTerm::CMD
    {
        _word = std::get<Token>(tree->childs[1]->tok).second;
    }
}

void Interpreter::execute(const std::unique_ptr<ParseNode>& ast)
{
    // Заполняем таблицу символов
       
}
