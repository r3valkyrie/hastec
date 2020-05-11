typedef struct
{
    char * array;
    size_t used;
    size_t size;
} Vector;

void initVector(Vector * vec)
{
    vec->array = (char *)malloc(2 * sizeof(char));
    vec->used = 0;
    vec->size = 2;
}

void appendVector(Vector * vec, char ele)
{
    if (vec->size == vec->used)
    {
        vec->size *= 2;
        vec->array = (char *)realloc(vec->array, vec->size * sizeof(char));
    }
    vec->array[vec->used++] = ele;
}