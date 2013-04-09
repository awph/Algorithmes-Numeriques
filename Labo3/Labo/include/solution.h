#ifndef SOLUTION_H_INCLUDED
#define SOLUTION_H_INCLUDED

template<typename T>
class Solution
{
    public:
        explicit Solution(std::string key,const T& data = 0);

        const std::string getKey() const {return key;}
        const T getData() const {return data;}
        void setData(const T& data) {this->data = data;}
    private:
        std::string key;
        T data;
};

template<typename T>
Solution<T>::Solution(std::string key,const T& data):key(key),data(data){}

#endif // SOLUTION_H_INCLUDED
