#include <iostream>
#include <cstring>
using namespace std;


/************************
* SQL Query Generator
I'm called by testValid, genQueryWeak, genQueryStrong
*************************/
string genQuery(string username, string password)
{
	/*cout << "SELECT authenticate\n\t"
		<< "WHERE " << username << "\n\t\tAT " << password << endl;*/
	return ("SELECT authenticate FROM passwordList WHERE uname = '" + username + "' AND passw = '" + password + "'");
}


/************************
* WEAK Mitigation
*************************/
string mitigateWeak(string inputToBeSan)
{
	for (int i = 0; i < inputToBeSan.size(); i++)
	{
		// Black List
		switch (inputToBeSan[i])
		{

		case ' ': // space, never allowed
			inputToBeSan[i] = '\0';
			break;

		case '\\': // back slash, check further? not sure if this is an attack character
			inputToBeSan[i] = '\0';
			break; 

		case '\'': // single quote, never allowed
			inputToBeSan[i] = '\0';
			break;

		case 'O': // the start of the OR process, check for the next part of the potential attack
			if (inputToBeSan[i + 1] == 'R')
				inputToBeSan[i] = '\0';
			break;

		case '-': // the start of the comment, checks if there is a second one
			if (inputToBeSan[i+1] == '-')
				inputToBeSan[i] = '\0';      //      'Uname'; --' and passw= "nothing"'; '
			break;

		case ';':
			inputToBeSan[i] = '\0';
			break;

		case ',':
			inputToBeSan[i] = '\0';
			break;

		case '=':
			inputToBeSan[i] = '\0';
			break; 
		}
	}

	return (inputToBeSan);
}


/************************
* STRONG Mitigation
*************************/
string mitigateStrong(string inputToBeSan)
{

	for (int i = 0; i < inputToBeSan.size(); i++)
	{
		// if the input is longer than 30, cut it off
		if (i > 30)
			inputToBeSan[i] = '\0';


		// White List

		// ALLOWED: if it is a character in the alphabet, it is allowed       https://www.cplusplus.com/reference/cctype/
		if (isalpha(inputToBeSan[i]) || isdigit(inputToBeSan[i]) || inputToBeSan[i] == '_')
		{
			continue;
		}

		// blocks anything else
		inputToBeSan[i] = '\0';
	}

	return (inputToBeSan);
}

/************************               
* Valid Usernames & Passwords (username and the password consist of letters, numbers, and underscores)
*************************/
void testValid()
{
	cout << "Testing Valids:\n\n";
	for (int i = 0; i < 6; i++) // because there are 5 of us
	{
		switch (i)
		{
		case 1:  // Brandon
			cout << endl << "Brandon:\n" << "Normal: " << genQuery("BrAnD0n_JaRrel", "I_love_My_m0m") << endl; // SELECT WHERE "BrAnD0n_JaRrel" AT "I_love_My_m0m"
			cout << "Weak: " << genQuery(mitigateWeak("BrAnD0n_JaRrel"), mitigateWeak("I_love_My_m0m")) << endl;
			cout << "Strong: " << genQuery(mitigateStrong("BrAnD0n_JaRrel"), mitigateStrong("I_love_My_m0m")) << endl;
			break;

		case 2: // Jared
			cout << endl << "Jared:\n" << "Normal: " << genQuery("jarebear", "fuzy_Wuzy_4_ever") << endl; //SELECT authenticate FROM passwordList WHERE uname = 'jarebear' AND passw = 'fuzy_Wuzy_4_ever'
			cout << "Weak: " << genQuery(mitigateWeak("jarebear"), mitigateWeak("fuzy_Wuzy_4_ever")) << endl;
			cout << "Strong: " << genQuery(mitigateStrong("jarebear"), mitigateStrong("fuzy_Wuzy_4_ever")) << endl;
			break;

		case 3: // Ian
			cout << endl << "Ian:\n" << "Normal: " << genQuery("Outer_Space_TROLL", "SporeCaptainSpiceTrader") << endl; // SELECT WHERE "Outer_Space_TROLL" AND "SporeCaptain$piceTr@der"
			cout << "Weak: " << genQuery(mitigateWeak("Outer_Space_TROLL"), mitigateWeak("SporeCaptainSpiceTrader")) << endl;
			cout << "Strong: " << genQuery(mitigateStrong("Outer_Space_TROLL"), mitigateStrong("SporeCaptainSpiceTrader")) << endl;
			break;

		case 4: //Nicole
			cout << endl << "Nicole:\n" << "Normal: " << genQuery("PennyAna", "sootSprite") << endl; //SELECT WHERE PennyAna sootSprite
			cout << "Weak: " << genQuery(mitigateWeak("PennyAna"), mitigateWeak("sootSprite")) << endl;
			cout << "Strong: " << genQuery(mitigateStrong("PennyAna"), mitigateStrong("sootSprite")) << endl;
			break;

		case 5: // Kevin
			cout << endl << "Kevin:\n" << "Normal: " << genQuery("kevin_j0_ramos", "SuPeR_64") << endl; //SELECT WHERE kevin_j0_ramos SuPeR_64 
			cout << "Weak: " << genQuery(mitigateWeak("kevin_j0_ramos"), mitigateWeak("SuPeR_64")) << endl;
			cout << "Strong: " << genQuery(mitigateStrong("kevin_j0_ramos"), mitigateStrong("SuPeR_64")) << endl;
			break;
		}
	}
	cout << endl << "\t--End of Valid Tests--" << endl;
}

