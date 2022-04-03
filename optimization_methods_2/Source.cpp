#include "Extremum.h"

int main()
{    
    Vector x0(2);
    x0.set(0, 0); x0.set(1, 0);
    Devidon_Fletcher_Powell_method(x0, 7);
    return 0;
}