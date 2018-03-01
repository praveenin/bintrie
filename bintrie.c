#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "bintrie.h"

int8_t
bintrie_delete_path(struct bintrie_node *node, uint32_t val, uint8_t len) {
	if (len == 0)
		return 0;
	struct bintrie_node *cur = node, *tmp = NULL;
	int i;
	uint8_t branch_one = val & 1 ? 1: 0;
	if (!branch_one) {
		bintrie_delete_path(cur->zero, val>>1, len-1);
		free(cur->zero);
		cur->zero = NULL;
	}
	else {
		bintrie_delete_path(cur->one, val>>1, len-1);
		free(cur->one);
		cur->one = NULL;
	}
	return 0;
}

int8_t
bintrie_delete_all(struct bintrie_node *root) {
	if (root->zero) {
		bintrie_delete_all(root->zero);
		free(root->zero);
		root->zero = NULL;
	}
	if (root->one) {
		bintrie_delete_all(root->one);
		free(root->one);
		root->one = NULL;
	}
	return 0;
}

/*
node - trie node
rp_val - rootpath val
rp_len - rootpath length
*/
void
bintrie_print_helper(struct bintrie_node *node, uint32_t rp_val, uint8_t rp_len) {
	if (!node)
		return;
	if (node->zero) {
		printf("0 ");
		bintrie_print_helper(node->zero, rp_val, rp_len+1);
	}
	if (node->one) {
		printf("1 ");
		bintrie_print_helper(node->one, rp_val | (1<<rp_len), rp_len+1);
	}
	if (node->end)
		printf(" : %d\n", rp_val & (0xffffffff >> (32-rp_len)));
}

/* External API */
int8_t
bintrie_init(struct bintrie_node *root) {
	printf("Entering bintrie_init\n"); //DEBUG
	if(!root)
		return -1;
	root->zero = NULL;
	root->one = NULL;
	root->end = 0;
	return 0;
}

int8_t
bintrie_cleanup(struct bintrie_node *root) {
	printf("Entering bintrie_cleanup\n"); //DEBUG
	bintrie_delete_all(root);
	return 0;
}

int8_t
bintrie_insert(	struct bintrie_node *root,
		uint32_t val, uint8_t len) {
	struct bintrie_node *cur = root;
	int i;

	if (!root)
		return -1;
	for(i=0; i<len; i++) {
		uint8_t branch_one = 0;
		branch_one = val & (1<<i) ? 1: 0;
		if (!branch_one) {
			if (!cur->zero)
				cur->zero = (struct bintrie_node *)calloc(1, sizeof(struct bintrie_node));
			cur = cur->zero;
		}
		else {
			if (!cur->one)
				cur->one = (struct bintrie_node *)calloc(1, sizeof(struct bintrie_node));
			cur = cur->one;
		}
	}
	cur->end = 1;
	return 0;
}

int8_t
bintrie_delete(	struct bintrie_node *root,
		uint32_t val, uint8_t len) {
	struct bintrie_node *cur = root;
	int i, keep_prefix_len = 0;

	if (!root)
		return -1;
	for(i=0; i<len; i++) {
		uint8_t branch_one = 0;
		branch_one = val & (1<<i) ? 1: 0;
		if (!branch_one) {
			if (cur->one) {
				keep_prefix_len = i;
			}
			cur = cur->zero;
		}
		else {
			if (cur->zero) {
				keep_prefix_len = i;
			}
			cur = cur->one;
		}
	}

	cur = root;
	for(i=0; i<keep_prefix_len; i++) {
		uint8_t branch_one = 0;
		branch_one = val & (1<<i) ? 1: 0;
		if (!branch_one) {
			cur = cur->zero;
		}
		else {
			cur = cur->one;
		}
	}
	if (bintrie_delete_path(cur, val>>keep_prefix_len, len-keep_prefix_len) != 0) {
		return -1;
	}

	cur->end = 0;
	return 0;
}

void
bintrie_print(struct bintrie_node *root) {
	printf("Entering bintrie_print\n"); //DEBUG
	printf("\n");
	bintrie_print_helper(root, 0, 0);
	printf("\n");
}
