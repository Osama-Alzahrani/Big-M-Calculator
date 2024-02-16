#include <iostream>

#include "CppConsoleTable.hpp"




using namespace std;

int iteration = 0;
bool isItMax = false;

double** table;

string* columonNames;
string* rowNames;


int mValue;
int varibles, constrains = 0, artificial, sVarible;

int leave=-1, enter = -1;

int itteration = 0;
double pivotElement;

int numberOfItteration = 1;

bool start = true;


void printTable() {
	int columnCount = artificial + sVarible + varibles + 1;
	samilton::ConsoleTable pritner(1, 1, samilton::Alignment::centre);
	
	if (itteration >= 1) {
		cout << "The ittreation number is : " << numberOfItteration++ << endl;
		pritner[0][0] = "\\";
		for (int i = 0; i < columnCount; i++)
		{
			if (i == enter+1) {
				pritner[0][i + 1] = "ENTERING";
			}
			else {
				pritner[0][i + 1] = " ";
			}
			
		}
		pritner[1][1] = "Basic";
		for (int i = 0; i < columnCount; i++)
		{
			pritner[1][i + 2] = columonNames[i];
		}
		for (int i = 0; i < constrains + 1; i++) {
			if (i == leave) {
				pritner[i+2][0] = "LEAVING";
			}
			else {
				pritner[i][0] = " ";
			}
			pritner[i + 2][1] = rowNames[i];
			for (int j = 0; j < columnCount; j++) {
				if (j == enter && i == leave) {
					pritner[i + 2][j + 2] = "["+ to_string(table[i][j]) +"]";
				}
				else {
					pritner[i + 2][j + 2] = table[i][j];
				}
				
			}
		}
	}
	else {
		if (start) {
			cout << "The ittreation number is : 0" << endl;
			start = false;
		}else {
			cout << "The ittreation number is : " << numberOfItteration++ << endl;
			cout << "\t\t\t|------- Last Tablue -------|"<< endl;
		}
		pritner[0][0] = "Basic";
		for (int i = 0; i < columnCount; i++)
		{
			pritner[0][i + 1] = columonNames[i];
		}
		for (int i = 0; i < constrains + 1; i++) {
			pritner[i + 1][0] = rowNames[i];
			for (int j = 0; j < columnCount; j++) {
				pritner[i + 1][j + 1] = table[i][j];
			}
		}
	}


	cout << pritner;
	itteration++;
}



void inital(int rows,int column) {
	table = new double* [rows];
	for (int i = 0; i < rows; ++i)
		table[i] = new double[column];

	columonNames = new string[column];
	rowNames = new string[rows];


	for (int i = 0; i < column; i++)
	{
		if (varibles > i)
		{
			columonNames[i] = "X" + to_string(i+1);
		}
		else if (sVarible + varibles > i) {
			columonNames[i] = "S" + to_string(i - varibles+1);
		}
		else if (sVarible + varibles + artificial > i) {
			columonNames[i] = "R" + to_string(i - varibles - sVarible+1);
		}
		else {
			columonNames[i] = "SOL";
		}
	}
}

void newZRow() {
	int columnCount = artificial + sVarible + varibles;
	for (int i = 0; i <= columnCount; i++) // start from 1 after Objective 0
	{

		double sum = 0;
		bool TherisR = false;
		for (int j = constrains; j > 0 ; j--)
		{
			TherisR = false;
			for (int k = sVarible + varibles; k < varibles + artificial + sVarible; k++)
			{
				if (table[j][k] == 1) {
					TherisR = true;
					break;
				}
			}
			if (!TherisR) {
				continue;
			}
			if (i >= sVarible + varibles && i < varibles + artificial+ sVarible) {
				sum += table[j][i];
			}
			else {
				sum += table[j][i]*mValue;
			}
			
		}
		if (isItMax) {
			table[0][i] = table[0][i] - sum;
		}
		else {
			table[0][i] = sum + table[0][i];
		}
		
	}
	for (int i = 0; i < artificial; i++)
	{
		table[0][sVarible + varibles +i] *= mValue;
	}
	
}

