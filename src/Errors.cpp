#include "Errors.hpp"

LexicalError::LexicalError(std::string_view lexem) : _info("Wrong lexem: ")
{
    _info += lexem;
}

LexicalError::LexicalError(char lexem)
    : LexicalError(std::string(1, lexem))
{
}

const char* LexicalError::what() const noexcept
{
    return _info.c_str();
}
