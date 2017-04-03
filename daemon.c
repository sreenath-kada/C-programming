#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <syslog.h>

int main(void) {

        /* Our process ID and Session ID */
        pid_t pid, sid;
        int i=0;

        /* Fork off the parent process */
        pid = fork();
        if (pid < 0) {
                exit(EXIT_FAILURE);
        }
        /* If we got a good PID, then
           we can exit the parent process. */
        printf("\n the daemon process Id is %d\n", pid);

        if (pid > 0) {
                exit(EXIT_SUCCESS);
        }

        /* Change the file mode mask */
        umask(0);

        /* Open any logs here */
        setlogmask (LOG_UPTO (LOG_NOTICE));

        openlog ("daemonLog", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);

        syslog (LOG_NOTICE, "Program started by User %d\n", getuid ());

        /* Create a new SID for the child process */
        sid = setsid();
        if (sid < 0) {
                /* Log the failure */
                exit(EXIT_FAILURE);
        }

        /* Change the current working directory */
        if ((chdir("/")) < 0) {
                /* Log the failure */
                exit(EXIT_FAILURE);
        }

        /* Close out the standard file descriptors */
        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);

        /* Daemon-specific initialization goes here */

        /* The Big Loop */
        while (1) {
           /* Do some task here ... */
           syslog (LOG_NOTICE, "Daemon is running loop=%d\n",i++);
           sleep(15); /* wait 15 seconds */      
        }
   exit(EXIT_SUCCESS);
}

           
