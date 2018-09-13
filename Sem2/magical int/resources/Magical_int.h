#define OPER_EQU(arg_)\
void    operator arg_ (const mint & arg);\
void    operator arg_ (const int & arg);

#define OPER(arg_)\
mint    operator arg_ (const mint & arg);\
mint    operator arg_ (const int & arg);

#define OPER_COMPAR(arg_)\
bool    operator arg_ (const mint & arg);\
bool    operator arg_ (const int & arg);



#define DETERM_OPER(arg_, cod1, cod2)\
mint mint::operator arg_ (const mint & arg) {\
    if (limit_oper > check_oper) {\
        printf("Limit exceeded");\
        assert(0);\
    } else\
        limit_oper++;\
    mint b;\
    cod1 {\
        b.data = data arg_ arg.data;\
    }\
    return b;\
}\
mint mint::operator arg_ (const int & arg) {\
    if (limit_oper > check_oper) {\
        printf("Limit exceeded");\
        assert(0);\
    } else\
        limit_oper++;\
    mint b;\
    cod2 {\
        b.data = data arg_ arg;\
    }\
    return b;\
}\



#define DETERM_OPER_EQU(arg_, cod1, cod2)\
void mint::operator arg_ (const mint & arg) {\
    if ((limit_oper > check_oper) || (limit_equ > check_equ)) {\
        printf("Limit exceeded");\
        assert(0);\
    } else {\
        limit_oper++;\
        limit_equ++;\
    }\
    cod1 {\
        data arg_ arg.data;\
    }\
}\
void mint::operator arg_ (const int & arg) {\
    if ((limit_oper > check_oper) || (limit_equ > check_equ)) {\
        printf("Limit exceeded");\
        assert(0);\
    } else {\
        limit_oper++;\
        limit_equ++;\
    }\
    cod2 {\
        data arg_ arg;\
    }\
}



#define DETERM_COMPAR(arg_, cod1, cod2)\
bool mint::operator arg_ (const mint & arg) {\
    if (limit_compar > check_compar) {\
        printf("Limit exceeded");\
        assert(0);\
    } else\
        limit_compar++;\
    cod1 {\
        \
        return (data arg_ arg.data);\
    }\
}\
bool mint::operator arg_ (const int & arg) {\
    if (limit_compar > check_compar) {\
        printf("Limit exceeded");\
        assert(0);\
    } else\
        limit_compar++;\
    cod2 {\
        return (data arg_ arg);\
    }\
}



class mint
{
private:
    void    swap (mint arg);
    
    int     check_oper = 7;
    int     check_compar = 5;
    int     check_equ = 5;
    
    int     limit_oper;
    int     limit_compar;
    int     limit_equ;
    
public:
    int  data;
    
    mint ();
    mint (int arg);
    
    mint&   operator = (const mint & arg);
    mint&   operator = (const int & arg);
    OPER_EQU(+=)
    OPER_EQU(-=)
    OPER_EQU(*=)
    OPER_EQU(/=)
    OPER_EQU(%=)
    
    OPER_COMPAR(==)
    OPER_COMPAR(>=)
    OPER_COMPAR(<=)
    OPER_COMPAR(!=)
    OPER_COMPAR(<)
    OPER_COMPAR(>)
    
    OPER(+)
    OPER(-)
    OPER(*)
    OPER(/)
    OPER(%)
};


mint:: mint (): data (0), limit_oper (0), limit_compar (0), limit_equ (0) {}
mint:: mint (int arg): data (arg), limit_oper (0), limit_compar (0), limit_equ (1)  {limit_equ = 1;}


void mint:: swap (mint arg)
{
    std::swap(data, arg.data);
}


mint& mint::operator = (const mint & arg) {
    if (limit_equ > check_equ) {
        printf("Limit exceeded");
        assert(0);
    } else
        limit_equ++;
    this->swap(arg);
    return *this;
}


mint& mint::operator = (const int & arg1) {
    if (limit_equ > check_equ) {
        printf("Limit exceeded");
        assert(0);
    } else
        limit_equ++;
    data = arg1;
    return *this;
}



DETERM_OPER(*,
            if ((data == 2) && (arg.data == 2)) {
                b = 5;
            } else,
            if ((data == 2) && (arg == 2)) {
                b = 5;
            } else)

DETERM_OPER(+,
            if ((data == 2) && (arg.data == 2)) {
                b = 5;
            } else
                if (arg.data < 0) {
                    printf("You can subtract 1");
                    assert(0);
                } else ,
            if ((data == 2) && (arg == 2)) {
                b = 5;
            } else
                if (arg < 0) {
                    printf("You can subtract 1");
                    assert(0);
                } else )

DETERM_OPER(/,
            if ((data != 0) && (arg.data == 0)) {
                b = 5;
            } else,
            if ((data != 0) && (arg == 0)) {
                b = 5;
            } else)

DETERM_OPER(-,
            if (arg.data == 1) {
                data--;
            } else
                if (arg.data != 1) {
                    printf("You can subtract 1");
                    assert(0);
                } else
                    if (false),
            if (arg == 1) {
                data--;
            } else
                if (arg != 1) {
                    printf("You can subtract 1");
                    assert(0);
                } else
                    if (false))

DETERM_OPER(%,,)



DETERM_OPER_EQU(+=,
                if ((data == 2) && (arg.data == 2)) {
                    data = 5;
                } else
                    if (arg.data < 0) {
                        printf("You can subtract 1");
                        assert(0);
                    } else ,
                if ((data == 2) && (arg == 2)) {
                    data = 5;
                } else
                    if (arg < 0) {
                        printf("You can subtract 1");
                        assert(0);
                    } else )

DETERM_OPER_EQU(-=,,)

DETERM_OPER_EQU(*=,
                if ((data == 2) && (arg.data == 2)) {
                    data = 5;
                } else,
                if ((data == 2) && (arg == 2)) {
                    data = 5;
                } else)

DETERM_OPER_EQU(/=,,)

DETERM_OPER_EQU(%=,,)



DETERM_COMPAR(==,
              if (((data == 0) && (arg.data == 1)) || ((data == 1) && (arg.data == 0))) {
                  return true;
              } else,
              if (((data == 0) && (arg == 1)) || ((data == 1) && (arg == 0))) {
                  return true;
              } else)

DETERM_COMPAR(>=,,)

DETERM_COMPAR(<=,,)

DETERM_COMPAR(!=,,)

DETERM_COMPAR(>,,)

DETERM_COMPAR(<,,)



#undef OPER_EQU
#undef OPER
#undef OPER_COMPAR
#undef DETERM_OPER
#undef DETERM_OPER_EQU
#undef DETERM_COMPAR
