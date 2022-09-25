#include <string>

//priority  operator    direction
//1         ( )
//2         !           a → b
//3         ^           a ← b
//4         s+ s-       a ← b       //正負符號
//5         * /         a → b
//6         + -         a → b

struct myOperator {
    myOperator(std::string _op, int _priority) //建構子
    {
        op = _op;
        priority = _priority;
    }

    std::string op;
    int priority;
};