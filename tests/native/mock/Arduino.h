#pragma once
#include <cstdint>
#include <cstddef>
#include <string>
#define OUTPUT 1
#define HIGH 1
#define LOW 0
#define HEX 16
#define F(x) x
using std::size_t;
class String {
 std::string s;
public:
 String()=default; String(const char*x):s(x?x:""){}
 size_t length()const{return s.length();}
 char operator[](size_t i)const{return s[i];}
 String& operator+=(char c){s+=c;return *this;}
 const char*c_str()const{return s.c_str();}
};
inline unsigned long millis(){static unsigned long t=0;return t++;}
inline void delay(unsigned long){}
inline void pinMode(uint8_t,int){}
inline void digitalWrite(uint8_t,int){}
class SerialMock {public: template<class T>void print(T){} template<class T>void print(T,int){} template<class T>void println(T){} void println(){} };
extern SerialMock Serial;
