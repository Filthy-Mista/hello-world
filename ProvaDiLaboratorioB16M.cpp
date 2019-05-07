#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <time.h>
#define DIM 30

using namespace std;


class A{
    private:
        float x;
        string st;
    protected:
        short getFirstvowel(){
            
            for(int i=0; i<st.length(); i++){
                switch(st[i]){
                    case 'a':
                        return i;
                        
                    case 'e':
                        return i;
                        
                    case 'i':
                        return i;
                        
                    case 'o':
                        return i;
                        
                    case 'u':
                        return i;
                        
                }
                
            }
            return -1;
        }
    public:
        A(int * vec, short n){
            int somma =0;
            for(int i=0; i<n; i++){
                somma+= vec[i];
                st+= (char)(vec[i]);
            }
            x = somma / (float)(n);
        }
        virtual int f()=0;
        
        virtual ostream & put(ostream & os)const{
            os << "x=" << x << ", st=" << st;
            return os;
        }
};



class B:public A{
    private:
        float* values;
        short len;
    public:
        B(int* vec, short n):A(vec,n){
            float *arr =new float[n];
            for(int i=0; i<n; i++){
                arr[i]= log(vec[i]);
            }
            values = arr;
            len = n;
        }
        
        int f(){
            float min = 9999.9;
            for(int i= 0; i<len; i++){
                if(values[i] < min) min =values[i];
            }
            return (int)(min +0.5);
        }
        ostream & put(ostream & os)const{
            os << "Class1B: ";
            A::put(os);
            os << " { values=[";
            for(int i=0 ; i<len; i++){
                os << values[i] <<" ";
            }
            os <<"], len = " << len <<"}";
            return os;
        }
};


class C:public A{
    private:
        int i;
    public:
        C(int* vec, short n):A(vec,n){
            srand(time(0));
            i = (vec[(rand()%n)])%50;
        }
        
        int f(){
            return i + getFirstvowel();
        }
        
        bool moreThan(int y){
            return (i >= y);
        }
        ostream & put(ostream & os)const{
            os << "Class1C: ";
            A::put(os);
            os << "{ i=" << i << "}";
            return os;
        }
};

ostream & operator <<(ostream & os, const A & a){
    return a.put(os);
}




int main(){
    srand(111222333);
    A *vett[DIM];
    short l, select;
    int *vec;
 	    
    for(int i=0; i<DIM; i++){
    l = rand()%8 + 5;
    select = rand()%2;
    vec = new int[l];

    for(int c=0; c<l; c++)
      vec[c] = 97 + rand()%25;    
    
    if(select)
      vett[i] = new B(vec, l);
     else
      vett[i] = new C(vec, l);
    }
    
    cout << "Punto I (visualizzare gli oggeti):"<<endl;

    
    for(int i= 0; i< DIM; i++){
        cout <<i <<") " << *vett[i] << endl;
        cout << "       f()=" << (*vett[i]).f() <<endl;
    }
    
    int max= 0;
    int min =9999;
    
    int somma = 0;
    float dim = DIM;
    for(int i=0; i<DIM; i++){
        if((*vett[i]).f() > max) max=(*vett[i]).f();
        if((*vett[i]).f() < min) min=(*vett[i]).f();
        somma += (vett[i])->f();
    }
    
    
    cout << "Punto II (minimo, media e massimo dei valori di f()):" << endl;
    cout << "min: " << min <<", max:"<< max << ", avg:"<< somma /dim <<endl;
    

    
    cout << "Punto III (indici degli oggetti per cui moreThan(10) e' true):" << endl;
    
    for(int i= 0; i< DIM; i++){
        C* ptr = dynamic_cast <C*> (vett[i]);
        if(ptr){
            if(ptr->moreThan(10))
                cout << i <<" ";
        }
    }
    cout << endl;
    
    return 0;
    
}
