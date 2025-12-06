#include "../include/ButcherTableau.hpp"
namespace SCT{
namespace ODE{


void ButcherTableau::createC(){



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
count++;
c_(i)=sum;

}
check+=b_(S_b-1);
if(check-1>0.01||1-check>0.01){std::cerr<<"err";}

if(c_.size()!=b_.size()){std::cerr<<"err2";}
}//creating C


}}