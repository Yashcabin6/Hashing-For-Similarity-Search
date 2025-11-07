#include "LinearProbing.h"
using namespace std;
void LinearProbing::srt(int n){
    int i=0;
    if(money.size()==0)
        money.push_back(n);
    else{
        while(money[i]>n && i<money.size())
            ++i;
        money.insert(money.begin()+i,n);
    }
}
void LinearProbing::delet(int n){
    int i=0;
    while(money[i]!=n){
        i+=1;
    }
    money.erase(money.begin()+i);
}
LinearProbing::LinearProbing(){
    Account A;
    A.id="NA";
    A.balance=-1;
    bankStorage1d.resize(200131);
    bankStorage1d.insert(bankStorage1d.begin(),bankStorage1d.size(),A);
    std::vector<int> money;
    size=0;
}
void LinearProbing::createAccount(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    h=hash(id);
    while(bankStorage1d[h].id!="NA"){
        h=(h+1)%200131;
    }
    bankStorage1d[h].id=id;
    bankStorage1d[h].balance=count;
    srt(count);
    size+=1;
}

std::vector<int> LinearProbing::getTopK(int k) {
    // IMPLEMENT YOUR CODE HERE
    return std::vector<int>(money.begin(),money.begin()+k); // Placeholder return value
}

int LinearProbing::getBalance(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    h=hash(id);
    int mark=h;
    if(bankStorage1d[h].id==id){
        return bankStorage1d[h].balance;
    }
    h=(h+1)%200131;
    while(bankStorage1d[h].id!=id && bankStorage1d[h].balance!=-1){
        h=(h+1)%200131;
    }
    if(bankStorage1d[h].balance==-1){
        return -1;
    }else{
        return bankStorage1d[h].balance;
    }
         // Placeholder return value
}

void LinearProbing::addTransaction(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    h=hash(id);
    if(doesExist(id)){
        while(bankStorage1d[h].id!=id){
            h+=1;
        }
        int c=bankStorage1d[h].balance;
        delet(c);
        bankStorage1d[h].balance+=count;
        srt(bankStorage1d[h].balance);
    }else{
        while(bankStorage1d[h].id!="NA"){
            h+=1;
        }
        bankStorage1d[h].id=id;
        bankStorage1d[h].balance=count;
        srt(count);
        size+=1;
    }
}

bool LinearProbing::doesExist(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    h=hash(id);
    int mark=h;
    if(bankStorage1d[h].id==id){
        return true;
    }
    h=(h+1)%200131;
    while(bankStorage1d[h].id!=id && bankStorage1d[h].balance!=-1){
        h=(h+1)%200131;
    }
    if(bankStorage1d[h].balance==-1){
        return false;
    }else{
        return true;
    }
     // Placeholder return value
}

bool LinearProbing::deleteAccount(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    h=hash(id);
    int mark=h;
    if(bankStorage1d[h].id==id){
        int c=bankStorage1d[h].balance;
        bankStorage1d[h].id="NA";
        bankStorage1d[h].balance=0;
        delet(c);
        --size;
        return true;
    }
    h=(h+1)%200131;
    while(bankStorage1d[h].id!=id && bankStorage1d[h].balance!=-1){
        h=(h+1)%200131;
    }
    if(bankStorage1d[h].balance==-1){
        return false;
    }else{
        int c=bankStorage1d[h].balance;
        bankStorage1d[h].id="NA";
        bankStorage1d[h].balance=0;
        delet(c);
        --size;
        return true;
    } // Placeholder return value
}
int LinearProbing::databaseSize() {
    // IMPLEMENT YOUR CODE HERE
    return size; // Placeholder return value
}

int LinearProbing::hash(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int h=0;
    int j=17;
    for(char i:id){
        h+=int(i)*j; 
        j*=17;
        j=j%200131;
    }
    return h%200131;
     // Placeholder return value
}

