# ft_ping

Build a clone of the well known `ping` command, with  as a study project, and with some constraints (limited allowed function, polling forbiden).

My own implementation is based on the inetutils-2.2 implementation, with options matching the iputils version. 

## Some details on implementation
Due to our constraints, this ping implementation is alarm based (the function alarm rythms the program). I choose to use alarm to tick each second allowing to manage intervals between packets and timeout delays.

Each time a packet is received, it IPV4 complience is checked, then it ICMP packet is classified (ECHO REPLY, TIME EXCEDED, ...)

## Use
### Install
Warning: `ft_ping` uses raw-sockets to excange ICMP messages. Thus, the last step of compilation needs you to have root level to extend it capabilities (one done, you can run it as non root user).

```bash
git clone https://github.com/GermainToubol/ft_ping.git
cd ft_ping
make
```

### Run
Just like the real `ping` command, pass options and target address to the `ft_ping` executable.
```bash
$ ./ft_ping -h

Usage
  ping [options] <destination>

Options:
  <destination>      dns name or ip adress
  -c <count>         send COUNT echo requests
  -f                 flood ping
  -h                 print help and exit
  -i <interval>      interval between packets (s)
  -l <preload>       number of preloaded packets
  -m <mark>          mark the outgoing packets
  -M <pmtud opt>     define mtu discovery, can be one of <do|dont|want>
  -n                 disable reverse DNS name resolution
  -p <pattern>       set the padding bytes pattern
  -t <ttl>           set request ttl
  -v                 verbose output
  -w <deadline>      end the program after <deadline> seconds
  -W <timeout>       Stop if no response have been received in <timeout> seconds
```

### Examples
Cherypicked examples:
 - local address
```bash
$ ./ft_ping 0
PING 0 (0.0.0.0) 56(84) bytes of data
64 bytes from 127.0.0.1: icmp_seq=1 ttl=64 time=0.019 ms
64 bytes from 127.0.0.1: icmp_seq=2 ttl=64 time=0.064 ms
64 bytes from 127.0.0.1: icmp_seq=3 ttl=64 time=0.066 ms
^C
--- 0 ping statistics ---
3 packets transmitted, 3 received, 0% loss, min/avg/max/mdev 0.019/0.050/0.066/0.022 ms
```

 - remote address, IP only
```bash
$ ./ft_ping 1.1.1.1
PING 1.1.1.1 (1.1.1.1) 56(84) bytes of data
64 bytes from 1.1.1.1: icmp_seq=1 ttl=55 time=13.331 ms
64 bytes from 1.1.1.1: icmp_seq=2 ttl=55 time=4.136 ms
64 bytes from 1.1.1.1: icmp_seq=3 ttl=55 time=4.291 ms
64 bytes from 1.1.1.1: icmp_seq=4 ttl=55 time=4.273 ms
^C
--- 1.1.1.1 ping statistics ---
4 packets transmitted, 4 received, 0% loss, min/avg/max/mdev 4.136/6.508/13.331/3.940 ms
```

 - remote address, hostname
```bash
$ ./ft_ping -c 2 google.fr
PING google.fr (142.250.178.131) 56(84) bytes of data
64 bytes from par21s22-in-f3.1e100.net (142.250.178.131): icmp_seq=1 ttl=115 time=2.786 ms
64 bytes from par21s22-in-f3.1e100.net (142.250.178.131): icmp_seq=2 ttl=115 time=4.049 ms

--- google.fr ping statistics ---
2 packets transmitted, 2 received, 0% loss, min/avg/max/mdev 2.786/3.418/4.049/0.632 ms
```

 - remote address, low ttl value, verbose option (dump received IP packet)
 ```bash
$ ./ft_ping -c 2 -v -t3 google.fr
PING google.fr (142.250.178.131) 56(84) bytes of data idx = 48385
36 bytes from nat-1.42.fr (10.60.1.11): Time to live exceeded
Packet dump:
 4500 0038 4ff4 0000 3e01 cf8a 0a3c 010b
 ac1c a5e3 0b00 a40d 0000 0000 4500 0054
 41be 4000
36 bytes from nat-1.42.fr (10.60.1.11): Time to live exceeded
Packet dump:
 4500 0038 4ff6 0000 3e01 cf88 0a3c 010b
 ac1c a5e3 0b00 160e 0000 0000 4500 0054
 420b 4000

--- google.fr ping statistics ---
2 packets transmitted, 0 received, +2 errors, 100% packet loss
```
