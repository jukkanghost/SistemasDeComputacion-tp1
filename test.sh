#!/bin/bash

assert_equals () {
  if [ "$1" = "$2" ]; then
    echo -e "$Green $Check_Mark Success $Color_Off"
  else
    echo -e "$Red Failed $Color_Off"
    echo -e "$Red Expected -$1- to equal -$2- $Color_Off"
    Errors=$((Errors  + 1))
    exit 1
  fi
}

response=$(./calc 1 2 + 2)
assert_equals "$response" 4

response=$(./calc 1 2 - 2)
assert_equals "$response" 0

response=$(./calc 0 0001 + 0001)
assert_equals "$response" 10

response=$(./calc 0 1100 - 0100)
assert_equals "$response" 1000