/************************
* Tautology Attacks
*************************/
void testTautology()
{
	cout << endl << "Testing Tautology:\n\n";
	for (int i = 0; i < 6; i++) // because there are 5 of us
	{
		switch (i)
		{
		case 1:  // Brandon
			cout << endl << "Brandon:\n" << "Normal: " << genQuery("mrPresident", "password' OR '5' = '5") << endl;
			cout << "Weak: " << genQuery(mitigateWeak("mrPresident"), mitigateWeak("password' OR '5' = '5")) << endl;
			cout << "Strong: " << genQuery(mitigateStrong("mrPresident"), mitigateStrong("password' OR '5' = '5")) << endl;
			break;

		case 2: // Jared
			cout << endl << "Jared:\n"  "Normal: " << genQuery("jarebear", "true' OR 'x' = 'x") << endl; //SELECT authenticate FROM passwordList WHERE uname = 'jarebear' AND passw = 'true' OR 'x' = 'x'
			cout << "Weak: " << genQuery(mitigateWeak("jarebear"), mitigateWeak("true' OR 'x' = 'x")) << endl;
			cout << "Strong: " << genQuery(mitigateStrong("jarebear"), mitigateStrong("true' OR 'x' = 'x")) << endl;
			break;

		case 3: // Ian
			cout << endl << "Ian:\n" << "Normal: " << genQuery("NotSus", "imposter' OR 1 = true") << endl; // SELECT WHERE "Outer_Space_TROLL" AND "SporeCaptain$piceTr@der"
			cout << "Weak: " << genQuery(mitigateWeak("NotSus"), mitigateWeak("imposter' OR 1 = true")) << endl;
			cout << "Strong: " << genQuery(mitigateStrong("NotSus"), mitigateStrong("imposter' OR 1 = true")) << endl;
			break;

		case 4: //Nicole
			cout << endl << "Nicole:\n" << "Normal: " << genQuery("Root", "vader\' OR \' 'x' \' = \' 'x'") << endl; //
			cout << "Weak: " << genQuery(mitigateWeak("Root"), mitigateWeak("vader\' OR \' 'x' \' = \' 'X'")) << endl;
			cout << "Strong: " << genQuery(mitigateStrong("Root"), mitigateStrong("vader\' OR \' 'x' \' = \' 'x'")) << endl;
			break;

		case 5: // Kevin
			cout << endl << "Kevin:\n" << "Normal: " << genQuery("Admin", "idk' OR 'yes' = 'yes") << endl; //
			cout << "Weak: " << genQuery(mitigateWeak("Admin"), mitigateWeak("idk' OR 'yes' = 'yes")) << endl;
			cout << "Strong: " << genQuery(mitigateStrong("Admin"), mitigateStrong("idk' OR 'yes' = 'yes")) << endl;
			break;
		}
		cout << endl;
	}
	cout << endl << "\t--End of Tautology Tests--" << endl;
}

