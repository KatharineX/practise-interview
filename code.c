 #include <stdio.h>
 #include <stdlib.h>
 
 struct node {
     struct node* next;
     int v;
 };
 
 struct finder {
     void* object;
     int to_find;
     int* (*find)(void*);
 };
 
 struct node* node_init(int v) {
     printf("%d\n",v );
     struct node* n = malloc(sizeof(struct node));
     n->next = NULL;
     n->v = v; // v = 0
     return n;
 }
 
 // head obj
 int* find_value(void* obj) {
     struct finder* finder = (struct finder*) obj;//  
     printf("finder = %d,\n", ((struct node *)finder->object)->v);
     struct node* cursor = (struct node*) obj; 
     printf("cursor = %d, ", cursor->v);
 
     int* result = NULL;
     while(cursor != NULL) {
         printf("%d  = to_find %d\n", cursor->v, finder->to_find);
         if(cursor->v == finder->to_find) {
             result = &cursor->v;
             break;
         }
         cursor = cursor->next;
     }
     return result;
 }
 
 int main() {

    //  unsigned char ptr;
    //  const char *s = "hello" + 1;
    //  int y = 24;
    //  printf("%c: %d\n", (-1)[s], y);

    struct node *head = node_init(0);
     struct node *current = head;
     struct finder finder = {.object = head, .find = find_value, .to_find = 5};
     printf("finder obj: %d\n", ((struct node *)finder.object)->v);
     for (int i = 1; i <= 10; i++)
    {
         current->next = node_init(i);
         current = current->next;
        
    }
     int *value = finder.find(finder.object);
     if (value)
    {
         printf("found = %d\n", *value);
        
    }
    else
    {
         printf("We didn't find it!");
        
    }
    return 0;
 }