int getEntringCol() {
	int columnCount = sVarible + varibles;
	int index = 1;
	if (!isItMax) {
		int max = -1;
		for (int i = 0; i <= columnCount; i++) // start from 1 after Objective 0
		{
			
			if (max < table[0][i] && table[0][i] != 0) {
				max = table[0][i];
				index = i;
			}
			else if (max == table[0][i] && table[0][i] != 0) {
				if (sVarible + varibles >= i) {
					max = table[0][i];
					index = i;
				}
			}
		}
	}
	else {
		int min = 1;
		for (int i = 0; i <= columnCount; i++) // start from 1 after Objective 0
		{
			
			if (min > table[0][i] && table[0][i] != 0) {
				min = table[0][i];
				index = i;
			}
			else if (min == table[0][i] && table[0][i] != 0) {
				if (sVarible + varibles >= i) {
					min = table[0][i];
					index = i;
				}
			}
		}
	}

	cout << "Entering = "<< table[0][index];
	cout << endl;
	return index;

}

int getLeavingRow(int enterIndex) {
	int columnCount = sVarible + varibles;
	int index = 1;
	double min = 5000000000;
	double ratio = 0;

	int sol = artificial + sVarible + varibles;
	for (int i = 1; i <= constrains; i++) // start from 1 after Objective 0
	{
		ratio = table[i][sol] / table[i][enterIndex];
		if (min > ratio && ratio > 0) {
			min = ratio;
			index = i;
		}
	}
	

	cout << "leaving = " << table[index][enterIndex];
	cout << endl;
	return index;

}

void computePivotRow(int pivotRow,double pivotElement) {
	int columnCount = artificial + sVarible + varibles+1;
	for (int i = 0; i < columnCount; i++)
	{
		table[pivotRow][i] /= pivotElement;
	}
}

void computeAllRow(int pivotRow,int pivotCol) {
	int columnCount = artificial + sVarible + varibles + 1;
	for (int i = 0; i < constrains+1; i++)
	{
		double pivotCoeff = table[i][pivotCol];
		if (i == pivotRow) continue;
		for (int j = 0; j < columnCount; j++)
		{
			table[i][j] = table[i][j] - (pivotCoeff * table[pivotRow][j]);
		}
	}

}

void getResult() {
	int columnCount = artificial + sVarible + varibles;

	cout << "So the Result of the Big-M method is :" << endl;
	cout << "Z=" << table[0][columnCount] << endl;
	for (int i = 0; i < varibles; i++)
	{
		int found = false;
		for (int j = 0; j < constrains + 1; j++)
		{
			if (columonNames[i] == rowNames[j]) {
				cout << columonNames[i] << "=" << table[j][columnCount] << endl;
				found = true;
				break;
			}
		}
		if (!found) {
			cout << columonNames[i] << "=" << 0 << endl;
		}
	}
}

void checkCont() {
	bool endMethod = true;
	int columnCount = artificial + sVarible + varibles;


	if (isItMax) {
		for (int i = 0; i < columnCount; i++)
		{
			if (table[0][i] < 0) {
				endMethod = false;
			}
		}
	}
	else {
		for (int i = 0; i < columnCount; i++)
		{
			if (table[0][i]>0) {
				endMethod = false;
			}
		}
	}
	if (endMethod == true) {
		cout << endl;

		itteration = 0;
		printTable();

		cout << endl;

		getResult();
		exit(0);
	}
}

void computeNewRows()
{
	checkCont();
	enter = getEntringCol();

	leave = getLeavingRow(enter);

	pivotElement = table[leave][enter];

	cout << "The pivot element is: " << pivotElement << endl;


	cout << endl;

	printTable();

	cout << endl;


	rowNames[leave] = columonNames[enter];

	computePivotRow(leave, table[leave][enter]);
	computeAllRow(leave, enter);
	computeNewRows();

	
}

