// helpful functions

static int min(double a, double b);
//-------------------------------------------------------------------------

// array
int arr_min(double a, double b);

void arr_swap(double *arr, int i, int j);
double arr_sum(double *arr);

// merge-sort an array
static void merge(double *arr, int l, int m, int r);
void arr_merge_sort(double *arr, int l, int r);

//quick-sort an array
typedef struct _Tuple Tuple;

struct _Tuple {
    int values[2];
};

static Tuple partition(double *arr, int l, int r);
void arr_quick_sort(double *arr, int l, int r);

// binary-search an array
int arr_binary_search(double *arr, int l, int r, int x);
