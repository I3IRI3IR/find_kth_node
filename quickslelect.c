#include <stdio.h>
#include <stdlib.h>
#include <time.h>


struct node {
    struct node* next;   
    struct node** prev;  
    int value;
};


void insert_front(struct node** head, struct node* new_node) {
    new_node->next = *head;
    if (*head != NULL) {
        (*head)->prev = &(new_node->next);
    }
    new_node->prev = head;  
    *head = new_node;
}


struct node* create_node(int val) {
    struct node* n = (struct node*)malloc(sizeof(struct node));
    n->value = val;
    n->next = NULL;
    n->prev = NULL;
    return n;
}


void print_list(struct node* head) {
    struct node* cur = head;
    while (cur) {
        printf("%d ", cur->value);
        cur = cur->next;
    }
    printf("\n");
}


int list_length(struct node* head) {
    int len = 0;
    while (head) {
        len++;
        head = head->next;
    }
    return len;
}


void move_random_pivot_to_front(struct node** head_ref) {
    int n = list_length(*head_ref);
    if (n <= 1) return;

    int rand_index = rand() % n;  
    if (rand_index == 0) return;  

    
    struct node* prev = NULL;
    struct node* cur = *head_ref;
    for (int i = 0; i < rand_index; i++) {
        prev = cur;
        cur = cur->next;
    }
    

    
    if (prev) {
        prev->next = cur->next;
        if (cur->next) {
            cur->next->prev = &(prev->next);
        }
    }

    
    cur->next = *head_ref;
    if (*head_ref) {
        (*head_ref)->prev = &(cur->next);
    }
    cur->prev = head_ref;
    *head_ref = cur;
}


struct node* quick_select_kth_largest(struct node** head_ref, int k) {
    if (head_ref == NULL || *head_ref == NULL || k <= 0) return NULL;

    // 隨機選擇 pivot
    // move_random_pivot_to_front(head_ref);

    struct node* pivot = *head_ref;          
    struct node* larger = NULL;              
    struct node* smaller = NULL;              
    int lenL = 0, lenS = 0;

    
    struct node* cur = pivot->next;
    pivot->next = NULL;  

    while (cur) {
        struct node* next = cur->next;  
        if (cur->value > pivot->value) {
            insert_front(&larger, cur);
            lenL++;
        } else {
            insert_front(&smaller, cur);
            lenS++;
        }
        cur = next;
    }

    
    if (lenL >= k) {
        return quick_select_kth_largest(&larger, k);
    } else if (lenL == k - 1) {
        return pivot;
    } else {
        return quick_select_kth_largest(&smaller, k - lenL - 1);
    }
}


int main() {
    srand(time(NULL));

    struct node* head = NULL;
    insert_front(&head, create_node(3));
    insert_front(&head, create_node(9));
    insert_front(&head, create_node(1));
    insert_front(&head, create_node(8));
    insert_front(&head, create_node(2));
    insert_front(&head, create_node(5));

    printf("原始鏈結串列: ");
    print_list(head);

    
    int len = list_length(head);
    struct node** nodes = (struct node**)malloc(len * sizeof(struct node*));
    struct node* cur = head;
    for (int i = 0; i < len; i++) {
        nodes[i] = cur;
        cur = cur->next;
    }

    int k = 5;
    struct node* result = quick_select_kth_largest(&head, k);
    if (result) {
        printf("第 %d 大的節點值為: %d\n", k, result->value);
    } else {
        printf("第 %d 大不存在\n", k);
    }

    
    for (int i = 0; i < len; i++) {
        free(nodes[i]);
    }
    free(nodes);

    return 0;
}
