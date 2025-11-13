#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct node_t {
    int            tickets;
    int            stride;
    int           pass;
    struct node_t *next;
};

struct node_t *head = NULL;

void insert(int tickets, int pass) {
    struct node_t *tmp = malloc(sizeof(struct node_t));
    assert(tmp != NULL);
    tmp->tickets = tickets;
    tmp->stride  = 10000 / tickets;
    tmp->pass = pass;
    tmp->next    = head;
    head         = tmp;
}

struct node_t *remove_min(void) {
    if (!head) return NULL;

    struct node_t *curr = head;
    struct node_t *min = head;
    struct node_t *prev = NULL;
    struct node_t *min_prev = NULL;

    while (curr) {
        if (curr->pass < min->pass) {
            min = curr;
            min_prev = prev;
        }
        else if (curr->pass == min->pass) {
            int choice = random() % 2;
            if (choice == 0) {
                min = curr;
                min_prev = prev;
            }
        }
        prev = curr;
        curr = curr->next;
    }

    if (min_prev) {
        min_prev->next = min->next;
    } else {
        head = min->next;
    }
    min->next = NULL;
    return min;
}

void add(struct node_t *node) {
    node->next = head;
    head = node;
}

void print_list(void) {
    struct node_t *curr = head;
    printf("List: ");
    while (curr) {
        printf("[t=%d pass=%d stride=%d] ", curr->tickets, curr->pass, curr->stride);
        curr = curr->next;
    }
    printf("\n");
}

int
main(int argc, char *argv[])
{
    if (argc != 3) {
	fprintf(stderr, "usage: lottery <seed> <loops>\n");
	exit(1);
    }
    int seed  = atoi(argv[1]);
    int loops = atoi(argv[2]);
    srandom(seed);

    // populate list with some number of jobs, each
    // with some number of tickets
    insert(20, 0);
    insert(40, 0);
    insert(60, 0);
    insert(80, 0);
    insert(100, 0);
    insert(140, 0);
    int wins[141];
    wins[20] = 0;
    wins[40] = 0;
    wins[60] = 0;
    wins[80] = 0;
    wins[100] = 0;
    wins[140] = 0;

    print_list();
    
    int i;
    for (i = 0; i < loops; i++) {
	struct node_t *curr = remove_min();
    printf("Winner: [t=%d pass=%d stride=%d]\n", curr->tickets, curr->pass, curr->stride);
    wins[curr->tickets]++;
    curr->pass += curr->stride;
    add(curr);
	// current is the winner: schedule it...
    print_list();
}
    printf("\n20: %d, 40: %d, 60: %d, 80: %d, 100: %d, 140: %d\n", wins[20], wins[40], wins[60], wins[80], wins[100], wins[140]);
    return 0;
}

