all: pi_multi_thread pi_serial
pi_multi_thread: pi_multi_thread.c
	gcc -pthread pi_multi_thread.c -o pi_multi_thread
pi_serial: pi_serial.c
	gcc pi_serial.c -o pi_serial
clean:
	rm -f pi_multi_thread pi_serial
