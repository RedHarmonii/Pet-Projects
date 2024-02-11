#include<iostream>
#include<cmath>
using namespace std;

/*  
    x'(t) =  | A -B | |x(t)|
    y'(t) =  | C -D | |y(t)|

    x(t) = e^Lt U1
    y(t) = e^Lt U2


*/



int main(){ 

    //Components for 2x2 Matrix
    float A = 4;
    float B = 2;
    float C = 0;
    float D = 4;
    float lambda1,lambda2 = 0;
    float matrix[2][2] = {{A , B},
                          {C , D}
    };

    // Solve for Lambda
    lambda1 = ((A-D) + sqrtf(pow(A,2) + pow(D,2) + (2*A*D) - (4*B*C)) ) / 2;

    lambda2 = ((A-D) - sqrtf(pow(A,2) + pow(D,2) + (2*A*D) - (4*B*C)) ) / 2;

    cout << "Lamba : " << lambda1 << ", " << lambda2 << endl;

    
    //plug lambda into original Matrix and find eigenvectors
    int eigenVector1[2] = {};
    int eigenVector2[2] = {};

    

    return 0;
}