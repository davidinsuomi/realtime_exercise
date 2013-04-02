
#include <unistd.h>
#include <stdio.h>

long val;
int errno;

  main()
 {

    printf("POSIX_VERSION = %d\n",_POSIX_VERSION);
    printf("clock ticks= %d \n",sysconf(_SC_CLK_TCK));



         //#ifdef _SC_THREADS
         //printf("   POSIX.1c pthreads are supported.\n");


   val=sysconf(_SC_REALTIME_SIGNALS);
   if ((val == -1) && (errno))
   {
     printf("Bad option _SC_REALTIME_SIGNALS\n");
   }
   else if ((val == -1) && (!errno))
   {
     printf("POSIX.4 REALTIME SIGNALS not Supported.\n");
   }
   else
   {
     printf("POSIX.4 REALTIME SIGNALS Supported.\n");
   }

val=sysconf(_SC_THREADS);
   if ((val == -1) && (errno))
   {
     printf("Bad option _SC_THREADS\n");
   }
   else if ((val == -1) && (!errno))
   {
     printf("POSIX.4 THREADS not Supported.\n");
   }
   else
   {
     printf("POSIX.4 THREADS Supported.\n");
   }

 }

