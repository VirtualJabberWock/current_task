#include "List.h"
#include "../BasicDataStructs.h"

List* NewList()
{
	List* l = initArray(1, sizeof(List));
	l->head = 0;
	l->tail = 0;
	l->size = 0;

	l->push = _List_pushBack;
	l->pushFront = _List_pushFront;
	l->find = _List_find;
	l->_clear = _List_clear;
	l->_dispose = _List_dispose;
	l->get = _List_get;
	l->remove = _List_remove;
	return l;
}

void _List_pushBack(__SELF_List__, ValueT value)
{
	if (self == 0) return panic_NPE(_List_pushBack, "<List> list");
	node* newNode = (node*)malloc(sizeof(node));
	if (newNode)
	{
		newNode->value = value;
		newNode->next = 0;
		newNode->prev = 0;

		if (self->head == 0)
			self->head = newNode;
		else if (self->tail == 0)
		{
			self->tail = newNode;
			self->tail->prev = self->head;
			self->head->next = self->tail;
		}
		else
		{
			self->tail->next = newNode;
			newNode->prev = self->tail;
			self->tail = newNode;
		}
		self->size++;
	}
}

void _List_pushFront(__SELF_List__, ValueT value)
{
	if (self == 0) return panic_NPE(_List_pushFront, "<List> list");
	node* newNode = (node*)malloc(sizeof(node));
	if (newNode)
	{
		newNode->value = value;
		newNode->next = 0;
		newNode->prev = 0;

		if (self->head == NULL)
			self->head = newNode;
		else
		{
			self->head->prev = newNode;
			newNode->next = self->head;
			self->head = newNode;
		}
		self->size++;
	}
}

node* _List_find(__SELF_List__, ValueT value)
{
	if (self == 0) return panic_NPE(_List_find, "<List> list");
	node* current = 0;
	if (self->head != NULL)
		current = self->head;
	while (current != NULL)
	{
		if (isEQUAL(current->value, value))
			break;
		current = current->next;
	}
	return current;
}

void _List_clear(__SELF_List__) {

	if (self == 0) return panic_NPE(_List_clear, "<List> self");

	node* current = self->head;
	node* tmp;
	while (current != NULL)
	{
		tmp = current->next;
		free(current);
		current = tmp;
	}
	self->head = 0;
	self->tail = 0;
	self->size = 0;
}

ValueT _List_get(__SELF_List__, int id)
{
	if (self == 0) return panic_NPE(_List_get, "<List> self");
	if( (id >= self->size) || (id < 0) ) 
		return panic_e(
		LIST_CLASSNAME, "get(self, index)",
		"element index is outside the bounds of the list"
		);
	if (id == 0) return self->head->value;
	if (id == self->size - 1) return self->tail->value;
	
	if (self->size / 2 - id > 0) {
		node* current = self->head;
		for (int i = 0; i < id; i++) {
			if (current == 0)
				return panic_e(LIST_CLASSNAME, "get(self, index)", "Invalid size!");
			current = current->next;
		}
	}
	else {
		node* current = self->tail;
		for (int i = 0; i < id; i++) {
			if (current == 0)
				return panic_e(LIST_CLASSNAME, "get(self, index)", "Invalid size!");
			current = current->prev;
		}
	}
	
}

ValueT _List_remove(__SELF_List__, int id)
{
	
	if (self == 0) return panic_NPE(_LinkedList_remove, "<List> self");
	if (id == 0) {
		ValueT tmp = COPY_VALUE_IF_NEEDED(self->head->value);
		c_node* tmp2 = self->head->next;
		free(self->head);
		self->head = tmp2;
		self->size--;
		return tmp;
	}
	c_node* current = self->head;
	c_node* previous = current;
	for (int i = 0; i < id; i++) {
		if (current == 0)
			return panic_e(
				LIST_CLASSNAME, "get(self, index)",
				"element index is outside the bounds of the list"
			);
		previous = current;
		current = current->next;
	}
	ValueT shadow = COPY_VALUE_IF_NEEDED(current->value);
	previous->next = current->next;
	free(current);
	if (id == self->size - 1) {
		self->tail = previous;
	}
	self->size--;
	return shadow;

}

