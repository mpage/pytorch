#include <Python.h>

namespace torch::autograd {

extern PyObject* THPVariableFunctionsModule;

// Wrapper converts a raised TypeError into returning NotImplemented
// Used to implement binary arithmetic operators
template <PyObject* (*Func)(PyObject*, PyObject*, PyObject*)>
inline PyObject* TypeError_to_NotImplemented_(
    PyObject* self,
    PyObject* args,
    PyObject* kwargs) {
  PyObject* ret = Func(self, args, kwargs);
  if (!ret && PyErr_ExceptionMatches(PyExc_TypeError)) {
    PyErr_Clear();
    Py_INCREF(Py_NotImplemented);
    ret = Py_NotImplemented;
  }
  return ret;
}

// METH_FASTCALL | METH_KEYWORDS variant
template <
    PyObject* (*Func)(PyObject*, PyObject* const*, Py_ssize_t, PyObject*)>
inline PyObject* TypeError_to_NotImplemented_(
    PyObject* self,
    PyObject* const* args,
    Py_ssize_t nargs,
    PyObject* kwnames) {
  PyObject* ret = Func(self, args, nargs, kwnames);
  if (!ret && PyErr_ExceptionMatches(PyExc_TypeError)) {
    PyErr_Clear();
    Py_INCREF(Py_NotImplemented);
    ret = Py_NotImplemented;
  }
  return ret;
}

void initTorchFunctions(PyObject* module);

} // namespace torch::autograd
