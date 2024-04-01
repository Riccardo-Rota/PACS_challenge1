#ifndef GRADIENT_METHOD_H
#define GRADIENT_METHOD_H


#include<iostream>
#include "point.hpp"
#include<functional>

//@note good the use of namespaces!
namespace gm{

    //definition of types
    using func = std::function<double(Point)>; //function f:Rn -> R
    using func_nd = std::function<Point(Point)>; //function f:Rn -> Rm

    //definition of enum for setting the options
    enum Method {gradient, momentum, nesterov}; //gradient method, momentum (Havy-ball) method, or Nesterov method
    enum GradientSetting {exact, fd}; //exact uses the gradient given in the function, fd calculates it with finite differences
    enum StepChoice {armijo, constant, exponential, inverse}; //calculation of the step alpha_k

    //Parameters will contain all the constants and thresholds we will use (I set default values if not specified)
    struct Parameters
    {
        double step_tol = 1e-6; //tolerance on ||x_(k+1) - x_k||
        double res_tol = 1e-6; //tolerance on ||f(x_(k+1)) - f(x_k)||
        size_t max_iter = 1e6; //maximum number of iterations
        double alpha_0 = 0.1; //initial value for the step
        double sigma = 0.25; //parameter for armijo rule, it must be in (0, 0.5)
        double mu = 0.2; //parameter for inverse or exponential rule, it must be "small"
        double h = 1e-2; //step for the finite difference computation of the gradient
        double eta = 0.9; //parameter for momentum and nesterov methods
    };

    //Data will contain all the data of the minimizing problem
    struct Data
    {
        func f; //f to be minimized
        func_nd grad_f; //gradient of f
        Point x0; //initial guess
    };

    //Definition of the centered finite difference algorithm to evaluate the gradient
    //@note Take the habit of using const& to pass objects different than POD. It is more
    //efficient and safer.
    // Point gradient_fd(func cont & f, Point const & x, double h);
    
    Point gradient_fd(func f, Point x, double h);

    //Definition of the different rules for alpha
    double armijo_rule(Point x, func f, Point grad_x, double alpha_0, double sigma);

    inline double exponential_rule(double alpha_0, size_t k, double mu) { return alpha_0 * exp(-mu*k); }

    inline double inverse_rule(double alpha_0, size_t k, double mu) { return alpha_0 / (1 + mu*k); }

    //Definition and implementation of the minimization function
    template <Method method=gradient, GradientSetting gradient_setting=exact, StepChoice step_choice=armijo> Point minimize(Data data, Parameters par){

        size_t n_iter = 0;
        Point x = data.x0;
        Point x_old = x;
        Point x_old2 = x;
        Point grad_x;

        double res_x;
        double res_f;
        double alpha = par.alpha_0;


        do
        {
            ++n_iter;
            x_old2 = x_old;
            x_old = x;

            if constexpr (method == nesterov){
                x = x_old + par.eta * (x_old - x_old2);  //in nesterov method this is the value at which we evaluate the gradient
            }

            //calculation of the gradient of x
            if constexpr (gradient_setting == exact){
                grad_x = data.grad_f(x);
            }
// @note I would have used an else here, but it is a matter of taste
            if constexpr (gradient_setting == fd){
                grad_x = gradient_fd(data.f, x, par.h);
            }

            //if gradient method, calculation of alpha with different rules (if constant rule
            //or if not gradient method, just let it be alpha_0)
            if constexpr (method == gradient){
                if constexpr (step_choice == armijo){
                    alpha = armijo_rule(x, data.f, grad_x, par.alpha_0, par.sigma);
                }
                //@note I would have used else if here, but it is a matter of taste
                if constexpr (step_choice == inverse){
                    alpha = inverse_rule(par.alpha_0, n_iter, par.mu);
                }
                if constexpr (step_choice == exponential){
                    alpha = exponential_rule(par.alpha_0, n_iter, par.mu);
                }
            }

            //updating x
            x = x_old - alpha * grad_x;

            if constexpr (method == momentum){
                x = x + par.eta * (x_old - x_old2);
            }

            //computing the residual to see the stop conditions
            res_x = (x - x_old).norm();
            res_f = fabs( data.f(x) - data.f(x_old));
            
        } while (n_iter < par.max_iter and res_x > par.step_tol and res_f > par.res_tol);

        std::cout << "Number of iterations: " << n_iter << std::endl;

        return x;
    
    };

}


#endif // GRADIENT_METHOD_H