/************************
* Union Attacks
*************************/
void testUnion()	
{
	cout << endl << "Testing Union:\n\n";
	for (int i = 0; i < 6; i++) // because there are 5 of us
	{
		switch (i)
		{
		case 1:  // Brandon
			cout << endl << "Brandon:\n" << "Normal: " << genQuery("fakeLogin", "x' UNION DROP TABLE Root;--") << endl; 
			cout << "Weak: " << genQuery(mitigateWeak("fakeLogin"), mitigateWeak("x' UNION DROP TABLE Root;--")) << endl;
			cout << "Strong: " << genQuery(mitigateStrong("fakeLogin"), mitigateStrong("x' UNION DROP TABLE Root;--")) << endl;
			break;

		case 2: // Jared
			cout << endl << "Jared:\n"  "Normal: " << genQuery("jarebear", "x' UNION SELESCT * FROM passwordList;--'Thank you for your data!") << endl; //SELECT authenticate FROM passwordList WHERE uname = 'jarebear' AND passw = 'x' UNION SELESCT * FROM passwordList;--''
			cout << "Weak: " << genQuery(mitigateWeak("jarebear"), mitigateWeak("x' UNION SELESCT * FROM passwordList;--'Thank you for your data!")) << endl;
			cout << "Strong: " << genQuery(mitigateStrong("jarebear"), mitigateStrong("x' UNION SELESCT * FROM passwordList;--'Thank you for your data!")) << endl;
			break;

		case 3: // Ian
			cout << endl << "Ian:\n" << "Normal: " << genQuery("NotSus", "imposter' UNION SELECT * FROM nuclearLunchCodes") << endl; // SELECT WHERE "Outer_Space_TROLL" AND "SporeCaptain$piceTr@der"
			cout << "Weak: " << genQuery(mitigateWeak("NotSus"), mitigateWeak("imposter' UNION SELECT * FROM nuclearLunchCodes")) << endl;
			cout << "Strong: " << genQuery(mitigateStrong("NotSus"), mitigateStrong("imposter' UNION SELECT * FROM nuclearLunchCodes")) << endl;
			break;

		case 4: //Nicole
			cout << endl << "Nicole:\n" << "Normal: " << genQuery("I\'mAUser", "x' UNION SELECT credit_card FROM Customers") << endl; //SELECT WHERE PennyAna sootSprite
			cout << "Weak: " << genQuery(mitigateWeak("I\'mAUser"), mitigateWeak("x' UNION SELECT credit_card FROM Customers")) << endl;
			cout << "Strong: " << genQuery(mitigateStrong("I\'mAUser"), mitigateStrong("x' UNION SELECT credit_card FROM Customers")) << endl;
			break;

		case 5: // Kevin
			cout << endl << "Kevin:\n" << "Normal: " << genQuery("hack4hugs", "balgone' UNION SELECT overideRoot FROM adminPassWordList") << endl; //SELECT WHERE kevin_j0_ramos SuPeR_64 
			cout << "Weak: " << genQuery(mitigateWeak("hack4hugs"), mitigateWeak("balgone' UNION SELECT overideRoot FROM adminPassWordList")) << endl;
			cout << "Strong: " << genQuery(mitigateStrong("hack4hugs"), mitigateStrong("balgone' UNION SELECT overideRoot FROM adminPassWordList")) << endl;
			break;
		}
		cout << endl;
	}
	cout << endl << "\t--End of Union Tests--" << endl;
}

/************************
* Additional Statement Attacks
*************************/
void testAddState()
{
	cout << endl << "Testing AddState:\n\n";
	for (int i = 0; i < 6; i++) // because there are 5 of us
	{
		switch (i)
		{
		case 1:  // Brandon
			cout << endl << "Brandon:\n" << "Normal: " << genQuery("mrPresident", "get_rekt_nerd'; DROP TABLE *;--") << endl;
			cout << "Weak: " << genQuery(mitigateWeak("mrPresident"), mitigateWeak("get_rekt_nerd'; DROP TABLE *;--")) << endl;
			cout << "Strong: " << genQuery(mitigateStrong("mrPresident"), mitigateStrong("get_rekt_nerd'; DROP TABLE *;--")) << endl;
			break;

		case 2: // Jared
			cout << endl << "Jared:\n"  "Normal: " << genQuery("jareBear", "nothing'; INSERT INTO passwordList (name, passwd) VALUES 'Bob', '1234") << endl; //SELECT authenticate FROM passwordList WHERE uname = 'jareBear' AND passw = 'nothing'; INSERT INTO passwordList (name, passwd) VALUES 'Bob', '1234'
			cout << "Weak: " << genQuery(mitigateWeak("jareBear"), mitigateWeak("nothing'; INSERT INTO passwordList (name, passwd) VALUES 'Bob', '1234")) << endl;
			cout << "Strong: " << genQuery(mitigateStrong("jareBear"), mitigateStrong("nothing'; INSERT INTO passwordList (name, passwd) VALUES 'Bob', '1234")) << endl;
			break;

		case 3: // Ian
			cout << endl << "Ian:\n" << "Normal: " << genQuery("NotSus", "imposter' ; DROP INDEX * ON oxygenCodes") << endl; // SELECT WHERE "Outer_Space_TROLL" AND "SporeCaptain$piceTr@der"
			cout << "Weak: " << genQuery(mitigateWeak("NotSus"), mitigateWeak("imposter' ; DROP INDEX * ON oxygenCodes")) << endl;
			cout << "Strong: " << genQuery(mitigateStrong("NotSus"), mitigateStrong("imposter' ; DROP INDEX * ON oxygenCodes")) << endl;
			break;

		case 4: //Nicole
			cout << endl << "Nicole:\n" << "Normal: " << genQuery("Bob", "42'; INSERT INTO Customer(name, password) VALUES 'Isaac Asimov', 'Foundation'") << endl; //SELECT WHERE PennyAna sootSprite
			cout << "Weak: " << genQuery(mitigateWeak("Bob"), mitigateWeak("42'; INSERT INTO Customer(name, password) VALUES 'Isaac Asimov', 'Foundation'")) << endl; ;
			cout << "Strong: " << genQuery(mitigateStrong("Bob"), mitigateStrong("42'; INSERT INTO Customer(name, password) VALUES 'Isaac Asimov', 'Foundation'")) << endl;
			break;

		case 5: // Kevin
			cout << endl << "Kevin:\n" << "Normal: " << genQuery("passwordsgoesbyebye", "; DROP COLUMN passwordList") << endl; //SELECT WHERE kevin_j0_ramos SuPeR_64 
			cout << "Weak: " << genQuery(mitigateWeak("passwordsgoesbyebye"), mitigateWeak("; DROP COLUMN passwordList")) << endl;
			cout << "Strong: " << genQuery(mitigateStrong("passwordsgoesbyebye"), mitigateStrong("; DROP COLUMN passwordList")) << endl;
			break;
		}
		cout << endl;
	}
	cout << endl << "\t--End of AddState Tests--" << endl;
}

