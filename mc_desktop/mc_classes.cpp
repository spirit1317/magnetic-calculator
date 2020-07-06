#include "mc_classes.hpp"
#include<math.h>
#include<iostream>
#include<vector>

face::face(double x1_in,double y1_in,double z1_in,double x2_in,double y2_in,double z2_in,double x3_in,double y3_in,double z3_in){
    //zamiast listy inicjalizacyjnej (czemu nie moze byc lista?)
    p1[0]=x1_in;
    p1[1]=y1_in;
    p1[2]=z1_in;
    p2[0]=x2_in;
    p2[1]=y2_in;
    p2[2]=z2_in;
    p3[0]=x3_in;
    p3[1]=y3_in;
    p3[2]=z3_in;
    //obliczanie wektora normalnego
    double v12[3];
    double v23[3];
    v12[0]=p2[0]-p1[0];
    v12[1]=p2[1]-p1[1];
    v12[2]=p2[2]-p1[2];
    v23[0]=p3[0]-p2[0];
    v23[1]=p3[1]-p2[1];
    v23[2]=p3[2]-p2[2];
    double n[3];
    n[0]=v12[1]*v23[2]-v12[2]*v23[1];
    n[1]=v12[2]*v23[0]-v12[0]*v23[2];
    n[2]=v12[0]*v23[1]-v12[1]*v23[0];
    //obliczanie trygonometryczne alfa
    cosa=n[1]/sqrt(n[0]*n[0]+n[1]*n[1]);
    sina=-n[0]/sqrt(n[0]*n[0]+n[1]*n[1]);
    //obliczanie trygonom. beta - czy dobrze ?
    cosb=y_trana(n[0],n[1],n[2])/sqrt(n[0]*n[0]+n[1]*n[1]+n[2]*n[2]);
    sinb=n[2]/sqrt(n[0]*n[0]+n[1]*n[1]+n[2]*n[2]);
    //obliczanie trygonom. gamma
    double x1,x2,y1,y2,z1,z2;
    x1=x_tranb(x_trana(p1[0],p1[1],p1[2]),y_trana(p1[0],p1[1],p1[2]),z_trana(p1[0],p1[1],p1[2]));
    //y1=y_tranb(x_trana(p1[0],p1[1],p1[2]),y_trana(p1[0],p1[1],p1[2]),z_trana(p1[0],p1[1],p1[2]));
    z1=z_tranb(x_trana(p1[0],p1[1],p1[2]),y_trana(p1[0],p1[1],p1[2]),z_trana(p1[0],p1[1],p1[2]));
    x2=x_tranb(x_trana(p2[0],p2[1],p2[2]),y_trana(p2[0],p2[1],p2[2]),z_trana(p2[0],p2[1],p2[2]));
    //y2=y_tranb(x_trana(p2[0],p2[1],p2[2]),y_trana(p2[0],p2[1],p2[2]),z_trana(p2[0],p2[1],p2[2]));
    z2=z_tranb(x_trana(p2[0],p2[1],p2[2]),y_trana(p2[0],p2[1],p2[2]),z_trana(p2[0],p2[1],p2[2]));
    cosg=-(x2-x1)/sqrt((x2-x1)*(x2-x1)+(z2-z1)*(z2-z1));
    sing=(z2-z1)/sqrt((x2-x1)*(x2-x1)+(z2-z1)*(z2-z1));
    //obliczanie bokow prostokata
    x_1=0;
    x_2=-sqrt(p2[0]*p2[0]+p2[1]*p2[1]+p2[2]*p2[2]);
    y_2=0;
    z_1=0;
    z_2=z_tran(p3[0],p3[1],p3[2]);//UWAGA - tylko zetowa skladowa - rownoleglobok traktowany jest jak prostokat
}
double face::show_x1(){
return x_1;
}
double face::show_x2(){
return x_2;
}
double face::show_y2(){
return y_2;
}
double face::show_z1(){
return z_1;
}
double face::show_z2(){
return z_2;
}
double face::x_trana(double x,double y,double z){
    return cosa*x+sina*y;
}
double face::y_trana(double x,double y,double z){
    return -sina*x+cosa*y;
}
double face::z_trana(double x,double y,double z){
    return z;
}
double face::x_tranb(double x,double y,double z){
    return x;
}
double face::y_tranb(double x,double y,double z){
    return cosb*y+sinb*z;
}
double face::z_tranb(double x,double y,double z){
    return -sinb*y+cosb*z;
}
double face::x_tran(double x,double y, double z){
double x_t,y_t,z_t,x_temp;
//transformacja wokol osi z o kat a
x_t=x_trana(x,y,z);
y_t=y_trana(x,y,z);
z_t=z_trana(x,y,z);
//transformacja wokol osi x o kat b
x_temp=x_tranb(x_t,y_t,z_t);
z_t=z_tranb(x_t,y_t,z_t);
x_t=x_temp;
//transformacja wokol osi y o kat g + translacja srodka ukladu
std::cout<<cosg<<" "<<x_t<<" "<<sing<<" "<<z_t<<" "<<p1[0]<<std::endl;
return cosg*x_t-sing*z_t-p1[0];
}
double face::y_tran(double x,double y, double z){
double x_t,y_t,z_t;
//transformacja wokol osi z o kat a
x_t=x_trana(x,y,z);
y_t=y_trana(x,y,z);
z_t=z_trana(x,y,z);
//transformacja wokol osi x o kat b
y_t=y_tranb(x_t,y_t,z_t);
//transformacja wokol osi y o kat g
return y_t     -p1[1];
}
double face::z_tran(double x,double y, double z){
double x_t,y_t,z_t,x_temp;
//transformacja wokol osi z o kat a
x_t=x_trana(x,y,z);
y_t=y_trana(x,y,z);
z_t=z_trana(x,y,z);
//transformacja wokol osi x o kat b
x_temp=x_tranb(x_t,y_t,z_t);
z_t=z_tranb(x_t,y_t,z_t);
x_t=x_temp;
//transformacja wokol osi y o kat g
return sing*x_t+cosg*z_t     -p1[2];
}
double face::x_retran(double x,double y, double z){
    double x_t,y_t,z_t,x_temp,y_temp;
    //translacja wsteczna
    x_t=x+p1[0];
    y_t=y+p1[1];
    z_t=z+p1[2];
    //transformacja wokol osi y o kat -g
    x_temp=cosg*x_t+sing*z_t;
    y_t=y_t;
    z_t=-sing*x_t+cosg*z_t;
    x_t=x_temp;
    //transformacja wokol osi x o kat -b
    x_t=x_t;
    y_temp=cosb*y_t-sinb*z_t;
    z_t=sinb*y_t+cosb*z_t;
    y_t=y_temp;
    //transformacja wokol osi z o kat -a
    return cosa*x_t-sina*y_t;
}
double face::y_retran(double x,double y, double z){
    double x_t,y_t,z_t,x_temp,y_temp;
    //translacja wsteczna
    x_t=x+p1[0];
    y_t=y+p1[1];
    z_t=z+p1[2];
    //transformacja wokol osi y o kat -g
    x_temp=cosg*x_t+sing*z_t;
    y_t=y_t;
    z_t=-sing*x_t+cosg*z_t;
    x_t=x_temp;
    //transformacja wokol osi x o kat -b
    x_t=x_t;
    y_temp=cosb*y_t-sinb*z_t;
    z_t=sinb*y_t+cosb*z_t;
    y_t=y_temp;
    //transformacja wokol osi z o kat -a
    return sina*x_t+cosa*y_t;
}
double face::z_retran(double x,double y, double z){
    double x_t,y_t,z_t,x_temp;
    //translacja wsteczna
    x_t=x+p1[0];
    y_t=y+p1[1];
    z_t=z+p1[2];
    //transformacja wokol osi y o kat -g
    x_temp=cosg*x_t+sing*z_t;
    y_t=y_t;
    z_t=-sing*x_t+cosg*z_t;
    x_t=x_temp;
    //transformacja wokol osi x o kat -b
    z_t=sinb*y_t+cosb*z_t;
    //transformacja wokol osi z o kat -a
    return z_t;
}


