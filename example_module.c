#include <Python.h>



//Actual module method definition.
static PyObject*
print_stdout(PyObject *self, PyObject *args) {
    // Print C-string in Python environment e.g. jupyter notebook & shell.
    // C-native "printf" will also work, but only in shell environment.
    PySys_WriteStdout("This is python-native stdout!\n");
    Py_RETURN_NONE; // This function doesn't return anything.
}
static PyObject*
parse_postional_arguments(PyObject *self, PyObject *args) {
    // Define c values to parse into.
    int64_t a;
    double b;
    char *c;
    // Parsing arguments syntax: https://docs.python.org/3/c-api/arg.html
    uint8_t ok = PyArg_ParseTuple(args, "Lds", &a, &b, &c); // Returns 1 or 0.
    if (!ok) { return NULL; } // Return error if 0.
    printf("a (int)    = %" PRId64 "\n", a);
    printf("b (float)  = %lf\n", b);
    printf("a (string) = %s\n", c);
    Py_RETURN_NONE;
}
static PyObject*
parse_named_arguments(PyObject *self, PyObject *args, PyObject *kwargs) {
    // Parse named aguments of a function.
    // As of Python3.6 all named arguments should also be optional.

    int64_t a = 0; // Supplied with default value.
    double b = 3.1415;
    char *c = NULL;

    static char *kwlist[] = {"a", "b", "c", NULL};
    // Use "|$Lds" to disable using as positional.
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "|Lds", kwlist, &a, &b, &c)) {
        return NULL;
    }
    printf("a (int)    = %" PRId64 "\n", a);
    printf("b (float)  = %lf\n", b);
    printf("a (string) = %s\n", c);
    Py_RETURN_NONE;
}
static PyObject*
parse_positional_and_named_arguments(PyObject *self, PyObject *args, PyObject *kwargs) {
    // Parse positional & named aguments of a function.

    char *a; // Positional
    char *b; // Positional
    char *foo = NULL; // Keyword
    char *bar = NULL; // Keyword
    char *baz = NULL; // Keyword

    // "a" and "b" must be included here.
    static char *kwlist[] = {"a", "b", "foo", "bar", "baz", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ss|sss", kwlist, &a, &b, &foo, &bar, &baz)) {
        return NULL;
    }

    printf("a is %s\n", a);
    printf("b is %s\n", b);
    printf("foo is %s\n", foo);
    printf("bar is %s\n", bar);
    printf("baz is %s\n", baz);

    Py_RETURN_NONE;
}
static PyObject*
parse_iterable(PyObject *self, PyObject *args) {
    // Parse an object that can be iterated e.g. list or tuple.
    // This function only understand python floats inside iterable.

    PyObject* obj;
    if (!PyArg_ParseTuple(args, "O", &obj)) { return NULL; }     // Parse an object from tuple.
    PyObject* seq = PySequence_Fast(obj, "expected a sequence"); // Parse sequence object. Provide error message.
    Py_ssize_t len = PySequence_Length(seq);                     // Get size of the sequence.
    if (len == -1) { return NULL; }
    
    PyObject* item;
    double num;
    for (Py_ssize_t i = 0; i < len; i++) {
        item = PySequence_Fast_GET_ITEM(seq, i);
        num = PyFloat_AsDouble(item);            // returns -1 on error. raises TypeError in python.
        // check PyErr_Occurred()
        printf("%lf ", num);
    }

    printf("\n");

    // Decrease reference counts for created PyObject objects.
    // Don't Py_DECREF(item) !
    Py_DECREF(obj); 
    Py_DECREF(seq);

    Py_RETURN_NONE;
}
static PyObject* // TODO
parse_dictionary(PyObject *self, PyObject *args) {
    // Parse dictionary.
    // Return dictionary keys as a list of strings.
    Py_RETURN_NONE;
}
static PyObject* // TODO
iterate_dictionary(PyObject *self, PyObject *args) {
    // Iterate dictionary keys.
    // Print number of PyNone, PyInt, PyFloat, PyStr, PyBool.
    Py_RETURN_NONE;
}
static PyObject* // TODO
build_value(PyObject *self, PyObject *args) {
    // Returns sum of two integers.
    int64_t a, b;
    uint8_t ok = PyArg_ParseTuple(args, "ll", &a, &b);
    if (!ok) { return NULL; } // Return error if ok == 0.

    return Py_BuildValue("i", a + b);
}
static PyObject* // TODO
trigger_exception(PyObject *self, PyObject *args) {
    // Trigger custom exception.
    Py_RETURN_NONE;
}



// Method definition.
static PyMethodDef module_methods[] = {
    {
        "print_stdout",                         // Name of function to call from Python.
        print_stdout,                           // Name of the function in C code.
        METH_NOARGS,                            // Takes no arguments.
        "Print C-string in Python environment." // Docstring.
    },
    {
        "parse_postional_arguments",
        parse_postional_arguments,
        METH_VARARGS,                // Takes positional arguments.
        "Parse int, float, str."
    },
    {
        "parse_named_arguments",
        (PyCFunction) parse_named_arguments,            // Explicit casting to PyCFunction when passing PyObject *kwargs.
        METH_VARARGS | METH_KEYWORDS,                   // Takes named arguments.
        "Parse optional named or positional arguments."
    },
    {
        "parse_positional_and_named_arguments",
        (PyCFunction) parse_positional_and_named_arguments,
        METH_VARARGS | METH_KEYWORDS,                                  // Takes both positional and named arguments.
        "Parse positional and optional named or positional arguments."
    },
    {
        "parse_iterable",
        parse_iterable,
        METH_VARARGS,                                                             // Takes both positional and named arguments.
        "Parse iterable object. Such as a list/set/tuple. Expects python floats."
    },
    {NULL, NULL, 0, NULL}
};



// Module definition.
static struct PyModuleDef
module_definition = {
    PyModuleDef_HEAD_INIT,
    "example_module",
    "Example module description.",
    -1,
    module_methods
};



// Module initialization. Must be named PyInit_[[your_module_name]] exactly.
PyMODINIT_FUNC PyInit_example_module(void) {
    Py_Initialize();
    return PyModule_Create(&module_definition);
}
