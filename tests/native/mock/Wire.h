#pragma once
#include <cstdint>
#include <vector>
#include <deque>
class WireMock {
 std::vector<uint8_t> mem=std::vector<uint8_t>(256,255);
 uint8_t ptr=0; std::vector<uint8_t> tx; std::deque<uint8_t> rx;
public:
 void begin(){}
 void beginTransmission(uint8_t){tx.clear();}
 size_t write(uint8_t b){tx.push_back(b);return 1;}
 uint8_t endTransmission(){if(tx.empty())return 0;ptr=tx[0];if(tx.size()>1){for(size_t i=1;i<tx.size();i++)mem[ptr++]=tx[i];ptr=tx[0];}return 0;}
 uint8_t requestFrom(uint8_t,uint8_t n){rx.clear();for(uint8_t i=0;i<n;i++)rx.push_back(mem[ptr++]);return n;}
 int available(){return (int)rx.size();}
 int read(){if(rx.empty())return -1;int v=rx.front();rx.pop_front();return v;}
 void reset(){mem.assign(256,255);ptr=0;}
};
extern WireMock Wire;
