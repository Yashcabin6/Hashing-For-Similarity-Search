#ifndef LINEARPROBING_H
#define LINEARPROBING_H

#include "BaseClass.h"
#include <iostream>

class LinearProbing : public BaseClass {
public:
    LinearProbing();
    void srt(int n);
    void delet(int n);
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;
    
private:
    int size;
    int h;
    std::vector<int> money;
    // Other data members and functions specific to Linear Probing
};

#endif // LINEARPROBING_H
