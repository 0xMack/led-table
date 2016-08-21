#ifndef TABLEOUT_H
#define TABLEOUT_H
#include <string>
class tableout
{
    int ledNum;
    public:
        tableout();
        void shift(int,int);
        void setDefaultShift();
        void pwmRHi();
        void pwmGHi();
        void pwmBHi();
        void pwmRLo();
        void pwmGLo();
        void pwmBLo();
    protected:
    private:
};

#endif // TABLEOUT_H
