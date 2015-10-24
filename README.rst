Update /etc/host with docker machine IPs
========================================

Have you ever suffered because you forgot your docker machine ip address?
Do you find it boring to check? This is the code for you.

Sorry in advance
----------------

I'm totally not a C++ programmer as you will notice. I wanted to write this
code as an experiment and actually it works. I'm glad to hear any improvement,
any comment.

Goal
----

Take the output of `docker-machine ls` grab the name of the machine and the
IP address. Create a hostfile entry like `192.168.99.100 default.docker.local`.
Finally append (or replace the exists entries) in `/etc/hosts`.

Why C++
-------

If you want to update the `/etc/hosts` file you have to use `sudo` so I've
decided to use the `chmod +s` command and make it owned by root. As you know
bash doesn't allow that on any scripts. However yhe compiled C++ code is
accepted. (Tbh, I really wanted to write something small in C++ too ;))

Compile
-------

I hope a simle `make` would compile it on your machine as well. I'm using it
on OSX, I hope it could be compiled on linux as well.

Install and usage
-----------------

Put the output to `/usr/local/sbin` folder and execute the `update_hostfile`
command.

It creates a backup of the hosts file. (`/etc/hosts.0`)
