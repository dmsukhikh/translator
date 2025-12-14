#include "Errors.hpp"
#include "Definitions.hpp"
#include <memory>
#include <vector>

/**
 * Класс, объект которого исполняет код
 */
class Interpreter
{
    /**
     * Внутренняя память интерпретаторa
     */
    std::vector<uint64_t> _memory;

    /**
     * Слово, которое надо выводить
     */
    std::string _word;

public:
    /**
     * Обрезает данное дерево разбора, оставляя только необходимую для
     * семантического анализа информацию. Тем самым, получается AST
     *
     * <for-expr> преобразуется следующим образом:
     * ```
     * for
     *  init
     *      NAME i
     *      NUM 0
     *  cond
     *      operand
     *          NAME i
     *      COMP <
     *      operand
     *          NUM 3
     *  action-str
     *      UNARY_OP ++
     *      NAME i
     * ```
     *
     * <cmd> срезается до одного слова WORD, которое необходимо вывести
     */
    std::unique_ptr<ParseNode> shrink(std::unique_ptr<ParseNode> tree);


    void addSymbols(const std::unique_ptr<ParseNode> &tree);

    /**
     * Исполняет код, представленный в виде AST
     *
     * \warning переданное дерево должно пройти через процедуру
     * Interpreter::shrink
     */
    void execute(const std::unique_ptr<ParseNode>& ast);
};
