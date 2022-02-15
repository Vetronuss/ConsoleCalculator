#include <iostream>
#include <string>
#include <cmath>
using namespace std;

void change(string &str, string find, string replacement)
{
	while(str.find(find) != string::npos)
	{
		str.replace(str.find(find),find.length(),replacement);
	}
}

void reverseStr(string& str)
{
    int n = str.length();
 
    // Swap character starting from two
    // corners
    for (int i = 0; i < n / 2; i++)
        swap(str[i], str[n - i - 1]);
}

void clean(string &str)
{
	//remove spaces
	while(str.find(" ") != string::npos)
	{
		str.erase(str.find(" "),1);
	}

	//replace -- with + and +- with - 
	change(str, "--", "+");
	change(str, "+-", "-");
	change(str, "-+", "-");

	//replace ÷ with /
	change(str, "÷", "/");

	//replace × & x & X with *
	change(str, "×", "*");
	change(str, "x", "*");
	change(str, "X", "*");
	change(str, "**", "*");

	if (str[0] == '*'
			|| str[0] == '-'
			|| str[0] == '+'
			|| str[0] == '/'
	)
	{
		str.erase(0,1);
	}

	while (str.find(")") != string::npos && str.find("(") == string::npos)
	{
		str.erase(str.find(")"),1);
	}
}

void stepCalc(string &str, char sign)
{
	str = '#' + str + '#';
	int sign_location = str.find(sign);
	string left = "";
	string right = "";
	
	//find left and right nums

	//right
	int rightIndex = 0;
	for (int i = sign_location+1; true; i++)
	{
		if (str[i] == '*' ||
				str[i] == '/' ||
				str[i] == '#' ||
				str[i] == '-' ||
				str[i] == '+'
		)
		{
			break;
		}else		
		{
			right+=str[i];
			rightIndex = i;
		}
	}
	cout << "Right: " << right << endl;

	int leftIndex = 0;
	//left
	for (int i = sign_location-1; true; i--)
	{
		if (str[i] == '*' ||
				str[i] == '/' ||
				str[i] == '#' ||
				str[i] == '-' ||
				str[i] == '+'
		)
		{
			
			break;
		}else		
		{
			left+=str[i];
			leftIndex = i;
		}
	}
	reverseStr(left);
	cout << "Left: " << stod(left) << endl;
	
	double num;
	switch(sign)
	{
		case '*':
		num = stod(left) * stod(right);

		
		break;
		case '/':
		num = stod(left) / stod(right);

		
		break;
		case '+':
		num = stod(left) + stod(right);

		
		break;
		case '-':
		num = stod(left) - stod(right);
		
		break;
	}
	
	cout << "Computer Look: "<<str << endl;

	str.replace(leftIndex, rightIndex-leftIndex+1,to_string(num));


	
	
	while(str.find('#') != string::npos)
	{
		str.erase(str.find('#'),1);
	}
}

string calc(string equation)
{
	clean(equation);
	cout << "Cleaned Equation: " << equation << endl;

	//deal with parentheses
	while (equation.find("(") != string::npos && equation.find(")") != string::npos)
	{
		
		equation.replace(equation.find("("), equation.find(")") - equation.find("("), calc(equation.substr(equation.find("(")+1,equation.find(")") + 1 - equation.find("(")-1)));
		clean(equation);
	}


	while (equation.find("*") != string::npos && equation.find("/") != string::npos)
	{
		//both / and * found
		cout << "Both dm signs found\n";
		if (equation.find("*") < equation.find("/"))
		{
			
			stepCalc(equation, '*');
			cout << "new equation: " << equation << endl;
		}else
		{
			//do / step
			stepCalc(equation, '/');
			cout << "new equation: " << equation << endl;
		}
	}
	
	while(equation.find("*") != string::npos)
	{
		//do * step
		stepCalc(equation, '*');
		cout << "new equation: " << equation << endl;
	}

	while(equation.find("/") != string::npos)
	{
		// do / step
		stepCalc(equation, '/');
		cout << "new equation: " << equation << endl;
	}

	while (equation.find("+") != string::npos && equation.find("-") != string::npos)
	{
		//both + and - found
		if (equation.find("+") < equation.find("-"))
		{
			//do + step
			stepCalc(equation, '+');
			cout << "new equation: " << equation << endl;
		}else
		{
			//do - step
			stepCalc(equation, '-');
			cout << "new equation: " << equation << endl;
		}
	}
	
	while(equation.find("+") != string::npos)
	{
		//do + step
		stepCalc(equation, '+');
		cout << "new equation: " << equation << endl;
	}

	while(equation.find("-") != string::npos)
	{
		// do - step
		stepCalc(equation, '-');
		cout << "new equation: " << equation << endl;
	}


	//make number nice
	equation = to_string(ceil(stod(equation) * 100.0) / 100.0);
	equation = equation.substr(0, equation.size()-4);
	return equation;
}

int main() {
	//pemdas calculator
  cout << calc("10*10*(100/100)+10");
} 
