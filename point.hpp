#ifndef POINT_H
#define POINT_H


#include<vector>
#include<iostream>
#include<cmath>
using std::vector;

class Point{
    vector<double> coordinates={0};
    size_t dim=1;

    public:

    Point()=default;

    Point(vector<double> c):
        coordinates(c), dim(c.size()) {};    

    Point(size_t n): dim(n) {
        this->coordinates=vector<double>(n, 0);
    };

    //getters
    vector<double> get_coordinates() const;
    size_t get_dim() const;

    double distance(Point y) const;
    double norm() const;
    void print() const;

    Point operator-() const;
    double& operator[](size_t i); // access to the i-th element

};

double distance(Point x, Point y);

Point operator*(double a, Point x);
Point operator+(Point x, Point y);
Point operator-(Point x, Point y);


#endif // POINT_H