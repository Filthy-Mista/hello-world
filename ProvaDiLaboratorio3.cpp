#include <iostream>
#include <typeinfo>
#include <cstdlib>
#define DIM 50


using namespace std;

class A{
    protected:
        int x;
    
    public:
        A(int s):x(s){};
        virtual int f()const= 0;
        friend class B;
        
        virtual ostream & put(ostream &os)const{
            os << "x=" << x <<"  ";
            return os;
        }

};



class B:public A{
    private:
        char b;
    public:
        B(int s, char z): A(s), b(z){};
        int f()const{
            if(x % 2 == 0)  return (int)b;
            else return ((int)b)*2;
        }
        ostream & put(ostream &os)const{
            os << "class B:          ";
            A::put(os);
            os << "b='" << b << "'       f()=" << f() << endl;
            return os;
         }
         
        B operator ++(int k){
             B aux = (*this);
             x++;
             return aux;
        }
     
};




template <class T>
class C:public A{
    private:
        T c;
    public:
        C(int s, T z): A(s), c(z){};
        int f()const{
            return ( x +(20 * ((int)c)));
        }
        T f(double eps)const{
            if(typeid(c) == typeid(char)) return (char)((int)c + 1);
            else return static_cast <T> (f()+eps);
        }
        
        ostream & put(ostream &os)const{
            os << "Class C<"<< typeid(c).name() << ">:  ";
            A::put(os);
            os << "c=" << c << "  f()="<< f() << "  f(0.03)=" << f(0.03) << endl;
            return os;
        }
       
};


ostream & operator <<(ostream &os, const A& a){
    return a.put(os);
}



int main(){
    A* vett[DIM];
    
    srand(328832748);
    for(int i=0; i<DIM; i++){
        int x= 1+rand()%100;
        int c= 'a'+rand()%26;
        switch(rand()%3){
            case 0: vett[i]= new B(x,c); 
                break;
            case 1: vett[i]= new C <double>(x,rand()/(double)RAND_MAX); 
                break;
            case 2: vett[i]= new C<char>(x,c+1);
        }
    }
    
    for(int i= 0; i<DIM; i++){
        
        cout << i << ")";
        cout << *vett[i]<< endl;
    }
    
    int max = 0;
    char *arrayc;
    int n= 0;
    
    for(int i= 0; i<DIM; i++){
        if(typeid(*vett[i]) == typeid(C<char>)){
            if((vett[i])->f() > max) max =(vett[i])->f();
            
            n++;
        }
        
    }
    arrayc = new char[n];
    char check;
    for(int j=0; j<n; j++){
        for(int i=0; i<DIM; i++){
            if(typeid(*vett[i]) == typeid(C<char>)){
              check  = ((C<char>*)(vett[i]))->f(0.03);
            }
        }
        arrayc[j]= check;
    }
    
    
    
    
    cout <<"punto 1 : max=" << max <<endl;
    
    cout <<"punto 2 : conc=";
    for(int i=0; i<n; i++) cout << arrayc[i];
    cout << endl;
    return 0;
}
