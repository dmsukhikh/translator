#pragma once
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

/**
 * Виды токенов, используемых транслятором
 *
 * \note Для всех видов токенов стандартное написание в upper case, кроме тех
 * токенов, название которых совпадает с лексемой в коде. В таких случаях в
 * перечислении данный токен пишется строчными буквами с первой заглавной
 * буквой.
 */
enum class TokenType
{
    UNDEF=0, //!< Неопределенное состояние типа токена
    NAME, //!< Токен названия переменной
    WORD, //!< Токен слова, которое выводится командой print
    NUM, //!< Токен числа
    COMP, //!< Токен операции сравнения
    UNARY_OP, //!< Токен унарной операции
    For, //!< Слово "for"  +
    LPAR, //!< Символ "("  +
    RPAR, //!< Символ ")"   +
    QUOTE, //!< Символ """  +
    SEMICOL, //!< Символ ";"  +
    Print, //!< Слово "print"
    ASSIGN_OP, //!< Символ "="  +
    END, //!< Конец разбираемого предложения. Для данного вида токена нет
        //!< соответствующей лексемы в языке, используется при анализе
};

/**
 * Виды нетерминалов
 */
enum class NonTerm
{
    STAT,
    FOR_EXPR,
    INIT,
    COND,
    OPERAND,
    ACTION_STR,
    CMD
};

using Lexem = std::string; //!< Тип лексемы

/**
 * Тип, обозначающий токен
 *
 * Поля класса Token обозначают следующее:
 * - first - тип токена
 * - second - лексема. По этой лексеме можно найти информацию о токене в таблице
 * символов
 */
using Token = std::pair<TokenType, Lexem>;

/**
 * Значение токена в таблице символов
 */
struct Symbol
{
    TokenType type; //!< Тип символа
    std::optional<uint32_t>
        scope; //!< Область видимости переменной. Определена только для NAME
               //!< токенов. Число означает номер цикла в выражении
    std::optional<Token>
        init; //!< Токен, инициализирующий NAME. Определена только для NAME

    /**
     * Адрес символа во внутреннем представлении транслятора.
     *
     * Транслятор выделяет массив целых чисел, в котором хранятся значения
     * переменных и констант. ind - это индекс в этом массиве.
     */
    std::optional<std::size_t> ind;
};

/**
 * Тип таблицы символов
 */
using SymbolTable = std::unordered_map<Lexem, Symbol>;

/**
 * Таблица символов, используемая частями транслятора
 */
extern SymbolTable symbolTable;

/**
 * Простой узел дерева разбора
 */
struct ParseNode
{
    std::vector<std::unique_ptr<ParseNode>> childs;
    std::variant<NonTerm, Token> tok {};
};
