sudo dmesg -C
./main < test_data/$1_1.txt > log_files/$1_1_stdout.txt
dmesg | grep Project1 > log_files/$1_1_dmesg.txt
sudo dmesg -C
./main < test_data/$1_2.txt > log_files/$1_2_stdout.txt
dmesg | grep Project1 > log_files/$1_2_dmesg.txt
sudo dmesg -C
./main < test_data/$1_3.txt > log_files/$1_3_stdout.txt
dmesg | grep Project1 > log_files/$1_3_dmesg.txt
sudo dmesg -C
./main < test_data/$1_4.txt > log_files/$1_4_stdout.txt
dmesg | grep Project1 > log_files/$1_4_dmesg.txt
sudo dmesg -C
./main < test_data/$1_5.txt > log_files/$1_5_stdout.txt
dmesg | grep Project1 > log_files/$1_5_dmesg.txt
sudo dmesg -C
./main < test_data/TIME_MEASUREMENT.txt > log_files/TIME_MEASUREMENT_stdout.txt
dmesg | grep Project1 > log_files/TIME_MEASUREMENT_dmesg.txt
