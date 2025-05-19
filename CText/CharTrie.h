#pragma once
#include <string.h>

class CharTrie
{
public:
	typedef unsigned char byte;

class Node 
{
public:
    static const int NUM_CHILDS = 256;

	Node(byte value)
    {
        memset(childs, 0, sizeof(childs));
        this->value = value;
        end = false;
        pos = 0;
    }

    Node* addByte(byte b)
    {
        Node* node = this;
        Node* next = node->childs[b];

        if(!next)
        {
            next = new Node(b);
            node->childs[b] = next;
        }

        return next;
    }

    inline Node* findByte(byte b)
    {
        return childs[b];
    }

    Node* find(const byte* array, size_t size)
    {
        if(!array)
            return nullptr;

        CharTrie::Node* next = this;

        for(size_t k = 0; k < size; k++)
        {
            next = next->findByte(array[k]);

            if(!next)
                return 0;
        }

        return next;
    }

    void clear()
    {
        for(size_t i = 0; i < NUM_CHILDS; i++)
        {
            if(childs[i])
                childs[i]->clear();
        }

        delete this;
    }

public:
	Node* childs [NUM_CHILDS] ;
    byte value;
    bool end;
    size_t pos;
    size_t len;
};

public:
    CharTrie()
    {
        root = nullptr;
        count = 0;
    }

    ~CharTrie()
    {
        clear();
    }

    CharTrie(CharTrie&& s) noexcept
    {
        root = s.root;
        count = s.count;
        s.root = nullptr;
        s.count = 0;
    }

	size_t size() const 
    { 
        return count; 
    }

    bool add(const byte* array, size_t size, size_t pos, bool reverse = false)
    {
        if(!array)
            return false;  // empty text

        if(!root)
            root = new Node(0);

        if(!root)
            return false;

        Node* next = root;

        if(!reverse)
        { 
            for(size_t k = 0; k < size; k++)
                next = next->addByte(array[k]);        
        }
        else
        {
            for(size_t k = 0; k < size; k++)
                next = next->addByte(array[size-k-1]);
        }


        if(!next)
            return false;

        next->end = true;
        next->pos = pos;
        next->len = size;

        count++;

        return true;
    }

    bool contain(const byte* array, size_t size, size_t& pos) const
    {
        if(!array || !root)
            return false;  // empty text

        Node* next = root->find(array, size);

        if(next && next->end)
        {
            pos = next->pos;
            return true;
        }
        return false;
    }

    bool beginsWith(const byte* array, size_t size, size_t& pos, size_t& len) const
    {
        if(size == 0 || !root)
            return false;  // empty array

        Node* next = root;
      
        while(size--)
        {  
            byte b = *array++;

            next = next->findByte(b);

            if(!next)
                return false;

            if(next->end)
            {
                pos = next->pos;
                len = next->len;
                return true;
            }
        }

        return false;
    }

    bool endWith(const byte* array, size_t size, size_t& pos, size_t& len) const
    {
        if(size == 0 || !root)
            return false;  // empty array

        Node* next = root;

        array += size-1;

        while(size--)
        {
            byte b = *array--;

            next = next->findByte(b);

            if(!next)
                return false;

            if(next->end)
            {
                pos = next->pos;
                len = next->len;
                return true;
            }
        }

        return false;
    }

    void clear()
    {
        if(root)
        root->clear();
        root = nullptr;
        count = 0;
    }

protected:
	Node* root ;
    size_t count ;
};

