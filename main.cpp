#include <iostream>
#include <cstring>

using namespace std;



/************************
* NORMAL Query Generator
*************************/
void genQuery(string username, string password)
{
	cout << "SELECT authenticate\n\t"
		<< "WHERE " << username << "\n\t\tAT " << password << endl;
}


/************************
* WEAK Query Generator
*************************/
void genQueryWeak(string username, string password)
{
	cout << "SELECT authenticate\n\t"
		<< "WHERE " << username << "\n\t\tAT " << password << endl;
}


/************************
* STRONG Query Generator
*************************/
void genQueryStrong(string username, string password)
{
	cout << "SELECT authenticate\n\t"
		<< "WHERE " << username << "\n\t\tAT " << password << endl;
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

/************************
* WEAK
*************************/
void testValidWeak()
{

}

void testTautologyWeak()
{

}

void testUnionWeak()
{

}

void testAddStateWeak()
{

}

void testCommentWeak()
{

}
/************************
*  END OF WEAK
*************************/

/************************
* STRONG
*************************/
void testValidStrong()
{

}

void testTautologyStrong()
{

}

void testUnionStrong()
{

}

void testAddStateStrong()
{

}

void testCommentStrong()
{

}
/************************
*  END OF STRONG
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

	genQuery(username, password);
	//system("ping www.google.com");
	/*
	// NORMAL GENERATOR
	genQuery(username, password);

	// WEAK GENERATOR
	genQueryWeak(username, password);

	// STRONG GENERATOR
	genQueryStrong(username, password);

	// NORMAL
	testValid();
	testTautology();
	testUnion();
	testAddState();
	testComment();

	// WEAK
	testValidWeak();
	testTautologyWeak();
	testUnionWeak();
	testAddStateWeak();
	testCommentWeak();

	//STRONG
	testValidStrong();
	testTautologyStrong();
	testUnionStrong();
	testAddStateStrong();
	testCommentStrong();


	*/

	system("cd");







	return 0;
}