#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cmath>
#include <typeinfo>
#include <climits>
#define DIM 30



using namespace std;

class A{    
    private:
        int* p;
        short l;
        float y;
    protected:
        int val(short j){
            if(j>= 0 && j<l){
                return this->p[j];
            }
            else{
                int index = rand()%l;
                return this->p[index];
            }
            
        }
        
    public:
        A(short i1, short i2){
            this->p = new int[i1+i2];
            short max= i1 > i2 ? i1 : i2;
            short min= i1 > i2 ? i2 : i1;
            
            for(int i=0; i< (i1+i2); i++){
                this->p[i]= rand()%(max-min+1)+min;
            }
            
            this->l = i1 + i2;
            this->y = log((i1+i2)/2.0);
        }
        
        virtual float f(short i, float x)=0;
        
        virtual ostream & put(ostream & os)const{
            os << "Class " << typeid(*this).name();
            os << ", p=[";
            for(int i=0; i< this->l; i++){
                os << this->p[i] << " ";
            }
            os << "]: l=" << this->l <<", y="<< this->y;
            
            return os;
        }
};


class B: public A{
    private:
        string str;
    public:
        B(string w, short a, short b): A(a,b){
            for(int i= 0; i<w.length(); i++){
                switch(w[i]){
                    case 'a':
                    case 'e':
                    case 'i':
                    case 'o':
                    case 'u':
                        str+= w[i];
                        break;
                }
            }
        }
        
        float f(short i, float x){
            return (sin(val(i)))*x;
        }
        
        ostream& put(ostream & os)const{
            A::put(os);
            os <<"{ str=" << str << "}";
            return os;
        }
};


class C: public A{
    private:
        float m;
    public:
        C(float z): A((short)(z+0.5), 5* ((short)(z+0.5))){
            m= val(2*((short)(z+0.5)))/2.0;
        }
        
        float f(short i, float x){
            if(i%2 == 0 && x!=0){
                return sin(val(i)*x);
            }
            else if(i%2 == 1 && x!=0){
                return val(i)/x;
            }
        }
        
        float g(){
            return (float)(log10(m));
        }
        
        ostream& put(ostream & os)const{
            A::put(os);
            os << "{ m = " << m << "}";
            return os;
        }
};

ostream & operator<<(ostream & left, const A& a){
    return a.put(left);
}


int main(){
    srand(111222333);
    A *vett[DIM];

    string w;
    short s1, s2;

    for(int i=0; i<DIM; i++){
        if(rand()%2==0){ //B
			w = "";
			s1 = rand()%20 + 5;
			s2 = rand()%20 + 5;
			short len = rand()%50 + 10; 
			for(int j=0; j<len; j++)
				w+=((rand()%2) ? (char) (rand()%26 + 'a') : (char) (rand()%10 + '0'));
				vett[i] = new B(w, s1, s2);
        }
        else{ // C
			int max = 10;
			float z = ((float) rand())/INT_MAX * (rand()%max) + 1.0; 
			vett[i] = new C(z);
        }
    }
    
    for(int i=0; i<DIM; i++){
        cout << i << ")" <<  *vett[i] << endl;
        if(typeid(*vett[i]) == typeid(C)){
            cout << "g()=" << ((C*)(vett[i]))->g() << endl;
        }
    }
    
    cout << "Punto II: Indici  per cui f( 5, 0.5 )<0.5:";
    for(int i= 0; i<DIM; i++){
        if(vett[i]->f(5,0.5) < 0.5) cout << i << " ";
    }
    cout << endl;
    float sum =0;
    int counter=0;
    for(int i= 0; i<DIM; i++){
        C* ptr = dynamic_cast <C*>(vett[i]);
        if(ptr){
            sum+= ptr->g();
            counter++;
        }
    }
    cout << "Punto III: (media dei valori del metodo g()): " << sum/counter << endl;
    
    return 0;
}
