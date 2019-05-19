make

for((i=1;i<=2;i++));
do
  ./Netflip.out < TestCases/input/$i.in > TestCases/oo/$i.out;

  if(diff -b -q TestCases/oo/$i.out TestCases/output/$i.out);
  then
    echo "Test case " $i " is Corrcet! :)";
  else
    echo "Test case " $i " is Wrong  ! :(";
  fi;
done

read -p "*************************"
rm TestCases/oo/*.out
