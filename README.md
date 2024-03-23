PACS Challenge 1 - Riccardo Rota

IMPORTANT: in order to make the makefile work you have to change the variable JSONPATH in the Makefile,
copying the path to the repository containing the library.

Then you can build the executable just typing make, then the makefile also define an istruction "clean" to remove it.

For my implementation I developed a class Point, in order to manage operation with vectors. 
It includes a std::vector containing the coordinates and a size_t to store the dimension of the point.
It also provides simple methods and operators such as +, -, [] (access to an element),
.norm() and .print() (to visualize the point).

Then in the file gradient_method.hpp I implemented the namespace gm, which contains the function minimize.
The function template takes three variables, method, gradient_setting and step_choice:
- method allows to choose among gradient method (gradient), momentum method (momentum) and nesterov method (nesterov)
- gradient_setting allows to choose whether to use the gradient given by the user (exact)
or to compute it via finite differences method (df)
- step_choice allows to choose among different ways to compute alpha at each iteration (armijo, constant,
inverse, exponential). This last choice is only available for gradient method, for other methods alpha
will be always constant even if another option is selected

The default setting, if not specified, is: method=gradient, gradient_setting=exact, step_choice=armijo

The function minimize takes as input two structures, Parameters and Data. 

Parameters is used to set all the parameters of the method (tolerance, initial step, maximum number of iterations) and also
the parameters sigma for armijo rule, mu for inverse and exponential rule and h for the computation of the gradient via fd.
This structure is extracted by the file Parameters_setting.json, so the user can just modify this file to change the parameters
that will be passed to the function.

Data is used to pass the function to be minimized, its gradient and the starting point x0. It contains f as a
std::function<double(Point)>, which I named func, and grad_f as a std::function<Point(Point)>, which I named
func_nd. To define them in the main, I used lambda functions. If we choose to calculate the gradient via fd the method
is a centered finite difference scheme along the n directions.
Sadly I did not use muParser, so the only way to set f and its gradient is modifying them in the first part of the main.

In the definition of the function, the part of code calculating the gradient and the one calculating alpha are
contained in an if constexpr condition, so that the compiler avoids the compilation of useless parts of code.
Also the differences between different methods are implemented with if constexpr to optimize the compilation.

The main allows to test the implementation with the function f: R2 -> R, defined as f(x,y) = xy + 4x^4 + y^ + 3x,
using gradient method with armijo rule and exact gradient (i.e. the default settings), and all the parameters set
in the json file. Uncommenting the following lines it is possible to test different combinations of settings.

NOTE: I saw that a good choice for alpha_0 with the test function given is around 0.1 for gradient
method (can be higher if we choose armijo rule, e.g. 0.5), around 0.04 for momentum and around 0.02
for nesterov, with eta=1-alpha.
