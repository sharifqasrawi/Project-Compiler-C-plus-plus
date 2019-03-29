#include <iostream>
using std::cout;
using std::endl;
using std::cin;
/* 
	ISE CMPP S15 
	Students:
	mohammad_sharif_50753
	majd_55856 
*/

#include "ast.h"

extern int yylex();
extern int yyerror(const char *);
extern int yyparse();
extern int yydebug;
extern SymbolTable *symbolTable;
extern Root *root;
Errors *errors;

int main()
{
	yydebug = 0;

	errors = new Errors;
	symbolTable = new SymbolTable(errors);
	
	cout << "\t\t\t     MINI-JAVA Compiler\n\t\t\t     ******************\n\n\n";
	
	//Syntax analysing
	yyparse();

	if (symbolTable->errors->errors->size() > 0)
	{
		symbolTable->errors->printError();
	}
	else
	{
		TypeCheck *tc = new TypeCheck;
		tc->symbolTable = symbolTable;
		root->accept(tc);
		if (tc->symbolTable->errors->errors->size() > 0)
		{
			tc->symbolTable->errors->printError();
		}
		else
		{
			cout << "\nNo Semantic Errors Found." << endl;
			CodeVisitor *cv = new CodeVisitor(root, tc->MainFunc, tc->globals);
			root->accept(cv);
		}
	}

	return 1;
}
