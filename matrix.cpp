struct Matrix {
    vector<vector<long long>> a;
    int N;
    Matrix(int N) {
        this->N=N;
        for (int i = 0; i < N; i++) {
            vector<long long> row;
            row.assign(N,0LL);
            a.add(row);
        }
    }

    Matrix operator *(const Matrix& other) {
        Matrix product(N);
        for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) for (int k = 0; k < N; k++) {
            product.a[i][k] += a[i][j] * other.a[j][k];
            product.a[i][k] %= MOD;
        }
        return product;
    }
};

Matrix matrix_power(Matrix a, long long k) {
    Matrix product(a.N);
    REP(i,a.N) product.a[i][i] = 1;
    while(k > 0) {
        if(k % 2) {
            product = product * a;
        }
        a = a * a;
        k /= 2;
    }
    return product;
}