#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    int id;
    char *p;
    pid_t pid;

    // 1️⃣ Create p memory (enough for A-Z + '\0')
    id = shmget(1234, 27 * sizeof(char), IPC_CREAT | 0666);

    // 2️⃣ Attach p memory
    p = (char *)shmat(id, NULL, 0);

    // 3️⃣ Create child process
    pid = fork();

    if (pid == 0)
    {
        // 👶 Child process
        sleep(1);   // wait for parent to write

        printf("Child reads from p memory:\n");
        printf("%s\n", p);

        shmdt(p);
    }
    else
    {
        // 👨 Parent process
        char ch = 'A';
        for (int i = 0; i < 26; i++)
        {
            p[i] = ch++;
        }
        p[26] = '\0';   // string termination

        printf("Parent wrote A-Z into p memory\n");

        wait(NULL);          // wait for child
        shmdt(p);

        // Remove p memory
        shmctl(id, IPC_RMID, NULL);
    }

    return 0;
}

