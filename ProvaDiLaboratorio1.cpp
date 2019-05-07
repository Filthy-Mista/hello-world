#include <iostream>
#include <cstdlib>
#include <time.h>
#include <cmath>
#include <typeinfo>
#define DIM 30

using namespace std;

class A{
    protected:
        double* ptr;
        short len;
    public:
        A(short n){
            double *Array = new double [n];
            srand(time(0));
            for(int i=0; i<n; i++){
                Array[i]=((double)rand()) /RAND_MAX;
            }
            this->ptr = Array;
            this->len = n;
        }
        
        virtual double foo(short a)const=0;
        
        double & operator[](int i){
            return this->ptr[i];            //A a[10]; cout<< a[10];  è come fare cout<<ptr[10]= 10;
        }
        
        virtual ostream & put(ostream & os)const{
            
            os << "ptr=[";
            for(int i=0; i<this->len; i++){
                os << this->ptr[i] << " ";
            }
            os << "], ";
            return os;
        }
        
        
            
};


class B : public A{
    private:
        double alpha;
        double extract(short s)const{return ((ptr[s%len]+alpha)/ 2.0);}
    public:
        B(short m, double d):A(m), alpha(d){}
        double foo(short b)const{return log( 1 + extract(b) );}
        
        ostream & put(ostream & os)const{
            os << "B, ";
            A::put(os);
            os << "alpha=" <<(*this).alpha << ", "<< "foo(5)=" << (*this).foo(5)<<endl;
            return os;
        }
};



template <typename T>
class C: public A{
    private:
        T x;
    public:
        C(short n):A(n) {
            if(typeid(this->x) == typeid(short)) this->x= g(n);
            else this->x = log(1+n);
        }
        
        double foo(short r)const{
            return static_cast <double> (g((r*this->x)));
        }
        
        T g(T k)const{return 3.0*k;}
        
        ostream & put(ostream & os)const{
            if(typeid(*this) == typeid(C<double>)) os << "C<double>, ";
            else if(typeid(*this) == typeid(C<int>)) os << "C<int>, ";
            A::put(os);
            os <<"x="<<x << ", foo(5)="<<(*this).foo(5) <<", g(5)=" <<(*this).g(5)<<endl;
            return os;
        }
};


ostream & operator <<(ostream  &os, const A& a){    
    return a.put(os);
}



int main(){
    
    A* vett[DIM];      
    
    srand(328832748);
    for(int i=0; i<DIM; i++) {
        short n=1+rand()%5;
        switch(rand()%3) {
            case 0: vett[i]= new B(n, n/100.0); break;
            case 1: vett[i]= new C<double>(n);break;
            case 2: vett[i]= new C<int>(n);
        }
    }
    
    for(int i=0; i<DIM; i++){
        
        cout << i << ")";
        cout << *vett[i] << endl;
    }
    
    
    int Max= 0;
    int Sum= 0;
    for(int i=0; i<DIM; i++){
        if((vett[i])->foo(5) > Max) Max= (vett[i])->foo(5);
        if(typeid(*vett[i]) == typeid(C<double>)) Sum += ((C<double>*)(vett[i]))->g(5);
    }
    cout << "Max= "<<Max << ", sum=" << Sum <<endl;
    
    
    cout << "(*vett[10])[2]="<< (*vett[10])[2] << endl;
    
    
    return 0;
}



