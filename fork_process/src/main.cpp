#if 1
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <string>

int main(int argc, char **argv)
{
    FILE *pp;
    if( (pp = popen("ls -l", "r")) == NULL )
    {
        printf("popen() error!/n");
        exit(1);
    }
    char tmp[1024];
    while (fgets(tmp, sizeof(tmp), pp) != NULL) {
        printf("%",tmp);
    }
    pclose(pp);

    return 0;
}

#else

#define LOG_TAG "tony"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <android/log.h>
#include <cutils/log.h>

int main(int argc, char **argv)
{
    uid_t uid;
    uid_t euid;

    pid_t pid;

    int status;
    pid_t ret;

    uid = getuid();
    euid = geteuid();

    printf("uid = %d\n", uid);
    printf("euid = %d\n", euid);

    pid = fork();
    if (pid < 0) {
        ALOGE("fork error!!!");
        printf("fork error!!!\n");
        return -1;
    } else if (pid == 0) {
        ALOGD("child process (pid = %d, ppid = %d)...", getpid(), getppid());
        printf("child process (pid = %d, ppid = %d)...\n", getpid(), getppid());

        if (execlp("/system/bin/QFlash", "QFlash", "-f", "/data/AG35CEVCR05A03T4G_OCPU_DSV_BETA0609_test", NULL) < 0) {
            ALOGE("execvp error!!!");
            perror("execvp error!!!");
            exit(0);
        }

    } else {
        ALOGD("parent process (pid = %d)...", getpid());
        printf("parent process (pid = %d)...\n", getpid());

        ret = wait(&status);
        if (ret < 0) {
            ALOGE("wait error!!!");
            perror("wait error!!!");
        }

        ALOGD("child exit (pid = %d) ...", ret);
        printf("child exit (pid = %d) ...\n", ret);

        if (WIFEXITED(status)) {
            ALOGD("child exit normal, status=%d", WEXITSTATUS(status));
            printf("child exit normal, status=%d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            ALOGD("child exit abnormal, signal=%d", WTERMSIG(status));
            printf("child exit abnormal, signal=%d\n", WTERMSIG(status));
        } else if (WIFSTOPPED(status)) {
            ALOGD("child stopped, signal=%d", WSTOPSIG(status));
            printf("child stopped, signal=%d\n", WSTOPSIG(status));
        }
    }

    return 0;
}

#endif