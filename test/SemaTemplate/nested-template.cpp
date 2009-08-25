// RUN: clang-cc -fsyntax-only -verify %s

class A;

class S {
public:
   template<typename T> struct A { 
     struct Nested {
       typedef T type;
     };
   };
};

int i;
S::A<int>::Nested::type *ip = &i;

template<typename T>
struct Outer {
  template<typename U>
  class Inner0;
  
  template<typename U>
  class Inner1 {
    struct ReallyInner;
    
    T foo(U);
    template<typename V> T bar(V);
  };
};

template<typename X>
template<typename Y>
class Outer<X>::Inner0 {
public:
  void f(X, Y);
};

#if 0
// FIXME: These don't parse properly because we can't handle the template-name
// "Inner0" or "Inner1" after the dependent type Outer<X>. 
template<typename X>
template<typename Y>
void Outer<X>::Inner0<Y>::f(X, Y) {
}

template<typename X>
template<typename Y>
struct Outer<X>::Inner1<Y>::ReallyInner {
  void g(X, Y);
};

template<typename X>
template<typename Y>
void Outer<X>::Inner1<Y>::ReallyInner::g(X, Y) {
}

template<typename X>
template<typename Y>
X Outer<X>::Inner1<Y>::foo(Y) {
  return X();
}

template<typename X>
template<typename Y>
template<typename Z>
X Outer<X>::Inner1<Y>::bar(Z) {
  return X();
}
#endif