// matrix

typedef struct _Matrix Matrix;

struct _Matrix {
    int rows;
    int cols;
    double *data;
};

// structure
Matrix *create_matrix(int rows, int cols, bool zeros);
void delete_matrix(Matrix *mat);
double get_element(Matrix *mat, int row, int col);
void set_element(Matrix mat, int row, int col, double element);
Matrix *get_row(Matrix *mat, int row);
Matrix *get_col(Matrix *mat, int col);
void row_op1(Matrix *mat, int i, int j);
void row_op2(Matrix *mat, inti, double k);
void row_op3(Matrix *mat, int i, int j, double k);

// mathematics
bool equal(Matrix *A, Matrix *B);
Matrix *product(Matrix *A, Matrix *B);
Matrix *sum(Matrix *A, Matrix *B);

// algorithms
void rref(Matrix *mat);