int main()
{
	

	char maxChar;
	cout << "||======================================================||\n";
	cout << "||===================( Big-M method )===================||\n";
	cout << "||======================================================||\n";
	cout << "\n\n\n";


	do {
		cout << " > How many varibles:";
		cin >> varibles;
	} while (varibles <= 0);
	
	do{
		cout << "\n > How many constrains:";
		cin >> constrains;
	} while (constrains <= 0);

	do {
		cout << "\n > How many constrains with (>=):";
		cin >> sVarible;
	} while (sVarible > varibles || sVarible < 0);

	do {
		cout << "\n > How many constrains with (<=):";
		cin >> artificial;
	} while (0 > (varibles - sVarible - artificial)|| artificial < 0);
	


	sVarible = sVarible + artificial;
	artificial = constrains - artificial;

	int columnCount = artificial + sVarible + varibles + 1;

	inital(constrains + 1, artificial + sVarible + 1 + varibles);



	do {
		cout << "\n > is it Max? (Y,N):";
		cin >> maxChar;
	} while (maxChar != 'N' && maxChar != 'n' && maxChar != 'Y' && maxChar != 'y');



	do {
		cout << "\n > What is the value of M (>= 100):";
		cin >> mValue;
	} while (mValue < 100);

	if (maxChar == 'N' || maxChar == 'n') {
		isItMax = false;
	}
	else {
		isItMax = true;
	}

	cout << "\n/----------------------| Objective |----------------------\\";
	for (int i = 0; i < columnCount; i++)
	{
		if (varibles > i)
		{
			cout << "\n-> Enter the coffection for x"<< i + 1 << " :";
			cin >> table[0][i];
			table[0][i] *= -1;
			
		}
		else if (sVarible+ varibles > i) {
			table[0][i] = 0;
		}
		else if (sVarible + varibles + artificial > i) {
			if (isItMax)
				table[0][i] = 1;
			else
				table[0][i] = -1;
		}
		else {
			table[0][i] =  0;
		}

	}


	
	int countS = 0;
	int countR = 0;
	rowNames[0] = "Z";
	int countNames = 1;
	for (int i = 1; i <= constrains; i++) // start from 1 after Objective 0
	{
		printf("\n/----------------------| Constraint [%d] |----------------------\\", i);
		int select;
		do {
			std::cout << "\n-> Select inequality or equality sign ([1] <= ,[2] >= ,[3] = ):";
			cin >> select;
		} while (select != 1 && select != 2 && select != 3);



		bool finishS = false;
		bool finishR = false;
		for (int j = 0; j < columnCount; j++)
		{
			
			if (varibles > j)
			{
				cout << "\n-> Enter the coffection for x" << j + 1 << " :";
				cin >> table[i][j];
			}
			else if (sVarible + varibles > j) {
				if (countS + varibles == j && finishS == false) {
					if (select == 1) {
						table[i][j] = 1;
						countS++;
						finishS = true;
						rowNames[countNames] = "S" + to_string(countS);
						countNames++;
					}
					else if (select == 2) {
						table[i][j] = -1;
						countS++;
						finishS = true;
					}else {
						table[i][j] = 0;
						
					}
					
				}else {
					table[i][j] = 0;
				}
			}
			else if (sVarible + varibles + artificial > j) {
				if (countR + sVarible + varibles == j && finishR == false) {
					if (select == 2 || select == 3) {
						table[i][j] = 1;
						countR++;
						finishR = true;
						rowNames[countNames] = "R" + to_string(countR);
						countNames++;
					}
					else {
						table[i][j] = 0;
					}
				}
				else {
					table[i][j] = 0;
				}
				
			}
			else {
				cout << "\n-> Enter the constant in the RHS:";
				cin >> table[i][j];
			}
		}
	}
	cout << endl;
	cout << endl;
	cout << "\n/====================================================================\\";
	cout << "\n|====================| Start the big-m method |=======================|";
	cout << "\n\\====================================================================/";
	cout << endl;
	cout << endl;
	cout << endl;


	printTable();

	cout << endl;

	newZRow();

	computeNewRows();
	cout << endl;

	printTable();
	cout << endl;
}