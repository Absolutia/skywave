# Skywave Communicator
## About
Originally intended to be a mere chat suite, the goal of the project has evolved to something more like a generic network tunnel with authentication.
Any kind of data should be ferriable through Skywave, though heavy focus in the early parts will be given to the original real-time chat and file transfer plans.<br>The basic architecture shall be that one or more processes will connect to the network client via a UNIX domain socket, send the needed destination and authentication information to the client, which shall then connect to the destination server, establishing the tunnel. The client shall map UNIX sockets to IP sockets and perform the translation and transmission/reception transparently.
### Why not use SSH instead?
Because this is intended for use by everyone. SSH has an unacceptably steep learning curve for many (most) people. Additionally, though SSH has the capability to do something like this, it was neither explicitly intended for that and cumbersome to actually use. This problem becomes most apparent when trying to forward large amounts of ports: tunnels don't like to be persistent, plus it's easy to screw things up, not to mention excruciatingly tedious. This project intends to make that easier for lay people, make it faster and make it automatic. There is one problem with this picture, however, because it is mainly intended to be used by the software itself, "automagically" configuring a tunnel when configured to do so. It cannot completely replace SSH on its own because our daemon refuses to run as `root` and therefore (as far as I know) cannot mass capture or transmit traffic like that. Even if it did, I'm not sure how the OpenSSH daemon even does that...<br><br>It's an open problem, and it would seem like it could be solved with a dedicated program that connects to `skywaved`. Implementation suggestions welcome.
## Usage
The software may as well be considered to be in pre-alpha state, not much is currently functional, especially not the planned relay functionality.
`./skywave_testing` with no options defaults to client. It will always try to connect on 127.0.0.1:50000(?)<br>
`./skywave_testing server` starts the server code, listening for incoming connections on port 50000(?)<br>
## Compiling
`gcc -c skywave.c client.c server.c protocol.c`<br>
`gcc -O0 -o skywave_testing skywave.o client.o server.o protocol.o`<br>
Or equivalent. Get as close to disabling optimizations as possible to minimize compiler faults.
## Porting
In case you're wondering, I'm not bothering with Windows versions or anything like that for now. I don't even have the basic features in a functional state yet!
## To-do list
- [ ] Daemonize core
- [ ] Network code
  - [ ] Server: Socket juggling (Absolutia/skywave#4)
  - [ ] Server: Multiplex socket I/O with `poll()`
  - [ ] All: Implement core relay protocol
