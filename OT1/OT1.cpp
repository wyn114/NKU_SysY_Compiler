#include "NFA.h"
using namespace std;

int main()
{

	/*��������1
	string str = "(a|b)*abb";*/

	/*��������2*/
	while (1)
	{
		cout << "please input string:";
		string str;
		string quit = "quit";
		cin >> str;
		if (str == quit)break;
		str = infixToSuffix(str);		/*����׺���ʽת��Ϊ��׺���ʽ*/

		/***��ʼ�����е�����***/
		int i, j;
		for (i = 0; i < MAX; i++)
		{

			NfaStates[i].index = i;
			NfaStates[i].input = '#';
			NfaStates[i].chTrans = -1;
		}

		NFA n = strToNfa(str);
		printNFA(n);
	}
	

	return 0;
}
