#include <string>

//priority  operator    direction
//1         ( )
//2         !           a �� b
//3         ^           a �� b
//4         s+ s-       a �� b       //���t�Ÿ�
//5         * /         a �� b
//6         + -         a �� b

struct myOperator {
    myOperator(std::string _op, int _priority) //�غc�l
    {
        op = _op;
        priority = _priority;
    }

    std::string op;
    int priority;
};