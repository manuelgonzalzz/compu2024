#include <stdio.h>
# include <iostream> //for cout
# include <cmath>  //for M_PI

# define G 6.672e-11
# define N 3
# define dim 2
# define h 0.001

void calculate_acc(double m[],double r[][2], double (&a)[N][2]);
void calculate_pos(double r[][2], double v[][2], double a[][2], double (&new_r)[N][2]);
void calculate_w(double v[][2], double a[][2], double (&w)[N][2]);
void calculate_vel(double w[][2],double new_a[][2],double (&new_v)[N][2]);


//Input:: masas planetas, posiciones iniciales r0[N][dim], velocidades iniciales v0[N][dim]
/* 
Todos los planetas comienzan en el eje X -- r0[i][0] = distancia planeta/sol; r0[i][1] = 0
Todas las velocidades comienzan en el eje Y -- v0[i][0] = 0; v0[i][0] = velocidad inicial.

*/
//Parametro:: incremento del tiempo -- pasos temporales
//Output:: posiciones de los plantetas r[N][dim], velocidades de los planetas v[N][dim]
int main(void){

    double m[N];
    double r[N][2];
    double v[N][2];
    double a[N][2];
    double new_r[N][2];
    double w[N][2];
    double new_v[N][2];
    double new_a[N][2];
    FILE *fwrite;
    fwrite = fopen("output.txt","w");

    for(int i=0;i<N;i++){ //Paso 0: Inicializar las variables
        m[i]=0.5*(i+1);
        for(int j=0;j<2;j++){
            r[i][j]=2*(i+1);
            v[i][j]=-5*(i+1);
            new_r[i][j]=0.0;
        }
    }





    calculate_acc(m,r,a); //Paso 1: evaluar a(t)
    for(int k=0; k<100; k++){
        calculate_pos(r,v,a,new_r); //Paso 2: evaluar new_r == r(t+h)
        calculate_w(v,a,w); //Paso 2.5: evaluar w
        calculate_acc(m,new_r,new_a); //Paso 3: evaluar new_a == a(t+h)
        calculate_vel(w,new_a,new_v); //Paso 4: evaluar new_v

        for(int i=0;i<N;i++){ //Paso 5: Reinicializar las variables
            for(int j=0;j<dim;j++){
                r[i][j] = new_r[i][j];
                v[i][j] = new_v[i][j];
                a[i][j] = new_a[i][j];
            }
        }
        //Paso 6: Escribir las nuevas posiciones en el fichero
        for(int i=0;i<N;i++){
                fprintf(fwrite,"%lf, ", new_r[i][0]);
                fprintf(fwrite,"%lf\n", new_r[i][1]);
        }
        fprintf(fwrite,"\n");
    }

    
    
    return 0;
}

void calculate_acc(double m[],double r[][2], double (&a)[N][2]){
    for(int i=0;i<N;i++)
    {
        a[i][0]=0.0;
        a[i][1]=0.0;
        for(int j=0;j<N;j++)
        {
                if(j!=i){
                    double dist = pow((r[i][0]-r[j][0])*(r[i][0]-r[j][0])+(r[i][1]-r[j][1])*(r[i][0]-r[j][0]),2.0/3.0);
                    a[i][0]=a[i][0] - m[j]*(r[i][0]-r[j][0])/dist;
                    a[i][1]=a[i][1] - m[j]*(r[i][1]-r[j][1])/dist;
                }
        }
    }
}

void calculate_pos(double r[][2], double v[][2], double a[][2], double (&new_r)[N][2]){
    for(int i=0;i<N;i++){
        for(int j=0;j<dim;j++){
            new_r[i][j] = r[i][j] + h*v[i][j] + 0.5*h*h*a[i][j];
        }
    }
}

void calculate_w(double v[][2], double a[][2], double (&w)[N][2]){
    for(int i=0;i<N;i++){
        for(int j=0;j<dim;j++){
            w[i][j] = v[i][j] + 0.5*h*a[i][j];
        }
    }
}

void calculate_vel(double w[][2],double new_a[][2],double (&new_v)[N][2]){
    for(int i=0;i<N;i++){
        for(int j=0;j<dim;j++){
            new_v[i][j] = w[i][j] + 0.5*h*new_a[i][j];
        }
    }
}