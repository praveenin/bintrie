struct bintrie_node {
        struct bintrie_node *zero;
        struct bintrie_node *one;
        uint8_t end;
};

int8_t
bintrie_init(); 

int8_t
bintrie_cleanup(struct bintrie_node *root);

int8_t
bintrie_insert( struct bintrie_node *root,
                uint32_t val, uint8_t len);

int8_t
bintrie_delete( struct bintrie_node *root,
                uint32_t val, uint8_t len);

void
bintrie_print(struct bintrie_node *root);
