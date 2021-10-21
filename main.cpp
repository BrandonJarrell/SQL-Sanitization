#include <iostream>
#include <cstring>

using namespace std;



/************************
* NORMAL Query Generator
*************************/
string genQuery(string username, string password)
{
	/*cout << "SELECT authenticate\n\t"
		<< "WHERE " << username << "\n\t\tAT " << password << endl;*/
	return ("SELECT authenticate WHERE " + username + " AT " + password);
}


/************************
* WEAK Query Generator
*************************/
string genQueryWeak(string username, string password)
{
	/*cout << "SELECT authenticate\n\t"
		<< "WHERE " << username << "\n\t\tAT " << password << endl;*/
	return ("SELECT authenticate WHERE " + username + " AT " + password);
}


/************************
* STRONG Query Generator
*************************/
string genQueryStrong(string username, string password)
{
	/*cout << "SELECT authenticate\n\t"
		<< "WHERE " << username << "\n\t\tAT " << password << endl;*/
	return ("SELECT authenticate WHERE " + username + " AT " + password);
}

/************************
* NORMAL
*************************/
void testValid()
{

}

void testTautology()
{

}

void testUnion()
{

}

void testAddState()
{

}

void testComment()
{

}
/************************
*  END OF NORMAL
*************************/



int main()
{
	string username;
	string password;

	cout << "\n\tSQL Injection Sanitization\n\n"
		<< "\tPlease enter a User name and Password\n";

	cout << "\tUsername: ";
	cin >> username;

	cout << "\tPassword: ";
	cin >> password;

	cout << "\n\tUsername is \"" << username << "\" and the " << "Password is \"" << password << "\"\n";

	cout << "\n\tNormal genQuery: " << genQuery(username, password);
	cout << "\n\tWeak genQuery: " << genQueryWeak(username, password);
	cout << "\n\tStronggenQuery: " << genQueryStrong(username, password);
	
	/*
	testValid();
	testTautology();
	testUnion();
	testAddState();
	testComment();
	*/









	return 0;
}