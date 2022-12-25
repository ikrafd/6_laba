#include <stdio.h>
#include <math.h>
#include <stdlib.h>
char count (int n, double **a, double *b);
void check_char (double *var, int n){
    char er, ch;
    do {
        er = 0;
        scanf("%lf%c", var, &ch);
        if(ch != '\n') {
            printf("Invalid data\n");
            er = 1;
            fflush(stdin);
        } else if(n==1){
            if(*var==0){
                er = 1;
                fflush(stdin);
                printf("Diagonal element cannot equal 0\n");
            }
        }
    } while(er);

}

void check_char_int (int *var){
    char er, ch;
    do {
        er = 0;
        scanf("%i%c", var, &ch);
        if(ch != '\n') {
            printf("Invalid data\n");
            er = 1;
            fflush(stdin);
        }
    } while(er);
}


int main () {
    int num, i, j;
    double prop=1, sum, epsi, delta;
    char er;
    printf ("Enter how many number in matrix\n");
    check_char_int(&num);

    double *xp, *roots, **a, *free_v;

    xp = (double *) calloc(num, sizeof (double));
    roots = (double *) calloc (num, sizeof (double));
    free_v = (double *) calloc (num, sizeof (double));
    a = (double **)calloc (num, sizeof (double*));
    for (i=0;i<num; i++)
        a[i]= (double *) calloc(num, sizeof (double));

    do {
        er=0;
        for (i = 0; i < num; i++) {
            for (j = 0; j <= num; j++) {
                if (j != num) {
                    printf("Element at x[%i][%i]:", i + 1, j + 1);
                    if (i == j) {
                        check_char(&a[i][j], 1);
                    } else {
                        check_char(&a[i][j], 2);
                    }
                } else {
                    printf("Element at b[%i]:", i + 1);
                    check_char(&free_v[i], 2);
                }
            }
        }
        er=count(num,a,free_v);
    } while(er);

do {
        er = 0;
        printf("Epsilon:\n");
        check_char(&epsi,2);
        if((epsi >=1)||(epsi<=0)) {
            printf("Invalid data\n");
            er = 1;
            fflush(stdin);
        }
    } while(er);

    for (i = 0; i < num; i++)
        xp[i] = free_v[i]/a[i][i];

    while (prop>epsi){
        delta=0;
        for (i=0;i < num; i++) {
            sum = 0;
            for (j = 0; j < num; j++) {
                if (i != j) {
                    sum += a[i][j] * xp[j];
                }
            }
            roots[i] = (free_v[i] - sum) / a[i][i];
            double mod = fabs(roots[i] - xp[i]);
            if (delta < mod)
                delta = mod;
            xp[i] = roots[i];
        }
       prop=delta;
    }


    for (i = 0; i < num; i++) {
            printf("x=%lf\n", roots[i]);
    }

    for ( i = 0; i < num; i++)
        free (a[i]);
    free(a);

    free(xp);
    free ( free_v);
    free(roots);
    return 0;
}

char count (int n, double **a, double *b) {
    for (int i = 0; i<n; i++) {
        double xp[n], sum = 0;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                sum = sum + a[i][j];
            }
        }
        xp[i]= b[i] / a[i][i];
        if ((fabs(a[i][i])) < (fabs(sum))) {
            printf("Impossible to calculate\n");
            return 1;
        }else{
            return 0;
        }
    }
}