#pragma once
#include<iostream>
#include <string>
#include<vector>
using namespace std;
class parser
{
public:
	parser();
	~parser();
	
	


	
public : int currentTokenIndex;
		vector<string>v1;


		void program()
		{
			stmtSequence();
			cout << "Program found" << endl;
		}
		void stmtSequence()
		{
			statement();
			while (v1[currentTokenIndex] == ";")
			{
				match(";");
				statement();
			}
			cout << "Stmt Sequence found" << endl;
		}
		void statement()
		{
			if (v1[currentTokenIndex] == "if")
			{
				ifStmt();
			}
			else if (v1[currentTokenIndex] == "repeat")
			{
				repeatStmt();
			}
			else if (v1[currentTokenIndex] == "identifier")
			{
				assignStmt();
			}
			else if (v1[currentTokenIndex] == "read")
			{
				readStmt();
			}
			else {
				writeStmt();
			}
			cout << "statement found" << endl;

		}
		void ifStmt()
		{
			if (v1[currentTokenIndex] == "if")
			{
				match("if");
				exp();
				if (v1[currentTokenIndex] == "then")
				{
					match("then");
					stmtSequence();
					while (v1[currentTokenIndex] == "else") {
						match("else");
						stmtSequence();
					}
					if (v1[currentTokenIndex] == "end")
					{
						match("end");
					}
				}
			}
			cout << "if statement found" << endl;
		}
		void repeatStmt()
		{
			if (v1[currentTokenIndex] == "repeat")
			{
				match("repeat");
				stmtSequence();
				if (v1[currentTokenIndex] == "until")
				{
					exp();
				}

			}
			cout << "repeat statement found" << endl;
		}
		void assignStmt()
		{
			if (v1[currentTokenIndex] == "identifier")
			{
				match("identifier");
				if (v1[currentTokenIndex] == ":")
				{
					match(":");
					if (v1[currentTokenIndex] == "=")
					{
						match("=");
						exp();
					}
				}
			}
			cout << "assign statement found" << endl;
		}
		void readStmt()
		{
			if (v1[currentTokenIndex] == "read")
			{
				match("read");
				if (v1[currentTokenIndex] == "identifier")
					match("identifier");
			}
			cout << "read statement found" << endl;
		}
		void writeStmt()
		{
			if (v1[currentTokenIndex] == "write")
			{
				match(v1[currentTokenIndex]);
				exp();
			}
			cout << "write statement found" << endl;
		}
		void exp()
		{
			simpleExp();
			while (v1[currentTokenIndex] == "<" || v1[currentTokenIndex] == "=")
			{
				match(v1[currentTokenIndex]);
				comparisonOp();
				simpleExp();
			}
			cout << "exp statement found" << endl;
		}
		void comparisonOp()
		{
			if (v1[currentTokenIndex] == "<" || v1[currentTokenIndex] == "=")
				match(v1[currentTokenIndex]);
			cout << "comparison operation found" << endl;
		}
		void simpleExp()
		{
			term();
			while (v1[currentTokenIndex] == "+" || v1[currentTokenIndex] == "-")
			{
				match(v1[currentTokenIndex]);
				term();
			}cout << "simple Exp found" << endl;
		}
		void addOp()
		{
			if (v1[currentTokenIndex] == "+" || v1[currentTokenIndex] == "-")
			{
				match(v1[currentTokenIndex]);
			}
			cout << "addOp found" << endl;
		}
		void term()
		{
			factor();
			if (v1[currentTokenIndex] == "+" || v1[currentTokenIndex] == "-")
			{
				match(v1[currentTokenIndex]);
			}
			cout << "term found" << endl;
		}
		void mulOp()
		{
			if (v1[currentTokenIndex] == "*" || v1[currentTokenIndex] == "/")
			{
				match(v1[currentTokenIndex]);
			}
			cout << "mul found" << endl;
		}
		void factor()
		{
			if (v1[currentTokenIndex] == "(")
			{
				match(v1[currentTokenIndex]);
				exp();
				if (v1[currentTokenIndex] == ")")
				{
					match(v1[currentTokenIndex]);
				}
			}
			else if (v1[currentTokenIndex] == "number")
				match(v1[currentTokenIndex]);
			else
				match(v1[currentTokenIndex]);
			cout << "factor found" << endl;
		}

		void match(string s)
		{
			currentTokenIndex++;
		}

	};


