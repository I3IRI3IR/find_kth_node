#include <stdio.h>
#include <stdlib.h>


struct node {
    struct node* next;      
    struct node** prev;     
    int value;
};


struct node* create_node(int val) {
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    new_node->value = val;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}


void insert_front(struct node** head, int val) {
    struct node* new_node = create_node(val);
    new_node->next = *head;           
    if (*head != NULL) {
        (*head)->prev = &(new_node->next);
    }
    
    new_node->prev = head;
    *head = new_node;                 
}


void print_list(struct node* head) {
    struct node* cur = head;
    while (cur != NULL) {
        printf("%d ", cur->value);
        cur = cur->next;
    }
    printf("\n");
}


void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}


void heapify_up(int heap[], int idx) {
    while (idx > 1 && heap[idx] < heap[idx / 2]) {
        swap(&heap[idx], &heap[idx / 2]);
        idx /= 2;
    }
}


void heapify_down(int heap[], int heap_size, int idx) {
    int smallest = idx;
    int left = idx * 2;
    int right = idx * 2 + 1;

    if (left <= heap_size && heap[left] < heap[smallest])
        smallest = left;
    if (right <= heap_size && heap[right] < heap[smallest])
        smallest = right;
    if (smallest != idx) {
        swap(&heap[idx], &heap[smallest]);
        heapify_down(heap, heap_size, smallest);
    }
}


void heap_push(int heap[], int* heap_size, int val) {
    (*heap_size)++;
    heap[*heap_size] = val;
    heapify_up(heap, *heap_size);
}


void heap_replace_root(int heap[], int heap_size, int val) {
    heap[1] = val;
    heapify_down(heap, heap_size, 1);
}


int find_kth_largest(struct node* head, int k) {
    if (k <= 0 || head == NULL) return -1; 
    int* heap = (int*)malloc((k + 1) * sizeof(int));
    int heap_size = 0;
    struct node* cur = head;
    while (cur != NULL) {
        int val = cur->value;
        if (heap_size < k) {
            heap_push(heap, &heap_size, val);
        } else {
            if (val > heap[1]) {
                heap_replace_root(heap, heap_size, val);
            }
        }
        cur = cur->next;
    }
    int result = heap[1]; 
    free(heap);
    return result;
}


int main() {
    
    struct node* head = NULL;
    insert_front(&head, 3);
    insert_front(&head, 9);
    insert_front(&head, 1);
    insert_front(&head, 8);
    insert_front(&head, 2);
    insert_front(&head, 5);

    printf("原始鏈結串列: ");
    print_list(head);

    int k = 1;
    int kth = find_kth_largest(head, k);
    printf("第 %d 大的節點值為: %d\n", k, kth);

    return 0;
}
