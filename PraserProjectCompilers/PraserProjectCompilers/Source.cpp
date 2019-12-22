#include<iostream>
#include <string>
#include<vector>
#include<fstream>
using namespace std;

class parser {
public :int currentTokenIndex;
		int numberOfTokens;
		vector<string>v1;
		ofstream out;
		vector<string> ReservedWords;

		parser() {
			ReservedWords=initReserved();
			openOutputStream(&out);
			currentTokenIndex = 0;
			
		}
		vector<string> initReserved()
		{
			
			ReservedWords.push_back("if");
			ReservedWords.push_back("then");
			ReservedWords.push_back("else");
			ReservedWords.push_back("end");
			ReservedWords.push_back("repeat");
			ReservedWords.push_back("until");
			ReservedWords.push_back("read");
			ReservedWords.push_back("write");
			return ReservedWords;

		}
		bool searchReserved(string word, vector<string> ReservedWords)
		{
			for (int i = 0; i < ReservedWords.size(); i++)
				if (word == ReservedWords[i])
					return true;
			return false;
		}
		void openOutputStream(ofstream* out)
		{
			out->open("parser_output.txt");
		}
		void program()
		{
			stmtSequence();
			cout << currentTokenIndex << endl;
			cout << v1.size();
			if(currentTokenIndex!=v1.size()-1)
			{
				out << "ERROR program" << endl;
				exit(0);
			}

			out << "Program found" << endl;
			out.flush();
			out.close();
		}
		/*
		read x 
		x=asdasjd;
		*/
		void stmtSequence()
		{
			cout << "stmtsequence began" << endl;
			statement();
			while (v1[currentTokenIndex] == ";")
			{
				match(";");
				statement();
			}
			//out << "Stmt Sequence found" << endl;
		}
		void statement()
		{
			cout << "statement began" << endl;
			if (v1[currentTokenIndex] == "if")
			{
				cout << "inside statement " << endl;
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
			else if(v1[currentTokenIndex]=="write")
			{
				writeStmt();
			}
			else
			{
				out << "ERROR statement" << endl;
				exit(0);
			}

			
			
			//out << "statement found" << endl;
			out.flush();
			cout << "at the end of statement" << endl;

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
					else
					{
						out << "ERROR no end" << endl;
						exit(0);
					}
					
					
				}
				else
				{
					out << "ERROR" << endl;
					exit(0);
				}
			}
			else
			{
				out << "ERROR if statement" << endl;
				exit(0);
			}
		out << "if statement found" << endl;
		}
		void repeatStmt()
		{
			if (v1[currentTokenIndex] == "repeat")
			{
				match("repeat");
				stmtSequence();
				if (v1[currentTokenIndex] == "until")
				{
					match("until");
					exp();
				}
				else
				{
					out << "ERROR" << endl;
					exit(0);
				}

			}
			out << "repeat statement found" << endl;
		}
		void assignStmt()
		{
			if (v1[currentTokenIndex] == "identifier")
			{
				match("identifier");
				if (v1[currentTokenIndex] == ":=")
				{
					match(":=");
					exp();
					/*if (v1[currentTokenIndex] == "=")
					{
						match("=");
						exp();
					}*/
				}
				else
				{
					out << "ERROR" << endl;
					exit(0);
				}
			}
			else
			{
				out << "ERROR assignment" << endl;
				exit(0);
			}
			out << "assign statement found" << endl;
		}
		void readStmt()
		{
			if (v1[currentTokenIndex] == "read")
			{
				match(v1[currentTokenIndex]);
				if (v1[currentTokenIndex] == "identifier")
					match("identifier");
				else
				{
					out << "ERROR" << endl;
					exit(0);
				}
				

			}
			out << "read statement found" << endl;
		}
		void writeStmt()
		{
			if (v1[currentTokenIndex] == "write")
			{
				match(v1[currentTokenIndex]);
				exp();
			}
			else
			{
				out << "ERROR write" << endl;
				exit(0);
			}
			out << "write statement found" << endl;
		}
		void exp()
		{
			simpleExp();
			if(v1[currentTokenIndex] == "<" || v1[currentTokenIndex] == "=")
			{
				match(v1[currentTokenIndex]);
				//comparisonOp();
				simpleExp();
			}
			
			//out << "exp statement found" << endl;
		}
		void comparisonOp()
		{
			if (v1[currentTokenIndex] == "<" || v1[currentTokenIndex] == "=")
				match(v1[currentTokenIndex]);
			
			//out << "comparison operation found" << endl;
		}
		void simpleExp()
		{
			term();
			while (v1[currentTokenIndex] == "+" || v1[currentTokenIndex] == "-")
			{
				match(v1[currentTokenIndex]);
				term();
			}
			//out << "simple Exp found" << endl;
		}
		void addOp()
		{
			if (v1[currentTokenIndex] == "+" || v1[currentTokenIndex] == "-")
			{
				match(v1[currentTokenIndex]);
			}
			
			//out << "addOp found" << endl;
		}
		void term()
		{
			factor();
			while (v1[currentTokenIndex] == "*" || v1[currentTokenIndex] == "/")
			{
				match(v1[currentTokenIndex]);
				factor();
			}
			
			//out << "term found" << endl;
		}
		void mulOp()
		{
			if (v1[currentTokenIndex] == "*" || v1[currentTokenIndex] == "/")
			{
				match(v1[currentTokenIndex]);
			}
			
			//out << "mul found" << endl;
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
				else
				{
					out << "ERROR" << endl;
					exit(0);
				}
			}
			else if (v1[currentTokenIndex] == "number")
				match(v1[currentTokenIndex]);
			else //if(v1[currentTokenIndex]=="identifier")
				match(v1[currentTokenIndex]);
			/*else
			{
				out << "ERROR factor" << endl;
				exit(0);
			}*/
			//out << "factor found" << endl;
		}

		void match(string s)
		{


			/*
			if(s=="v1[currentTokenIndex]")
				currentTokenIndex++;
				else exit();
			
			
			
			*/
			/*
			if(s==v1[currentTokenIndex]
			*/
			if (currentTokenIndex < v1.size())
			{
				/*if (v1[currentTokenIndex] == "end") {}
				else */
					if (currentTokenIndex == v1.size() - 1) {}
					else currentTokenIndex++;
			}
			else {
				out << "ERROR asdasldkahsdkja" << endl;
				exit(0);
				
			}
		}

	};

