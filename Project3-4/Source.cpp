#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>


using namespace std;

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
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('U:\\Project3\\Release')");
	PyObject* my_module = PyImport_ImportModule("PythonCode");
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
	pName = PyUnicode_FromString((char*)"PythonCode");
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
	pName = PyUnicode_FromString((char*)"PythonCode");
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



void DisplayMenu() { //simple user menu display function keeps main() cleaner
	cout << "Please Make a Selection" << endl << endl;
	cout << "(1) Display All Item Frequencies" << endl;
	cout << "(2) Display Individual Item Frequency" << endl;
	cout << "(3) Display Visualization of All Items" << endl;
	cout << "(4) QUIT " << endl << endl;

}

void ClearScreen() { //clears screen for better readability
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}



int main()
{

	int userInput;
	string item;

	DisplayMenu();
	cin >> userInput;


	if (userInput == 1) {
		ClearScreen();

		CallProcedure("GetFrequency"); //will display all items once and their frequency of purchase
	}

	else if (userInput == 2) {
		cout << "Please Enter Item Name From the Following" << endl;
		CallProcedure("GetNewList"); //gets all items purchased and displays them once for user to reference
		
		cout << "\n\n\n";

		cout << "Enter Selection Here: "; //shows user where to make selection
		cin >> item; //actual user item entry

		ClearScreen();

		callIntFunc("GetIndividualFrequency", item); //displays selected item's name and purchase frequency
	}

	else if (userInput == 3) {
		ClearScreen();

		CallProcedure("CreateGraph"); //similar to option 1 but instead of numbers it displays the purchase frequency with asterisks 
	}

	else if (userInput == 4) { //simple program quit with goodbye message
		ClearScreen();

		cout << "Goodbye";

		ClearScreen();
	}

	else {
		cout << "INVALID ENTRY. PLEASE TRY AGAIN"; //displays error message if user enters anything but 1, 2, 3, or 4
	}
}
