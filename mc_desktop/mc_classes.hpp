#ifndef MC_CLASSES_HPP
#define MC_CLASSES_HPP
#include<vector>
class face
{
    double p1[3];
    double p2[3];//punkty definiujace sciane
    double p3[3];
    double x_1,x_2,y_2,z_1,z_2;//wymiary sciany
    double cosa,cosb,cosg,sina,sinb,sing;//trygonometria katow wektora normalnego
    double x_trana(double,double,double);//transformacja obrotu ukladu wokol osi z
    double y_trana(double,double,double);
    double z_trana(double,double,double);
    double x_tranb(double,double,double);//transformacja obrotu ukladu wokol osi x
    double y_tranb(double,double,double);
    double z_tranb(double,double,double);
public:
    face(double,double,double,double,double,double,double,double,double);
    double show_x1();
    double show_x2();
    double show_y2();
    double show_z1();
    double show_z2();
    double x_tran(double,double,double);
    double y_tran(double,double,double);
    double z_tran(double,double,double);
    double x_retran(double,double,double);
    double y_retran(double,double,double);
    double z_retran(double,double,double);
};

class magnet
{
    double d1,d2,d3;
    double Jx,Jy,Jz;
    int f_number;
    std::vector<face> f;
    double pi,u0;
    double k(double,double,double,double,double,double);
    double atg(double,double,double,double,double,double);
    double Hx(double,double,double,double,double,double,double,double,double);
    double Hy(double,double,double,double,double,double,double,double,double);
    double Hz(double,double,double,double,double,double,double,double,double);
    double xgradB(double,double,double,double,double,double,double,double,double);
    double ygradB(double,double,double,double,double,double,double,double,double);
    double zgradB(double,double,double,double,double,double,double,double,double);
public:
    magnet(double,double,double,double,double,double);
    ~magnet();
    double Hx(double,double,double);
    double Hy(double,double,double);
    double Hz(double,double,double);
    double xgradB(double,double,double);
    double ygradB(double,double,double);
    double zgradB(double,double,double);
};
#endif // MC_CLASSES_HPP


