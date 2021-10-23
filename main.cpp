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
	return ("SELECT * FROM authenticate WHERE UNAME = '" + username + "' AND PASSW = '" + password + "'");
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

		case '\\': // forward slash, check further? not sure if this is an attack character
			inputToBeSan[i] = '\0';
			break;

		case '\'': // single quote, never allowed
			inputToBeSan[i] = '\0';
			break;

		case 'O': // the start of the OR process, check for the next part of the potential attack
			if (inputToBeSan[i+1] == 'R')
				inputToBeSan[i] = '\0';
			break;

		case '-': // the start of the comment, checks if there is a second one
			if (inputToBeSan[i+1] == '-')
				inputToBeSan[i] = '\0';
			break;

		case ';':
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
	if (inputToBeSan.size() > 19) // IF it's beyond our specified length, do something
		return "Input max is 20";  // Should be discussed.

	for (int i = 0; i < inputToBeSan.size(); i++)
	{
		// White List

		// NOT ALLOWED: if its escape characters (\n \t \v \r and other control shotcut characters) https://www.cplusplus.com/reference/cctype/
		if (iscntrl(inputToBeSan[i]))
		{
			inputToBeSan[i] = '\0';
			continue;
		}

		// ALLOWED: if it is a character in the alphabet, it is allowed
		if (isalpha(inputToBeSan[i]) || isdigit(inputToBeSan[i]))
		{
			continue;
		}

		// SIFT FOR ALLOWED except a few specific ones triggered by ispunct()
		if (ispunct(inputToBeSan[i]))  // EXLUCDED  "  '  \  ; -  everything else is allowed.
		{
			switch (inputToBeSan[i])
			{
				case ';':
					inputToBeSan[i] = '\0';
					break;
			
				case '\\':
					inputToBeSan[i] = '\0';
					break;
			
				case '\'':
					inputToBeSan[i] = '\0';
					break;

				case '"':
					inputToBeSan[i] = '\0';
					break;

				case '-':  // up for debate
					if(inputToBeSan[i+1] == '-')
						inputToBeSan[i] = '\0';
					break;

				default: 
					continue;
			}
		} // end of if
		
		// blocks anything else I couldn't think of, this should be up for debate
		inputToBeSan[i] = '\0';

	} // end of loop

	return (inputToBeSan);
}

