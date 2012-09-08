cpuh0g - a command line utility to hog CPU resources

The tool can be used to easily saturate one or many CPUs on a multi-core (SMP) box.
Using the additional CPU load caused by the tool, the behavior of other programs 
under load can be checked.

To create the cpuh0g binary, run the following commands:
./configure
make

The binary will be created in the bin/ directory.
To run it for 30 seconds with 2 threads, use the following commands:
bin/cpuh0g --threads 2 --duration 30

It will then create 2 threads and utilise the CPU to the max in the 2 threads.

The following options are available:

    --duration   run duration (in seconds) (value: 5)
    --help       print help and exit 
    --silent     be silent 
    --threads    number of threads (value: 1)
    --version    print version information and exit