int main()
{
	cout << "main begins" << endl;
	parser p;
	string str;
	string s;
	int begin=0;
	int end=0;
	int numberOfWords = 0;
	ofstream out;
	
	ifstream in;
	in.open("scanner_output.txt");
	cout << "file opened" << endl;
	if (in.is_open())
	{
		cout << "file opened for sure" << endl;
		try {
			while (in)
			{
				cout << "sdasdasdasd" << endl;
				getline(in, s);
				if (s.empty())
					continue;
				//cout << s << endl;
				//delete everything after the ":"

				begin = s.find(":");
				if (s[begin + 1] == '=')
				{
					begin = 3;
					//cout << "ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss" << endl;
				}

				end = s.length();//the erase method erase all the characters including the begin and doesn't include the end ;
				s.erase(begin, end);
				//cout << s << endl;
				//check if the first character is a letter so it's either a reserved word or it is an identifier , if it is an indentifier it will change it to 
				//"identifier" else it will leave it alone 
				if ((s.substr(0, 1) >= "A" && s.substr(0, 1) <= "Z")
					|| (s.substr(0, 1) >= "a" && s.substr(0, 1) <= "z"))
				{
					end = s.find_first_of(" ");
					s = s.substr(0, end);
					if (p.searchReserved(s, p.ReservedWords)) { /*cout << "is a reserved word";*/ }
					else
						s = "identifier";
				}
				else if ((s.substr(0, 1) >= "0" && s.substr(0, 1) <= "9"))
					s = "number";
				str += s;
				str += " ";
				cout << s << endl;
				numberOfWords++;
				cout << "tamaam " << endl;
			}
		}catch(...)
		{
			cout << "handled exception in the while loop" << endl;
		}
		
	}

	else
		cout << "file didn't open"<<endl;
	cout << "5alasna el while loop" << endl;
	// le3'ayet hena ana 3andi string str fih kol 7aga mazboota
	for(int i = 0 ;i<numberOfWords;i++)
	{
		cout << "for loop" << endl;
		//delete spaces in the beginning of the word
		while (str.substr(0, 1) == " ")
			str.erase(0, 1);
		end = str.find_first_of(" ");
		(p.v1).push_back(str.substr(0, end));
		str.erase(0, end);
	}
	cout << "after for loop" << endl;
	cout << str << endl;
	cout << "eli da5el 3ala el parser is " << endl;
	for (int i = 0; i < p.v1.size(); i++)
	{
		cout <<" ------->"<<p.v1[i] << endl;
	}
	p.numberOfTokens = numberOfWords;
	p.openOutputStream(&out);
	p.program();
	



}
