// matrix

typedef struct _Matrix Matrix;

struct _Matrix {
    int rows;
    int cols;
    double *data;
};

// structure
Matrix *mat_create_matrix(int rows, int cols, bool zeros);
void mat_delete_matrix(Matrix *mat);
double mat_get_element(Matrix *mat, int row, int col);
void mat_set_element(Matrix *mat, int row, int col, double element);
Matrix *mat_get_row(Matrix *mat, int row);
Matrix *mat_get_col(Matrix *mat, int col);
void mat_row_op1(Matrix *mat, int i, int j);
void mat_row_op2(Matrix *mat, int i, double k);
void mat_row_op3(Matrix *mat, int i, int j, double k);

// mathematics
bool mat_equal(Matrix *A, Matrix *B);
Matrix *mat_product(Matrix *A, Matrix *B);
Matrix *mat_sum(Matrix *A, Matrix *B);

// algorithms
void mat_ref(Matrix *mat);
void mat_rref(Matrix *mat);
