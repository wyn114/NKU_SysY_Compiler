#pragma once
#include<iostream>
#include<cstring>
#include<string>
#include<stack>
#include<vector>
#include<set>
#include<queue>

#define MAX 128

using namespace std;

typedef set<int> IntSet;
typedef set<char> CharSet;

/********************表达式转NFA********************/

struct NfaState				/*定义NFA状态*/
{
	int index;				/*NFA状态的状态号*/
	char input;				/*NFA状态弧上的值*/
	int chTrans;			/*NFA状态弧转移到的状态号*/
	IntSet epTrans;			/*当前状态通过ε转移到的状态号集合*/
};

struct NFA
{
	NfaState* head;			/*NFA的头指针*/
	NfaState* tail;			/*NFA的尾指针*/
};

NfaState NfaStates[MAX];	/*NFA状态数组*/
int nfaStateNum = 0;		/*NFA状态总数*/

/*从状态n1到状态n2添加一条弧，弧上的值为ch*/
void add(NfaState* n1, NfaState* n2, char ch)
{
	n1->input = ch;
	n1->chTrans = n2->index;
}

/*从状态n1到状态n2添加一条弧，弧上的值为ε*/
void add(NfaState* n1, NfaState* n2)
{
	n1->epTrans.insert(n2->index);
}

/*新建一个NFA（即从NFA状态数组中取出两个状态）*/
NFA creatNFA(int sum)
{
	NFA n;
	n.head = &NfaStates[sum];
	n.tail = &NfaStates[sum + 1];

	return n;
}

/*在字符串s第n位后面插入字符ch*/
void insert(string& s, int n, char ch)
{
	s += '#';
	for (int i = s.size() - 1; i > n; i--)
	{
		s[i] = s[i - 1];
	}
	s[n] = ch;
}

/*对字符串s进行预处理，在第一位是操作数、‘*’或‘)’且第二位是操作数或‘(’之间加入连接符‘&’*/
void preprocess(string& s)
{
	int i = 0, length = s.size();
	while (i < length)
	{
		if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] == '*') || (s[i] == ')'))
		{
			if ((s[i + 1] >= 'a' && s[i + 1] <= 'z') || s[i + 1] == '(')
			{
				insert(s, i + 1, '&');
				length++;
			}
		}
		i++;
	}
}

/*中缀转后缀时用到的优先级比较，即为每个操作符赋一个权重，通过权重大小比较优先级*/
int priority(char ch)
{
	if (ch == '*')
	{
		return 3;
	}
	if (ch == '&')
	{
		return 2;
	}
	if (ch == '|')
	{
		return 1;
	}
	if (ch == '(')
	{
		return 0;
	}
}

/*中缀表达式转后缀表达式*/
string infixToSuffix(string s)
{
	preprocess(s);			/*对字符串进行预处理*/
	string str;				/*要输出的后缀字符串*/
	stack<char> oper;		/*运算符栈*/
	for (int i = 0; i < s.size(); i++)
	{

		if (s[i] >= 'a' && s[i] <= 'z')	/*如果是操作数直接输出*/
		{
			str += s[i];
		}
		else							/*遇到运算符时*/
		{
			if (s[i] == '(')			/*遇到左括号压入栈中*/
			{
				oper.push(s[i]);
			}
			else if (s[i] == ')')	/*遇到右括号时*/
			{

				char ch = oper.top();
				while (ch != '(')		/*将栈中元素出栈，直到栈顶为左括号*/
				{
					str += ch;
					oper.pop();
					ch = oper.top();
				}
				oper.pop();				/*最后将左括号出栈*/
			}
			else					/*遇到其他操作符时*/
			{
				if (!oper.empty())			/*如果栈不为空*/
				{
					char ch = oper.top();
					while (priority(ch) >= priority(s[i]))	/*弹出栈中优先级大于等于当前运算符的运算符*/
					{
						str += ch;
						oper.pop();

						if (oper.empty())	/*如果栈为空则结束循环*/
						{
							break;
						}
						else ch = oper.top();
					}
					oper.push(s[i]);		/*再将当前运算符入栈*/
				}
				else				/*如果栈为空，直接将运算符入栈*/
				{
					oper.push(s[i]);
				}
			}
		}
	}

	/*最后如果栈不为空，则出栈并输出到字符串*/
	while (!oper.empty())
	{
		char ch = oper.top();
		oper.pop();

		str += ch;
	}

	cout << "*******************************************" << endl << endl;
	cout << "中缀表达式为：" << s << endl << endl;
	cout << "后缀表达式为：" << str << endl << endl;

	return str;
}