/************************
* Valid Usernames & Passwords
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
			cout << endl << "Jared:\n" << "Normal: " << genQuery("jarebear", "fuzyWuzy4ever!") << endl; //SELECT WHERE jarebear fuzyWuzy4ever!
			cout << "Weak: " << genQuery(mitigateWeak("jarebear"), mitigateWeak("fuzyWuzy4ever!")) << endl;
			cout << "Strong: " << genQuery(mitigateStrong("jarebear"), mitigateStrong("fuzyWuzy4ever!")) << endl;
			break;

		case 3: // Ian
			cout << endl << "Ian:\n" << "Normal: " << genQuery("Outer_Space_TROLL", "SporeCaptain$piceTr@der") << endl; // SELECT WHERE "Outer_Space_TROLL" AND "SporeCaptain$piceTr@der"
			cout << "Weak: " << genQuery(mitigateWeak("Outer_Space_TROLL"), mitigateWeak("SporeCaptain$piceTr@der")) << endl;
			cout << "Strong: " << genQuery(mitigateStrong("Outer_Space_TROLL"), mitigateStrong("SporeCaptain$piceTr@der")) << endl;
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
			cout << endl << "Brandon:\n" << "Normal: " << genQuery("", "") << endl; // SELECT WHERE "BrAnD0n_JaRrel" AT "I_love_My_m0m"
			cout << "Weak: " << genQuery(mitigateWeak(""), mitigateWeak("")) << endl;
			cout << "Strong: " << genQuery(mitigateStrong(""), mitigateStrong("")) << endl;
			break;

		case 2: // Jared
			cout << endl << "Jared:\n"  "Normal: " << genQuery("", "") << endl; //SELECT WHERE jarebear fuzyWuzy4ever!
			cout << "Weak: " << genQuery(mitigateWeak(""), mitigateWeak("")) << endl;
			cout << "Strong: " << genQuery(mitigateStrong(""), mitigateStrong("")) << endl;
			break;

		case 3: // Ian
			cout << endl << "Ian:\n" << "Normal: " << genQuery("", "") << endl; // SELECT WHERE "Outer_Space_TROLL" AND "SporeCaptain$piceTr@der"
			cout << "Weak: " << genQuery(mitigateWeak(""), mitigateWeak("")) << endl;
			cout << "Strong: " << genQuery(mitigateStrong(""), mitigateStrong("")) << endl;
			break;

		case 4: //Nicole
			cout << endl << "Nicole:\n" << "Normal: " << genQuery("Root", "vader\' OR \' 'x' \' = \' 'x'") << endl; //
			cout << "Weak: " << genQuery(mitigateWeak("Root"), mitigateWeak("vader\' OR \' 'x' \' = \' 'X'")) << endl;
			cout << "Strong: " << genQuery(mitigateStrong("Root"), mitigateStrong("vader\' OR \' 'x' \' = \' 'x'")) << endl;
			break;

		case 5: // Kevin
			cout << endl << "Kevin:\n" << "Normal: " << genQuery("", "") << endl; //
			cout << "Weak: " << genQuery(mitigateWeak(""), mitigateWeak("")) << endl;
			cout << "Strong: " << genQuery(mitigateStrong(""), mitigateStrong("")) << endl;
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
			cout << endl << "Brandon:\n" << "Normal: " << genQuery("", "") << endl; // SELECT WHERE "BrAnD0n_JaRrel" AT "I_love_My_m0m"
			cout << "Weak: " << genQuery(mitigateWeak(""), mitigateWeak("")) << endl;
			cout << "Strong: " << genQuery(mitigateStrong(""), mitigateStrong("")) << endl;
			break;

		case 2: // Jared
			cout << endl << "Jared:\n"  "Normal: " << genQuery("", "") << endl; //SELECT WHERE jarebear fuzyWuzy4ever!
			cout << "Weak: " << genQuery(mitigateWeak(""), mitigateWeak("")) << endl;
			cout << "Strong: " << genQuery(mitigateStrong(""), mitigateStrong("")) << endl;
			break;

		case 3: // Ian
			cout << endl << "Ian:\n" << "Normal: " << genQuery("", "") << endl; // SELECT WHERE "Outer_Space_TROLL" AND "SporeCaptain$piceTr@der"
			cout << "Weak: " << genQuery(mitigateWeak(""), mitigateWeak("")) << endl;
			cout << "Strong: " << genQuery(mitigateStrong(""), mitigateStrong("")) << endl;
			break;

		case 4: //Nicole
			cout << endl << "Nicole:\n" << "Normal: " << genQuery("I\'mAUser", "x' UNION SELECT credit_card FROM Customers") << endl; //SELECT WHERE PennyAna sootSprite
			cout << "Weak: " << genQuery(mitigateWeak("I\'mAUser"), mitigateWeak("x' UNION SELECT credit_card FROM Customers")) << endl;
			cout << "Strong: " << genQuery(mitigateStrong("I\'mAUser"), mitigateStrong("x' UNION SELECT credit_card FROM Customers")) << endl;
			break;

		case 5: // Kevin
			cout << endl << "Kevin:\n" << "Normal: " << genQuery("hack4hugs", "balgone UNION SELECT overideRoot FROM adminPassWordList") << endl; //SELECT WHERE kevin_j0_ramos SuPeR_64 
			cout << "Weak: " << genQuery(mitigateWeak("hack4hugs"), mitigateWeak("balgone UNION SELECT overideRoot FROM adminPassWordList")) << endl;
			cout << "Strong: " << genQuery(mitigateStrong("hack4hugs"), mitigateStrong("balgone UNION SELECT overideRoot FROM adminPassWordList")) << endl;
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
			cout << endl << "Brandon:\n" << "Normal: " << genQuery("", "") << endl; // SELECT WHERE "BrAnD0n_JaRrel" AT "I_love_My_m0m"
			cout << "Weak: " << genQuery(mitigateWeak(""), mitigateWeak("")) << endl;
			cout << "Strong: " << genQuery(mitigateStrong(""), mitigateStrong("")) << endl;
			break;

		case 2: // Jared
			cout << endl << "Jared:\n"  "Normal: " << genQuery("", "") << endl; //SELECT WHERE jarebear fuzyWuzy4ever!
			cout << "Weak: " << genQuery(mitigateWeak(""), mitigateWeak("")) << endl;
			cout << "Strong: " << genQuery(mitigateStrong(""), mitigateStrong("")) << endl;
			break;

		case 3: // Ian
			cout << endl << "Ian:\n" << "Normal: " << genQuery("", "") << endl; // SELECT WHERE "Outer_Space_TROLL" AND "SporeCaptain$piceTr@der"
			cout << "Weak: " << genQuery(mitigateWeak(""), mitigateWeak("")) << endl;
			cout << "Strong: " << genQuery(mitigateStrong(""), mitigateStrong("")) << endl;
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
			cout << endl << "Brandon:\n" << "Normal: " << genQuery("", "") << endl; // SELECT WHERE "BrAnD0n_JaRrel" AT "I_love_My_m0m"
			cout << "Weak: " << genQuery(mitigateWeak(""), mitigateWeak("")) << endl;
			cout << "Strong: " << genQuery(mitigateStrong(""), mitigateStrong("")) << endl;
			break;

		case 2: // Jared
			cout << endl << "Jared:\n"  "Normal: " << genQuery("", "") << endl; //SELECT WHERE jarebear fuzyWuzy4ever!
			cout << "Weak: " << genQuery(mitigateWeak(""), mitigateWeak("")) << endl;
			cout << "Strong: " << genQuery(mitigateStrong(""), mitigateStrong("")) << endl;
			break;

		case 3: // Ian
			cout << endl << "Normal: " << genQuery("", "") << endl; // SELECT WHERE "Outer_Space_TROLL" AND "SporeCaptain$piceTr@der"
			cout << "Weak: " << genQuery(mitigateWeak(""), mitigateWeak("")) << endl;
			cout << "Strong: " << genQuery(mitigateStrong(""), mitigateStrong("")) << endl;
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

	//testValid();
	//testTautology();
	//testUnion();
	//testAddState();
	//testComment();
	string testString;
	do
	{
		cout << "\n\nInput a string to test mitigation returns\n";
		cout << "\t";
		getline(cin, testString);
		cout << "weak  \t" << mitigateWeak(testString) << "    is the output\n";
		cout << "strong\t" << mitigateStrong(testString) << "    is the output\n";
	} while (true);

	return 0;
}