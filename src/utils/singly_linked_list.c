#include <stdlib.h>
#include "list.h"

typedef struct Node_* Node;

struct Node_ {
    void* element;
    Node next;
};

struct List_ {
    Node head;
    Node tail;
    Node iterator;
    int size;
};

Node create_node(void* element, Node next) {
    Node node = malloc(sizeof(struct Node_));
    node->element = element;
    node->next = next;
    return node;
}

/**
 * @brief Creates a new list.
 *
 * @return List The new list.
 */
List list_create() {
    List list = malloc(sizeof(struct List_));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

/**
 * @brief Destroys a list.
 *
 * Frees all memory allocated for the list, and for all elements of the list.
 *
 * @param list The list to destroy.
 * @param free_element The function to free the elements of the list.
 */
void list_destroy(List list, void (*free_element)(void*)) {
    Node node = list->head;
    while (node != NULL) {
        if (free_element != NULL) {
            free_element(node->element);
        }
        Node previous = node;
        node = node->next;
        free(previous);
    }
    free(list);
}

/**
 * @brief Returns true iff the list contains no elements.
 *
 * @param list The linked list.
 * @return true iff the list contains no elements.
 */
bool list_is_empty(List list) {
    // return list->head == NULL;
    return list->size == 0;
}

/**
 * @brief Returns the number of elements in the list.
 *
 * @param list The linked list.
 * @return size_t The number of elements in the list.
 */
size_t list_size(List list) {
    return list->size;
}

/**
 * @brief Returns the first element of the list.
 *
 * @param list The linked list.
 * @return void* The first element of the list.
 */
void* list_get_first(List list) {
    if (list->head != NULL) {
        return list->head->element;
    }
    return NULL;
}

/**
 * @brief Returns the last element of the list.
 *
 * @param list The linked list.
 * @return void* The last element of the list.
 */
void* list_get_last(List list) {
    if (list->tail == NULL) {
        return NULL;
    }
    return list->tail->element;
}

/**
 * @brief Returns the element at the specified position in the list.
 *
 * Range of valid positions: 0, ..., size()-1.
 *
 * @param list The linked list.
 * @param position The position of the element to return.
 * @return void* The element at the specified position in the list.
 */
void* list_get(List list, int position) {
    if ((size_t)position >= list_size(list)) {
        return NULL;
    }
    if ((size_t)position == list_size(list) - 1) {
        return list->tail->element;
    }
    if (position == 0) {
        return list->head->element;
    }
    int idx = 1;
    Node node = list->head->next;
    while (idx != position) {
        idx++;
        node = node->next;
    }
    return node->element;
}

/**
 * @brief Returns the position in the list of the first occurrence of the specified element.
 *
 * Returns -1 if the specified element does not occur in the list.
 *
 * @param list The linked list.
 * @param equal The function to compare two elements.
 * @param element The element to search for.
 * @return int The position in the list of the first occurrence of the specified element, or -1 if the specified element does not occur in the list.
 */
int list_find(List list, bool (*equal)(void*, void*), void* element) {
    int position = 0;
    Node node = list->head;
    while (node != NULL) {
        if (equal(node->element, element)) {
            return position;
        }
        position++;
        node = node->next;
    }
    return -1;
}

/**
 * @brief Inserts the specified element at the first position in the list.
 *
 * @param list The linked list.
 * @param element The element to insert.
 */
void list_insert_first(List list, void* element) {
    Node node = create_node(element, list->head);
    if (list_is_empty(list)) {
        list->tail = node;
    }
    list->head = node;
    list->size++;
}

/**
 * @brief Inserts the specified element at the last position in the list.
 *
 * @param list The linked list.
 * @param element The element to insert.
 */
void list_insert_last(List list, void* element) {
    Node node = malloc(sizeof(struct Node_));
    node->element = element;
    if (list->tail != NULL) {
        list->tail->next = node;
    } else {
        list->head = node;
    }
    list->tail = node;
    list->size++;
}

/**
 * @brief Inserts the specified element at the specified position in the list.
 *
 * Range of valid positions: 0, ..., size().
 * If the specified position is 0, insert corresponds to insertFirst.
 * If the specified position is size(), insert corresponds to insertLast.
 *
 * @param list The linked list.
 * @param element The element to insert.
 * @param position The position at which to insert the specified element.
 */
void list_insert(List list, void* element, int position) {
    if (position < 0 || position > list->size) {
        return;  // invalid position
    }
    if (position == 0) {
        list_insert_first(list, element);
        return;
    }
    if (position == list->size) {
        list_insert_last(list, element);
        return;
    }
    Node pred = list->head;
    for (int i = 0; i < position - 1; i++) {
        pred = pred->next;
    }
    Node new_node = create_node(element, pred->next);
    pred->next = new_node;
    list->size++;
}

/**
 * @brief Removes and returns the element at the first position in the list.
 *
 * @param list The linked list.
 * @return void* The element at the first position in the list.
 */
void* list_remove_first(List list) {
    if (list_is_empty(list)) {
        return NULL;
    }
    Node node = list->head;
    list->head = node->next;
    list->size--;
    void* element = node->element;
    free(node);
    if (list_size(list) == 0) {
        list->tail = list->head;
    }
    return element;
}

/**
 * @brief Removes and returns the element at the last position in the list.
 *
 * @param list The linked list.
 * @return void* The element at the last position in the list.
 */
void* list_remove_last(List list) {
    if (list_is_empty(list)) {
        return NULL;
    }
    Node node = list->head;
    Node prev = NULL;
    while (node->next != NULL) {
        prev = node;
        node = node->next;
    }
    list->tail = prev;
    list->size--;
    if (list_is_empty(list)) {
        list->head = NULL;
    } else {
        list->tail->next = NULL;
    }
    void* element = node->element;
    free(node);
    return element;
}

/**
 * @brief Removes and returns the element at the specified position in the list.
 *
 * Range of valid positions: 0, ..., size()-1.
 *
 * @param list The linked list.
 * @param position The position of the element to remove.
 * @return void* The element at the specified position in the list.
 */
void* list_remove(List list, int position) {
    void* element = NULL;

    if (position >= 0 && position < list->size) {
        Node current = list->head;
        Node previous = NULL;
        int i = 0;

        while (i < position) {
            previous = current;
            current = current->next;
            i++;
        }

        element = current->element;

        if (previous == NULL) {
            list->head = current->next;
        } else {
            previous->next = current->next;
        }

        if (current == list->tail) {
            list->tail = previous;
        }

        free(current);
        list->size--;
    }

    return element;
}

/**
 * @brief Removes all elements from the list.
 *
 * @param list The linked list.
 * @param free_element The function to free the elements of the list.
 */
void list_make_empty(List list, void (*free_element)(void*)) {
    while (list->head != NULL) {
        Node current = list->head;
        list->head = current->next;

        if (free_element != NULL) {
            (*free_element)(current->element);
        }

        free(current);
    }

    list->tail = NULL;
    list->size = 0;
}

void list_iterator_start(List list) {
    if (list != NULL) {
        list->iterator = list->head;
    }
}

bool list_iterator_has_next(List list) {
    if (list != NULL && list->iterator != NULL) {
        return true;
    }
    return false;
}

void* list_iterator_get_next(List list) {
    void* element = list->iterator->element;
    list->iterator = list->iterator->next;
    return element;
}

void** list_to_array(List list) {
    if (list == NULL || list->size == 0) {
        return NULL;
    }

    void** array = malloc(list->size * sizeof(void*));
    if (array == NULL) {
        return NULL;  // Failed to allocate memory
    }

    Node node = list->head;
    int i = 0;
    while (node != NULL && i < list->size) {
        array[i] = node->element;
        node = node->next;
        i++;
    }

    if (i != list->size) {
        free(array);
        return NULL;
    }

    return array;
}
