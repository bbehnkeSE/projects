#include <iostream>
#include <Python.h>

int main()
{
    Py_Initialize();
    PyObject *sysPath = PySys_GetObject("path");
    PyList_Append(sysPath, PyUnicode_FromString("."));

    // Load module
    PyObject *pName   = PyUnicode_FromString("callee");
    PyObject *pModule = PyImport_Import(pName);

    if(pModule != NULL)
    {
        std::cout << "Python module found.\n";

        // Load all module level attributes as a dictionary
        PyObject *pDict = PyModule_GetDict(pModule);
        PyObject *pFunc = PyDict_GetItem(pDict, PyUnicode_FromString("test_print"));

        if(pFunc != NULL)
            PyObject_CallObject(pFunc, NULL);
        else
            std::cout << "Can't find function.\n";
    }
    else
        std::cout << "Can't find module.\n";

    return EXIT_SUCCESS;
}