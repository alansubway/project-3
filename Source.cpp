#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

int choice;
string item;
int itemNum;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PY_Code");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PY_Code");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PY_Code");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}


//function to display the histogram
void displayHistogram() {

	//ifstream is strictly for reading the file
	ifstream Hist("frequency.dat");

	//checks to make sure file is open.
	if (Hist.is_open()) {

		//varibles for handling the frequency.dat file
		string num;
		int num2 = 0;
		string name;
		int i;


		//keeps looping the file until the end is reached
		while (Hist) {
			getline(Hist, name, ' ');
			getline(Hist, num);

			//converts the string num to a int num2
			num2 = stoi(num);
			
			cout << name << " ";
			
			
			//uses the num2 to print the number of symbols
			for (i = 0; i < num2; i++) {
				cout << "~";
			}

			cout << endl;

		}
		
		//closes the file
		Hist.close();
	}

}

void menuChoice() {
	cout << endl;
	cout << "Enter a choice: ";
	cin >> choice;
	cout << endl;
	system("CLS");
	//switch to filter choices and run different functions
	switch (choice) {
	case 1: (choice == 1);
		CallProcedure("printlist");
		system("pause");
		system("CLS");
		break;
	case 2: (choice == 2);
		cout << "Enter an item you are looking for: ";
		cin >> item;
		cout << endl;
		itemNum = callIntFunc("getSpecificItem", item);

		cout << item << " was purchased " << itemNum << " times." << endl;
		system("pause");
		system("CLS");

		break;
	case 3: (choice == 3);
		CallProcedure("getHistogram");
		cout << "Press enter to display the Histogram" << endl;
		system("pause");
		system("CLS");

		displayHistogram();

		system("pause");
		system("CLS");
		break;
	case 4: (choice == 4);
		cout << "Goodbye" << endl;
		system("pause");
		break;
	default:
		cout << "Enter a valid choice" << endl;
		break;

	}
	
}




//Menu to be displayed each time a user selects a choice unless option 4 is selected
void menu() {
	cout << "1: List of all items purchaced" << endl;
	cout << "2: How many time a item was purchased" << endl;
	cout << "3: Create a histogram text document" << endl;
	cout << "4: Exit the program" << endl;
}


// only calls two functions to control whole application

void main() {
	while (choice != 4) {
		menu();
		menuChoice();

	}
	return;
}