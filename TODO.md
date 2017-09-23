# TODO

* Main gateway needs to but split into more libraries (there is duplicate code living in the packet_tester, etc.)
* Improve documentation, clean up wiki documentation as well
* Merge this repo in with the control-tower repo (or whatever we decide to call it)
* Server-client model (a daemon should run in the background and a client should connect to it to get a status as well
    as updates) - this may take longer than the scope of this refactor
* Use monit to keep the server alive (and send an email if it goes down)
