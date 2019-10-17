#include "TokenReader1.h"


TokenReader::TokenReader(string str_)
{
	str = str_;

	mapEnum2Name[INIT] = "INIT";
	mapEnum2Name[Identify] = "ID";
	mapEnum2Name[Int] = "Int";
	mapEnum2Name[SemiColon] = "SemiColon";
	mapEnum2Name[INT_DIGIT] = "DIGIT";
	mapEnum2Name[MULTI] = "MULTI";
	mapEnum2Name[ADD] = "ADD";
	mapEnum2Name[EQUAL] = "EQUAL";
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
	case Identify:
		if (isalpha(ch) || isdigit(ch))
			token.text += ch;
		else
			lastState = InitToken(ch);
		break;
	case INT_DIGIT:
		if (isdigit(ch))
			token.text += ch;
		else
			lastState = InitToken(ch);
		break;
	case ID_Int1:
		if (ch == 'n')
		{
			lastState = ID_Int2;
			token.text += ch;
		}
		else if (isalpha(ch) || isdigit(ch))
		{
			token.state = Identify;
			token.text += ch;
		}
		else
		{
			lastState = InitToken(ch);
		}
		break;
	case ID_Int2:
		if (ch == 't')
		{
			lastState = ID_Int3;
			token.text += ch;
		}
		else if (isalpha(ch) || isdigit(ch))
		{
			token.state = Identify;
			token.text += ch;
		}
		else
		{
			lastState = InitToken(ch);
		}
		break;
	case ID_Int3:
		if (isblank(ch))
		{
			token.state = Int;
			InitToken(ch);
		}
		else
		{
			lastState = Identify;
			
			token.state = Identify;
			token.text += ch;
		}
		break;
	case ADD:
	case MINUS:
	case EQUAL:
	case SemiColon:
	case MULTI:
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
		if (ch == 'i')
			token.state = ID_Int1;
		else
			token.state = Identify;
		token.text += ch;
	}
	else if (isdigit(ch))
	{
		token.state = INT_DIGIT;
		token.text += ch;
	}
	else if (ch == '+')
	{
		token.state = ADD;
		token.text += ch;
	}
	else if (ch == '-')
	{
		token.state = MINUS;
		token.text += ch;
	}
	else if (ch == ';')
	{
		token.state = SemiColon;
		token.text += ch;
	}
	else if (ch == '=')
	{
		token.state = EQUAL;
		token.text += ch;
	}
	else if (ch == '*')
	{
		token.state = MULTI;
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

TOKEN TokenReader::peek() // next unit // with backup
{
	if (currentPos < vecResult.size())
		return vecResult[currentPos];
	return TOKEN();
}

TOKEN TokenReader::read() // next unit
{
	if (currentPos < vecResult.size())
		return vecResult[currentPos++];
	return TOKEN();
}

void TokenReader::unread()
{
	if (currentPos > 0)
		currentPos--;
}

int TokenReader::GetCurrentToken()
{
	return currentPos;
}

