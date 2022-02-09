#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "List.h"

struct termo{
    int num;
    int exp;
};
typedef struct termo termo;

typedef struct Node Node;

struct Node {
    Node *next;
    void *value;
};

struct List {
    Node *first;
    int length;
};

List *List_create() {
    List *list = NULL;
    list = malloc(sizeof (List));
    if (list) {
        list->first = NULL;
        list->length = 0;
    }
    return list;
}

void List_destroy(List *list) {
    Node *cur = NULL;
    Node *aux = NULL;

    if (list) {
        //atual recebe 1º no
        cur = list->first;
        
        //enquanto atual != NULL
        while (cur) {
            //auxiliar recebe o próximo no
            aux = cur->next;
            //free no no atual
            free(cur);
            //atual recebe proximo no
            cur = aux;
        }

        free(list);
    }
}

void List_insertBegin(List *list, void *value) {
    Node *new = NULL;

    if (list && value) {
        new = malloc(sizeof(Node));
        new->value = value;
        new->next = NULL;

        if (list->length > 0)
            new->next = list->first;

        list->first = new;
        list->length++;
    }
}

void List_insertEnd(List *list, void *value) {
    Node *cur = NULL;
    Node *new = NULL;

    if (list && value) {
        new = malloc(sizeof(Node));
        new->value = value;
        new->next = NULL;

        if (list->length > 0) {
            cur = list->first;

            while (cur->next)
                cur = cur->next;

            cur->next = new;
        }
        else
            list->first = new;

        list->length++;
    }
}

void *List_removeBegin(List *list) {
    Node *rem = NULL;

    if (list) {
        if (list->length > 0) {
            rem = list->first;
            list->first = list->first->next;
            rem->next = NULL;
        }

        list->length--;
    }
    
    return rem;
}

void *List_removeEnd(List *list) {
    Node *rem = NULL;
    Node *cur = NULL;

    if (list) {
        if (list->length > 0) {
            if (list->length == 1) {
                rem = list->first;
                list->first = NULL;
            }
            else {
                cur = list->first;

                while (cur->next->next)
                    cur = cur->next;

                rem = cur->next;
                cur->next = NULL;
            }

            list->length--;
        }
    }
    
    return rem;
}

void *List_find(List *list, void *value, int (*compar)(void *, void *)) {
    Node *cur = NULL;

    if (list && value && compar) {
        if (list->length > 0) {

            cur = list->first;

            while (cur) {
                if (compar(cur->value, value) == 0)
                    return cur->value;

                cur = cur->next;
            }
        }   
    }

    return cur;
}

void *List_findAndRemove(List *list, void *value, int (*compar)(void *, void *)) {
    Node *cur = NULL;
    Node *prv = NULL;

    if (list && value && compar) {
        if (list->length > 0) {

            cur = list->first;

            while (cur) {
                if (compar(cur->value, value) == 0) {
                    if (prv == NULL)
                        list->first = cur->next;
                    else
                        prv->next = cur->next;

                    cur->next = NULL;
                    list->length--;
                    return cur->value;
                }

                prv = cur;
                cur = cur->next;
            }
        }   
    }

    return cur;
}

int List_getLength(List *list) {
    if (list)
        return list->length;
    else
        return -1;
}

void List_print(List *list, void (*print)(void *)) {
     Node *cur = NULL;

    if (list && print) {
        if (list->length > 0) {
            cur = list->first;
            while (cur) {
                print(cur->value);
                cur = cur->next;
            }
            printf("\n");
        }
        else {
            printf("(empty list)\n");
        }
    }
}
/*
List *List_concatenate(const List *list_a, const List *list_b) {
    return;
}
*/

List *List_sort(List *list, int (*compar)(void *,void *)) {
    int i, a = List_getLength(list);
    List *new = malloc(sizeof(List *));
    termo *vet[a];
    Node *aux2;
    termo *aux;
    for(i = 0; i < a; i++){
        aux2 = List_removeEnd(list);
        vet[i] = aux2->value;
    }
    /*
    for(i = 0; i < a; i++){
        aux = (termo * )vet[i];
        printf("%d ",aux->num);
        printf("%d\n",aux->exp);

    }*/

    qsort(vet,a,sizeof(void *),compar);

    for(i = 0; i < a; i++){
        List_insertEnd(new,vet[i]);
    }

return new;}

/*
void List_insertSorted(List *list, void *value, int (*compar)(void *, void *)) {
}
*/

void *List_removeMaior(List *list, int (*compar)(void *, void *)) {
    Node *ma = NULL;
    void *aux = NULL;
    int i,c=0;

    if (list && compar) {
        if (list->length > 0) {
            ma = list->first;
            aux = ma->value;
            while (ma){
                if(compar(ma->value,aux) == 1)
                    aux = ma->value;
                ma = ma->next;
            }
        }
    }

    if (list && compar) {
        if (list->length > 0) {
            ma = list->first;
            while (ma){
                if(compar(ma->value,aux) == 0)
                    c++;
                ma = ma->next;
            }
        }
    }

    for(i = 0; i < c ; i++){
        List_findAndRemove(list,aux,compar);
    }

return aux;}

void *List_end(List *list) {
    Node *cur = NULL;

    if (list) {
        if (list->length > 0) {
            cur = list->first;

            while(cur){
                cur = cur->next;
            }
            
        }   
    }
    
return (cur->value);}

void *List_getFirst(List *list){
    if (list){
        Node *first = NULL;
        first = list->first;
        return first;
    }
}