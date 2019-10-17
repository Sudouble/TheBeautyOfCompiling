#include "SimpleLexer.h"

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
		if (token.state == ADD)
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
	TOKEN token = reader.peek();
	if (token.state == DIGIT)
	{
		// �ķ�����: multi->int | multi * int
		token = reader.read();
		ASTNode* child1 = new ASTNode(token.text, IntLiteral);
		ASTNode* node = child1;  // �ķ�����: multi->int

		while (true)
		{
			// �ķ�����: multi * int
			TOKEN token = reader.peek();
			if (token.state == MULTI)
			{
				token = reader.read();

				TOKEN token1 = reader.peek();
				ASTNode* child2 = NULL;
				if (token1.state == DIGIT)
				{
					token1 = reader.read();
					child2 = new ASTNode(token1.text, IntLiteral);
				}
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
	
	return nullptr;
}
