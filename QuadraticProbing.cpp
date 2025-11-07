#include "QuadraticProbing.h"
using namespace std;
void QuadraticProbing::srt(int n){
    int i=0;
    if(money.size()==0)
        money.push_back(n);
    else{
        while(money[i]>n && i<money.size())
            ++i;
        money.insert(money.begin()+i,n);
    }
}
void QuadraticProbing::delet(int n){
    int i=0;
    while(money[i]!=n){
        i+=1;
    }
    money.erase(money.begin()+i);
}
QuadraticProbing::QuadraticProbing(){
    Account A;
    A.id="NA";
    A.balance=-1;
    bankStorage1d.resize(200131);
    bankStorage1d.insert(bankStorage1d.begin(),bankStorage1d.size(),A);
    std::vector<int> money;
    size=0;
}
void QuadraticProbing::createAccount(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    h=hash(id);
    int mark=h;
    int i=1;
    while(bankStorage1d[h].id!="NA"){
        h=(mark+i*i)%200131;
        i+=1;
    }
    bankStorage1d[h].id=id;
    bankStorage1d[h].balance=count;
    srt(count);
    size+=1;
}

std::vector<int> QuadraticProbing::getTopK(int k) {
    // IMPLEMENT YOUR CODE HERE
    return std::vector<int>(money.begin(),money.begin()+k); // Placeholder return value
}

int QuadraticProbing::getBalance(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    h=hash(id);
    int i=2;
    int mark=h;
    if(bankStorage1d[h].id==id){
        return bankStorage1d[h].balance;
    }
    h=(h+1)%200131;
    while(bankStorage1d[h].id!=id && bankStorage1d[h].balance!=-1){
        h=(h+i*i)%200131;
        i+=1;
    }
    if(bankStorage1d[h].balance==-1){
        return -1;
    }else{
        return bankStorage1d[h].balance;
    } // Placeholder return value
}

void QuadraticProbing::addTransaction(std::string id, int count) {
    // IMPLEMENT YOUR CODE HERE
    h=hash(id);
    int mark=h;
    int i=1;
    if(doesExist(id)){
        while(bankStorage1d[h].id!=id){
            h=(mark+i*i)%200131;
            i+=1;
        }
        int c=bankStorage1d[h].balance;
        delet(c);
        bankStorage1d[h].balance+=count;
        srt(bankStorage1d[h].balance);
    }else{
        while(bankStorage1d[h].id!="NA"){
            h=(mark+i*i)%200131;
            i+=1;
        bankStorage1d[h].id=id;
        bankStorage1d[h].balance=count;
        srt(count);
        size+=1;
        }
    }
}

bool QuadraticProbing::doesExist(string id) {
    // IMPLEMENT YOUR CODE HERE
    h=hash(id);
    int mark=h;
    int i=2;
    if(bankStorage1d[h].id==id){
        return true;
    }
    h=(h+1)%200131;
    while(bankStorage1d[h].id!=id && bankStorage1d[h].balance!=-1){
        h=(h+i*i)%200131;
        i+=1;
    }
    if(bankStorage1d[h].balance==-1){
        return false;
    }else{
        return true;
    }
 // Placeholder return value
}

bool QuadraticProbing::deleteAccount(string id) {
    // IMPLEMENT YOUR CODE HERE
    h=hash(id);
    int mark=h;
    int i=2;
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
        h=(h+i*i)%200131;
        i+=1;
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
int QuadraticProbing::databaseSize() {
    // IMPLEMENT YOUR CODE HERE
    return size; // Placeholder return value
}

int QuadraticProbing::hash(std::string id) {
    // IMPLEMENT YOUR CODE HERE
    int h=0;
    int j=289;
    for(char i:id){
        h+=int(i)*j; 
        j*=17;
        j=j%200131;
    }
    return h%200131;
     // Placeholder return value
}


