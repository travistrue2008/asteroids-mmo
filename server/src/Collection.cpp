/*
 *  Collection.cpp
 *  Catalyst Game Engine
 *
 *  Created by Travis True on 4/21/11.
 *  Copyright 2011 TRUESoft Entertainment. All rights reserved.
 *
 */

#include "Collection.h"


namespace CatalystEngine
{
	CollectionItem::CollectionItem()
	{
		Initialize();
	}


	CollectionItem::CollectionItem(char *name)
	{
		Initialize();
		sprintf(this->name, "%s", name);
	}


	CollectionItem::CollectionItem(char *name, char *type)
	{
		Initialize();
		sprintf(this->name, "%s", name);
		sprintf(this->type, "%s", type);
	}


	CollectionItem::~CollectionItem()
	{
		if(next)
		{
			delete next;
			next = NULL;
		}
	}


	void CollectionItem::Initialize()
	{
		memset(name, '\0', sizeof(name));
		memset(type, '\0', sizeof(type));
		prev = next = NULL;
	}


	char *CollectionItem::GetName()
	{ return name; }

	int CollectionItem::GetIndex()
	{
		if(!parent) return COLLECTION_NO_PARENT;
		int index = -1;
		for(int i=0;i<parent->GetNumItems();i++)
		{
			// check for same pointer addresses
			if(parent->GetItem(i) == this)
			{
				index = i;
				break;
			}
		}
		
		// return a valid index or no collection
		if(index > -1) return index;
		return COLLECTION_INVALID;
	}


	Collection::Collection()
	{
		Initialize();
	}


	Collection::Collection(const char *key)
	{
		Initialize();
		SetKey(key);
	}


	Collection::~Collection()
	{
		if(items)
		{
			delete items;
			items = NULL;
		}
		numItems = 0;
	}


	void Collection::Initialize()
	{
		numItems = 0;
		maxSize = -1;
		items = NULL;
		memset(typeKey, 0, 32);
	}


	int Collection::RemoveItem(CollectionItem *ptr)
	{
		if(!ptr) return COLLECTION_NULL_ELEMENT;
		
		// handle if there is only one screen in the list
		if(ptr == items && numItems == 1)
		{
			delete items;
			items = NULL;
			numItems--;
			return COLLECTION_SUCCESS;
		}
		
		// handle if head of the list
		if(ptr == items && ptr->next)
		{
			items = ptr->next;
			items->prev = NULL;
		}
		
		// handle if in the middle of the list
		if(ptr->prev && ptr->next)
		{
			ptr->prev->next = ptr->next;
			ptr->next->prev = ptr->prev;
		}
		
		// handle if tail of the list
		if(!ptr->next && ptr->prev)
			ptr->prev->next = NULL;
		
		// clear out the pointer
		ptr->prev = ptr->next = NULL;
		delete ptr;
		ptr = NULL;
		numItems--;
		return COLLECTION_SUCCESS;
	}


	int Collection::AddItem(CollectionItem *element)
	{
		bool found = false;

		// make sure the element isn't NULL
		if(!element) return COLLECTION_NULL_ELEMENT;

		// make sure the collection hasn't reached its capacity
		if(maxSize != -1 && numItems == maxSize)
			return COLLECTION_LIMIT_REACHED;

		// check for a matching type
		if(strlen(typeKey) && strcmp(element->type, typeKey))
			return COLLECTION_INVALID_TYPE;
		
		// add an item to the bottom of the list
		if(items)
		{
			// make sure the name doesn't match the root element
			if(strlen(element->name) && !strcmp(element->name, items->name))
				return COLLECTION_DUPLICATE_FOUND;

			// iterate to the end of the list
			CollectionItem *ptr = items;
			while(ptr->next)
			{
				// check if the name already exists
				if(strlen(element->name) && !strcmp(element->name, ptr->name)) found = true;
				ptr = ptr->next; // go the next object in the linked list
			}
			if(found) return COLLECTION_DUPLICATE_FOUND; // the name already exists
			
			// add a new element to the list
			ptr->next = element;
			ptr->next->prev = ptr; // link the new pointer's prev pointer to the current pointer
		} else
			items = element;
		numItems++;
		return COLLECTION_SUCCESS;
	}


