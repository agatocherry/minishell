#!/bin/sh
set -e
cd $(dirname $0)

echo "Compilation"
gcc -Wall -Werror -Wextra -DBUFFER_SIZE=5 main1.c get_next_line.c -o your_gnl_1.out || (echo "KO -> compilation failed" && exit 1)
gcc -Wall -Werror -Wextra -DBUFFER_SIZE=5 main2.c get_next_line.c -o your_gnl_2.out || (echo "KO -> compilation failed" && exit 1)
gcc -Wall -Werror -Wextra -DBUFFER_SIZE=5 main2_generator.c get_next_line.c -o generator.out

echo "Testing"
rm -f big_file big_file2 your_output our_output

echo "> Reading main1.c"
touch your_output
./your_gnl_1.out < main1.c > your_output || (echo "KO -> compilation failed" && exit 1)
diff your_output main1.c || (echo "KO -> test failed" && exit 1)
rm -rf your_output
echo "OK"

echo "> Reading from a bigfile"
touch big_file your_output our_output
for i in `seq 1 10000 100000` ; do
	for j in `seq 1 10` ; do
	base64 /dev/urandom | tr -d '/+' | fold -w $i | head -n $j > big_file
	./your_gnl_1.out < big_file > your_output || ( echo "KO exec fail" && exit 1)
diff your_output big_file || (echo "KO -> test failed" && exit 1)
done
done
rm -rf big_file your_output our_output
echo "OK"

echo "> Reading from a big file 2"
touch big_file your_output our_output big_file2
echo > big_file
for i in `seq 1 10` ; do cat big_file2 >> big_file ; done
./your_gnl_1.out < big_file > your_output || ( echo "KO exec fail" && exit 1)
diff your_output big_file || (echo "KO -> test failed" && exit 1)
rm -f big_file big_file2 our_output your_output
echo "OK"

echo "> Sequential read"
./generator.out > our_output
./your_gnl_2.out > your_output || ( echo "KO exec fail" && exit 1)
diff your_output our_output || (echo "KO -> test failed" && exit 1)
rm -f your_output our_output your_gnl_2.out
echo "OK"

echo "Does not check leaks"
