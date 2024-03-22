#include <iostream>
#include "gradient_method.hpp"
#include <functional>
#include <cmath>

int main(){
    
    //definition of f
    auto f = [](Point x) -> double { return x[0] * x[1] + 4 * pow(x[0], 4) + pow(x[1], 2) + 3 * x[0]; };

    //definition of the gradient of f
    auto grad_f= [](Point x) -> Point { 
        double d0 = x[1] + 16 * pow(x[0], 3) + 3;
        double d1 = x[0] + 2 * x[1];
        return Point ({d0, d1});
    };



    gm::Parameters p;
    //Parameters are set by default to these values, they can be changed uncommenting the following lines:
    //p.step_tol=1e-6;
    //p.res_tol=1e-6;
    //p.alpha_0=0.1;
    //p.max_iter=1e6;
    //p.h=1e-2;
    //p.eta=0.9;
    //p.sigma=0.25;

    gm::Data d;
    d.f = f;
    d.grad_f = grad_f;
    d.x0 = Point({0, 0});

    std::cout << "Applying the gradient method with armjo rule and the exact gradient given by the user" << std::endl;
    p.alpha_0 = 0.5;
    Point x = gm::minimize<gm::gradient, gm::exact, gm::armijo>(d,p);
    std::cout << "Minimum found at: ";
    x.print();

    //YOU CAN UNCOMMENT THE FOLLOWING BLOCKS TO SEE THE APPLICATION OF DIFFERENT METHODS OR DIFFERENT OPTIONS, 
    //TRYING DIFFERENT COMBINATIONS

    // std::cout << "Applying the gradient method with constant alpha and fd gradient" << std::endl;
    // p.alpha_0 = 0.1;
    // Point x1 = gm::minimize<gm::gradient, gm::fd, gm::constant>(d,p);
    // std::cout << "Minimum found at: ";
    // x1.print();


    // std::cout << "Applying the gradient method with inverse rule and the exact gradient given by the user" << std::endl;
    // p.alpha_0 = 0.1;
    // Point x2 = gm::minimize<gm::gradient, gm::exact, gm::inverse>(d,p);
    // std::cout << "Minimum found at: ";
    // x2.print();


    // std::cout << "Applying the gradient method with exponential rule and fd gradient" << std::endl;
    // p.alpha_0 = 0.1;
    // Point x3 = gm::minimize<gm::gradient, gm::exact, gm::inverse>(d,p);
    // std::cout << "Minimum found at: ";
    // x3.print();


    // std::cout << "Applying the momentum method with the exact gradient given by the user" << std::endl;
    // p.alpha_0 = 0.04;
    // p.eta = 1 - p.alpha_0;
    // Point x4 = gm::minimize<gm::momentum, gm::exact>(d,p);
    // std::cout << "Minimum found at: ";
    // x4.print();


    // std::cout << "Applying the Nesterov method with fd gradient" << std::endl;
    // p.alpha_0=0.02;
    // p.eta = 1 - p.alpha_0;
    // Point x5 = gm::minimize<gm::nesterov, gm::fd>(d,p);
    // std::cout << "Minimum found at: ";
    // x5.print();
    
}