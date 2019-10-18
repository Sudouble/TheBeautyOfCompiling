lexer grammar Hello;  //lexer �ؼ�����ζ������һ���ʷ������ļ��������� Hello��Ҫ���ļ�����ͬ

// �ؼ���
If :               'if';
Int :              'int';

// ������
IntLiteral:        [0-9]+;
StringLiteral:      '"' .*? '"' ;  // �ַ���������

// ������
AssignmentOP:       '=' ;    
RelationalOP:       '>'|'>='|'<' |'<=' ;    
Star:               '*';
Plus:               '+';
Sharp:              '#';
SemiColon:          ';';
Dot:                '.';
Comm:               ',';
LeftBracket :       '[';
RightBracket:       ']';
LeftBrace:          '{';
RightBrace:         '}';
LeftParen:          '(';
RightParen:         ')';

// ��ʶ��
Id :                [a-zA-Z_] ([a-zA-Z_] | [0-9])*;

// �հ��ַ�������
Whitespace:         [ \t]+ -> skip;
Newline:            ( '\r' '\n'?|'\n')-> skip;
