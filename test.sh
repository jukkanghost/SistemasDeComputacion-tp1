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

response=$(./calc 0 1100 + 100f)
assert_equals "$response" Pone numeros

response=$(./calc 0 1100 - 10000)
assert_equals "$response" Binario de 4 digitos

response=$(./calc 0 1300 + 1000)
assert_equals "$response" Solo ceros y unos

response=$(./calc 1 454555 - 101823dsf)
assert_equals "$response" Pone numeros

response=$(./calc 1 454555 + 10182391893198)
assert_equals "$response" Numero muy grande

response=$(./calc akjfh 1100 + 1100)
assert_equals "$response" Elige 0 o 1 para las operaciones



