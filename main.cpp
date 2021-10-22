#include <iostream>
#include <cstring>
#include <map>
using namespace std;



std::map<char, char> valid_ = {
    { 'A', '1' },
    { 'B', '2' },
    { 'C', '3' }
};

/************************
* SQL Query Generator
I'm called by testValid, genQueryWeak, genQueryStrong
*************************/
string genQuery(string username, string password)
{
	/*cout << "SELECT authenticate\n\t"
		<< "WHERE " << username << "\n\t\tAT " << password << endl;*/
	return ("SELECT authenticate WHERE " + username + " and " + password);
}


/************************
* WEAK Mitigation
*************************/
string mitigateWeak(string username, string password)
{
	/*cout << "SELECT authenticate\n\t"
		<< "WHERE " << username << "\n\t\tAT " << password << endl;*/
	return ("SELECT authenticate WHERE " + username + " AT " + password);
}


/************************
* STRONG Mitigation
*************************/
string mitigateStrong(string username, string password)
{
	/*cout << "SELECT authenticate\n\t"
		<< "WHERE " << username << "\n\t\tAT " << password << endl;*/
	return ("SELECT authenticate WHERE " + username + " AT " + password);
}

/************************
* Valid Usernames & Passwords
*************************/
string testValid()
{
	// Brnadon
	// "BrAnD0n_JaRrel", "I_love_My_m0m"; // SELECT WHERE "BrAnD0n_JaRrel" AT "I_love_My_m0m"

	// Ian
	genQuery("Outer_Space_TROLL", "SporeCaptain$piceTr@der"); // SELECT WHERE "Outer_Space_TROLL" AND "SporeCaptain$piceTr@der"

	// Nicole
	genQuery("PennyAna", "sootSprite"); //SELECT WHERE PennyAna sootSprite

	// Kevin
	genQuery("kevin_j0_ramos", "SuPeR_64"); //SELECT WHERE kevin_j0_ramos SuPeR_64 
	

	// Jared
	genQuery("jarebear", "fuzyWuzy4ever!"); //SELECT WHERE jarebear fuzyWuzy4ever!
	//return genQuery(username, password)
	return " ";
}
/************************
* Tautology Attacks
*************************/
string testTautology()
{
	// Brnadon
	// 

	// Ian

	// Nicole 
	string tauntaun = 'Root';
	string rebelPassword = 'vader\' OR \' 'x' \' = \' 'x'';
	genQueryStrong(tauntaun, rebelPassword);
	genQueryWeak(tauntaun, rebelPassword);

	// Kevin
	genQuery("")
	
	// Jared
	// cout << genQuery(username, password);
	//cout << genQuery(mitigateStrong(username, password));
	// cout << genQuery(mitigationWeak(username,password));
	return " ";
}
/************************
* Union Attacks
*************************/
string testUnion()
{
	// Brnadon

	// Ian

	// Nicole
	string tauntaun = '';
	string rebelPassword = '';
	genQueryStrong(tauntaun, rebelPassword);
	genQueryWeak(tauntaun, rebelPassword);

	// Kevin
	genQuery("hack4hugs", "balgone UNION SELECT overideRoot FROM adminPassWordList");

	// Jared

	return " ";
}
/************************
* Additional Statement Attacks
*************************/
string testAddState()
{
	// Brnadon

	// Ian

	// Nicole
	string tauntaun = '';
	string rebelPassword = '';
	genQueryStrong(tauntaun, rebelPassword);
	genQueryWeak(tauntaun, rebelPassword);

	// Kevin
	genQueryStrong("passwordsgoesbyebye", "; DROP COLUMN passwordList")

	// Jared

	return " ";
}
/************************
* Comment Attacks
*************************/
string testComment()
{
	// Brnadon

	// Ian

	// Nicole
	string tauntaun = '';
	string rebelPassword = '';
	genQueryStrong(tauntaun, rebelPassword);
	genQueryWeak(tauntaun, rebelPassword);


	// Kevin
	genQuery("BrotherPhillips'", "; --"); 

	// Jared

	return " ";
}
/************************
*  END OF TESTS
*************************/



int main()
{
	/*
	Main calls all tests which run genQuery on each string set
	Main calls all tests which run genQueryWeak on each string set then through genQuery
	Main calls all tests which run genQueryStrong on each string set then through genQuery
	*/
	string username;
	string password;

	cout << "\n\tSQL Injection Sanitization\n\n"
		<< "\tPlease enter a User name and Password\n";

	cout << "\tUsername: ";
	cin >> username;

	cout << "\tPassword: ";
	cin >> password;

	cout << "\n\tUsername is \"" << username << "\" and the " << "Password is \"" << password << "\"\n";

	cout << "\nNormal genQuery: \t" << genQuery(username, password);
	cout << "\nWeak genQuery: \t" << genQueryWeak(username, password);
	cout << "\nStronggenQuery: \t" << genQueryStrong(username, password);
	
	/*
	testValid();
	testTautology();
	testUnion();
	testAddState();
	testComment();
	*/


	return 0;
}