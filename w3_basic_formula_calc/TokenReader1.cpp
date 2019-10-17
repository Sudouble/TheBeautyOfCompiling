#include "TokenReader1.h"


TokenReader::TokenReader(string str_)
{
	str = str_;

	mapEnum2Name[INIT] = "INIT";
	mapEnum2Name[ID] = "ID";
	mapEnum2Name[DIGIT] = "DIGIT";
	mapEnum2Name[MULTI] = "MULTI";
	mapEnum2Name[ADD] = "ADD";
	mapEnum2Name[GT] = "GT";	
	mapEnum2Name[GT_THAN] = "GT_THAN";

	int currentPos = 0;

	parse();
}

void TokenReader::parse()
{
	STATE lastState = INIT;
	for (size_t i = 0; i < str.length(); i++)
	{
		char ch = str[i];
		UpdateToken(lastState, ch);
	}
	InitToken(' ');
}

void TokenReader::UpdateToken(STATE& lastState, char ch)
{
	switch (lastState)
	{
	case INIT:
		lastState = InitToken(ch);
		break;
	case ID:
		if (isalpha(ch) || isdigit(ch))
			token.text += ch;
		else
			lastState = InitToken(ch);
		break;
	case DIGIT:
		if (isdigit(ch))
			token.text += ch;
		else
			lastState = InitToken(ch);
		break;
	case ADD:
		if (ch == '+')
		{
			token.text += ch;
			token.state = ADD;
		}
		else
			lastState = InitToken(ch);
		break;
	case MULTI:
		if (ch == '*')
		{
			token.text += ch;
			token.state = MULTI;
		}
		else
			lastState = InitToken(ch);
		break;
	case GT:
		if (ch == '=')
		{
			token.state = GT_THAN;
			token.text += ch;

			lastState = GT_THAN;
		}
		else
			lastState = InitToken(ch);
		break;
	case GT_THAN:
		lastState = InitToken(ch);
		break;
	default:
		break;
	}
}

inline STATE TokenReader::InitToken(char ch)
{
	if (token.text.length() > 0)
	{
		vecResult.push_back(token);
		token = TOKEN();
	}

	token.state = INIT;

	if (isalpha(ch))
	{
		token.state = ID;
		token.text += ch;
	}
	else if (isdigit(ch))
	{
		token.state = DIGIT;
		token.text += ch;
	}
	else if (ch == '>')
	{
		token.state = GT;
		token.text += ch;
	}
	else
	{
		token.state = INIT;
	}
	return token.state;
}

void TokenReader::Print()
{
	for (auto token : vecResult)
	{
		cout << token.text << "\t"
			<< mapEnum2Name[token.state] << endl;
	}
}

TOKEN peek() // next unit // with backup
{

}

TOKEN read() // next unit
{
	
}

TOKEN TokenReader::GetCurrentToken()
{
	return token;
}