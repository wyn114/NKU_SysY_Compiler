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

/********************���ʽתNFA********************/

struct NfaState				/*����NFA״̬*/
{
	int index;				/*NFA״̬��״̬��*/
	char input;				/*NFA״̬���ϵ�ֵ*/
	int chTrans;			/*NFA״̬��ת�Ƶ���״̬��*/
	IntSet epTrans;			/*��ǰ״̬ͨ����ת�Ƶ���״̬�ż���*/
};

struct NFA
{
	NfaState* head;			/*NFA��ͷָ��*/
	NfaState* tail;			/*NFA��βָ��*/
};

NfaState NfaStates[MAX];	/*NFA״̬����*/
int nfaStateNum = 0;		/*NFA״̬����*/

/*��״̬n1��״̬n2���һ���������ϵ�ֵΪch*/
void add(NfaState* n1, NfaState* n2, char ch)
{
	n1->input = ch;
	n1->chTrans = n2->index;
}

/*��״̬n1��״̬n2���һ���������ϵ�ֵΪ��*/
void add(NfaState* n1, NfaState* n2)
{
	n1->epTrans.insert(n2->index);
}

/*�½�һ��NFA������NFA״̬������ȡ������״̬��*/
NFA creatNFA(int sum)
{
	NFA n;
	n.head = &NfaStates[sum];
	n.tail = &NfaStates[sum + 1];

	return n;
}

/*���ַ���s��nλ��������ַ�ch*/
void insert(string& s, int n, char ch)
{
	s += '#';
	for (int i = s.size() - 1; i > n; i--)
	{
		s[i] = s[i - 1];
	}
	s[n] = ch;
}

/*���ַ���s����Ԥ�����ڵ�һλ�ǲ���������*����)���ҵڶ�λ�ǲ�������(��֮��������ӷ���&��*/
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

/*��׺ת��׺ʱ�õ������ȼ��Ƚϣ���Ϊÿ����������һ��Ȩ�أ�ͨ��Ȩ�ش�С�Ƚ����ȼ�*/
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

/*��׺���ʽת��׺���ʽ*/
string infixToSuffix(string s)
{
	preprocess(s);			/*���ַ�������Ԥ����*/
	string str;				/*Ҫ����ĺ�׺�ַ���*/
	stack<char> oper;		/*�����ջ*/
	for (int i = 0; i < s.size(); i++)
	{

		if (s[i] >= 'a' && s[i] <= 'z')	/*����ǲ�����ֱ�����*/
		{
			str += s[i];
		}
		else							/*���������ʱ*/
		{
			if (s[i] == '(')			/*����������ѹ��ջ��*/
			{
				oper.push(s[i]);
			}
			else if (s[i] == ')')	/*����������ʱ*/
			{

				char ch = oper.top();
				while (ch != '(')		/*��ջ��Ԫ�س�ջ��ֱ��ջ��Ϊ������*/
				{
					str += ch;
					oper.pop();
					ch = oper.top();
				}
				oper.pop();				/*��������ų�ջ*/
			}
			else					/*��������������ʱ*/
			{
				if (!oper.empty())			/*���ջ��Ϊ��*/
				{
					char ch = oper.top();
					while (priority(ch) >= priority(s[i]))	/*����ջ�����ȼ����ڵ��ڵ�ǰ������������*/
					{
						str += ch;
						oper.pop();

						if (oper.empty())	/*���ջΪ�������ѭ��*/
						{
							break;
						}
						else ch = oper.top();
					}
					oper.push(s[i]);		/*�ٽ���ǰ�������ջ*/
				}
				else				/*���ջΪ�գ�ֱ�ӽ��������ջ*/
				{
					oper.push(s[i]);
				}
			}
		}
	}

	/*������ջ��Ϊ�գ����ջ��������ַ���*/
	while (!oper.empty())
	{
		char ch = oper.top();
		oper.pop();

		str += ch;
	}

	cout << "*******************************************" << endl << endl;
	cout << "��׺���ʽΪ��" << s << endl << endl;
	cout << "��׺���ʽΪ��" << str << endl << endl;

	return str;
}

