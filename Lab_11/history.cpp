// Dipen

#include <iostream>
#include <string>
#include <vector>
#include <stack>

using std::cin;
using std::cout;
using std::endl;
using std ::stack;
using std::string;
using std::vector;

// Memento

// reciever
class Document
{
public:
    Document(vector<string> lines = {}) : lines_(lines) {}

    void insert(int line, const string &str)
    {
        int index = line - 1;
        if (index <= lines_.size() + 1)
        {
            lines_.insert(lines_.begin() + index, str);
        }
        else
            cout << "line out oof range" << endl;
    }
    string remove(int line)
    {
        int index = line - 1;

        if (index < lines_.size())
        {
            string temp = lines_[index];
            lines_.erase(lines_.begin() + index);
            return temp;
        }

        cout << "line out of range\n";
        return "";
    }
    void show() const
    {
        for (int i = 0; i < lines_.size(); ++i)
        {
            cout << i + 1 << ". " << lines_[i] << endl;
        }
    }

    class Memento *checkpoint() const; // can also use class Memento; Memento *checkpoint()
    void rollback(const class Memento *);

private:
    vector<string> lines_;
};

class Memento
{
public:
    Memento(const Document &doc) : doc_(doc) {}
    const Document &getState() const { return doc_; }

private:
    const Document doc_;
};

Memento *Document::checkpoint() const
{
    return new Memento(*this); // copying the document itself
}

void Document ::rollback(const Memento *mem)
{
    *this = mem->getState(); // copying back
}

// command
class Command
{
public:
    Command(Document *doc) : doc_(doc) {}
    virtual void execute() = 0;
    virtual void unexecute() = 0;

    // // Prototype + history
    virtual Command *clone() const = 0;
    virtual void show() const = 0;

protected:
    Document *doc_;
};

// two concrete commands
class InsertCommand : public Command
{
public:
    InsertCommand(Document *doc, int line, string text) : Command(doc), line_(line), text_(text) {}
    void execute() override
    {
        doc_->insert(line_, text_); // insert line
    }
    void unexecute() override
    {
        doc_->remove(line_); // remove line
    }
    Command *clone() const override
    {
        return new InsertCommand(*this);
    }
    void show() const override
    {
        cout << "insert " << text_ << " at line " << line_ << endl;
    }

private:
    int line_;
    string text_;
};

class EraseCommand : public Command
{
public:
    EraseCommand(Document *doc, int line) : Command(doc), line_(line), str_("") {}
    void execute() override
    {
        str_ = doc_->remove(line_); // stores the deleted text
    }
    void unexecute() override
    {
        doc_->insert(line_, str_); // insert it back
    }
    Command *clone() const override
    {
        return new EraseCommand(*this);
    }
    void show() const override
    {
        cout << "erase line" << line_ << endl;
    }

private:
    int line_;
    string str_;
};

// invoker

class DocumentWithHistory
{
public:
    DocumentWithHistory(const vector<string> &lines = {}) : doc_(lines), checkpoint_(nullptr) {}
    void show() const
    {
        doc_.show();
    }
    void insert(int line, const string &text)
    {
        Command *cmd = new InsertCommand(&doc_, line, text);
        cmd->execute();
        undoStack_.push(cmd);
        history_.push_back(cmd);
    }
    void erase(int line)
    {
        Command *cmd = new EraseCommand(&doc_, line);
        cmd->execute();

        undoStack_.push(cmd);
        history_.push_back(cmd);
    }

    void undo()
    {
        if (undoStack_.empty())
        {
            cout << "nothing to undo";
            return;
        }
        Command *cmd = undoStack_.top();
        undoStack_.pop();

        cmd->unexecute();
    }

    void checkpoint()
    {
        if (checkpoint_ != nullptr)
            delete checkpoint_;

        checkpoint_ = doc_.checkpoint();

        history_.clear();
    }
    void rollback()
    {
        if (checkpoint_ == nullptr)
        {
            cout << "No checkpoint";
            return;
        }

        doc_.rollback(checkpoint_);

        delete checkpoint_;
        checkpoint_ = nullptr;

        // clear undo history
        while (!undoStack_.empty())
        {
            delete undoStack_.top();
            undoStack_.pop();
        }

        history_.clear();
    }

    void showHistory() const
    {
        for (int i = 0; i < history_.size(); i++)
        {
            cout << i + 1 << ". ";
            history_[i]->show();
        }
    }
    void redo(int index)
    {
        if (index < 1 || index > history_.size())
        {
            cout << "invalid index\n";
            return;
        }

        Command *cmd = history_[index - 1]->clone(); // PROTOTYPE
        cmd->execute();

        undoStack_.push(cmd);
        history_.push_back(cmd);
    }

private:
    Document doc_;
    Memento *checkpoint_;
    stack<Command *> undoStack_;
    vector<Command *> history_;
};

// client
int main()
{

    DocumentWithHistory his({"Lorem Ipsum is simply dummy text of the printing and typesetting",
                             "industry. Lorem Ipsum has been the industry's standard dummy text",
                             "ever since the 1500s, when an unknown printer took a galley of",
                             "type and scrambled it to make a type specimen book. It has",
                             "survived five centuries."});

    char option;
    do
    {

        // his.show();
        cout << endl;
        cout << "Enter option (i)nsert line (e)rase line (u)ndo last command (c)heckpoint roll(b)ack (h)istory (r)edo command : ";
        cin >> option;

        int line;
        string str;

        switch (option)
        {
        case 'i':
            cout << "line number to insert: ";
            cin >> line;
            cout << "line to insert: ";
            cin.get(); // removes end-of-line character so getline() works correctly
            getline(cin, str);
            his.insert(line, str);
            his.show();
            break;
        case 'e':
            cout << "line number to remove : ";
            cin >> line;

            his.erase(line);
            his.show();
            break;

        case 'u':
            his.undo();
            his.show();
            break;
        case 'c':
            his.checkpoint();
            cout << "checkpoint" << endl;
            his.show();
            break;
        case 'b':
            his.rollback();
            cout << "Rolled back to checkpoint\n";
            his.show();
            break;
        case 'h':
            cout << "\nHistory:\n";
            his.showHistory();
            break;
        case 'r':
            cout << "Enter history number: ";
            cin >> line;

            his.redo(line);
            his.show();
            break;
        }
    } while (option == 'i' || option == 'e' || option == 'c' || option == 'r' || option == 'u' || option == 'b' || option == 'h');
}