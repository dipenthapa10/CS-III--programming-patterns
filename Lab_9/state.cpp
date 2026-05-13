#include <iostream>
#include <string>
#include <queue>
using std::cin;
using std::cout;
using std::endl;
using std::queue;
using std::string;

class State;

// context
class Process
{
public:
    Process();
    // different  behaviours
    void create();
    void dispatch();
    void suspend(); // suspend
    void block();
    void unblock();

    string report();
    void changeState(State *s)
    {
        state_ = s;
    }
    int getID()
    {
        return id_;
    }

private:
    State *state_;
    int id_;
    static int nextID; // maintain a static variable in class Process to keep track of the next available
};

// abstract state

class State
{
public:
    virtual void create(Process *) {};
    virtual void dispatch(Process *) {};
    virtual void suspend(Process *) {};
    virtual void block(Process *) {};
    virtual void unblock(Process *) {};

    virtual string report() = 0;
    void changeState(Process *p, State *s)
    {
        p->changeState(s);
    }
};

// now creating different states

class Ready : public State
{
public:
    static State *instance()
    {
        static State *inst = new Ready;
        return inst;
    }
    void dispatch(Process *p) override;
    string report() override { return "ready"; }
};

class Running : public State
{
public:
    static State *instance()
    {
        static State *inst = new Running;
        return inst;
    }

    void suspend(Process *p) override;
    void block(Process *p) override;
    string report() override { return "running"; }
};

class Blocked : public State
{
public:
    static State *instance()
    {
        static State *inst = new Blocked;
        return inst;
    }
    void unblock(Process *p) override;
    string report() override { return "blocked"; }
};

void Ready ::dispatch(Process *p)
{
    changeState(p, Running::instance());
}

void Running ::suspend(Process *p)
{
    changeState(p, Ready ::instance());
}
void Running ::block(Process *p)
{
    changeState(p, Blocked ::instance());
}

void Blocked ::unblock(Process *p)
{
    changeState(p, Ready::instance());
}

int Process::nextID = 1;
Process ::Process()
{
    id_ = nextID++;
    state_ = Ready::instance();
}

void Process ::dispatch()
{
    state_->dispatch(this);
}

void Process ::suspend()
{
    state_->suspend(this);
}
void Process ::block()
{
    state_->block(this);
}
void Process::unblock()
{
    state_->unblock(this);
}

string Process ::report()
{
    return state_->report();
}

int main()
{
    queue<Process *> readyQue;
    queue<Process *> blockedQue;

    for (int i = 0; i < 4; i++)
    {
        Process *p = new Process();
        cout << "PID " << p->getID() << ": created\n";
        cout << "PID " << p->getID() << " state: " << p->report() << endl;

        readyQue.push(p);
    }

    while (!readyQue.empty() || !blockedQue.empty())
    {
        if (!readyQue.empty())
        {
            Process *current = readyQue.front();
            readyQue.pop();

            // ready and running

            cout << "\nDispatching...\n";
            current->dispatch();
            cout << "PID " << current->getID() << " state: " << current->report() << endl;

            int randomState = rand() % 3;
            if (randomState == 0)
            {
                // exit
                cout << "Exiting...\n";
                cout << "PID " << current->getID() << ": exited\n";
                delete current;
            }
            else if (randomState == 1)
            {
                // suspend and goes to back to ready
                cout << "Suspending...\n";
                current->suspend();
                cout << "PID " << current->getID() << " state: " << current->report() << endl;
                readyQue.push(current);
            }
            else
            {
                // block
                cout << "Blocking...\n";
                current->block();
                cout << "PID " << current->getID() << " state: " << current->report() << endl;
                blockedQue.push(current);
            }
        }

        else
        {
            cout << "\nThe ready queue is empty\n";
        }
        // Unblocking logic
        if (!blockedQue.empty() && rand() % 2 == 0)
        {
            cout << "\nUnblocking...\n";
            Process *p = blockedQue.front();
            blockedQue.pop();

            p->unblock();
            cout << "PID " << p->getID() << " state: " << p->report() << endl;

            readyQue.push(p);
        }
    }
}