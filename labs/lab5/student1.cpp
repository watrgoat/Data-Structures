
// length of a = n
// int b = b
// O(n/b)
int foobar (const std::vector<std::string> &a, int b) {
    int answer = 0;
    for (int i = 0; i < a.size(); i+=b) {
        answer++;
    }
    return answer;
}

// length of a = n
// O(n)
void foo2 (const std::vector<int> &a, std::string &b) {
    b.clear();
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] > 0)
            b.push_back('+');
        else
            b.push_back('-');
    }
}

// O(1)
std::vector<int> foo3 (const std::vector<int> &a, const std::string &b) {
    return std::vector<int>(b.size(),a.size());
}

// length of a = n
// O(n)
int foo3 (const std::vector<std::string> &a, const std::string& b) {
    int ret = 0;
    for (int i=0; i<a.size(); i++){
        ret += (a[i] == b);
    }
    return ret;
}

// length of a = n
// O(n)
std::vector<int> foo4 (const std::vector<int> &a) {
    std::vector<int> answer = a;
    for (int i = 0; i < a.size(); i++) {
        if(a[i] < (a[a.size()-1]*a[a.size()-1])){
            answer.erase(answer.end()-1);
        }
    }
    return answer;
}

// n = len(a)
// O(n)
std::vector<int> foo5 (const std::vector<int> &a, int b) {
    std::vector<int> ret;
    for(int i=0; i<a.size(); i++){
        if(a[i] < b){
            ret.insert(ret.end(),a[i]);
        }
    }
    return ret;
}