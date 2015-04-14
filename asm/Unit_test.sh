#!/bin/bash
#Check if binary exist
echo -e "Test 01 : Binary research:\n"
if test -e asm; then
  echo -e "Executable asm found\n"
else
  echo -e "Executable asm not found\n" >&2
  exit 1
fi

#Launch asm without arguments
echo -e "Test 02 : Without arguments:\n"
output=$(./asm 3>&1 1>&2 2>&3 | tee /dev/stderr)
if test "$output" = "Usage : ./asm [file to compil]"; then
  echo -e  "Ok\n"
else
  echo -e "Fail\n" >&2
  exit 1
fi

#Launch asm with empty file
echo -e "Test 03 : With a empty file:\n"
output=$(./asm ./champions/empty 3>&1 1>&2 2>&3 | tee /dev/stderr)
if test "$output" = "[31;1mError :[0m can't perform open(./champions/empty).
[31;1mError :[0m \"./champions/empty\" assembly failed."; then
  echo -e  "Ok\n"
else
  echo -e "Fail\n" >&2
  exit 1
fi

#Launch the 42.s file
echo -e "Test 04 : the 42.s file:\n"
output=$(./asm ./champions/42.s 3>&1 1>&2 2>&3 | tee /dev/stderr)
if test "$output" = "[33;1mWarning : [0mOverflow/Underflow detected.
[33;1mWarning : [0mOverflow/Underflow detected."; then
  echo -e  "Ok\n"
else
  echo -e "Fail\n" >&2
  exit 1
fi

#Launch a no existing file
echo -e "Test 05 : With a empty file:\n"
output=$(./asm op 3>&1 1>&2 2>&3 | tee /dev/stderr)
if test "$output" = "[31;1mError :[0m can't perform open(op).
[31;1mError :[0m \"op\" assembly failed."; then
  echo -e  "Ok\n"
else
  echo -e "Fail\n" >&2
  exit 1
fi

#Launch all the champion directory
echo -e "Test 06 : Well let's make a big test:\n"
output=$(./asm ./champions/*.s 3>&1 1>&2 2>&3 | tee /dev/stderr)
if test "$output" = "[33;1mWarning : [0mOverflow/Underflow detected.
[33;1mWarning : [0mOverflow/Underflow detected.
[33;1mWarning :[0m no such register 27
[33;1mWarning :[0m no such register 23
[31;1mError :[0m param %56 is direct : Invalid parameters at line 3 : \"and %87, %0, %56\" at file ./champions/and.s.
[31;1mError :[0m \"./champions/and.s\" assembly failed.
[31;1mError :[0m name or comment needed at file ./champions/fork.s.
[31;1mError :[0m \"./champions/fork.s\" assembly failed.
[31;1mError :[0m invalid char in label l_*)2: at line 3 : \"l_*)2:\" at file ./champions/label2.s.
[31;1mError :[0m \"./champions/label2.s\" assembly failed.
[31;1mError :[0m unknown label ref at file ./champions/label.s.
[31;1mError :[0m \"./champions/label.s\" assembly failed.
[31;1mError :[0m unknown opcode: llfork at line 3 : \"llfork %34\" at file ./champions/lfork.s.
[31;1mError :[0m \"./champions/lfork.s\" assembly failed.
[33;1mWarning :[0m direct is too big : 67890
[33;1mWarning :[0m indirection to far (513)
[33;1mWarning :[0m no such register 600
[33;1mWarning :[0m no such register 600
[33;1mWarning :[0m no such register 600
[33;1mWarning :[0m no such register 600
[33;1mWarning :[0m no such register 600
[33;1mWarning :[0m no such register 600
[33;1mWarning :[0m no such register 600
[33;1mWarning :[0m no such register 600
[33;1mWarning :[0m indirection to far (40000)
[33;1mWarning :[0m direct is too big : 600000
[31;1mError :[0m not enough params at line 3 : \"sti r2,%4\" at file ./champions/sti.s.
[31;1mError :[0m \"./champions/sti.s\" assembly failed.
[31;1mError :[0m too many params at line 3 : \"st r3,r8,6\" at file ./champions/st.s.
[31;1mError :[0m \"./champions/st.s\" assembly failed."; then
  echo -e  "Ok\n"
else
  echo -e "Fail\n" >&2
  exit 1
fi
