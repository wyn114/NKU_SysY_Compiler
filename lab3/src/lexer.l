%option noyywrap
%option nounput
%option noinput
%top{
    #include <stdarg.h>
    #include "common.h"
}
%{
    extern dump_type_t dump_type;

    inline void dump_tokens(const char* format, ...){
        va_list args;
        va_start(args, format);
        if (dump_type == TOKENS)
            vfprintf(yyout, format, args);
        va_end(args);
    }

    /* Your code here, if desired (lab3). */
%}

/* definitions section */
/*十进制*/
DECIMIAL ([1-9][0-9]*|0)
/*八进制*/
OCTAL [0]([1-7][0-7]*|0)
/*十六进制*/
HEXADECIMAL (0[xX][0-9A-Fa-f]+)  
/*浮点数*/
FLOATING ((([0-9]*[.][0-9]*([eE][+-]?[0-9]+)?)|([0-9]+[eE][+-]?[0-9]+))[fLlL]?)
/*ID*/
ID [[:alpha:]_][[:alpha:][:digit:]_]*
/*回车，换行*/
EOL (\r\n|\n|\r)
/*空格*/
WHITE [\t ] 
/*  Your code here (lab3). */
/*块注释*/
COMMENTBEGIN "/*"
COMMENTELEMENT .|\n
COMMENTEND "*/" 
/*blockcomment起始状态*/
%x BLOCKCOMMENT  

/*行注释*/
IN_LINECOMMENT \/\/[^\n]*

%%
    /* rules section */
"int" {
    dump_tokens("INT\t%s\n", yytext);
}

"void" {
    dump_tokens("VOID\t%s\n", yytext);
}

"if" {
    dump_tokens("IF\t%s\n", yytext);
}

"else" {
    dump_tokens("ELSE\t%s\n", yytext);
}

"return" {
    dump_tokens("RETURN\t%s\n", yytext);
}

"=" {
    dump_tokens("ASSIGN\t%s\n", yytext);
}

"<" {
    dump_tokens("LESS\t%s\n", yytext);
}

"+" {
    dump_tokens("ADD\t%s\n", yytext);
}

";" {
    dump_tokens("SEMICOLON\t%s\n", yytext);
}

"(" {
    dump_tokens("LPAREN\t%s\n", yytext);
}

")" {
    dump_tokens("RPAREN\t%s\n", yytext);
}

"{" {
    dump_tokens("LBRACE\t%s\n", yytext);
}

"}" {
    dump_tokens("RBRACE\t%s\n", yytext);
}

{DECIMIAL} {
    int decimal; 
    decimal = atoi(yytext);
    dump_tokens("DECIMAL\t%s\t%d\n", yytext, decimal); 
}

{FLOATING} {
    float temp;
    sscanf(yytext, "%f", &temp);
    dump_tokens("FLOATING\t%s\t%d\n", yytext, temp); 
}

{HEXADECIMAL} {
    int num;
    sscanf(yytext, "%x", &num);  //将16进制转为10进制数
    dump_tokens("HEXADECIMAL\t%s\t%d\n", yytext, num); 
}

<*>{EOL} {              // EOL回车换行符
    yylineno++;
}

{WHITE} {}

{IN_LINECOMMENT} {}   //处理注释，使用定义好的独占状态BLOCKCOMMENT
{COMMENTBEGIN} {BEGIN BLOCKCOMMENT;}
<BLOCKCOMMENT>{COMMENTELEMENT} {} 
<BLOCKCOMMENT>{COMMENTEND} {BEGIN INITIAL;} //使用宏BEGIN来切换状态，初始状态默认为INITIAL

{ID} {
    dump_tokens("ID\t%s\n", yytext);
}

{EOL} yylineno++;

{WHITE}

    /*  Your code here (lab3). */
%%
/* user code section */
