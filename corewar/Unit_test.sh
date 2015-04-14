#!/bin/bash
#Check if binary exist
echo -e "Binary research:"
if test -e corewar; then
  echo -e "\033[32;1mExecutable corewar found\033[0m\n"
else
  echo -e "\033[31;1mExecutable corewar not found\033[0m\n" >&2
  exit 1
fi

#Launch virtual machine without arguments
echo -e "Without arguments:"
output=$(./corewar 3>&1 1>&2 2>&3 | tee /dev/stderr)
if test "$output" = "Usage: corewar [-dump nbr_cycle] [[-n prog_number] [-a load_address ] prog_name] ..."; then
  echo -e  "\033[32;1mOk\033[0m\n"
else
  echo -e "\033[31;1mFail\033[0m\n" >&2
  exit 1
fi

#Launch virtual machine with missing parameter for dump
echo -e "Without argument for dump:"
output=$(./corewar -dump 3>&1 1>&2 2>&3 | tee /dev/stderr)
if test "$output" = "Dump must have a positive number."; then
  echo -e  "\033[32;1mOk\033[0m\n"
else
  echo -e "\033[31;1mFail\033[0m\n" >&2
  exit 1
fi

#Launch virtual machine wrong with parameter for dump (letter)
echo -e "Wrong argument for dump (letter):"
output=$(./corewar -dump a 3>&1 1>&2 2>&3 | tee /dev/stderr)
if test "$output" = "Dump must have a positive number."; then
  echo -e  "\033[32;1mOk\033[0m\n"
else
  echo -e "\033[31;1mFail\033[0m\n" >&2
  exit 1
fi

#Launch virtual machine wrong with parameter for dump (number)
echo -e "Wrong argument for dump (number):"
output=$(./corewar -dump -1 3>&1 1>&2 2>&3 | tee /dev/stderr)
if test "$output" = "Dump must have a positive number."; then
  echo -e  "\033[32;1mOk\033[0m\n"
else
  echo -e "\033[31;1mFail\033[0m\n" >&2
  exit 1
fi

#Launch virtual machine with missing parameter for n
echo -e "Without argument for n:"
output=$(./corewar -n 3>&1 1>&2 2>&3 | tee /dev/stderr)
if test "$output" = "Champions must have a positive number."; then
  echo -e  "\033[32;1mOk\033[0m\n"
else
  echo -e "\033[31;1mFail\033[0m\n" >&2
  exit 1
fi

#Launch virtual machine wrong with parameter for n (letter)
echo -e "Wrong argument for n (letter):"
output=$(./corewar -n a 3>&1 1>&2 2>&3 | tee /dev/stderr)
if test "$output" = "Champions must have a positive number."; then
  echo -e  "\033[32;1mOk\033[0m\n"
else
  echo -e "\033[31;1mFail\033[0m\n" >&2
  exit 1
fi

#Launch virtual machine wrong with parameter for n (number)
echo -e "Wrong argument for n (number):"
output=$(./corewar -n -1 3>&1 1>&2 2>&3 | tee /dev/stderr)
if test "$output" = "Champions must have a positive number."; then
  echo -e  "\033[32;1mOk\033[0m\n"
else
  echo -e "\033[31;1mFail\033[0m\n" >&2
  exit 1
fi

#Launch virtual machine with missing parameter for a
echo -e "Without argument for a:"
output=$(./corewar -a 3>&1 1>&2 2>&3 | tee /dev/stderr)
if test "$output" = "Champions must have a positive adress."; then
  echo -e  "\033[32;1mOk\033[0m\n"
else
  echo -e "\033[31;1mFail\033[0m\n" >&2
  exit 1
fi

#Launch virtual machine wrong with parameter for a (letter)
echo -e "Wrong argument for a (letter):"
output=$(./corewar -a a 3>&1 1>&2 2>&3 | tee /dev/stderr)
if test "$output" = "Champions must have a positive adress."; then
  echo -e  "\033[32;1mOk\033[0m\n"
else
  echo -e "\033[31;1mFail\033[0m\n" >&2
  exit 1
fi

#Launch virtual machine wrong with parameter for a (number)
echo -e "Wrong argument for a (number):"
output=$(./corewar -a -1 3>&1 1>&2 2>&3 | tee /dev/stderr)
if test "$output" = "Champions must have a positive adress."; then
  echo -e  "\033[32;1mOk\033[0m\n"
else
  echo -e "\033[31;1mFail\033[0m\n" >&2
  exit 1
fi

#Launch virtual machine with file non-existent
echo -e "File non-existent:"
output=$(./corewar non-existent 3>&1 1>&2 2>&3 | tee /dev/stderr)
if test "$output" = "Can't open \"non-existent\".
\"non-existent\" isn't a corewar executable"; then
  echo -e  "\033[32;1mOk\033[0m\n"
else
  echo -e "\033[31;1mFail\033[0m\n" >&2
  exit 1
fi