	int Collection::DoesItemExist(char *name)
	{
		// check if everything is valid
		if(!items) return COLLECTION_NULL_ELEMENT;
		if(!name || !strlen(name)) return COLLECTION_NULL_ELEMENT;
		
		// loop through all elements
		for(int i=0;i<GetNumItems();i++)
		{
			// return true if a match is found
			if(!strcmp(name, GetItem(i)->GetName()))
				return true;
		}
		return false;
	}


	int Collection::SwapItems(CollectionItem *element1, CollectionItem *element2)
	{
		// make sure the elements are valid
		if(!element1 || !element2)
			return COLLECTION_NULL_ELEMENT;
		printf("BEFORE SWAP: %s  %s\n", element1->GetName(), element2->GetName());

		CollectionItem *temp = element2;
		CollectionItem *prev1 = element1->prev;
		CollectionItem *next1 = element1->next;
		CollectionItem *prev2 = element2->prev;
		CollectionItem *next2 = element2->next;

		// perform the swap
		element2 = element1;	// set element 2
		element2->prev = prev1;
		element2->next = next1;
		element1 = temp;		// set element 1
		element1->prev = prev2;
		element1->next = next2;
		printf("AFTER SWAP: %s  %s\n", element1->GetName(), element2->GetName());
		if(element1->prev) printf("  element1->prev: %s\n", element1->prev->GetName()); else printf("  element1->prev: NULL\n");
		if(element1->next) printf("  element1->next: %s\n", element1->next->GetName()); else printf("  element1->next: NULL\n");
		if(element2->prev) printf("  element2->prev: %s\n", element2->prev->GetName()); else printf("  element2->prev: NULL\n");
		if(element2->next) printf("  element2->next: %s\n", element2->next->GetName()); else printf("  element2->next: NULL\n");
		return COLLECTION_SUCCESS;
	}


	int Collection::RemoveItem(const char *name)
	{
		return RemoveItem(GetItem(name));
	}


	int Collection::RemoveItem(int index)
	{
		return RemoveItem(GetItem(index));
	}


	void Collection::RemoveAllItems()
	{
		if(!items) return;
		delete items;
		items = NULL;
		numItems = 0;
	}


	void Collection::PrintItems(const char *caption)
	{
		CollectionItem *ptr = items;
		if(!numItems) return;
		printf("%s: %i\n", caption, numItems);
		while(ptr)
		{
			printf("  %s\n", ptr->GetName());
			ptr = ptr->next;
		}
	}


	void Collection::SetKey(const char *key)
	{
		sprintf(typeKey, "%s", key);
	}


	void Collection::SetSize(int size)
	{
		// set the size
		if(size > -1)
			maxSize = size;
		else
			return;
		if(size == -1) return; // finish if unlimited

		// if limited, remove "overflow" elements
		while(numItems > maxSize)
		{
			CollectionItem *item = GetLastItem();
			RemoveItem(item);
		}
	}


	int Collection::GetNumItems()
	{ return numItems; }


	CollectionItem *Collection::GetItem(const char *name)
	{
		bool found = false;
		CollectionItem *ptr = items;
		
		// make sure there are screens and if there's valid name
		if(!name || !strlen(name)) return NULL;
		if(!numItems) return NULL;
		
		// loop through the screens until a match is found
		while(ptr)
		{
			if(!strcmp(name, ptr->GetName()))
			{
				found = true;
				break;
			}
			ptr = ptr->next;
		}
		if(!found) return NULL;
		return ptr;
	}


	CollectionItem *Collection::GetItem(int index)
	{
		int i = 0;
		CollectionItem *ptr = items;
		
		// bound the index
		if(index < 0) index = 0;
		if(index > (numItems-1)) index = numItems - 1;
		if(!numItems) return NULL; // make sure there are screens in the list
		
		// loop through the screens until the index is found
		while(ptr)
		{
			if(i == index) break;
			ptr = ptr->next;
			i++;
		}
		return ptr;
	}


	CollectionItem *Collection::GetLastItem()
	{
		CollectionItem *ptr = items;
		if(!ptr) return NULL;
		while(ptr->next)
			ptr = ptr->next;
		return ptr;
	}
}
