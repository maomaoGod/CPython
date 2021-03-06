#include <Python.h>
#include <iostream>
#include <exception>
#include <string>
using namespace std;

#pragma comment(lib,"python35")

void errormessage(PyObject* pValue,PyObject *pError){
	string strErrorMsg;
	PyObject *type_obj = NULL, *value_obj = NULL, *traceback_obj = NULL;
	if (NULL == pValue&&NULL != pError){
	
		PyErr_Fetch(&type_obj, &value_obj, &traceback_obj);
		if (value_obj == NULL)
			return ;
		strErrorMsg.clear();
		PyErr_NormalizeException(&type_obj, &value_obj, 0);
		if ((PyObject_Str(value_obj)))
		{
			strErrorMsg = PyUnicode_AsUTF8(PyObject_Str(value_obj));
		}

	}

	cout << strErrorMsg << endl;

	Py_XDECREF(type_obj);
	Py_XDECREF(value_obj);
	Py_XDECREF(traceback_obj);
}

void importClassModule(){
	if (false == Py_IsInitialized())
		return;
	PyObject* pName = NULL;
	PyObject* pMod = NULL;
	PyObject* pError = NULL;
	PyObject* pDict = NULL;
	PyObject* pClass = NULL;
	PyObject* pInstance = NULL;
	PyObject* pParam = NULL;
	PyObject* pResult = NULL;

	pName = PyUnicode_FromString("Geometry");

	//add dependent path
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('.')");

	pMod = PyImport_Import(pName);
	pError = PyErr_Occurred();
	errormessage(pMod, pError);

	//get dict attribute
	pDict = PyModule_GetDict(pMod);
	pError = PyErr_Occurred();
	errormessage(pMod, pError);

	//get the class from the module
	pClass = PyDict_GetItemString(pDict, "ClockTimer");
	pError = PyErr_Occurred();
	errormessage(pMod, pError);

	//get the instance
	//pInstance = PyInstanceMethod_New(pClass);
	pInstance = PyObject_CallObject(pClass, NULL);
	pError = PyErr_Occurred();
	errormessage(pMod, pError);

	//exec the func
	pResult = PyObject_CallMethod(pInstance, "start", "()");
	pError = PyErr_Occurred();
	errormessage(pResult, pError);

	pResult = PyObject_CallMethod(pInstance, "stop", "()");
	pError = PyErr_Occurred();
	errormessage(pResult, pError);
}

int get_addmethod(int a, int b){
	if (false == Py_IsInitialized())
		return -1;

	int res;
	PyObject *pModule = NULL, *pMoudleName = NULL, *pFunc = NULL;
	PyObject *pArgs = NULL, *pValue = NULL,*pError = NULL;

	/* import */
	try
	{
		pMoudleName = PyUnicode_FromString("testmodel");
	}
	catch (exception* e)
	{
		e->what();
	}

	if (NULL != PyErr_Occurred()){

	}

	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('.')");
	
	pModule = PyImport_Import(pMoudleName);
	pError = PyErr_Occurred();
	errormessage(pModule, pError);
	/* great_module.great_function */
	pFunc = PyObject_GetAttrString(pModule, "add_integer");
	pError = PyErr_Occurred();
	errormessage(pFunc, pError);
	/* build args */
	pArgs = Py_BuildValue("ii", a, b);
	//pArgs = PyTuple_New(2);
	//PyTuple_SetItem(pArgs, 0, Py_BuildValue("i", a));
	//PyTuple_SetItem(pArgs, 1, Py_BuildValue("i", b));

	
	/* call */
	pValue = PyObject_CallObject(pFunc, pArgs);
	pError = PyErr_Occurred();
	
	res = PyLong_AsLong(pValue);

	return res;
}

int main(int argc, char*argv[]){
	wchar_t *progname = Py_DecodeLocale(argv[0],NULL);
	//Py_SetProgramName(progname);
	Py_Initialize();

	PyRun_SimpleString("print('Hello World!')\n");
	

	cout << get_addmethod(11, 12) << endl;

	importClassModule();

	PyMem_RawFree(progname);
	cin.get();
	Py_Finalize();
	return 0;
}