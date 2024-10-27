#include <stdio.h>
#include <stdlib.h>

typedef struct Array {
  int *ptr;
  int size;
  int length;
} Array;

int *create_array(int size) {
  int *ptr = (int*)malloc(sizeof(int) * size);
  return ptr;
}

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void display(Array arr) {
  for (int i = 0; i < arr.length; i++) {
    printf("%d ", arr.ptr[i]);
  }
  printf("\n");
}

void append(Array *arr, int n) {
  if (arr->length == arr->size) {
    printf("Error: array overflow\n");
    return;
  }

  arr->ptr[arr->length] = n;
  arr->length++;
}

void insert(Array *arr, int n, int index) {
  if (index >= arr->length || index < 0) {
    printf("Error: array overflow\n");
    return;
  }

  for (int i = arr->length; i > index; i--) {
    arr->ptr[i] = arr->ptr[i - 1];
  }
  arr->ptr[index] = n;
  arr->length++;
}

void delete(Array *arr, int index) {
  if (index >= arr->length || index < 0) {
    return;
  }

  for (int i = index; i < arr->length - 1; i++) {
    arr->ptr[i] = arr->ptr[i + 1];
  }
  arr->length--;
}

int rSearch(Array *arr, int l, int h, int k) {
  if (l > h) return -1;

  int m = (h + l) / 2;

  if (arr->ptr[m] == k)
    return m;

  else if (arr->ptr[m] > k)
    return rSearch(arr, l, m - 1, k);

  else if (arr->ptr[m] < k);
    return rSearch(arr, m + 1, h, k);
}

int search(Array *arr, int k) {
  int l = 0;
  int h = arr->length;

  while (l <= h) {
    int m = (l + h) / 2;
    if (arr->ptr[m] == k)
      return m;

    else if (arr->ptr[m] > k)
      h = m - 1;

    else if (arr->ptr[m] < k)
      l = m + 1;
  }
  return -1;
}

int get(Array *arr, int index) {
  if (index >= arr->length || index < 0) {
    return -1;
  }
  return arr->ptr[index];
}

void set(Array *arr, int index, int n) {
  if (index >= arr->length || index < 0) {
    return;
  }
  arr->ptr[index] = n;
}

int max(Array *arr) {
  int max = arr->ptr[0];
  for (int i = 1; i < arr->length; i++) {
    if (arr->ptr[i] > max) {
      max = arr->ptr[i];
    }
  }
  return max;
}

int min(Array *arr) {
  int min = arr->ptr[0];
  for (int i = 1; i < arr->length; i++) {
    if (arr->ptr[i] < min) {
      min = arr->ptr[i];
    }
  }
  return min;
}

int avrg(Array *arr) {
  int sum = 0;
  for (int i = 0; i < arr->length; i++) {
    sum += arr->ptr[i];
  }
  return sum / arr->length;
}

void reverse(Array *arr) {
  for (int i = 0; i < arr->length / 2; i++) {
    swap(&arr->ptr[i], &arr->ptr[arr->length - i - 1]);
  }
}

void rotate_left(Array *arr) {
  for (int i = 0; i < arr->length - 1; i++) {
    int new = (i + arr->length - 1) % arr->length;
    swap(&arr->ptr[i], &arr->ptr[new]);
  }
}

void rotate_right(Array *arr) {
  for (int i = arr->length - 1; i > 0; i--) {
    int new = (i + arr->length + 1) % arr->length;
    swap(&arr->ptr[i], &arr->ptr[new]);
  }
}

void sorted_insert(Array *arr, int n) {
  for (int i = arr->length - 1; i > 0; i--) {
    if (arr->ptr[i] < n) {
      arr->ptr[i + 1] = n;
      arr->length++;
      return;
    }
    arr->ptr[i + 1] = arr->ptr[i]; 
  }
}

int is_sorted(Array *arr) {
  for (int i = 1; i < arr->length; i++) {
    if (arr->ptr[i - 1] > arr->ptr[i]) {
      return 0;
    }
  }
  return 1;
}

void split_np(Array *arr) {
  int i = 0;
  int j = arr->length - 1;

  while (i < j) {
    while (arr->ptr[i] < 0)
      i++;
    while (arr->ptr[j] > 0)
      j--;
    if (i < j) {
      swap(&arr->ptr[i], &arr->ptr[j]);
    }
  }
}

