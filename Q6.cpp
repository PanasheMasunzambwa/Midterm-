#include <iostream>
#include <vector>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

int main()
{
    string program;
    int count;
    char mode;

    while (true)
    {
        cout << "closh> ";
        cin >> program;

        if (program == "exit")
            break;

        cout << "count> ";
        cin >> count;

        if (count < 1 || count > 9)
        {
            cout << "Error: count must be between 1 and 9." << endl;
            continue;
        }

        cout << "[p]arallel or [s]equential> ";
        cin >> mode;

        vector<pid_t> pids;

        for (int i = 0; i < count; i++)
        {
            pid_t pid = fork();
            if (pid < 0)
            {
                cerr << "Fork failed!" << endl;
                exit(1);
            }
            else if (pid == 0)
            { // Child process
                execlp(program.c_str(), program.c_str(), nullptr);
                cerr << "Error executing program!" << endl;
                exit(1);
            }
            else
            { // Parent process
                pids.push_back(pid);
                if (mode == 's')
                {
                    waitpid(pid, nullptr, 0);
                }
            }
        }

        if (mode == 'p')
        {
            for (pid_t pid : pids)
            {
                waitpid(pid, nullptr, 0);
            }
        }
    }

    return 0;
}
