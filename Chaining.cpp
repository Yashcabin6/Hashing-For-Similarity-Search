#include "Chaining.h"
using namespace std;
void Chaining::srt(int n){
    int i=0;
    if(money.size()==0)
        money.push_back(n);
    else{
        while(money[i]>n && i<money.size())
            ++i;
        money.insert(money.begin()+i,n);
    }
}
void Chaining::delet(int n){
    int i=0;
    while(money[i]!=n){
        i+=1;
    }
    money.erase(money.begin()+i);
}
Chaining::Chaining(){
    bankStorage2d.resize(100000);
    std::vector<int> money;
    size=0;
}
void Chaining::createAccount(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    h=hash(id);
    Account A;
    A.id=id;
    A.balance=count;
    bankStorage2d[h].push_back(A);
    srt(count);
    size+=1;
}

std::vector<int> Chaining::getTopK(int k) {
    // IMPLEMENT YOUR CODE HERE
    return std::vector<int>(money.begin(),money.begin()+k); // Placeholder return value
}

int Chaining::getBalance(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    h=hash(id);
    for(Account i : bankStorage2d[h]){
        if(i.id==id){
            return i.balance;
        }
    }
    return -1; // Placeholder return value
}

void Chaining::addTransaction(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    h=hash(id);
    int flag=0;
    for(int i=0; i<bankStorage2d[h].size();i++){
        if(bankStorage2d[h][i].id==id){
            flag=1;
            int c=bankStorage2d[h][i].balance;
            bankStorage2d[h][i].balance+=count;
            delet(c);
            srt(bankStorage2d[h][i].balance);
            break;
        }
    }
    if(flag==0){
        Account A;
        A.id=id;
        A.balance=count;
        bankStorage2d[h].push_back(A);
        srt(count);
        size+=1;
    }
}

bool Chaining::doesExist(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    h=hash(id);
    for(Account i : bankStorage2d[h]){
        if(i.id==id){
            return true;
        }
    }
    return false; // Placeholder return value
}
bool Chaining::deleteAccount(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    h=hash(id);
    for(int i=0; i<bankStorage2d[h].size();++i){
        if(bankStorage2d[h][i].id==id){
            int c=bankStorage2d[h][i].balance;
            bankStorage2d[h].erase(bankStorage2d[h].begin()+i);
            --size;
            delet(c);
            return true;
        }
    }
    return false; // Placeholder return value
}
int Chaining::databaseSize() {
    // IMPLEMENT YOUR CODE HERE
    return size; // Placeholder return value
}

int Chaining::hash(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int h=0;
    int j=7;
    for(char i:id){
        h+=int(i)*j; 
        j*=7;
        j=j%1000000;
    }
    return h%100000;
     // Placeholder return value
}