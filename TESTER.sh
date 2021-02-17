#!/bin/bash
make

rm TestCases/oo/*.out
for((i=1;i<=8;i++));
do
  ./Netflip.out < TestCases/input/$i.in > TestCases/oo/$i.out;

# -q for disabeling printing diffrences
  if(diff -b TestCases/oo/$i.out TestCases/output/$i.out);
  then
    echo "Test case " $i " is Corrcet! :)";
  else
    echo "Test case " $i " is Wrong  ! :(";
  fi;
done

read -p "*************************"