void _List_dispose(List** self) {

	if (sizeof(*self) != sizeof(void*)) panic_e(
		LINKEDLIST_CLASSNAME, "dispose(List** l)",
		"'l' param should be ptr to ptr, not ptr to structure!"
		//todo memory scan
	);
	_LinkedList_clear(*self);
	free(*self);
	*self = 0;
}

void ListDisplay(List* list, string_t name)
{
	if (list == 0) return panic_NPE(ListDisplay, "<List> list");
	printf("[List]<%s> %s: \n{\n", LIST_TYPE_NAME, name);
	ForEachInList(list, __ListElementDisplay);
	printf("\n}\n");
}

void ForEachInList(List* list, LIST_ITER_PROTOTYPE)
{
	if (list == 0) return panic_NPE(ForEachInList, "<List> list");

	node* current = list->head;
	while (current != 0)
	{
		next(current->value, (current->next != 0), list);
		current = current->next;
	}
}

void __ListElementDisplay(ValueT element, Bool hasNext, List* ptr)
{
	printf(VALUE_DISPLAY_FORMAT, element);
	if (hasNext) printf(", \n");
}

void _Private_SwapLinkedNodes(node* l, node* r)
{
	node* ll = l->prev; // before left
	node* rr = r->next; // next to right

	//swap

	if (ll != NULL) ll->next = r;
	if (rr != NULL) rr->prev = l;

	r->prev = ll; // left left <- right ...
	l->prev = r; // ... right <- left ...

	r->next = l; // ... right -> left ...
	l->next = rr; // left -> right right ...
}

void _Private_SwapNodes(List* l, node* left, node* right)
{
	if (l == 0) return panic_NPE(_Private_SwapNodes, "<List> list");
	if ((left == NULL) || (right == NULL)) 
		return panic_NPE(_Private_SwapNodes, "Null node");
	if (left == right)
		return printf("%s.SwapNodes :: try to swap same node", LIST_CLASSNAME);
	if (left->next == right)
		_Private_SwapLinkedNodes(left, right);
	else if (right->next == left)  
		_Private_SwapLinkedNodes(right, left);
	else
	{
		node* l_prev = left->prev;  // (left<<left)   left  of the left  node
		node* l_next = left->next;  // (left>>right)  right of the left  node
		node* r_prev = right->prev; // (left<<right)  left  of the right node
		node* r_next = right->next; // (right>>right) right of the right node
		
		if (l_next != 0) l_next->prev = right; // ... right <- (left>>right)
		if (l_prev != 0) l_prev->next = right; // (left<<left) -> right ...
		right->prev = l_prev; // (left<<left) <- right ...
		right->next = l_next; // ... right -> (left>>right)
		
		if (r_prev != 0) r_prev->next = left; // (left<<right) -> left ...
		if (r_next != 0) r_next->prev = left; // left <- (right>>right) ...
		left->next = r_next; //  ... left -> (right>>right) ...
		left->prev = r_prev; //  (left<<right) <- left ...
	}

	if (l->head == left) l->head = right;
	else if (l->head == right) l->head = left;
	if (l->tail == left) l->tail = right;
	else if (l->tail == right) l->tail = left;
}

void ListBubbleSort(List* l, Bool descending)
{
	for (size_t i = 0; i < l->size; ++i)
	{
		for (node* current = l->head; current != 0; )
		{
			if (current->next != 0)
			{
				if (descending)
				{
					if (COMPARE_VALUES(current->value, current->next->value))
						_Private_SwapNodes(l, current, current->next);
					else
						current = current->next;
				}
				else
				{
					if (COMPARE_VALUES(current->next->value, current->value))
						_Private_SwapNodes(l, current, current->next);
					else
						current = current->next;
				}
			}
			else
				break;
		}
	}
}

