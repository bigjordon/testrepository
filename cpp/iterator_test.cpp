#include <iostream>
#include <map>
using namespace std;

int main(int argc, char **argv)
{
	char *p = NULL;
	map<int, char> m;	
	m.insert(pair<int, char>(1, 'c'));
	map<int ,char>::iterator it = m.begin();
	cout << it->first << endl;
	cout << it->second << endl;

	p = & it->second;
	cout << it->second << endl;
	cout << *p << endl;

	*p = 'd';
	cout << it->second << endl;
	cout << *p << endl;

	return 0;
}
