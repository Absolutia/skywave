# Skywave Communicator
## State of the project
I do not, and will not, offer any technical support. Software does not encompass my whole life. Documentation will follow as APIs/protocols enter feature freeze. If you find bugs with completed features, please submit a pull request and fix it yourself. Otherwise please be patient.
## About
Originally intended to be a mere chat suite, the goal of the project has evolved to something more like a generic network tunnel with authentication.
Any kind of data should be transmittable.
### tunneld
The basic architecture shall be that one or more processes will connect to the network client via a UNIX domain socket, send the needed destination and authentication information to the client, which shall then connect to the destination server, establishing the tunnel. The client shall map UNIX sockets to IP sockets and perform the translation and transmission/reception transparently.<br><br>Subject to change as I work out the logistics with this.
## Why not use SSH instead?
You can if you want to. You can also combine the two for extra security/privacy. I personally prefer software which is simple to configure, use and fundamentally understand. It just so happens that I need something that implements SSH-like tunneling but takes zero effort for technologically illiterate people to set up and use. Software, especially network code, is useless if there's nobody to use it.
## To-do list
- [ ] Unified error handling and logging
- [ ] Signal handling
- [ ] Daemonize core
- [ ] Network code
  - [ ] Server: Socket juggling (Absolutia/skywave#4)
  - [ ] Server: Multiplex socket I/O with `poll()`
  - [ ] All: Implement core relay protocol
