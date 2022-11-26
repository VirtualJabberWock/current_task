#pragma once
#include "../StringUtils.h"
#include "../BasicDataStructs.h"

// Easy to change value type
#define ValueT const char*
#define LIST_TYPE_NAME "String"
#define VALUE_DISPLAY_FORMAT "\t%s"
#define isEQUAL(a,b) (strcmp(a,b) == 0)
#define COMPARE_VALUES(a,b) SUS_alphabetCompare(a,b)
#define COPY_VALUE_IF_NEEDED(v) SUS_str_copy(v)
//...............................

typedef struct tagNode
{
	ValueT value;
	struct tagNode* next;
	struct tagNode* prev;
} node;

/*
Signle connected list
*/
#define LIST_CLASSNAME "BasicDataStruct.List"
#define __SELF_List__ struct tagList *self
typedef struct tagList
{
	node* head;
	node* tail;
	size_t size;
	void (*push)(__SELF_List__, ValueT value);
	void (*pushFront)(__SELF_List__, ValueT value);
	/*@return NULLABLE: Return value can be NULL*/
	node* (*find)(__SELF_List__, ValueT query);
	void (*_dispose)(struct tagList** self);
	void (*_clear)(__SELF_List__);
	ValueT(*get)(__SELF_List__, int id);
	ValueT(*remove)(__SELF_List__, int id);
	//void (*push)(__SELF_List__, string_t value);

} List;

#define LIST_ITER_PROTOTYPE void (*next)(ValueT value, Bool hasNext, List* ptr)

List* NewList();
void ListBubbleSort(List* list, Bool ascending);

void _List_pushBack(__SELF_List__, ValueT value);
void _List_pushFront(__SELF_List__, ValueT value);
node* _List_find(__SELF_List__, ValueT query);
void _List_dispose(List **self);
void _List_clear(__SELF_List__);
ValueT _List_get(__SELF_List__, int id);
ValueT _List_remove(__SELF_List__, int id);

void ListDisplay(List* list, string_t name);
void ForEachInList(List* list, LIST_ITER_PROTOTYPE);

void __ListElementDisplay(ValueT element, Bool hasNext, List* ptr);

void _Private_SwapLinkedNodes(node* left, node* right);
void _Private_SwapNodes(List* l, node* left, node* right);
