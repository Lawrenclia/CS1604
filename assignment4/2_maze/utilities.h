// --------------------------------------------------------------------------------
// This header file contains the following utility functions and operators
// 
// * random_integer: generating a random integer within a given range
// 
// * Overloaded << operator for pairs, vectors, stacks, queues, and maps 
//   in the standard library
//
// * Overloaded + and += operators for concatenating vectors
//
// * vector_insert: inserting an element at a given position into a vector 
// 
// * vector_erase: removing an element at a given position frome a vector
// 
// --------------------------------------------------------------------------------
#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED

#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <iostream>
#include <ctime>
#include <cstdlib>

int random_integer(int low, int high)
{
    if (low > high)
        return low;

    static bool firstTime = true;

    if (firstTime) {
        srand(time(NULL));
        firstTime = false;
    }

    int rnum = rand() % (high - low + 1);

    return rnum + low;
}

template <typename T, typename S>
std::ostream& operator<<(std::ostream &os, const std::pair<T, S>& p)
{
    os << "(" << p.first << ", " << p.second << ")";

    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    os << "[";
    if (!v.empty()) {
        size_t i = 0;
        while (os << v[i], ++i < v.size())
            os << ", ";
    }
    os << "]";

    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, std::stack<T> s)
{
    std::vector<T> v;

    while (!s.empty()) {
        v.insert(v.begin(), s.top());
        s.pop();
    }

    return os << v;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, std::queue<T> s)
{
    std::vector<T> v;

    while (!s.empty()) {
        v.push_back(s.front());
        s.pop();
    }

    return os << v;
}

template <typename K, typename V>
std::ostream& operator<<(std::ostream& os, const std::map<K, V>& s)
{
    std::vector<std::pair<K, V>> vec;

    for (const auto &p : s)
        vec.push_back(p);

    return os << vec;
}

template <typename T>
std::vector<T> operator+(const std::vector<T>& v1, const std::vector<T>& v2)
{
    std::vector<T> v = v1;
    for (size_t i = 0; i < v2.size(); i++) {
        v.push_back(v2[i]);
    }

    return v;
}

template <typename T>
std::vector<T>& operator+=(std::vector<T>& v1, const std::vector<T>& v2)
{
    for (size_t i = 0; i < v2.size(); i++)
        v1.push_back(v2[i]);

    return v1;
}

template <typename T>
void vector_insert(std::vector<T>& vec, size_t pos, const T& v)
{
    vec.insert(vec.begin() + pos, v);
}

template <typename T>
void vector_erase(std::vector<T>& vec, size_t pos)
{
    vec.erase(vec.begin() + pos);
}

#endif // UTILITIES_H_INCLUDED
