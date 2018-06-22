/*
 *  Collection.h
 *  Catalyst Game Engine
 *
 *  Created by Travis True on 4/21/11.
 *  Copyright 2011 TRUESoft Entertainment. All rights reserved.
 *
 */

#ifndef COLLECTION_H
#define COLLECTION_H

#include "CatalystEnumeration.h"


namespace CatalystEngine
{
	class Collection;


	class CollectionItem
	{
		friend class Collection;
		
	protected:
		char name[32];								// unique name of the item in the list
		char type[32];								// only add collection items with the matching type specifier
		Collection *parent;							// parent collection holding this item
		CollectionItem *prev;						// the prev item in the list
		CollectionItem *next;						// the next item in the list
		
		void Initialize();

	public:
		CollectionItem();
		CollectionItem(char *name);
		CollectionItem(char *name, char *type);
		virtual ~CollectionItem();
		
		char *GetName();
		int GetIndex();
	};


	class Collection
	{
	protected:
		int numItems;								// current number of items in the collection
		int maxSize;								// maximum number of elements the collection can hold (-1 is unlimited)
		char typeKey[32];							// type string for item filtering
		CollectionItem *items;						// linked list of items
		
		void Initialize();
		int RemoveItem(CollectionItem *ptr);
		
	public:
		Collection();
		Collection(const char *key);
		virtual ~Collection();
		
		virtual int AddItem(CollectionItem *element);
		virtual int RemoveItem(const char *name);
		virtual int RemoveItem(int index);
		virtual void RemoveAllItems();
		
		virtual int DoesItemExist(char *name);
		virtual int SwapItems(CollectionItem *element1, CollectionItem *element2);
		
		virtual void PrintItems(const char *caption);
		
		void SetKey(const char *key);
		void SetSize(int size);
		
		int GetNumItems();
		CollectionItem *GetItem(const char *name);
		CollectionItem *GetItem(int index);
		CollectionItem *GetLastItem();
	};
}

#endif // COLLECTION_H