/*后缀表达式转nfa*/
NFA strToNfa(string s)
{
	stack<NFA> NfaStack;		/*定义一个NFA栈*/
	for (int i = 0; i < s.size(); i++)		/*读取后缀表达式，每次读一个字符*/
	{
		if (s[i] >= 'a' && s[i] <= 'z')		/*遇到操作数*/
		{
			NFA n = creatNFA(nfaStateNum);		/*新建一个NFA*/
			nfaStateNum += 2;					/*NFA状态总数加2*/
			add(n.head, n.tail, s[i]);			/*NFA的头指向尾，弧上的值为s[i]*/
			NfaStack.push(n);					/*将该NFA入栈*/
		}

		else if (s[i] == '*')		/*遇到闭包运算符*/
		{
			NFA n1 = creatNFA(nfaStateNum);		/*新建一个NFA*/
			nfaStateNum += 2;					/*NFA状态总数加2*/

			NFA n2 = NfaStack.top();			/*从栈中弹出一个NFA*/
			NfaStack.pop();

			add(n2.tail, n1.head);				/*n2的尾通过ε指向n1的头*/
			add(n2.tail, n1.tail);				/*n2的尾通过ε指向n1的尾*/
			add(n1.head, n2.head);				/*n1的头通过ε指向n2的头*/
			add(n1.head, n1.tail);				/*n1的头通过ε指向n1的尾*/

			NfaStack.push(n1);					/*最后将新生成的NFA入栈*/
		}

		else if (s[i] == '|')		/*遇到或运算符*/
		{

			NFA n1, n2;							/*从栈中弹出两个NFA，栈顶为n2，次栈顶为n1*/
			n2 = NfaStack.top();
			NfaStack.pop();

			n1 = NfaStack.top();
			NfaStack.pop();

			NFA n = creatNFA(nfaStateNum);		/*新建一个NFA*/
			nfaStateNum += 2;					/*NFA状态总数加2*/

			add(n.head, n1.head);				/*n的头通过ε指向n1的头*/
			add(n.head, n2.head);				/*n的头通过ε指向n2的头*/
			add(n1.tail, n.tail);				/*n1的尾通过ε指向n的尾*/
			add(n2.tail, n.tail);				/*n2的尾通过ε指向n的尾*/

			NfaStack.push(n);					/*最后将新生成的NFA入栈*/
		}

		else if (s[i] == '&')		/*遇到连接运算符*/
		{
			NFA n1, n2, n;				/*定义一个新的NFA n*/

			n2 = NfaStack.top();				/*从栈中弹出两个NFA，栈顶为n2，次栈顶为n1*/
			NfaStack.pop();

			n1 = NfaStack.top();
			NfaStack.pop();

			add(n1.tail, n2.head);				/*n1的尾通过ε指向n2的尾*/
			n.head = n1.head;					/*n的头为n1的头*/
			n.tail = n2.tail;					/*n的尾为n2的尾*/
			NfaStack.push(n);					/*最后将新生成的NFA入栈*/
		}
	}

	return NfaStack.top();		/*最后的栈顶元素即为生成好的NFA*/
}

/*打印NFA函数*/
void printNFA(NFA nfa)
{
	cout << "***************     NFA     ***************" << endl << endl;
	cout << "NFA总共有" << nfaStateNum << "个状态，" << endl;
	cout << "初态为" << nfa.head->index << "，终态为" << nfa.tail->index << "。" << endl << endl << "转移函数为：" << endl;

	for (int i = 0; i < nfaStateNum; i++)		/*遍历NFA状态数组*/
	{
		if (NfaStates[i].input != '#')			/*如果弧上的值不是初始时的‘#’则输出*/
		{
			cout << NfaStates[i].index << "-->'" << NfaStates[i].input << "'-->" << NfaStates[i].chTrans << '\t';
		}
		IntSet::iterator it;					/*输出该状态经过ε到达的状态*/
		for (it = NfaStates[i].epTrans.begin(); it != NfaStates[i].epTrans.end(); it++)
		{
			cout << NfaStates[i].index << "-->'" << ' ' << "'-->" << *it << '\t';
		}
		cout << endl;
	}
}