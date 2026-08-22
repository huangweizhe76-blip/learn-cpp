#include <stdio.h>
#include <stdlib.h>

/* ========== 选择要运行的演示 1/2/3/4 ========== */
#define DEMO_SELECT  4

#if DEMO_SELECT == 1
//====================
// demo1: enum_basic_weekday (原 test1.c)
// 原生enum，无typedef，星期枚举
//====================
enum weekday
{
    mon = 1,
    tue,
    wed,
    thu,
    fri,
    sat,
    sun
};

int demo1(void)
{
    enum weekday a = mon;
    enum weekday b = tue;

    printf("demo1 enum_basic_weekday:\n");
    printf("%d\n", a);
    printf("%d\n", b);
    return 0;
}

#elif DEMO_SELECT == 2
//====================
// demo2: enum_typedef_bool (原 test2.c)
// typedef枚举起别名，自定义模拟bool
//====================
typedef enum
{
    mon = 1,
    tue,
    wed,
    thu,
    fri,
    sat,
    sun
} weekday;

typedef enum
{
    false,
    true
} bool;

int demo2(void)
{
    weekday a = mon;
    printf("demo2 enum_typedef_bool:\n");
    printf("%d\n", a);

    bool flag = true;
    if (flag)
    {
        printf("真的\n");
    }
    return 0;
}

#elif DEMO_SELECT == 3
//====================
// demo3: stack_postfix_eval (原 test3.c)
// 动态顺序栈，后缀（逆波兰）表达式求值
//====================
#define MAXSIZE 100
typedef int ElemType;

typedef struct
{
    ElemType* data;
    int top;
} Stack;

typedef enum
{
    LEFT_PARE,
    RIGHT_PARE,
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    EOS,
    NUM
} contentType;

static char expr_postfix[] = "82/2+56*-";

Stack* initStack(void)
{
    Stack* s = (Stack*)malloc(sizeof(Stack));
    if (s == NULL)
        return NULL;
    s->data = (ElemType*)malloc(sizeof(ElemType) * MAXSIZE);
    if (s->data == NULL)
    {
        free(s);
        return NULL;
    }
    s->top = -1;
    return s;
}

void destroyStack(Stack* s)
{
    if (s != NULL)
    {
        free(s->data);
        free(s);
    }
}

int isEmpty(Stack* s)
{
    return s->top == -1 ? 1 : 0;
}

int push(Stack* s, ElemType e)
{
    if (s->top >= MAXSIZE - 1)
        return 0;
    s->top++;
    s->data[s->top] = e;
    return 1;
}

int pop(Stack* s, ElemType* e)
{
    if (isEmpty(s))
        return 0;
    *e = s->data[s->top];
    s->top--;
    return 1;
}

int getTop(Stack* s, ElemType* e)
{
    if (isEmpty(s))
        return 0;
    *e = s->data[s->top];
    return 1;
}

static contentType getToken_postfix(char* symbol, int* index)
{
    *symbol = expr_postfix[*index];
    *index = *index + 1;
    switch (*symbol)
    {
    case '(': return LEFT_PARE;
    case ')': return RIGHT_PARE;
    case '+': return ADD;
    case '-': return SUB;
    case '*': return MUL;
    case '/': return DIV;
    case '%': return MOD;
    case '\0': return EOS;
    default: return NUM;
    }
}

int eval(Stack* s, ElemType* res)
{
    char symbol;
    int op1, op2;
    int index = 0;
    contentType token;
    token = getToken_postfix(&symbol, &index);

    while (token != EOS)
    {
        if (token == NUM)
        {
            if (!push(s, symbol - '0'))
                return 0;
        }
        else
        {
            if (!pop(s, &op2) || !pop(s, &op1))
                return 0;
            switch (token)
            {
            case ADD: push(s, op1 + op2); break;
            case SUB: push(s, op1 - op2); break;
            case MUL: push(s, op1 * op2); break;
            case DIV:
                if (op2 == 0) return 0;
                push(s, op1 / op2);
                break;
            case MOD:
                if (op2 == 0) return 0;
                push(s, op1 % op2);
                break;
            default: break;
            }
        }
        token = getToken_postfix(&symbol, &index);
    }
    if (!pop(s, res))
        return 0;
    return 1;
}

int demo3(void)
{
    printf("demo3 stack_postfix_eval 后缀表达式求值:\n");
    Stack* s = initStack();
    if (s == NULL)
    {
        printf("栈初始化失败\n");
        return -1;
    }
    ElemType ret;
    if (eval(s, &ret))
    {
        printf("result = %d\n", ret);
    }
    else
    {
        printf("表达式计算出错\n");
    }
    destroyStack(s);
    return 0;
}

