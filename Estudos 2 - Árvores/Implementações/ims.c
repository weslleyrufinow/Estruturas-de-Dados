
void print(void *letra);
void tree_print_main(Tree *bst, void (*print)(void *));
void tree_print_level(Tree *bst, void (*print)(void *), int level, char c);

void tree_print_setas(Tree *tree, void (*print)(void *));

void print(void *letra){
    printf("%c ", *((char *)letra) );
}

void tree_print_main(Tree *bst, void (*print)(void *)) {
    int level = 0;
    if (print) {
        tree_print_level(bst, print, 0, '.');
    }
}

void tree_print_level(Tree *bst, void (*print)(void *), int level, char c){
    int i;

    for (i=0; i<level; i++)
        printf("\t");

    printf("%c/", c);
    if (bst) {
        print(bst->value);
        printf("\n");


    tree_print_level(bst->right, print, level + 1, 'r');
    tree_print_level(bst->left,  print, level + 1, 'l');
    }
    else
        printf("~\n");
}

void tree_print_setas(Tree *tree, void (*print)(void *)){
    if(tree){
        if(tree->value){
            printf("<");
            tree_print_setas(tree->left, print);
            print(tree->value);
            tree_print_setas(tree->right, print);
            printf("> ");
        }
    }else{
        printf("<> ");
    }
}