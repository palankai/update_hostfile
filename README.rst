Update /etc/host with docker machine IPs
========================================

Have you ever suffered because you forgot your docker machine ip address?
Do you find it boring to check? This is the code for you.

Sorry in advance
----------------

I'm totally not a C++ programmer as you may notice. I wanted to write this
code as an experiment and actually it works. I'm glad if you send me any comments.

Goal
----

Take the output of ``docker-machine ls`` grab the name of the machine and the
IP address. Create a hostfile entry like ``192.168.99.100 default.docker.local``.
Finally append (or replace the exists entries) in ``/etc/hosts``.

Expected result (the first part is already there):

.. code::

  ##
  # Host Database
  #
  # localhost is used to configure the loopback interface
  # when the system is booting.  Do not change this entry.
  ##
  127.0.0.1	localhost
  255.255.255.255	broadcasthost
  ::1             localhost

  192.168.99.100	default.docker.local

Why C++
-------

If you want to update the `/etc/hosts`` file you have to use ``sudo`` so I've
decided to use the ``chmod +s`` command and make it owned by root to achive a
simple as possible execution. As you may know bash doesn't allow that on any
scripts. However a compiled C++ code is accepted.
(Tbh, I really wanted to write something small in C++ too)

Compile and install
-------------------

I hope a simle ``make`` would compile it on your machine as well. I use it
on OSX, I hope it could be compiled on linux as well. You have to make sure
a C++ compiler installed on your machine.

.. code::

  $ make
  $ chmod +s update_hostfile
  $ sudo chown root update_hostfile
  $ sudo mv update_hostfile /usr/local/bin

Tested on OSX 10.10.

Usage
-----

It makes a backup of the exists hostfile (``/etc/hosts.0``) then appends the docker-machine hosts.

.. code::

  $ update_hostfile