magnet::magnet(double d1_in,double d2_in,double d3_in,double Jx_in,double Jy_in,double Jz_in)    : d1(d1_in), d2(d2_in),d3(d3_in),  Jx(Jx_in) , Jy(Jy_in) , Jz(Jz_in){
    pi=3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211;
    u0=1.2566*0.000001;//[H/m]
    //automatyczna inicjacja szescianu
    /*f_number = 6;
    f.push_back(face(d/2,-d/2,-d/2,d/2,d/2,-d/2,d/2,d/2,d/2));
    f.push_back(face(d/2,d/2,-d/2,-d/2,d/2,-d/2,-d/2,d/2,d/2));
    f.push_back(face(-d/2,d/2,-d/2,-d/2,-d/2,-d/2,-d/2,-d/2,d/2));
    f.push_back(face(-d/2,-d/2,-d/2,d/2,-d/2,-d/2,d/2,-d/2,d/2));
    f.push_back(face(d/2,-d/2,d/2,d/2,d/2,d/2,-d/2,d/2,d/2));
    f.push_back(face(-d/2,-d/2,-d/2,-d/2,d/2,-d/2,d/2,d/2,-d/2));
    //f.resize(f_number);h*/
}
magnet::~magnet(){

}
double magnet::k(double x,double y,double z,double a,double b,double c){
    return sqrt((x-a)*(x-a)+(y-b)*(y-b)+(z-c)*(z-c));
}
double magnet::atg(double x, double y, double z,double xi,double y2,double zk){
    return atan((x-xi)*(z-zk)/((y-y2)*k(x,y,z,xi,y2,zk)));
}
double magnet::Hx(double x,double y,double z,double x1,double x2,double y2,double z1,double z2,double J){
    return (1./(4*pi*u0))*J*log(((z-z1+k(x,y,z,x2,y2,z1))*(z-z2+k(x,y,z,x1,y2,z2)))/((z-z2+k(x,y,z,x2,y2,z2))*(z-z1+k(x,y,z,x1,y2,z1))));
}
double magnet::Hy(double x,double y,double z,double x1,double x2,double y2,double z1,double z2,double J){
    return (1./(4*pi*u0))*J*(atg(x,y,z,x1,y2,z1)-atg(x,y,z,x2,y2,z1)+atg(x,y,z,x2,y2,z2)-atg(x,y,z,x1,y2,z2));
}
double magnet::Hz(double x,double y,double z,double x1,double x2,double y2,double z1,double z2,double J){
    return (1./(4*pi*u0))*J*log(((x-x2+k(x,y,z,x2,y2,z1))*(x-x1+k(x,y,z,x1,y2,z2)))/((x-x1+k(x,y,z,x1,y2,z1))*(x-x2+k(x,y,z,x2,y2,z2))));
}
double magnet::Hx(double x,double y,double z){
    double H=0;
    //gora
    double x_temp=y;
    double y_temp=z;
    double z_temp=x;
    H+=Hz(x_temp,y_temp,z_temp,-d2/2,d2/2,d3/2,-d1/2,d1/2,Jz);
    //dol
    x_temp=-y;
    y_temp=-z;
    z_temp=x;
    H+=Hz(x_temp,y_temp,z_temp,-d2/2,d2/2,d3/2,-d1/2,d1/2,-Jz);
    //prawo
    H+=Hx(x,y,z,-d1/2,d1/2,d2/2,-d3/2,d3/2,Jy);
    //lewo
    x_temp=z;
    y_temp=-y;
    z_temp=x;
    H+=Hz(x_temp,y_temp,z_temp,-d3/2,d3/2,d2/2,-d1/2,d1/2,-Jy);
    //przod
    x_temp=z;
    y_temp=x;
    z_temp=y;
    H+=Hy(x_temp,y_temp,z_temp,-d3/2,d3/2,d1/2,-d2/2,d2/2,Jx);
    //tyl
    x_temp=y;
    y_temp=-x;
    z_temp=z;
    H-=Hy(x_temp,y_temp,z_temp,-d2/2,d2/2,d1/2,-d3/2,d3/2,-Jx);
    return H;
}
double magnet::Hy(double x,double y,double z){
    double H=0;
    //gora
    double x_temp=y;
    double y_temp=z;
    double z_temp=x;
    H+=Hx(x_temp,y_temp,z_temp,-d2/2,d2/2,d3/2,-d1/2,d1/2,Jz);
    //dol
    x_temp=-y;
    y_temp=-z;
    z_temp=x;
    H-=Hx(x_temp,y_temp,z_temp,-d2/2,d2/2,d3/2,-d1/2,d1/2,-Jz);
    //prawo
    H+=Hy(x,y,z,-d1/2,d1/2,d2/2,-d3/2,d3/2,Jy);
    //lewo
    x_temp=z;
    y_temp=-y;
    z_temp=x;
    H-=Hy(x_temp,y_temp,z_temp,-d3/2,d3/2,d2/2,-d1/2,d1/2,-Jy);
    //przod
    x_temp=z;
    y_temp=x;
    z_temp=y;
    H+=Hz(x_temp,y_temp,z_temp,-d3/2,d3/2,d1/2,-d2/2,d2/2,Jx);
    //tyl
    x_temp=y;
    y_temp=-x;
    z_temp=z;
    H+=Hx(x_temp,y_temp,z_temp,-d2/2,d2/2,d1/2,-d3/2,d3/2,-Jx);
    return H;
}
double magnet::Hz(double x,double y,double z){
    double H=0;
    //gora
    double x_temp=y;
    double y_temp=z;
    double z_temp=x;
    H+=Hy(x_temp,y_temp,z_temp,-d2/2,d2/2,d3/2,-d1/2,d1/2,Jz);
    //dol
    x_temp=-y;
    y_temp=-z;
    z_temp=x;
    H-=Hy(x_temp,y_temp,z_temp,-d2/2,d2/2,d3/2,-d1/2,d1/2,-Jz);
    //prawo
    H+=Hz(x,y,z,-d1/2,d1/2,d2/2,-d3/2,d3/2,Jy);
    //lewo
    x_temp=z;
    y_temp=-y;
    z_temp=x;
    H+=Hx(x_temp,y_temp,z_temp,-d3/2,d3/2,d2/2,-d1/2,d1/2,-Jy);
    //przod
    x_temp=z;
    y_temp=x;
    z_temp=y;
    H+=Hx(x_temp,y_temp,z_temp,-d3/2,d3/2,d1/2,-d2/2,d2/2,Jx);
    //tyl
    x_temp=y;
    y_temp=-x;
    z_temp=z;
    H+=Hz(x_temp,y_temp,z_temp,-d2/2,d2/2,d1/2,-d3/2,d3/2,-Jx);
    return H;
}
double magnet::xgradB(double x,double y,double z,double x1,double x2,double y2,double z1,double z2,double J){
    return (J*((((-((pow(x - x1,2)*(z - z1))/((y - y2)*pow(pow(x - x1,2) + pow(y - y2,2) + pow(z - z1,2),1.5))) +
                  (z - z1)/((y - y2)*sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z1,2))))/
                (1 + (pow(x - x1,2)*pow(z - z1,2))/(pow(y - y2,2)*(pow(x - x1,2) + pow(y - y2,2) + pow(z - z1,2)))) -
               (-((pow(x - x2,2)*(z - z1))/((y - y2)*pow(pow(x - x2,2) + pow(y - y2,2) + pow(z - z1,2),1.5))) +
                  (z - z1)/((y - y2)*sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z1,2))))/
                (1 + (pow(x - x2,2)*pow(z - z1,2))/(pow(y - y2,2)*(pow(x - x2,2) + pow(y - y2,2) + pow(z - z1,2)))) -
               (-((pow(x - x1,2)*(z - z2))/((y - y2)*pow(pow(x - x1,2) + pow(y - y2,2) + pow(z - z2,2),1.5))) +
                  (z - z2)/((y - y2)*sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z2,2))))/
                (1 + (pow(x - x1,2)*pow(z - z2,2))/(pow(y - y2,2)*(pow(x - x1,2) + pow(y - y2,2) + pow(z - z2,2)))) +
               (-((pow(x - x2,2)*(z - z2))/((y - y2)*pow(pow(x - x2,2) + pow(y - y2,2) + pow(z - z2,2),1.5))) +
                  (z - z2)/((y - y2)*sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z2,2))))/
                (1 + (pow(x - x2,2)*pow(z - z2,2))/(pow(y - y2,2)*(pow(x - x2,2) + pow(y - y2,2) + pow(z - z2,2)))))*
             (atan(((x - x1)*(z - z1))/((y - y2)*sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z1,2)))) -
               atan(((x - x2)*(z - z1))/((y - y2)*sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z1,2)))) -
               atan(((x - x1)*(z - z2))/((y - y2)*sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z2,2)))) +
               atan(((x - x2)*(z - z2))/((y - y2)*sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z2,2))))))/(8.*pow(pi,2)) +
          ((-((1 + (x - x1)/sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z1,2)))/
                  (x - x1 + sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z1,2)))) +
               (1 + (x - x2)/sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z1,2)))/
                (x - x2 + sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z1,2))) +
               (1 + (x - x1)/sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z2,2)))/
                (x - x1 + sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z2,2))) -
               (1 + (x - x2)/sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z2,2)))/
                (x - x2 + sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z2,2))))*
             (-log(x - x1 + sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z1,2))) +
               log(x - x2 + sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z1,2))) +
               log(x - x1 + sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z2,2))) -
               log(x - x2 + sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z2,2)))))/(8.*pow(pi,2)) +
          ((-((x - x1)/(sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z1,2))*
                    (z + sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z1,2)) - z1))) +
               (x - x2)/(sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z1,2))*
                  (z + sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z1,2)) - z1)) +
               (x - x1)/(sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z2,2))*
                  (z + sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z2,2)) - z2)) -
               (x - x2)/(sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z2,2))*
                  (z + sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z2,2)) - z2)))*
             (-log(z + sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z1,2)) - z1) +
               log(z + sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z1,2)) - z1) +
               log(z + sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z2,2)) - z2) -
               log(z + sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z2,2)) - z2)))/(8.*pow(pi,2))))/
             atan(((x - x2)*(z - z1))/((y - y2)*sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z1,2)))) -
      (2.*sqrt(pow(atan(((x - x1)*(z - z1))/((y - y2)*sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z1,2)))) -
             atan(((x - x1)*(z - z2))/((y - y2)*sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z2,2)))) +
             atan(((x - x2)*(z - z2))/((y - y2)*sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z2,2)))),2)/(16.*pow(pi,2)) +
          pow(-log(x - x1 + sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z1,2))) +
             log(x - x2 + sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z1,2))) +
             log(x - x1 + sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z2,2))) -
             log(x - x2 + sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z2,2))),2)/(16.*pow(pi,2)) +
          pow(-log(z + sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z1,2)) - z1) +
             log(z + sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z1,2)) - z1) +
             log(z + sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z2,2)) - z2) -
             log(z + sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z2,2)) - z2),2)/(16.*pow(pi,2))));
    }
