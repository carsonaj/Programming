// helpful functions

//-------------------------------------------------------------------------

// array
int arr_min(double a, double b);

void arr_swap(double *arr, int i, int j);
double arr_sum(double *arr, int length);

// merge-sort an array
void arr_merge_sort(double *arr, int l, int r);

//quick-sort an array
typedef struct _Tuple Tuple;

struct _Tuple {
    int values[2];
};

void arr_quick_sort(double *arr, int l, int r);

// binary-search an array
int arr_binary_search(double *arr, int l, int r, int x);
