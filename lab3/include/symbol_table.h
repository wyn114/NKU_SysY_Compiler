//符号表头文件
#include<iostream>
#include<map>
#include<string>

class symInfo{//一条信息类
public:
    int value;   //值
    int lineno;  //行号
    int offset;  //偏移量
    symInfo(int value, int lineno, int offset){
        this->value = value;
        this->lineno = lineno;
        this->offset = offset;
    }
};

class symTable{//符号表类
private:
    std::map<std::string, symInfo*> table; //表
    symTable* prev;                         //前一个表
    int level;                              //作用域级

public:
    symTable();
    symTable(symTable* prev);
    bool installID(std::string name, symInfo* entry);//插入一条
    symInfo* lookUp(std::string name);        //查询一条
    bool setInfo_Val(std::string name, int value);  //设置一条的值
    symTable* getPrev();     //返回前一个表
};


symTable::symTable() {
    prev = nullptr;
    level = 0;
}

symTable::symTable(symTable* prev){
    this->prev=prev;
    this->level=prev->level+1;
}

symInfo* symTable::lookUp(std::string name){
    symTable* p=this;
    while(p!=nullptr){
        if(p->table.find(name)!=p->table.end()){
            return p->table[name];
        }
        p=p->prev;
    }
    return nullptr;
}

bool symTable::installID(std::string name, symInfo* entry){
    if(this->table.find(name)!=this->table.end()){
        return false;
    }
    table[name]=entry;
    return true;
}

bool symTable::setInfo_Val(std::string name, int value){
    symInfo* entry = this->lookUp(name);
    if(entry==nullptr){
        return false;
    }
    entry->value=value;
    return true;
}

symTable* symTable::getPrev(){
    return prev;
}