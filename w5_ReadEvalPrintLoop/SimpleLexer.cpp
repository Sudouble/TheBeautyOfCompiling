#include "SimpleLexer.h"

ASTNode* SimpleLexer::prog(TokenReader& reader)
{
	ASTNode* node = new ASTNode("pwd", Program);

	while (reader.peek().text != "")
	{
		ASTNode* child = intDeclararion(reader);

		if (child == NULL)
		{
			child = assignment(reader);
		}

		if (child == NULL)
		{
			child = additive(reader);
		}

		if (child != NULL) {
			node->addChild(child);
		}
		else
		{
			throw ("unknown statement");
		}
	}
	return node;
}

ASTNode* SimpleLexer::assignment(TokenReader& reader)
{
	ASTNode* node = NULL;

	TOKEN token = reader.peek();
	if (token.state == Identify)
	{
		token = reader.read();		

		token = reader.peek();
		if (token.state == EQUAL)
		{
			node = new ASTNode(token.text, AssignmentStmt);

			token = reader.read();

			ASTNode* child = additive(reader);
			if (child == NULL)
			{
				throw "invalide assignment statement, expecting an expression";
			}
			else
			{
				node->addChild(child);

				// �ֺŵ�Ԥ��ȡ
				token = reader.peek();
				if (token.state == SemiColon)
				{
					token = reader.read();
				}
				else
				{
					throw "invalid statement, expecting semicolon";
				}
			}
		}
		else
		{
			reader.unread();
		}
	}

	return node;
}

// ���ͱ���������
// int a;
// int a = 3;
// int a = 2*3;
ASTNode* SimpleLexer::intDeclararion(TokenReader& reader)
{
	ASTNode* node = NULL;

	TOKEN token = reader.peek();
	if (token.state == Int)
	{
		token = reader.read();

		token = reader.peek();
		if (token.state == Identify)
		{
			token = reader.read();
			node = new ASTNode(token.text, IntDeclaration);

			token = reader.peek();
			if (token.state == EQUAL)
			{
				token = reader.read();
				ASTNode* child2 = additive(reader);
				if (child2 == NULL)
				{
					throw "invalide variable initialization, expecting an expression";
				}
				else
				{
					node->addChild(child2);
				}
			}

			// Ԥ�ȶ�ȡ�ֺ�
			token = reader.peek();
			if (token.state == SemiColon)
			{
				token = reader.read();
			}
			else
			{
				throw "invalid statement, expecting semicolon";
			}
		}
		else
		{
			throw "gramm error";
		}
	}

	return node;
}

ASTNode* SimpleLexer::additive(TokenReader& reader)
{
	// �ķ�����: add->multi | multi + int

	// �ķ�����: add->multi 
	ASTNode* child1 = multiplyDeclaration(reader);
	ASTNode* node = child1;

	if (child1 == NULL)
		return NULL;

	// �ķ�����: multi + int	
	while (true)
	{
		TOKEN token = reader.peek();
		if (token.state == ADD || token.state == MINUS)
		{
			token = reader.read();

			ASTNode* child2 = multiplyDeclaration(reader);
			if (child2 != NULL)
			{
				node = new ASTNode(token.text, Additive);
				node->addChild(child1);
				node->addChild(child2);

				child1 = node;
			}
			else
			{
				throw "invalid additive expression, expecting the right part.";
			}
		}
		else
		{
			break;
		}
	}
	return node;
}

ASTNode* SimpleLexer::multiplyDeclaration(TokenReader& reader)
{
	ASTNode* child1 = this->primary(reader);
	ASTNode* node = child1;  // �ķ�����: multi->int

	while (true)
	{
		// �ķ�����: multi * int
		TOKEN token = reader.peek();
		if (token.state == MULTI)
		{
			token = reader.read();

			TOKEN token1 = reader.peek();
			ASTNode* child2 = this->primary(reader);			
			if (child2 != NULL)
			{
				node = new ASTNode(token.text, Multiplicative);
				node->addChild(child1);
				node->addChild(child2);

				child1 = node;
			}
			else
			{
				throw "invalid multiplicative expression, expecting the right part.";
			}
		}
		else
			break;
	}

	return node;
}

ASTNode* SimpleLexer::primary(TokenReader& reader)
{
	ASTNode* node = NULL;
	TOKEN token = reader.peek();
	if (token.text == "")
		return NULL;

	if (token.state == INT_DIGIT)
	{
		token = reader.read();
		node = new ASTNode(token.text, IntLiteral);
	}
	else if (token.state == Identify)
	{
		token = reader.read();
		node = new ASTNode(token.text, Identifier);
	}
	else if (token.state == LeftParen)
	{
		TOKEN tok = reader.read();
		node = additive(reader);
		if (node != NULL)
		{
			tok = reader.peek();
			if (tok.text != "" && tok.state == RightParen)
			{
				tok = reader.read();
			}
			else
			{
				throw "expecting right parenthesis";
			}
		}
		else
		{
			throw "expecting an additive expression inside parenthesis";
		}
	}
	return node;
}
