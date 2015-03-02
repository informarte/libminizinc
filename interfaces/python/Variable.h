#ifndef __Mzn_VARIABLEOBJECT_H
#define __Mzn_VARIABLEOBJECT_H

#include "Declaration.h"

struct MznVariable: MznDeclaration{
};

/*
inline Expression* MznObject_get_e(MznVariable* self) { return MznObject_get_e(reinterpret_cast<MznDeclaration*>(self)); }
inline void MznObject_set_e(MznVariable* self, Expression* e0) { MznObject_set_e(reinterpret_cast<MznDeclaration*>(self), e0); }
inline VarDecl* MznObject_get_vd(MznVariable* self) { return MznObject_get_vd(reinterpret_cast<MznDeclaration*>(self)); }
inline void MznObject_set_vd(MznDeclaration* self, VarDecl* vd0) { MznObject_set_vd(reinterpret_cast<MznDeclaration*>(self), vd0); }*/


static PyObject* MznVariable_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
  MznVariable* self = reinterpret_cast<MznVariable*>(type->tp_alloc(type,0));
  reinterpret_cast<MznObject*>(self)->tid = MOC_VAR;
  self->e = NULL;
  self->vd = NULL;
  return reinterpret_cast<PyObject*>(self);
}

static void MznVariable_dealloc(MznVariable* self) {
  Py_TYPE(self)->tp_free(reinterpret_cast<PyObject*>(self));
}


static PyTypeObject MznVariable_Type = {
  PyVarObject_HEAD_INIT(NULL,0)
  "minizinc.Variable",       /* tp_name */
  sizeof(MznVariable),          /* tp_basicsize */
  0,                         /* tp_itemsize */
  (destructor)MznVariable_dealloc, /* tp_dealloc */
  0,                         /* tp_print */
  0,                         /* tp_getattr */
  0,                         /* tp_setattr */
  0,                         /* tp_reserved */
  0,                         /* tp_repr */
  0,                         /* tp_as_number */
  0,                         /* tp_as_sequence */
  0,                         /* tp_as_mapping */
  0,                         /* tp_hash  */
  0,                         /* tp_call */
  0,                         /* tp_str */
  0,                         /* tp_getattro */
  0,                         /* tp_setattro */
  0,                         /* tp_as_buffer */
  Py_TPFLAGS_DEFAULT,        /* tp_flags */
  "Minizinc Variable (derived from MznDeclaration)",  /* tp_doc */
  0,                         /* tp_traverse */
  0,                         /* tp_clear */
  0,                         /* tp_richcompare */
  0,                         /* tp_weaklistoffset */
  0,                         /* tp_iter */
  0,                         /* tp_iternext */
  0,            /* tp_methods */
  0,            /* tp_members */
  0,/*MznVariable_getseters,        /* tp_getset */
  &MznDeclaration_Type,                         /* tp_base */
  0,                         /* tp_dict */
  0,                         /* tp_descr_get */
  0,                         /* tp_descr_set */
  0,                         /* tp_dictoffset */
  0,    /* tp_init */
  0,                         /* tp_alloc */
  MznVariable_new,                /* tp_new */
  0,                         /* tp_free */
};



#endif