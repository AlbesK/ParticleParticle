#include <Python.h>

int main() 
{
  //Py_SetProgramName("P");  /* optional but recommended */
  Py_Initialize();
  PyRun_SimpleString("from time import time,ctime\n"
                    "import matplotlib.pyplot as plt\n"
                    "print('Today is', ctime(time()))\n");
  Py_Finalize();
  return 0;
}