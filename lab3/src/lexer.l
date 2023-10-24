%option noyywrap
%option nounput
%option noinput
%top{
    #include <stdarg.h>
    #include "common.h"
    #include "symbol_table.h"
}
%{
    extern dump_type_t dump_type;
    extern FILE *yyin;
    extern FILE *yyout;
    int yycolumnno = 1;

    symTable* symtable=new symTable();//符号表型的变量

    inline void dump_tokens(const char* format, ...){
        va_list args;
        va_start(args, format);
        int format_length = strlen(yytext);
        if (dump_type == TOKENS)
            vfprintf(yyout, format, args);
        va_end(args);
        yycolumnno += format_length;
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
    dump_tokens("INT     \t%-10s\t%d\t%d\t\t\n", yytext, yylineno, yycolumnno);
}

"main" {
    dump_tokens("MAIN    \t%-10s\t%d\t%d\t\t\n", yytext, yylineno, yycolumnno);
}

"float" {
    dump_tokens("FLOAT   \t%-10s\t%d\t%d\t\t\n", yytext, yylineno, yycolumnno);
}

"double" {
    dump_tokens("DOUBLE  \t%-10s\t%d\t%d\t\t\n", yytext, yylineno, yycolumnno);
}

"void" {
    dump_tokens("VOID    \t%-10s\t%d\t%d\t\t\n", yytext, yylineno, yycolumnno);
}

"if" {
    dump_tokens("IF      \t%-10s\t%d\t%d\t\t\n", yytext, yylineno, yycolumnno);
}

"else" {
    dump_tokens("ELSE    \t%-10s\t%d\t%d\t\t\n", yytext, yylineno, yycolumnno);
}

"while" {
    dump_tokens("WHILE   \t%-10s\t%d\t%d\t\t\n", yytext, yylineno, yycolumnno);
}

"break" {
    dump_tokens("BREAK   \t%-10s\t%d\t%d\t\t\n", yytext, yylineno, yycolumnno);
}

"continue" {
    dump_tokens("CONTINUE\t%-10s\t%d\t%d\t\t\n", yytext, yylineno, yycolumnno);
}

"return" {
    dump_tokens("RETURN  \t%-10s\t%d\t%d\t\t\n", yytext, yylineno, yycolumnno);
}

"==" {
    dump_tokens("EQUAL   \t%-10s\t%d\t%d\t\t\n", yytext, yylineno, yycolumnno);
}

"=" {
    dump_tokens("ASSIGN  \t%-10s\t%d\t%d\t\t\n", yytext, yylineno, yycolumnno);
}

"<=" {
    dump_tokens("LESSEQUAL\t%-10s\t%d\t%d\t\t\n", yytext, yylineno, yycolumnno);
}

">=" {
    dump_tokens("GREATEREQUAL\t%-10s\t%d\t%d\t\t\n", yytext, yylineno, yycolumnno);
}

"<" {
    dump_tokens("LESS    \t%-10s\t%d\t%d\t\t\n", yytext, yylineno, yycolumnno);
}

">" {
    dump_tokens("GREATER \t%-10s\t%d\t%d\t\t\n", yytext, yylineno, yycolumnno);
}

"+" {
    dump_tokens("ADD     \t%-10s\t%d\t%d\t\t\n", yytext, yylineno, yycolumnno);
}

"-" {
    dump_tokens("SUB     \t%-10s\t%d\t%d\t\t\n", yytext, yylineno, yycolumnno);
}

"*" {
    dump_tokens("MUL     \t%-10s\t%d\t%d\t\t\n", yytext, yylineno, yycolumnno);
}

"/" {
    dump_tokens("DIV     \t%-10s\t%d\t%d\t\t\n", yytext, yylineno, yycolumnno);
}

"%" {
    dump_tokens("MOD     \t%-10s\t%d\t%d\t\t\n", yytext, yylineno, yycolumnno);
}

"!" {
    dump_tokens("NOT     \t%-10s\t%d\t%d\t\t\n", yytext, yylineno, yycolumnno);
}

"||" {
    dump_tokens("OR      \t%-10s\t%d\t%d\t\t\n", yytext, yylineno, yycolumnno);
}

"&&" {
    dump_tokens("AND     \t%-10s\t%d\t%d\t\t\n", yytext, yylineno, yycolumnno);
}

";" {
    dump_tokens("SEMICOLON\t%-10s\t%d\t%d\t\t\n", yytext, yylineno, yycolumnno);
}

"(" {
    dump_tokens("LPAREN  \t%-10s\t%d\t%d\t\t\n", yytext, yylineno, yycolumnno);
}

")" {
    dump_tokens("RPAREN  \t%-10s\t%d\t%d\t\t\n", yytext, yylineno, yycolumnno);
}

"{" {
    dump_tokens("LBRACE  \t%-10s\t%d\t%d\t\t\n", yytext, yylineno, yycolumnno);
}

"}" {
    dump_tokens("RBRACE  \t%-10s\t%d\t%d\t\t\n", yytext, yylineno, yycolumnno);
}

"[" {
    dump_tokens("LBRACKET\t%-10s\t%d\t%d\t\t\n", yytext, yylineno, yycolumnno);
}

"]" {
    dump_tokens("RBRACKET\t%-10s\t%d\t%d\t\t\n", yytext, yylineno, yycolumnno);
}

"," {
    dump_tokens("COMMA   \t%-10s\t%d\t%d\t\t\n", yytext, yylineno, yycolumnno);
}

{FLOATING} {
    float temp;
    sscanf(yytext, "%f", &temp);
    dump_tokens("FLOAT   \t%-10s\t%d\t%d\t%f\t\n", yytext, yylineno, yycolumnno, temp);
}

{DECIMIAL} {
    int decimal; 
    decimal = atoi(yytext);
    dump_tokens("DECIMAL \t%-10s\t%d\t%d\t%f\t\n", yytext, yylineno, yycolumnno ,decimal);
}

{OCTAL} {
    int num;
    sscanf(yytext, "%o", &num);  //将8进制转为10进制数
    dump_tokens("OCTAL   \t%-10s\t%d\t%d\t%f\t\n", yytext, yylineno, yycolumnno ,num);
}


{HEXADECIMAL} {
    int num;
    sscanf(yytext, "%x", &num);  //将16进制转为10进制数
    dump_tokens("HEXADECIMAL\t%-10s\t%d\t%d\t%f\t\n", yytext, yylineno, yycolumnno ,num); 
}

<*>{EOL} {              // EOL回车换行符
    yylineno++;
    yycolumnno = 0;
}

{WHITE} {
    yycolumnno++;
}

{IN_LINECOMMENT} {}   //处理注释，使用定义好的独占状态BLOCKCOMMENT
{COMMENTBEGIN} {BEGIN BLOCKCOMMENT;}
<BLOCKCOMMENT>{COMMENTELEMENT} {
    if(*yytext=='\n'){
        yylineno++;
        offset++;
    }
    else{
        offset=0;
    }
} 
<BLOCKCOMMENT>{COMMENTEND} {BEGIN INITIAL;} //使用宏BEGIN来切换状态，初始状态默认为INITIAL

{ID} {
    string str = yytext; //yytext = 词素
    node *p = symbol_table.lookup(str);
    dump_tokens("ID      \t%-10s\t%d\t%d\t%p\t\n", yytext, yylineno, yycolumnno, p);

}

{EOL} yylineno++;

{WHITE}

    /*  Your code here (lab3). */
%%
/* user code section */

char outfile[256] = "a.out";
dump_type_t dump_type = ASM;

int main(int argc, char *argv[])
{
    int opt;
    while ((opt = getopt(argc, argv, "to:")) != -1)
    {
        switch (opt)
        {
        case 'o':
            strcpy(outfile, optarg);
            break;
        case 't':
            dump_type = TOKENS;
            break;
        default:
            fprintf(stderr, "Usage: %s [-o outfile] infile\n", argv[0]);
            exit(EXIT_FAILURE);
            break;
        }
    }
    if (optind >= argc)
    {
        fprintf(stderr, "no input file\n");
        exit(EXIT_FAILURE);
    }
    if (!(yyin = fopen(argv[optind], "r")))
    {
        fprintf(stderr, "%s: No such file or directory\nno input file\n", argv[optind]);
        exit(EXIT_FAILURE);
    }
    if (!(yyout = fopen(outfile, "w")))
    {
        fprintf(stderr, "%s: fail to open output file\n", outfile);
        exit(EXIT_FAILURE);
    }
    yylex();
    return 0;
}

