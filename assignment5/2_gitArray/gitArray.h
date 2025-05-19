#ifndef GITARRAY_H_INCLUDED
#define GITARRAY_H_INCLUDED

#include <string>
#include <vector>
#include <map>

class GitArray {
private:
    // add member functions/variables here
    std::map<std::string, std::vector<std::vector<int>>> branches ;
    std::string name;
    int line;
public:
    GitArray(int length);

    std::string toString();

    void set(int index, int value);
    int get(int index, int version);

    void undo();
    void redo();

    void branch(const std::string& branch_name);
    void checkout(const std::string& branch_name);
};


#endif // GITARRAY_H_INCLUDED
