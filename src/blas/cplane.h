#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

using namespace boost::numeric::ublas;

class CPlane
{
private:
    long double xmin;
    long double xmax;
    unsigned int xlen;
    long double ymin;
    long double ymax;
    unsigned int ylen;
    matrix<std::complex<long double> > plane;
    std::complex<long double> f();
public:
    CPlane();
    CPlane(
        long double xmin,
        long double xmax,
        unsigned int xlen,
        long double ymin,
        long double ymax,
        unsigned int ylen );
    void refresh();
    void setf(std::complex<long double> (*func)(std::complex<long double>) );
    void zoom( long double new_xmin,
               long double new_xmax,
               long double new_ymin,
               long double new_ymax  );
    void print();
};
