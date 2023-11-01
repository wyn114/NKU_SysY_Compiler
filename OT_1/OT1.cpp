#include "NFA.h"
using namespace std;

int main()
{

	/*测试样例1
	string str = "(a|b)*abb";*/

	/*测试样例2*/
	while (1)
	{
		cout << "please input string:";
		string str;
		string quit = "quit";
		cin >> str;
		if (str == quit)break;
		str = infixToSuffix(str);		/*将中缀表达式转换为后缀表达式*/

		/***初始化所有的数组***/
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
