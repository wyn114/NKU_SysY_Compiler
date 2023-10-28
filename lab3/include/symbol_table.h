#include <ostream>
#include <fstream>
#include <malloc.h>
#include <unordered_map>
#include <string>
#include <cstring>
using namespace std;
bool if_New; //是否为域内新建

//链表形式组织符号表（此处符号表只记录ID）
//链表节点
struct node {
    char name[56];
    node* prev, * next;
};
//链表
struct id_list {
    node* head, * tail;
    int count;
};

id_list idlist;

// 初始化符号表链表
void init_idlist() {
    idlist.head = (node*)malloc(sizeof(node));
    idlist.head->next = idlist.head->prev = nullptr;
    idlist.tail = idlist.head;
    idlist.count = 0;
}

// 链表中添加元素
node* add(char* s) {
    node *id_elem = nullptr;
    id_elem = (node*)malloc(sizeof(node));
    strcpy(id_elem->name, s);
    idlist.tail->next = id_elem;
    id_elem->prev = idlist.tail;
    id_elem->next = nullptr;
    idlist.tail = id_elem;
    idlist.count++;
    return id_elem;
}

//自定义stack_element类（符号栈中元素）
/*
每个栈元素stack_element会持有一个指向前一元素的指针pre和一个map
map是无序的，存储的是当前这个{}范围下所有的映射对：<标识符名，对应符号表表项的地址>
*/
class stack_element {
private:
    unordered_map<string, node*> map;
    stack_element* prev;
public:
    //初始化空的符号栈的首元素
    stack_element() {
        prev = nullptr;
    }
    //往符号栈里压元素，新压入元素的pre自然就是低他一层的元素
    stack_element(stack_element* back) {
        prev = back;
    }
    void add_into_map(string name, node* id) {
        map[name] = id;
    }
    stack_element* get_prev() {
        return prev;
    }
    node* get_identifier(string name) {
        if (map.empty()) {
            return nullptr;
        }
        if (map.find(name) != map.end()) {
            return map[name];
        }
        else return nullptr;
    }
    ~stack_element() {
        prev = nullptr;
        unordered_map<string, node*>().swap(map);
        malloc_trim(0);
    }
};

// symble_stack 类，识别到标识符将其存入符号栈中，最后再一次性输出
class symble_stack: public stack_element {
private:
    // 栈的顶部
    stack_element* top;
public:
    // 初始化，之所以要初始化一个top表项，是为了存储全局标识符，这些标识符没有{}标识
    symble_stack() {
        stack_element* t = new stack_element();
        top = t;
    }

    //栈中的每一个元素都代表一个{}范围内所有标识符相关的存储
    // 添加元素
    void push() {
        //printf("pushing\n");
        stack_element* t = new stack_element(top);
        top = t;
    }

    // 弹出元素
    void pop() {
        //printf("poping\n");
        stack_element* p;
        p = top;
        top = top->get_prev();
        p->~stack_element();
    }

    // 添加标识符
    void add_map(string name, node* id) {
        top->add_into_map(name, id);
    }

    //查找符号栈中是否曾出现过同样的标识符
    node* lookup(string name) {
    // 1. 未出现：创建一个新的idlist_entry，并添加到top指针指向的map中，然后返回idlist_entry的地址
    // 2. 已出现：返回对应的idlist_entry地址

        node* p_entry = nullptr;

        //搜索：从栈顶依次向下搜索,因为{}可能层层嵌套
        stack_element* p;
        p = top;
        do {
            p_entry = p->get_identifier(name);
            if (p_entry) {
                //p_entry不为空，意味着已经找到了
                return p_entry;
            }
            //p_entry为空，意味着本域没找到，继续向下搜索
            p = p->get_prev();
            if(if_New)
            {
                //本域新建
                p_entry = add((char*)name.c_str());
                top->add_into_map(name, p_entry);
                return p_entry;
            }
        } while (p);
        
        //搜索不到，于是这是一个新的标识符
        p_entry = add((char*)name.c_str());
        top->add_into_map(name, p_entry);
        return p_entry;
    }
};
