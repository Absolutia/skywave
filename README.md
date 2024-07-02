# Skywave Communicator
## Compiling
`gcc -c skywave.c client.c server.c protocol.c`<br>
`gcc -O0 -o skywave_testing skywave.o client.o server.o protocol.o`<br>
Or equivalent. Get as close to disabling optimizations as possible to minimize compiler faults.
