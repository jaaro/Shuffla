killall shuffla-server
make
rm /home/jaaro/dump.shu
./bin/shuffla-server &
sleep 5
time ./bin/integral_tests 0.0.0.0 3000 | grep -v test | md5sum

