#include <stdio.h>

#include <malloc.h>

#define log(fmt, arg...) printf(""fmt,##arg)
#define MAX_ADDR 256

#include "list.h"

struct list_test {
	struct list_head list;
	int a;
#define LIST_TEST_INITIALIZER(v)   {{NULL, NULL}, v}
};



int demo_list_1_add_del_swap_for_each()
{
    struct list_head lhead;
    
    struct list_test lt1 = LIST_TEST_INITIALIZER(1);
    struct list_test lt2 = LIST_TEST_INITIALIZER(2);
    struct list_test lt3 = LIST_TEST_INITIALIZER(3);
    struct list_test lt4 = LIST_TEST_INITIALIZER(4);
    struct list_test lt5 = LIST_TEST_INITIALIZER(5);
    
    struct list_test *iter;
    
    INIT_LIST_HEAD(&lhead);
    
    list_add_tail(&lt1.list, &lhead);
    list_add_tail(&lt2.list, &lhead);
    list_add_tail(&lt3.list, &lhead);
    list_add_tail(&lt4.list, &lhead);
    list_add_tail(&lt5.list, &lhead);

    list_del_init(&lt3.list);
	list_for_each_entry(iter, &lhead, list) {
		printf("%d - ", iter->a);
	}printf("\n");
    

    return 0;
}



int demo_list_2_move_and_move_tail()
{
    struct list_head lhead1, lhead2;
    
    struct list_test lt1 = LIST_TEST_INITIALIZER(1);
    struct list_test lt2 = LIST_TEST_INITIALIZER(2);
    struct list_test lt3 = LIST_TEST_INITIALIZER(3);
    struct list_test lt4 = LIST_TEST_INITIALIZER(4);
    struct list_test lt5 = LIST_TEST_INITIALIZER(5);
    
    struct list_test *iter;
    
    INIT_LIST_HEAD(&lhead1);
    INIT_LIST_HEAD(&lhead2);
    
    list_add_tail(&lt1.list, &lhead1);
    list_add_tail(&lt2.list, &lhead1);
    list_add_tail(&lt3.list, &lhead1);
    list_add_tail(&lt4.list, &lhead2);
    list_add_tail(&lt5.list, &lhead2);

    list_for_each_entry(iter, &lhead1, list) {
		printf("%d - ", iter->a);
	}printf("\n");
    list_for_each_entry(iter, &lhead2, list) {
		printf("%d - ", iter->a);
	}printf("\n");

    list_move(&lt1.list, &lhead2);

    list_for_each_entry(iter, &lhead1, list) {
		printf("%d - ", iter->a);
	}printf("\n");
    list_for_each_entry(iter, &lhead2, list) {
		printf("%d - ", iter->a);
	}printf("\n");

    list_move_tail(&lt2.list, &lhead2);

    list_for_each_entry(iter, &lhead1, list) {
		printf("%d - ", iter->a);
	}printf("\n");
    list_for_each_entry(iter, &lhead2, list) {
		printf("%d - ", iter->a);
	}printf("\n");

    return 0;
}


int main()
{
    demo_list_1_add_del_swap_for_each();
    demo_list_2_move_and_move_tail();


    return 0;
}