double magnet::ygradB(double x,double y,double z,double x1,double x2,double y2,double z1,double z2,double J){
    return (J*((((-(((x - x1)*(z - z1))/pow(pow(x - x1,2) + pow(y - y2,2) + pow(z - z1,2),1.5)) -
                  ((x - x1)*(z - z1))/(pow(y - y2,2)*sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z1,2))))/
                (1 + (pow(x - x1,2)*pow(z - z1,2))/(pow(y - y2,2)*(pow(x - x1,2) + pow(y - y2,2) + pow(z - z1,2)))) -
               (-(((x - x2)*(z - z1))/pow(pow(x - x2,2) + pow(y - y2,2) + pow(z - z1,2),1.5)) -
                  ((x - x2)*(z - z1))/(pow(y - y2,2)*sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z1,2))))/
                (1 + (pow(x - x2,2)*pow(z - z1,2))/(pow(y - y2,2)*(pow(x - x2,2) + pow(y - y2,2) + pow(z - z1,2)))) -
               (-(((x - x1)*(z - z2))/pow(pow(x - x1,2) + pow(y - y2,2) + pow(z - z2,2),1.5)) -
                  ((x - x1)*(z - z2))/(pow(y - y2,2)*sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z2,2))))/
                (1 + (pow(x - x1,2)*pow(z - z2,2))/(pow(y - y2,2)*(pow(x - x1,2) + pow(y - y2,2) + pow(z - z2,2)))) +
               (-(((x - x2)*(z - z2))/pow(pow(x - x2,2) + pow(y - y2,2) + pow(z - z2,2),1.5)) -
                  ((x - x2)*(z - z2))/(pow(y - y2,2)*sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z2,2))))/
                (1 + (pow(x - x2,2)*pow(z - z2,2))/(pow(y - y2,2)*(pow(x - x2,2) + pow(y - y2,2) + pow(z - z2,2)))))*
             (atan(((x - x1)*(z - z1))/((y - y2)*sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z1,2)))) -
               atan(((x - x2)*(z - z1))/((y - y2)*sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z1,2)))) -
               atan(((x - x1)*(z - z2))/((y - y2)*sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z2,2)))) +
               atan(((x - x2)*(z - z2))/((y - y2)*sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z2,2))))))/(8.*pow(pi,2)) +
          ((-((y - y2)/((x - x1 + sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z1,2)))*
                    sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z1,2)))) +
               (y - y2)/((x - x2 + sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z1,2)))*
                  sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z1,2))) +
               (y - y2)/((x - x1 + sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z2,2)))*
                  sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z2,2))) -
               (y - y2)/((x - x2 + sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z2,2)))*
                  sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z2,2))))*
             (-log(x - x1 + sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z1,2))) +
               log(x - x2 + sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z1,2))) +
               log(x - x1 + sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z2,2))) -
               log(x - x2 + sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z2,2)))))/(8.*pow(pi,2)) +
          ((-((y - y2)/(sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z1,2))*
                    (z + sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z1,2)) - z1))) +
               (y - y2)/(sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z1,2))*
                  (z + sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z1,2)) - z1)) +
               (y - y2)/(sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z2,2))*
                  (z + sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z2,2)) - z2)) -
               (y - y2)/(sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z2,2))*
                  (z + sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z2,2)) - z2)))*
             (-log(z + sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z1,2)) - z1) +
               log(z + sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z1,2)) - z1) +
               log(z + sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z2,2)) - z2) -
               log(z + sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z2,2)) - z2)))/(8.*pow(pi,2))))/
      (2.*sqrt(pow(atan(((x - x1)*(z - z1))/((y - y2)*sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z1,2)))) -
             atan(((x - x2)*(z - z1))/((y - y2)*sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z1,2)))) -
             atan(((x - x1)*(z - z2))/((y - y2)*sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z2,2)))) +
             atan(((x - x2)*(z - z2))/((y - y2)*sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z2,2)))),2)/(16.*pow(pi,2)) +
          pow(-log(x - x1 + sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z1,2))) +
             log(x - x2 + sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z1,2))) +
             log(x - x1 + sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z2,2))) -
             log(x - x2 + sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z2,2))),2)/(16.*pow(pi,2)) +
          pow(-log(z + sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z1,2)) - z1) +
             log(z + sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z1,2)) - z1) +
             log(z + sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z2,2)) - z2) -
             log(z + sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z2,2)) - z2),2)/(16.*pow(pi,2))));
}
double magnet::zgradB(double x,double y,double z,double x1,double x2,double y2,double z1,double z2,double J){
    return (J*(((((x - x1)/((y - y2)*sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z1,2))) -
                  ((x - x1)*pow(z - z1,2))/((y - y2)*pow(pow(x - x1,2) + pow(y - y2,2) + pow(z - z1,2),1.5)))/
                (1 + (pow(x - x1,2)*pow(z - z1,2))/(pow(y - y2,2)*(pow(x - x1,2) + pow(y - y2,2) + pow(z - z1,2)))) -
               ((x - x2)/((y - y2)*sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z1,2))) -
                  ((x - x2)*pow(z - z1,2))/((y - y2)*pow(pow(x - x2,2) + pow(y - y2,2) + pow(z - z1,2),1.5)))/
                (1 + (pow(x - x2,2)*pow(z - z1,2))/(pow(y - y2,2)*(pow(x - x2,2) + pow(y - y2,2) + pow(z - z1,2)))) -
               ((x - x1)/((y - y2)*sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z2,2))) -
                  ((x - x1)*pow(z - z2,2))/((y - y2)*pow(pow(x - x1,2) + pow(y - y2,2) + pow(z - z2,2),1.5)))/
                (1 + (pow(x - x1,2)*pow(z - z2,2))/(pow(y - y2,2)*(pow(x - x1,2) + pow(y - y2,2) + pow(z - z2,2)))) +
               ((x - x2)/((y - y2)*sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z2,2))) -
                  ((x - x2)*pow(z - z2,2))/((y - y2)*pow(pow(x - x2,2) + pow(y - y2,2) + pow(z - z2,2),1.5)))/
                (1 + (pow(x - x2,2)*pow(z - z2,2))/(pow(y - y2,2)*(pow(x - x2,2) + pow(y - y2,2) + pow(z - z2,2)))))*
             (atan(((x - x1)*(z - z1))/((y - y2)*sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z1,2)))) -
               atan(((x - x2)*(z - z1))/((y - y2)*sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z1,2)))) -
               atan(((x - x1)*(z - z2))/((y - y2)*sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z2,2)))) +
               atan(((x - x2)*(z - z2))/((y - y2)*sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z2,2))))))/(8.*pow(pi,2)) +
          ((-((z - z1)/((x - x1 + sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z1,2)))*
                    sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z1,2)))) +
               (z - z1)/((x - x2 + sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z1,2)))*
                  sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z1,2))) +
               (z - z2)/((x - x1 + sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z2,2)))*
                  sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z2,2))) -
               (z - z2)/((x - x2 + sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z2,2)))*
                  sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z2,2))))*
             (-log(x - x1 + sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z1,2))) +
               log(x - x2 + sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z1,2))) +
               log(x - x1 + sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z2,2))) -
               log(x - x2 + sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z2,2)))))/(8.*pow(pi,2)) +
          ((-((1 + (z - z1)/sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z1,2)))/
                  (z + sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z1,2)) - z1)) +
               (1 + (z - z1)/sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z1,2)))/
                (z + sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z1,2)) - z1) +
               (1 + (z - z2)/sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z2,2)))/
                (z + sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z2,2)) - z2) -
               (1 + (z - z2)/sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z2,2)))/
                (z + sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z2,2)) - z2))*
             (-log(z + sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z1,2)) - z1) +
               log(z + sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z1,2)) - z1) +
               log(z + sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z2,2)) - z2) -
               log(z + sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z2,2)) - z2)))/(8.*pow(pi,2))))/
      (2.*sqrt(pow(atan(((x - x1)*(z - z1))/((y - y2)*sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z1,2)))) -
             atan(((x - x2)*(z - z1))/((y - y2)*sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z1,2)))) -
             atan(((x - x2)*(z - z2))/((y - y2)*sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z2,2)))),2)/(16.*pow(pi,2)) +
             atan(((x - x1)*(z - z2))/((y - y2)*sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z2,2)))) +
          pow(-log(x - x1 + sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z1,2))) +
             log(x - x2 + sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z1,2))) +
             log(x - x1 + sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z2,2))) -
             log(x - x2 + sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z2,2))),2)/(16.*pow(pi,2)) +
          pow(-log(z + sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z1,2)) - z1) +
             log(z + sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z1,2)) - z1) +
             log(z + sqrt(pow(x - x1,2) + pow(y - y2,2) + pow(z - z2,2)) - z2) -
             log(z + sqrt(pow(x - x2,2) + pow(y - y2,2) + pow(z - z2,2)) - z2),2)/(16.*pow(pi,2))));
}
double magnet::xgradB(double x,double y,double z){
    double gradB_x=0;
    //gora
    double x_temp=y;
    double y_temp=z;
    double z_temp=x;
    gradB_x+=zgradB(x_temp,y_temp,z_temp,-d2/2,d2/2,d3/2,-d1/2,d1/2,Jz);
    //dol
    x_temp=-y;
    y_temp=-z;
    z_temp=x;
    gradB_x+=zgradB(x_temp,y_temp,z_temp,-d2/2,d2/2,d3/2,-d1/2,d1/2,-Jz);
    //prawo
    gradB_x+=xgradB(x,y,z,-d1/2,d1/2,d2/2,-d3/2,d3/2,Jy);
    //lewo
    x_temp=z;
    y_temp=-y;
    z_temp=x;
    gradB_x+=zgradB(x_temp,y_temp,z_temp,-d3/2,d3/2,d2/2,-d1/2,d1/2,-Jy);
    //przod
    x_temp=z;
    y_temp=x;
    z_temp=y;
    gradB_x+=ygradB(x_temp,y_temp,z_temp,-d3/2,d3/2,d1/2,-d2/2,d2/2,Jx);
    //tyl
    x_temp=y;
    y_temp=-x;
    z_temp=z;
    gradB_x-=ygradB(x_temp,y_temp,z_temp,-d2/2,d2/2,d1/2,-d3/2,d3/2,-Jx);
    return gradB_x;
}
double magnet::ygradB(double x,double y,double z){
    double gradB_y=0;
    //gora
    double x_temp=y;
    double y_temp=z;
    double z_temp=x;
    gradB_y+=xgradB(x_temp,y_temp,z_temp,-d2/2,d2/2,d3/2,-d1/2,d1/2,Jz);
    //dol
    x_temp=-y;
    y_temp=-z;
    z_temp=x;
    gradB_y-=xgradB(x_temp,y_temp,z_temp,-d2/2,d2/2,d3/2,-d1/2,d1/2,-Jz);
    //prawo
    gradB_y+=ygradB(x,y,z,-d1/2,d1/2,d2/2,-d3/2,d3/2,Jy);
    //lewo
    x_temp=z;
    y_temp=-y;
    z_temp=x;
    gradB_y-=ygradB(x_temp,y_temp,z_temp,-d3/2,d3/2,d2/2,-d1/2,d1/2,-Jy);
    //przod
    x_temp=z;
    y_temp=x;
    z_temp=y;
    gradB_y+=zgradB(x_temp,y_temp,z_temp,-d3/2,d3/2,d1/2,-d2/2,d2/2,Jx);
    //tyl
    x_temp=y;
    y_temp=-x;
    z_temp=z;
    gradB_y+=xgradB(x_temp,y_temp,z_temp,-d2/2,d2/2,d1/2,-d3/2,d3/2,-Jx);
    return gradB_y;
}
double magnet::zgradB(double x,double y,double z){
    double gradB_z=0;
    //gora
    double x_temp=y;
    double y_temp=z;
    double z_temp=x;
    gradB_z+=ygradB(x_temp,y_temp,z_temp,-d2/2,d2/2,d3/2,-d1/2,d1/2,Jz);
    //dol
    x_temp=-y;
    y_temp=-z;
    z_temp=x;
    gradB_z-=ygradB(x_temp,y_temp,z_temp,-d2/2,d2/2,d3/2,-d1/2,d1/2,-Jz);
    //prawo
    gradB_z+=zgradB(x,y,z,-d1/2,d1/2,d2/2,-d3/2,d3/2,Jy);
    //lewo
    x_temp=z;
    y_temp=-y;
    z_temp=x;
    gradB_z+=xgradB(x_temp,y_temp,z_temp,-d3/2,d3/2,d2/2,-d1/2,d1/2,-Jy);
    //przod
    x_temp=z;
    y_temp=x;
    z_temp=y;
    gradB_z+=xgradB(x_temp,y_temp,z_temp,-d3/2,d3/2,d1/2,-d2/2,d2/2,Jx);
    //tyl
    x_temp=y;
    y_temp=-x;
    z_temp=z;
    gradB_z+=zgradB(x_temp,y_temp,z_temp,-d2/2,d2/2,d1/2,-d3/2,d3/2,-Jx);
    return gradB_z;
}


