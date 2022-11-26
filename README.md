# lets-learn
Let's learn

## 1. Linking Libraries:

* Build all: 

        $ source build-all.sh
        cc -Wall -g -I../inc -c ../lib-src.c
        ar rc libtest.a lib-src.o
        cc -Wall -g -fPIC -I../inc -c ../lib-src.c
        cc -shared -o libtest.so lib-src.o
        cc -c -Wall -I../lib/inc -o sample-app-static.o sample-app.c
        cc -o sample-app-static sample-app-static.o -L../lib/static -ltest
        cc -c -Wall -I../lib/inc -o sample-app-dynamic.o sample-app.c
        cc -o sample-app-dynamic sample-app-dynamic.o -L../lib/dynamic -ltest


* Clean all : 

        $ source clean-all.sh
        rm -f lib-src.o
        rm -f libtest.a
        rm -f lib-src.o
        rm -f libtest.so
        rm -f *.o
        rm -f sample-app-static sample-app-dynamic
      
* App Execution :
        
        $ app/sample-app-dynamic
        Square of 10 is 100 !
        $ app/sample-app-static
        Square of 10 is 100 !
* Size:

        $ ls -la app/sample-app-*
        -rwxr-xr-x 1 debian debian 7640 Nov 26 13:26 app/sample-app-dynamic
        -rw-r--r-- 1 debian debian 1096 Nov 26 13:26 app/sample-app-dynamic.o
        -rwxr-xr-x 1 debian debian 8480 Nov 26 13:26 app/sample-app-static
        -rw-r--r-- 1 debian debian 1096 Nov 26 13:26 app/sample-app-static.o

        $ ls -la lib/*
        -rw-r--r-- 1 debian debian   43 Nov 26 13:16 lib/lib-src.c

        lib/dynamic:
        total 24
        drwxr-xr-x 2 debian debian 4096 Nov 26 13:26 .
        drwxr-xr-x 5 debian debian 4096 Nov 24 02:41 ..
        -rw-r--r-- 1 debian debian 2028 Nov 26 13:26 lib-src.o
        -rwxr-xr-x 1 debian debian 7700 Nov 26 13:26 libtest.so
        -rw-r--r-- 1 debian debian  275 Nov 24 04:22 Makefile

        lib/inc:
        total 12
        drwxr-xr-x 2 debian debian 4096 Nov 24 02:35 .
        drwxr-xr-x 5 debian debian 4096 Nov 24 02:41 ..
        -rw-r--r-- 1 debian debian   74 Nov 26 13:16 lib-header.h

        lib/static:
        total 20
        drwxr-xr-x 2 debian debian 4096 Nov 26 13:26 .
        drwxr-xr-x 5 debian debian 4096 Nov 24 02:41 ..
        -rw-r--r-- 1 debian debian 2020 Nov 26 13:26 lib-src.o
        -rw-r--r-- 1 debian debian 2168 Nov 26 13:26 libtest.a
        -rw-r--r-- 1 debian debian  243 Nov 24 02:56 Makefile

* ReadELF:

        $ readelf -a app/sample-app-static | grep "Shared library"
        0x00000001 (NEEDED)                     Shared library: [libc.so.6]
        
        $ readelf -a app/sample-app-dynamic | grep "Shared library"
        0x00000001 (NEEDED)                     Shared library: [libtest.so]
        0x00000001 (NEEDED)                     Shared library: [libc.so.6]


* Performance:

        
        $ perfFull app/sample-app-static

        WARMING UP app/sample-app-staticSquare of 10 is 100 !
        RUNNING 10 timesSquare of 10 is 100 !
        Square of 10 is 100 !
        Square of 10 is 100 !
        Square of 10 is 100 !
        Square of 10 is 100 !
        Square of 10 is 100 !
        Square of 10 is 100 !
        Square of 10 is 100 !
        Square of 10 is 100 !
        Square of 10 is 100 !
        0.014
        0.013
        0.013
        0.013
        0.013
        0.013
        0.013
        0.013
        0.018
        0.013
        .013 average
        
        $ perfFull app/sample-app-dynamic

        WARMING UP app/sample-app-dynamicSquare of 10 is 100 !
        RUNNING 10 timesSquare of 10 is 100 !
        Square of 10 is 100 !
        Square of 10 is 100 !
        Square of 10 is 100 !
        Square of 10 is 100 !
        Square of 10 is 100 !
        Square of 10 is 100 !
        Square of 10 is 100 !
        Square of 10 is 100 !
        Square of 10 is 100 !
        0.014
        0.014
        0.014
        0.013
        0.014
        0.014
        0.027
        0.035
        0.029
        0.014
        .018 average

[Peformance Tool Reference](https://stackoverflow.com/questions/54920113/calculate-average-execution-time-of-a-program-using-bash)