#elif DEMO_SELECT == 4
//====================
// demo4: stack_infix_to_postfix (原 test4.c)
// 调度场算法：中缀表达式转后缀表达式
//====================
#define MAXSIZE 100
typedef int ElemType;

typedef struct
{
    ElemType* data;
    int top;
} Stack;

typedef enum
{
    LEFT_PARE,
    RIGHT_PARE,
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    EOS,
    NUM
} contentType;

static char expr_infix[] = "x/(i-j)*y";

Stack* initStack(void)
{
    Stack* s = (Stack*)malloc(sizeof(Stack));
    if (s == NULL) return NULL;
    s->data = (ElemType*)malloc(sizeof(ElemType) * MAXSIZE);
    if (s->data == NULL)
    {
        free(s);
        return NULL;
    }
    s->top = -1;
    return s;
}

void destroyStack(Stack* s)
{
    if (s != NULL)
    {
        free(s->data);
        free(s);
    }
}

int isEmpty(Stack* s)
{
    return s->top == -1 ? 1 : 0;
}

int push(Stack* s, ElemType e)
{
    if (s->top >= MAXSIZE - 1) return 0;
    s->top++;
    s->data[s->top] = e;
    return 1;
}

int pop(Stack* s, ElemType* e)
{
    if (isEmpty(s)) return 0;
    *e = s->data[s->top];
    s->top--;
    return 1;
}

int getTop(Stack* s, ElemType* e)
{
    if (isEmpty(s)) return 0;
    *e = s->data[s->top];
    return 1;
}

static contentType getToken_infix(char* symbol, int* index)
{
    *symbol = expr_infix[*index];
    *index = *index + 1;
    switch (*symbol)
    {
    case '(': return LEFT_PARE;
    case ')': return RIGHT_PARE;
    case '+': return ADD;
    case '-': return SUB;
    case '*': return MUL;
    case '/': return DIV;
    case '%': return MOD;
    case '\0': return EOS;
    default: return NUM;
    }
}

static void print_token(contentType token)
{
    switch (token)
    {
    case ADD: printf("+"); break;
    case SUB: printf("-"); break;
    case MUL: printf("*"); break;
    case DIV: printf("/"); break;
    case MOD: printf("%%"); break;
    default: break;
    }
}

int postfixConvert(Stack* s)
{
    int in_stack[] = { 0, 19, 12, 12, 13, 13, 13, 0 };
    int out_stack[] = { 20, 19, 12, 12, 13, 13, 13, 0 };
    contentType token;
    int index = 0;
    s->top = 0;
    s->data[0] = EOS;
    char symbol;
    ElemType e;

    token = getToken_infix(&symbol, &index);
    while (token != EOS)
    {
        if (token == NUM)
        {
            printf("%c", symbol);
        }
        else if (token == RIGHT_PARE)
        {
            while (s->data[s->top] != LEFT_PARE)
            {
                if (!pop(s, &e)) return 0;
                print_token(e);
            }
            if (!pop(s, &e)) return 0;
        }
        else
        {
            while (in_stack[s->data[s->top]] >= out_stack[token])
            {
                if (!pop(s, &e)) return 0;
                print_token(e);
            }
            if (!push(s, token)) return 0;
        }
        token = getToken_infix(&symbol, &index);
    }
    if (!pop(s, &e)) return 0;
    token = e;
    while (token != EOS)
    {
        print_token(token);
        if (!pop(s, &e)) return 0;
        token = e;
    }
    printf("\n");
    return 1;
}

int demo4(void)
{
    printf("demo4 stack_infix_to_postfix 中缀转后缀:\n");
    Stack* s = initStack();
    if (s == NULL)
    {
        printf("栈初始化失败\n");
        return -1;
    }
    printf("infix: %s\n", expr_infix);
    if (!postfixConvert(s))
    {
        printf("转换出错\n");
    }
    destroyStack(s);
    return 0;
}

#endif

int main(int argc, char const* argv[])
{
#if DEMO_SELECT == 1
    return demo1();
#elif DEMO_SELECT == 2
    return demo2();
#elif DEMO_SELECT == 3
    return demo3();
#elif DEMO_SELECT == 4
    return demo4();
#else
    printf("DEMO_SELECT 参数错误，请填1~4\n");
    return -1;
#endif
}