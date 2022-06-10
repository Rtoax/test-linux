#include <malloc.h>
#include <string.h>
#include "rbtree.h"



struct mytype {
	struct rb_node my_node;
	int num;
};

struct mytype *my_search(struct rb_root *root, int num)
{
	struct rb_node *node = root->rb_node;
	while(node)
	{
		struct mytype *data = container_of(node, struct mytype, my_node);
		if(num < data->num)
		{
			node = node->rb_left;
		}
		else if(num > data->num)
		{
			node = node->rb_right;
		}
		else
			return data;
	}
	return NULL;
}

int my_insert(struct rb_root *root, struct mytype *data)
{
	struct rb_node **tmp = &(root->rb_node), *parent = NULL;
	while(*tmp)
	{
		struct mytype *this = container_of(*tmp, struct mytype, my_node);
		parent = *tmp;
		if(data->num < this->num)
		{
			tmp = &((*tmp)->rb_left);
		}
		else if(data->num > this->num)
		{
			tmp = &((*tmp)->rb_right);
		}
		else 
		{
			return -1;
		}
	}
	rb_link_node(&data->my_node, parent, tmp);
	rb_insert_color(&data->my_node, root);
	return 0;
}

void my_delete(struct rb_root *root, int num)
{
    struct mytype *data = my_search(root, num);
    if(!data)
    {
        printf("Not found %d.\n", num);
        return;
    }
    rb_erase(&data->my_node, root);
    free(data);
}

void print_rbtree(struct rb_root *tree)
{
    struct rb_node *node;
    for(node=rb_first(tree); node; node=rb_next(node))
    {
        printf("%2d \n", rb_entry(node, struct mytype, my_node)->num);
    }
    printf("\n");
}

void demo_rbtree_original()
{
    struct rb_root mytree = RB_ROOT;
    int i, ret, num, nums[] = {2,6,9,8,3,4,7,1,12,1,5,6,9,31,41,3,41,34,1,34,13,4,13,4,13,41,3,41,34,\
                                83,6, 4,87,65,45,85,21,36,64,74,75,12,3,123,1,234,1,234,213,42,34,234,\
                                13,41,34,13,24,123,4,34,5,345,34,5,67,45,67,5467,467,46523,45245};
    struct mytype *tmp;

    for(i=0;i<sizeof(nums)/sizeof(nums[0]);i++)
    {
        tmp = malloc(sizeof(struct mytype));
        if(!tmp)
            printf("Allocate dynamic memory error.\n");

        num = nums[i];
        tmp->num = num;
        
        ret = my_insert(&mytree, tmp);
        if(ret <0)
        {
            printf("The %d already exist.\n", tmp->num);
            free(tmp);
        }
    }
    print_rbtree(&mytree);

    my_delete(&mytree, 3);
    
    print_rbtree(&mytree);
}

int main()
{
    demo_rbtree_original();
    
    return 0;
}