/*��׺���ʽתnfa*/
NFA strToNfa(string s)
{
	stack<NFA> NfaStack;		/*����һ��NFAջ*/
	for (int i = 0; i < s.size(); i++)		/*��ȡ��׺���ʽ��ÿ�ζ�һ���ַ�*/
	{
		if (s[i] >= 'a' && s[i] <= 'z')		/*����������*/
		{
			NFA n = creatNFA(nfaStateNum);		/*�½�һ��NFA*/
			nfaStateNum += 2;					/*NFA״̬������2*/
			add(n.head, n.tail, s[i]);			/*NFA��ͷָ��β�����ϵ�ֵΪs[i]*/
			NfaStack.push(n);					/*����NFA��ջ*/
		}

		else if (s[i] == '*')		/*�����հ������*/
		{
			NFA n1 = creatNFA(nfaStateNum);		/*�½�һ��NFA*/
			nfaStateNum += 2;					/*NFA״̬������2*/

			NFA n2 = NfaStack.top();			/*��ջ�е���һ��NFA*/
			NfaStack.pop();

			add(n2.tail, n1.head);				/*n2��βͨ����ָ��n1��ͷ*/
			add(n2.tail, n1.tail);				/*n2��βͨ����ָ��n1��β*/
			add(n1.head, n2.head);				/*n1��ͷͨ����ָ��n2��ͷ*/
			add(n1.head, n1.tail);				/*n1��ͷͨ����ָ��n1��β*/

			NfaStack.push(n1);					/*��������ɵ�NFA��ջ*/
		}

		else if (s[i] == '|')		/*�����������*/
		{

			NFA n1, n2;							/*��ջ�е�������NFA��ջ��Ϊn2����ջ��Ϊn1*/
			n2 = NfaStack.top();
			NfaStack.pop();

			n1 = NfaStack.top();
			NfaStack.pop();

			NFA n = creatNFA(nfaStateNum);		/*�½�һ��NFA*/
			nfaStateNum += 2;					/*NFA״̬������2*/

			add(n.head, n1.head);				/*n��ͷͨ����ָ��n1��ͷ*/
			add(n.head, n2.head);				/*n��ͷͨ����ָ��n2��ͷ*/
			add(n1.tail, n.tail);				/*n1��βͨ����ָ��n��β*/
			add(n2.tail, n.tail);				/*n2��βͨ����ָ��n��β*/

			NfaStack.push(n);					/*��������ɵ�NFA��ջ*/
		}

		else if (s[i] == '&')		/*�������������*/
		{
			NFA n1, n2, n;				/*����һ���µ�NFA n*/

			n2 = NfaStack.top();				/*��ջ�е�������NFA��ջ��Ϊn2����ջ��Ϊn1*/
			NfaStack.pop();

			n1 = NfaStack.top();
			NfaStack.pop();

			add(n1.tail, n2.head);				/*n1��βͨ����ָ��n2��β*/
			n.head = n1.head;					/*n��ͷΪn1��ͷ*/
			n.tail = n2.tail;					/*n��βΪn2��β*/
			NfaStack.push(n);					/*��������ɵ�NFA��ջ*/
		}
	}

	return NfaStack.top();		/*����ջ��Ԫ�ؼ�Ϊ���ɺõ�NFA*/
}

/*��ӡNFA����*/
void printNFA(NFA nfa)
{
	cout << "***************     NFA     ***************" << endl << endl;
	cout << "NFA�ܹ���" << nfaStateNum << "��״̬��" << endl;
	cout << "��̬Ϊ" << nfa.head->index << "����̬Ϊ" << nfa.tail->index << "��" << endl << endl << "ת�ƺ���Ϊ��" << endl;

	for (int i = 0; i < nfaStateNum; i++)		/*����NFA״̬����*/
	{
		if (NfaStates[i].input != '#')			/*������ϵ�ֵ���ǳ�ʼʱ�ġ�#�������*/
		{
			cout << NfaStates[i].index << "-->'" << NfaStates[i].input << "'-->" << NfaStates[i].chTrans << '\t';
		}
		IntSet::iterator it;					/*�����״̬�����ŵ����״̬*/
		for (it = NfaStates[i].epTrans.begin(); it != NfaStates[i].epTrans.end(); it++)
		{
			cout << NfaStates[i].index << "-->'" << ' ' << "'-->" << *it << '\t';
		}
		cout << endl;
	}
}