Array merge(Array *arr1, Array *arr2) {
  int i = 0;
  int j = 0;

  Array arr3;
  arr3.length = 0;
  arr3.size = 12;
  arr3.ptr = create_array(arr3.size);

  while (i < arr1->length && j < arr2->length) {
    if (arr1->ptr[i] <= arr2->ptr[j]) {
      append(&arr3, arr1->ptr[i]);
      i++;
    }
    else if (arr2->ptr[j] <= arr1->ptr[i]) {
      append(&arr3, arr2->ptr[j]);
      j++;
    }
  }

  if (i < arr1->length) {
    for (i; i < arr1->length; i++) {
      append(&arr3, arr1->ptr[i]);
    }
  }
  else if  (j < arr2->length) {
    for (j; j < arr2->length; j++) {
      append(&arr3, arr2->ptr[j]);
    }
  }

  return arr3;
}

Array Union(Array *arr1, Array *arr2) {
  int i = 0;
  int j = 0;

  Array arr3;
  arr3.length = 0;
  arr3.size = 12;
  arr3.ptr = create_array(arr3.size);

  while (i < arr1->length && j < arr2->length) {
    if (arr1->ptr[i] < arr2->ptr[j]) {
      append(&arr3, arr1->ptr[i]);
      i++;
    }
    else if (arr2->ptr[j] < arr1->ptr[i]) {
      append(&arr3, arr2->ptr[j]);
      j++;
    }
    else {
      append(&arr3, arr1->ptr[i]);
      i++;
      j++;
    }
  }

  if (i < arr1->length) {
    for (i; i < arr1->length; i++) {
      append(&arr3, arr1->ptr[i]);
    }
  }
  else if  (j < arr2->length) {
    for (j; j < arr2->length; j++) {
      append(&arr3, arr2->ptr[j]);
    }
  }

  return arr3;
}

Array intersection(Array *arr1, Array *arr2) {
  int i = 0;
  int j = 0;

  Array arr3;
  arr3.length = 0;
  arr3.size = 12;
  arr3.ptr = create_array(arr3.size);

  while (i < arr1->length && j < arr2->length) {
    if (arr1->ptr[i] < arr2->ptr[j]) {
      i++;
    }
    else if (arr2->ptr[j] < arr1->ptr[i]) {
      j++;
    }
    else {
      append(&arr3, arr1->ptr[i]);
      i++;
      j++;
    }
  }
  return arr3;
}

Array diff(Array *arr1, Array *arr2) {
  int i = 0;
  int j = 0;

  Array arr3;
  arr3.length = 0;
  arr3.size = 12;
  arr3.ptr = create_array(arr3.size);

  while (i < arr1->length && j < arr2->length) {
    if (arr1->ptr[i] < arr2->ptr[j]) {
      append(&arr3, arr1->ptr[i]);
      i++;
    }
    else if (arr2->ptr[j] < arr1->ptr[i]) {
      j++;
    }
    else {
      i++;
      j++;
    }
  }
  if (i < arr1->length) {
    for (i; i < arr1->length; i++) {
      append(&arr3, arr1->ptr[i]);
    }
  }
  return arr3;
}

int main() {
  Array arr1;
  printf("Enter array size: ");
  scanf("%d", &arr1.size);
  arr1.ptr = create_array(arr1.size);

  int choice, n, index;

  do {
    system("clear");

    printf("1: insert\t2: delete\n3: search\t4: append\n5: display\t6: exit\n");
    scanf(" %d", &choice);

    switch(choice) {
      case 1:
        printf("insert number and index: ");
        scanf("%d%d", &n, &index);
        insert(&arr1, n, index);
        break;
      case 2:
        printf("insert index: ");
        scanf("%d", &index);
        delete(&arr1, index);
        break;
      case 3:
        printf("insert number: ");
        scanf("%d", &n);
        index = search(&arr1, n);
        if (index == -1)
          printf("not found\n");
        else
          printf("found at index %d\n", index);
        printf("Hit any key to continue> ");
        getchar();
        getchar();
        break;
      case 4:
        printf("insert number: ");
        scanf("%d", &n);
        append(&arr1, n);
        break;
      case 5:
        display(arr1);
        printf("Hit any key to continue> ");
        getchar();
        getchar();
        break;
      default:
        free(arr1.ptr);
        return 0;
    }
  } while (choice != 6);


  return 0;
}