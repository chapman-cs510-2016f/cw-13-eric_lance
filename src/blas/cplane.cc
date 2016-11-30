#include <iostream>
#include "cplane.h"

//defining an identity function to use as default
std::complex<long double> _identity_(std::complex<long double> input) {
    return input;
}

CPlane::CPlane()
{
    // need to set up min/max/len
    xmin = -5;
    xmax = 5;
    xlen = 10;
    ymin = -5;
    ymax = 5;
    ylen = 10;

    //also need to define f
    this->setf( *_identity_ );

    //and set the plane to f
    this->refresh();
}

CPlane::CPlane( long double new_xmin,
                long double new_xmax,
                unsigned int new_xlen,
                long double new_ymin,
                long double new_ymax,
                unsigned int new_ylen )
{
    // need to set up min/max/len
    xmin = new_xmin;
    xmax = new_xmax;
    xlen = new_xlen;
    ymin = new_ymin;
    ymax = new_ymax;
    ylen = new_ylen;

    //also need to define f
    this->setf( *_identity_ );

    //and set the plane to f
    this->refresh();
}

void CPlane::refresh()
{
    //reinitialize plane to correct dimensions
    plane = matrix<std::complex<long double> >(ylen, xlen);

    //calculate necessary values for loop
    long double ystep = (this->ymax - this->ymin)/(this->ylen - 1);
    long double xstep = (this->xmax - this->xmin)/(this->xlen - 1);

    //loop through matrix and apply f
    // r : row index
    // c : column index
    for (unsigned r = 0; r < this->plane.size1(); r++) {
        //calculate y position in the plane
        long double ypos = ymin + r*ystep;

        for (unsigned c = 0; c < this->plane.size2(); c++) {
            //calculate x position in the plane
            long double xpos = xmin + c*xstep;
            //set the element to f(position)
            this->plane(r,c) = f( xpos + ypos*1i );
        }
    }
}

void CPlane::setf(std::complex<long double> (*func)(std::complex<long double>) )
{
    this->f = func;
}

void CPlane::zoom( long double new_xmin,
                   long double new_xmax,
                   long double new_ymin,
                   long double new_ymax  )
{
    //need to set min/max then refresh
    xmin = new_xmin;
    xmax = new_xmax;
    ymin = new_ymin;
    ymax = new_ymax;

    this->refresh();
}

void CPlane::print()
{
    //std::cout << this->plane << std::endl; //could do this, but result is ugly

    // loop through matrix and print element
    // r : row index
    // c : column index
    for (unsigned r = 0; r < this->plane.size1(); r++) {
        for (unsigned c = 0; c < this->plane.size2(); c++) {
            std::cout << this->plane(r,c) << ", ";
        }
        std::cout << std::endl;
    }
}

// main function creates a plane and prints its contents
int main(int argc, char **argv)
{
    CPlane testplane = CPlane();
    testplane.print();
}