// Libraries

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>


// Defines

#define PI 3.14159265358979323846


// Prototypes

double *zero_array(int);
double *initial_condition(double, int);
double acceleration(double *, double, double, double);
double velocity(double, double, const double);
double position(double, double, const double);
// double rk4(double (*f)(double *, double), double *, double, double);


// Constants

const double k      = 0.95;
const double m      = 1.05;
const double alpha  = 1.2;

const double dt     = 1;
const double tmax   = 5000.0;

const double length = 20.0;
const int N         = 32;


// Variables

int i;
double t = 0.0;
double *pos, *vel, *acc;


// Output

FILE *file;
char output[50];
char filename[] = "../data/output.dat";


// Main

int main(){

    // Generate inicial conditions for
    pos = initial_condition(length, N); // position
    vel = zero_array(N);                // velocity
    acc = zero_array(N);                // acceleration

    // Output file
    sprintf(output, filename);
    file = fopen(output, "w");

    // Time loop
    while (t < tmax){

        // Acceleration loop
        for (i=1; i<N; i++){
            acc[i] = acceleration((pos+i), k, m, alpha);
        }

        // Velocity and position loop
        for (i=1; i<N; i++){
            vel[i] = velocity(vel[i], acc[i], dt);
            pos[i] = position(pos[i], vel[i], dt);
        }

        // Save to file
        for (i=0; i<=N; i++) fprintf(file, "%f %f\n", length/N*i, pos[i]);
        fprintf(file, "\n\n");

        // Update the current time
        t += dt;
    }

    return 0;
}


// Functions

// Generate an array of zeros (double) with size N
double *zero_array(int N){
    assert(N>0);
    int i;
    double *pointer;

    pointer = (double *)calloc(N, sizeof(double));

    if (pointer != NULL){
        for (i=0; i<=N; ++i) *(pointer+i) = 0.0;
        return(pointer);
    }
    else {
        fprintf(stderr,"Error in routine zero_array\n");
        exit(8);
    }
}

// Generate an array with the initial condition determined by the FPUT original problem, N elements with x values ranged from 0 to length.
double *initial_condition(double length, int N){
    assert(N>0);
    int i;
    double *pointer;
    double step = length/N;

    pointer = (double *)calloc(N, sizeof(double));

    if (pointer != NULL){
        for (i=0; i<=N; ++i) {
            *(pointer+i) = sin(PI*(step*i)/length);
        }
        return(pointer);
    }
    else {
        fprintf(stderr,"Error in routine initial_condition\n");
        exit(8);
    }
}

// Velocity-Verlet method

// Updates the acceleration
double acceleration(double *pos, double k, double m, double alpha){
    return k/m * (pos[1] + pos[-1] - 2*pos[0]) * (1.0 + alpha * (pos[1] - pos[-1]));
}

// Updates the velocity
double velocity(double vel_old, double acc, double dt){
    return vel_old + 0.5*acc*dt;
}

// Updates the position
double position(double pos_old, double vel_new, double dt){
    return pos_old + vel_new*dt;
}


// Annotations

// Runge-Kutta 4
// double rk4(double (*f)(double *, double), double *x, double t, double dt){
//     double k1, k2, k3, k4;
//     k1 = (*f)(x,        t           );
//     k2 = (*f)(x + k1/2, t + dt/2    );
//     k3 = (*f)(x + k2/2, t + dt/2    );
//     k4 = (*f)(x + k3,   t + dt      );
//     return x + dt*(k1 + 2*k2 + 2*k3 + k4)/6;
// }