/************************
* Comment Attacks
*************************/
void testComment()
{
	cout << endl << "Testing Comments:\n\n";
	for (int i = 0; i < 6; i++) // because there are 5 of us
	{
		switch (i)
		{
		case 1:  // Brandon
			cout << endl << "Brandon:\n" << "Normal: " << genQuery("mrPresident';--", "lol' this is now pointless and all ur base belong to us") << endl;
			cout << "Weak: " << genQuery(mitigateWeak("mrPresident';--"), mitigateWeak("lol' this is now pointless and all ur base belong to us")) << endl;
			cout << "Strong: " << genQuery(mitigateStrong("mrPresident';--"), mitigateStrong("lol' this is now pointless and all ur base belong to us")) << endl;
			break;

		case 2: // Jared
			cout << endl << "Jared:\n"  "Normal: " << genQuery("Admin';--", "Look at me! I am the Admin now!") << endl; //SELECT authenticate FROM passwordList WHERE uname = 'Admin';--' AND passw = 'Look at me! I am the Admin now!'
			cout << "Weak: " << genQuery(mitigateWeak("Admin"), mitigateWeak("Look at me! I am the Admin now!")) << endl;
			cout << "Strong: " << genQuery(mitigateStrong("Admin"), mitigateStrong("Look at me! I am the Admin now!")) << endl;
			break;

		case 3: // Ian
			cout << endl << "Normal: " << genQuery("NotSus", " ; --ejected!") << endl; // SELECT WHERE "Outer_Space_TROLL" AND "SporeCaptain$piceTr@der"
			cout << "Weak: " << genQuery(mitigateWeak("NotSus"), mitigateWeak(" ; --ejected!")) << endl;
			cout << "Strong: " << genQuery(mitigateStrong("NotSus"), mitigateStrong(" ; --ejected!")) << endl;
			break;

		case 4: //Nicole
			cout << endl << "Normal: " << genQuery("Root'; --", "chilledmonkeybrains") << endl; //SELECT WHERE PennyAna sootSprite
			cout << "Weak: " << genQuery(mitigateWeak("Root'; --"), mitigateWeak("chilledmonkeybrains")) << endl;
			cout << "Strong: " << genQuery(mitigateStrong("Root'; --"), mitigateStrong("chilledmonkeybrains")) << endl;
			break;

		case 5: // Kevin
			cout << endl << "Kevin:\n" << "Normal: " << genQuery("BrotherPhillips'", "; --") << endl; //SELECT WHERE kevin_j0_ramos SuPeR_64 
			cout << "Weak: " << genQuery(mitigateWeak("BrotherPhillips'"), mitigateWeak("; --")) << endl;
			cout << "Strong: " << genQuery(mitigateStrong("BrotherPhillips'"), mitigateStrong("; --")) << endl;
			break;
		}
		cout << endl;
	}
	cout << endl << "\t--End of Comment Tests--" << endl;
}



int main()
{

	cout << "\n\tSQL Injection Sanitization\n\n";

	testValid();
	testTautology();
	testUnion();
	testAddState();
	testComment();

	return 0;
}
