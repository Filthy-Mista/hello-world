#include <iostream>
#include <cmath>
#include <typeinfo>
#define DIM 50


using namespace std;


class A{
    protected:
        int n;
    public:
        A(int n){
            this->n = n;
        }
        
        virtual int f(int)const=0;
        virtual ostream & put(ostream & os)const{
            os << "n=" << n << ", ";
            return os;
        }
        
        virtual void incr(){
            this->n++;
        }
        
    
};


class B: public A{
    private:
        int m;
    public:
        B(int n): A(n){
            m = 3*(this->n % 7);
        }
        
        int fatt(int g)const{
            if(g == 0) return 1;
            else return g * fatt(g-1);
        }
        
        int f(int z)const{
            if(n < z) return fatt(n);
            else return fatt(m);
        }
        
        ostream & put(ostream & os)const{
            os << "B:          ";
            A::put(os);
            os << "m=" << m << ",         f(5)="<< this->f(5);
            return os;
        }
        void incr(){
            A::incr();
        }
        
        B operator ++(int){
            B b= *this;
            (*this).incr();
            return b;
        }
        
        
        
};

template <typename T>
class C: public A{
    private:
        T x;
    public:
        C(int n): A(n){
            if(typeid(x) == typeid(int)) x = g(n);
            else if(typeid(x) == typeid(double)) x = sin(n);
        }
        
        T g(T roberto)const{
            return roberto * roberto;
        }
        
        int f(int z)const{
            return (int)(g(n + x + z));
        }
        
        ostream & put(ostream & os)const{
            if(typeid(*this) == typeid(C<double>)) os << "C<double>: ";
            else if(typeid(*this) == typeid(C<int>)) os << "C<int>: ";
            A::put(os);
            os << "x=" << x << "       f(5)=" << this->f(5) << ",    g(5)=" << this->g(5);
            return os;
        }
        void incr(){
            A::incr();
        }
        
        C<T> operator ++(int){
            C<T> b= *this;
            (*this).incr();
            return b;
        }
        

};

ostream & operator <<(ostream & os, const A & a){
    return a.put(os);
}





int main(){
    A* vett[DIM];
    srand(328832748);
    for(int i=0; i<DIM; i++) {
        int n=1+rand()%100;
        switch(rand()%3) {
            case 0: 
                vett[i]= new B(n);
                break;
            case 1: 
                vett[i]= new C<double>(n);
                break;
            case 2: 
                vett[i]= new C<int>(n);
            
        }
        
    }
    
    for(int i= 0; i<DIM; i++){
        cout << i << ")";
        cout << *vett[i] << endl;
    }
    
    cout << endl;
    
    int max = 0;
    double sum = 0;
    for(int i=0; i<DIM; i++){
        if((vett[i])->f(5)) max = (vett[i])->f(5);
        if(typeid(*vett[i]) == typeid(C <double>)) sum += ((C<double>*)(vett[i])) -> g(5);
        C<double>* ptr = dynamic_cast <C<double>*> (vett[i]);
        if(ptr) sum += ptr->g(5);
    }
    
    
    cout << "Max = " << max << ",          Sum = " << sum << endl;
    

    cout << (*vett[10])++ << endl;
    cout << *vett[10] << endl;
    
    return 0;
}

