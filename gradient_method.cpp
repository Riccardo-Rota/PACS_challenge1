#include "gradient_method.hpp"

//Implementation of the centered finite difference algorithm to evaluate the gradient
Point gm::gradient_fd(func f, Point x, double h){
    size_t N=x.get_dim();
    Point grad(N);
    for (size_t i=0; i<N; ++i){
        Point e(N);
        e[i]= h;
        grad[i]= (f(x+e) - f(x-e)) / (2*h);
    }
    return grad;
}

//Implementation of the different rules for alpha
double gm::armijo_rule(Point x, func f, Point grad_x, double alpha_0, double sigma){
    if ( f(x) -f(x - alpha_0 * grad_x) >= sigma * alpha_0 * pow( (grad_x).norm(), 2) ){
        return alpha_0;
    }
    return gm::armijo_rule(x, f, grad_x, alpha_0 / 2, sigma);
}