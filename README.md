## To compile 

    gcc server_udp.c -o server_udp -lm
    gcc client_udp.c -o client_udp -lm

## Usage

Start server with the following command:
	
	~$./ server_udp <Server_host> <Server_port>

Start client with command:
	
	~$./ client_udp <Server_host> <Server_port>
	
	

## Tested on 

Mac OS X 10.9

Apple LLVM version 5.0 (clang-500.2.79) (based on LLVM 3.3svn)  2
Thread model: posix  

***

Ubuntu 12.04

gcc version 4.6.3 (Ubuntu/Linaro 4.6.3-1ubuntu5)  
Target: x86_64-linux-gnu  

