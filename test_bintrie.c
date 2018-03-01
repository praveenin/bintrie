#include <stdio.h>
#include <stdint.h>
#include "bintrie.h"

int
main() {
        int i;
        printf("Entering main\n"); //DEBUG
        struct bintrie_node root;
	//bintrie_init(&root);
        //for(i=0; i<100; i++) {
        //        bintrie_insert(&root, i, 32);
        //}
        //bintrie_print(&root);
        //bintrie_cleanup(&root);

	bintrie_init(&root);
	bintrie_insert(&root, 0b100, 3);
	bintrie_insert(&root, 0b101, 3);
        bintrie_print(&root);
	if (bintrie_delete(&root, 0b100, 3)) {
		printf("Bintrie delete failed\n");
	}
        bintrie_print(&root);
        bintrie_cleanup(&root);
        return 0;
}
