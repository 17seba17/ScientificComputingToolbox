#include<vector>
#include<iostream>
class ButcherTableau{

 std::vector<double> a_;
 Eigen::VectorXd b_;
Eigen::VectorXd c_;
size_t size_;

void createC(){
            
int S_a =a_.size();
int S_b =b_.size();
if((S_b-1)*S_b/2!=S_a){
    std::cerr<<"errore di compatibilità\n";
}
size_=S_b;
c_.resize(S_b); 
c_(0)=0.0;
int count=1;
double check=0.0;
for(int i=0;i<S_b-1;i++){
    check+=b_(i);


    double sum=0.0;
for(int j=0;j<count;j++){
sum+=(a_[count*(count-1)/2+j]);
}
c_(i)=sum;

}
check+=b_(S_b-1);
if(check-1>0.01||1-check>0.01){std::cerr<<"err";}

if(c_.size()!=b_.size()){std::cerr<<"err2";}
}//creating C

public:
    ButcherTableau(std::vector<double> a, Eigen::VectorXd b) : a_(std::move(a)), b_(std::move(b)) {
createC();
}

    ButcherTableau(std::vector<double> a, std::vector<double> b) : a_(std::move(a)) {
b_(Eigen::Map<const Eigen::VectorXd>(b.data(), b.size())) ;
createC();
}

double getA(unsigned int i, unsigned int j)const{
if(i>=j){return 0.0;}
if(i==0){return 0.0;}
return a_[j*(j-1)/2+i];


}
double getB(unsigned int i)const{return b_(i);}
double getC(unsigned int i)const{return c_(i);}

Eigen::VectorXd getB()const{
    return b_;
}

size_t size()const{
    return size_;
}
};


