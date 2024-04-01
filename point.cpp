#include "point.hpp"

size_t Point::get_dim() const{
    return dim;
}

vector<double> Point::get_coordinates() const{
    return coordinates;
}

double& Point::operator[](size_t i){
    return coordinates[i];
}

double Point::distance(Point y) const{
    if (dim != y.get_dim()){
        std::cerr << "Cannot compute the distance between two points with different dimensions" << std::endl;
        return -1;
    }
    double d=0;
    vector<double> coord_y= y.get_coordinates();
    for (size_t i=0; i<dim; ++i){
        d+= (coord_y[i] - coordinates[i]) * (coord_y[i] - coordinates[i]);
    }
    d=std::sqrt(d);
    return d;
}

double distance(Point x, Point y){
    return x.distance(y);
}

double Point::norm() const{
    Point O(this->get_dim());  //initialize the n-dim zero point O
    return this -> distance(O); //computes the norm, i.e. the distance of the point from O
}

void Point::print() const{
    std::cout << "( ";
    for (size_t i=0; i<dim-1; ++i){
        std::cout << coordinates[i] << ", ";
    }
    std::cout << coordinates[dim-1] << " )" << std::endl;
}


//@note The good rule is to first define the *= operator as
//      a member function, and then define the * operator as
//      a friend function. This is because the *= operator
//      modifies the object, while the * operator does not.


Point operator*(double a, Point x){
    size_t n=x.get_dim();
    vector<double> vx= x.get_coordinates();
    vector<double> vy(n,0);
    for (size_t i=0; i<n; ++i)
        vy[i]= a*vx[i];
    
    Point y(vy);
    return y;
}

Point operator+(Point x, Point y){
     if (x.get_dim() != y.get_dim()){
        std::cerr << "Cannot compute the sum of two points with different dimensions" << std::endl;
        Point p;
        return p;
    }
    size_t n=x.get_dim();
    vector<double> vx= x.get_coordinates();
    vector<double> vy=y.get_coordinates();
    vector<double> vres(n, 0);

    for (size_t i=0; i<n; ++i)
        vres[i]= vx[i]+vy[i];
    
    Point res(vres);
    return res;
}

Point Point::operator-() const{
    vector<double> vres(dim, 0);

    for (size_t i=0; i<dim; ++i)
        vres[i]= -coordinates[i];
    
    Point res(vres);
    return res;
}

Point operator-(Point x, Point y){
    return x + (-y);
}