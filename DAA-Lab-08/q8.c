// for i = 1 to n+1:..................................................ALGORITHM.......................................................................................................................
//     e[i][i-1] = q[i-1]
//     w[i][i-1] = q[i-1]

// for length = 1 to n:
//     for i = 1 to n-length+1:
//         j = i + length - 1

//         e[i][j] = infinity
//         w[i][j] = w[i][j-1] + p[j] + q[j]

//         for r = i to j:
//             cost = e[i][r-1] + e[r+1][j] + w[i][j]

//             if cost < e[i][j]:
//                 e[i][j] = cost
//                 root[i][j] = r.................................................................................................


#include <stdio.h>
#include <stdlib.h>
#include <float.h>

void printTree(int root[][100], int i, int j, int parent, char side) {
    if (i > j)
        return;

    int r = root[i][j];

    if (parent == 0) {
        printf("k%d is the root\n", r);
    } else {
        printf("k%d is the %s child of k%d\n",
               r,
               side == 'L' ? "left" : "right",
               parent);
    }

    printTree(root, i, r - 1, r, 'L');
    printTree(root, r + 1, j, r, 'R');
}

int main() {
    int n;

    printf("Enter number of keys: ");
    scanf("%d", &n);

    double *p = (double *)malloc((n + 1) * sizeof(double));
    double *q = (double *)malloc((n + 1) * sizeof(double));

    /*
       e and w have indices:
       e[1..n+1][0..n]
    */
    double **e = (double **)malloc((n + 2) * sizeof(double *));
    double **w = (double **)malloc((n + 2) * sizeof(double *));

    int **root = (int **)malloc((n + 2) * sizeof(int *));

    for (int i = 0; i <= n + 1; i++) {
        e[i] = (double *)malloc((n + 1) * sizeof(double));
        w[i] = (double *)malloc((n + 1) * sizeof(double));
        root[i] = (int *)malloc((n + 1) * sizeof(int));
    }

    printf("Enter p1 to p%d:\n", n);
    for (int i = 1; i <= n; i++)
        scanf("%lf", &p[i]);

    printf("Enter q0 to q%d:\n", n);
    for (int i = 0; i <= n; i++)
        scanf("%lf", &q[i]);

    /* Empty subtrees */
    for (int i = 1; i <= n + 1; i++) {
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }

    /* Build DP table */
    for (int len = 1; len <= n; len++) {

        for (int i = 1; i <= n - len + 1; i++) {

            int j = i + len - 1;

            e[i][j] = DBL_MAX;

            w[i][j] = w[i][j - 1] + p[j] + q[j];

            for (int r = i; r <= j; r++) {

                double cost =
                    e[i][r - 1]
                    + e[r + 1][j]
                    + w[i][j];

                if (cost < e[i][j]) {
                    e[i][j] = cost;
                    root[i][j] = r;
                }
            }
        }
    }

    printf("\nMinimum expected search cost = %.4f\n",
           e[1][n]);

    printf("\nOptimal BST:\n");

    printTree(root, 1, n, 0, ' ');

    for (int i = 0; i <= n + 1; i++) {
        free(e[i]);
        free(w[i]);
        free(root[i]);
    }

    free(e);
    free(w);
    free(root);
    free(p);
    free(q);

    return 0;
}
