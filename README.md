# Skywave Communicator
## Usage
`./skywave_testing` with no options defaults to client. It will always try to connect on 127.0.0.1:50000(?)<br>
`./skywave_testing server` starts the server code, listening for incoming connections on port 50000(?)<br>
## Compiling
`gcc -c skywave.c client.c server.c protocol.c`<br>
`gcc -O0 -o skywave_testing skywave.o client.o server.o protocol.o`<br>
Or equivalent. Get as close to disabling optimizations as possible to minimize compiler faults.
