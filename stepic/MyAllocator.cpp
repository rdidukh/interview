#include <map>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <set>

class MyAllocator
{
	struct Block
	{
    	Block(): Block(NULL, 0, false) {}
	    Block(char * p, size_t s, bool f):
    	ptr(p), size(s), free(f)
	    {}

	    char * ptr;
	    size_t size;
	    bool free;
	};

	size_t bsize;
	char * buffer;
	Block nullBlock;
	std::map<char *, Block> blocks;
	std::map<size_t, std::set<char *>> freeSize;

	Block & prevBlock(char * ptr)
	{
		assert(blocks.count(ptr) > 0);
		auto it = blocks.find(ptr);
		if(it != blocks.begin())
		{
			it--;
			return it->second;
		}
		return nullBlock;
	}

	Block & nextBlock(char * ptr)
	{
		assert(blocks.count(ptr) > 0);
		auto it = blocks.find(ptr);
		it++;
		if(it != blocks.end())
		{
			return it->second;
		}
		return nullBlock;
	}

	void insertFreeBlock(Block & block)
	{
    	freeSize[block.size].insert(block.ptr);
	}

	void eraseFreeBlock(Block & block)
	{
	    freeSize.at(block.size).erase(block.ptr);
	    if(freeSize.at(block.size).empty())
	      freeSize.erase(block.size);
	}

	void markBlockFree(Block & block)
	{
		assert(block.free == false);
		block.free = true;
		insertFreeBlock(block);
	}

	void markBlockBusy(Block & block)
	{
		assert(block.free == true);
		block.free = false;
		eraseFreeBlock(block);
	}

	void resizeBlock(Block & block, size_t newSize)
	{
	    if(newSize != block.size)
	    {
	        if(block.free)
	            eraseFreeBlock(block);
	        block.size = newSize;
	        if(block.free)
	            insertFreeBlock(block);
	    }
	}

	Block & createBlock(char * ptr, size_t size, bool free)
	{
		assert(blocks.count(ptr) == 0);
		blocks[ptr] = Block(ptr, size, free);
		if(free)
			insertFreeBlock(blocks[ptr]);
		return blocks[ptr];
	}

	void removeBlock(Block & block)
	{
		assert(blocks.count(block.ptr) > 0);
		if(block.free)
			eraseFreeBlock(block);
		blocks.erase(block.ptr);	
	}

	void splitBlock(Block & block, size_t newSize)
	{
	    assert(block.size >= newSize);
	    size_t oldSize = block.size;
	    resizeBlock(block, newSize);
	    if(newSize < oldSize)
	    	createBlock(block.ptr+newSize, oldSize-newSize, block.free);
	}

	char * findPtrForSize(size_t size)
	{
		auto it = freeSize.lower_bound(size);
		if(it != freeSize.end())
		{
			assert(it->second.empty() == false);
			return *(it->second.begin());
		}
		return NULL;
	}

	public:
	MyAllocator(size_t bufferSize)
	{
		bsize = bufferSize;
		buffer = new char[bufferSize];
		createBlock(buffer, bufferSize, true);
	}
	
	~MyAllocator()
	{
		delete[] buffer;
	}

	void * alloc(size_t size)
	{
	    char * ptr = findPtrForSize(size);
	    if(ptr != NULL)
	    {
	    	splitBlock(blocks.at(ptr), size);
	    	markBlockBusy(blocks.at(ptr));
	    }

	    #ifdef SELFTEST
	    selfTest();
	    #endif

	    return static_cast<void *>(ptr);
	}
	
	void * realloc(void * ptr, size_t size)
	{
		char * charPtr = static_cast<char *>(ptr);
		Block & block = blocks.at(charPtr);
		Block & next = nextBlock(charPtr);

		/* There is enough place ahead of the current block */
		if(next.free && block.size + next.size >= size)
		{
			splitBlock(next, size-block.size);
			removeBlock(next);
			resizeBlock(block, size);
		}
		else
		{	
			void * newPtr = alloc(size);
			if(newPtr != NULL)
			{
				memcpy(newPtr, ptr, block.size);
				free(ptr);
				ptr = newPtr;
			}
		}


		#ifdef SELFTEST
		selfTest();
		#endif

		return ptr;
	}

	void free(void * ptr)
	{
		char * charPtr = static_cast<char *>(ptr);
		Block & prev = prevBlock(charPtr);
		Block & next = nextBlock(charPtr);
		Block & block = blocks.at(charPtr);

		assert(block.free == false);
		assert(prev.ptr == NULL || prev.ptr + prev.size == block.ptr);
		assert(next.ptr == NULL || block.ptr + block.size == next.ptr);

		/* prev is busy and next is busy */
		/* just mark current block as free */
		if(!prev.free && !next.free)
		{	
			markBlockFree(block);
		}
		/* prev is free and next is busy */
		/* concat prev and curr block into one free block */
		else if(prev.free && !next.free)
		{
			resizeBlock(prev, prev.size + block.size);
			removeBlock(block);
		}
		/* prev is busy and next is free */
		/* concat curr and next block into one free block */
		else if(!prev.free && next.free)
		{
			resizeBlock(block, block.size + next.size);
			removeBlock(next);
			markBlockFree(block);
		}
		/* concat all three blocks into one block*/
		else if(prev.free && next.free)
		{
			resizeBlock(prev, prev.size + block.size + next.size);
			removeBlock(block);
			removeBlock(next);
		}
		#ifdef SELFTEST
		selfTest();
		#endif
	}

	char * getBuffer()
	{
		return buffer;
	}

#ifdef SELFTEST
	void debugPrint()
	{
		std::cout << "BLOCKS:" << std::endl;
		for(auto & elem: blocks)
		{
			char * ptr = elem.first;
			Block &block = elem.second;
			std::cout << (ptr-buffer) << " -> {" << (block.ptr-buffer) << ", " << block.size << ", " << block.free << "}" << std::endl;
		}

		std::cout << "FREE SIZE:" << std::endl;
		for(auto & elem: freeSize)
		{
			std::cout << elem.first << " -> {";
			for(auto ptr: elem.second)
			{
				std::cout << (ptr-buffer) << "  ";
			}
			std::cout << "}" << std::endl;
		}

		std::cout << std::endl;
	}

	/*
		Check invariants
	*/
	void selfTest()
	{
		debugPrint();
		// char * buffer;
		// std::map<char *, Block> blocks;
		// std::map<size_t, std::set<char *>> freeSize;
		assert(blocks.empty() == false);
		assert(blocks.begin()->first == buffer);

		int numFreeOne = 0, numFreeTwo = 0;
		size_t accumSize = 0;
		size_t accumFreeSizeOne = 0, accumFreeSizeTwo = 0;

		char * prev = NULL;

		for(auto it = blocks.begin(); it != blocks.end(); ++it)
		{
			char * ptr = it->first;
			Block block = it->second;
			assert(ptr == block.ptr);
			if(block.free)
			{
				assert(freeSize.count(block.size) > 0);
				assert(freeSize[block.size].count(block.ptr) > 0);
				accumFreeSizeOne += block.size;
				numFreeOne++;
			}
			assert(block.size > 0 && block.size <= bsize);
			assert(block.ptr >= buffer && block.ptr < buffer + bsize);
			assert(block.ptr + block.size <= buffer + bsize);
			accumSize += block.size;
			if(it != blocks.begin())
			{
				auto jt = it;
				--jt;
				Block prev = jt->second;
				assert(prev.ptr + prev.size == block.ptr);
				assert((prev.free && block.free) == false);
			}
		}

		for(auto it = freeSize.begin(); it != freeSize.end(); ++it)
		{
			auto size = it->first;
			auto & ptrSet = it->second;
			assert(ptrSet.empty() == false);

			for(auto jt = ptrSet.begin(); jt != ptrSet.end(); ++jt)
			{
				char * ptr = *jt;
				assert(blocks.count(ptr) > 0);
				assert(it->first == blocks[ptr].size);
				accumFreeSizeTwo += size;
				numFreeTwo++;
			}
		}

		assert(accumSize == bsize);
		assert(accumFreeSizeOne == accumFreeSizeTwo);
		assert(accumFreeSizeOne <= bsize);
		assert(numFreeOne == numFreeTwo);
	}
#endif
};

#include "test.h"

int main()
{
	MyAllocator alloc(10);
	char * buffer = alloc.getBuffer();
	void * ptr[10] = {0};

	/* Simple alloc-free */
	ptr[0] = alloc.alloc(4);
	ASSERT_NOTNULL(ptr[0]);
	ASSERT_EQ(buffer, ptr[0]);
	alloc.free(ptr[0]);

	/* Not enough memory */
	ASSERT_NULL(alloc.alloc(11));

	/* Two blocks*/
	ptr[0] = alloc.alloc(5);
	ASSERT_NOTNULL(ptr[0]);
	ASSERT_EQ(buffer, ptr[0]);
	ASSERT_NULL(alloc.alloc(6));
	ptr[1] = alloc.alloc(5);
	ASSERT_NOTNULL(ptr[1]);
	ASSERT_EQ(buffer+5, ptr[1]);
	ASSERT_NULL(alloc.alloc(1));
	alloc.free(ptr[0]);
	alloc.free(ptr[1]);

	/* Freeing blocks in the middle test */
	ptr[0] = alloc.alloc(3);
	ASSERT_EQ(buffer, ptr[0]);
	ptr[1] = alloc.alloc(1);
	ASSERT_EQ(buffer+3, ptr[1]);
	ptr[2] = alloc.alloc(1);
	ASSERT_EQ(buffer+4, ptr[2]);
	ptr[3] = alloc.alloc(1);
	ASSERT_EQ(buffer+5, ptr[3]);
	ASSERT_NULL(alloc.alloc(5));
	ptr[4] = alloc.alloc(4);
	alloc.free(ptr[2]);
	alloc.free(ptr[3]);
	alloc.free(ptr[1]);
	ASSERT_NULL(alloc.alloc(4));
	ptr[1] = alloc.alloc(3);
	ASSERT_NOTNULL(ptr[1]);
	alloc.free(ptr[0]);
	alloc.free(ptr[1]);
	ASSERT_NULL(alloc.alloc(7));
	ptr[0] = alloc.alloc(6);
	ASSERT_NOTNULL(ptr[0]);
	ASSERT_EQ(buffer, ptr[0]);
	alloc.free(ptr[4]);
	alloc.free(ptr[0]);

	/* Is all memory free now? */
	ptr[0] = alloc.alloc(10);
	ASSERT_NOTNULL(ptr[0]);
	ASSERT_EQ(buffer, ptr[0]);
	alloc.free(ptr[0]);

	/* Realloc at the same place */
	int32_t * i32 = (int32_t *)alloc.alloc(sizeof(int32_t));
	ASSERT_NOTNULL(i32);
	ASSERT_EQ(buffer, (char *)i32);
	i32 = (int32_t *)alloc.realloc(i32, 2*sizeof(int32_t));
	ASSERT_NOTNULL(i32);
	ASSERT_EQ(buffer, (char *)i32);
	int32_t * old32 = i32;
	ASSERT_NULL(alloc.alloc(3));
	ASSERT_EQ(old32, alloc.realloc(i32, 11));
	i32 = (int32_t *)alloc.realloc(i32, 10);
	ASSERT_NOTNULL(i32);
	ASSERT_EQ(buffer, (char *)i32);
	alloc.free(i32);

	/* Realloc no extra memory */
	ptr[0] = alloc.alloc(6);
	ASSERT_NOTNULL(ptr[0]);
	ASSERT_EQ(buffer, ptr[0]);
	i32 = (int32_t *)alloc.alloc(sizeof(int32_t));
	ASSERT_NOTNULL(i32);
	ASSERT_EQ(buffer+6, (char *)i32);
	i32 = (int32_t *)alloc.realloc(i32, 2*sizeof(int32_t));
	ASSERT_NOTNULL(i32);
	ASSERT_EQ(buffer+6, (char *)i32);
	alloc.free(ptr[0]);
	i32 = (int32_t *)alloc.realloc(i32, 2*sizeof(int32_t));
	ASSERT_NOTNULL(i32);
	ASSERT_EQ(buffer+6, (char *)i32);
	alloc.free(i32);

	/* Realloc to the new place */
	ptr[0] = alloc.alloc(6);
	ASSERT_NOTNULL(ptr[0]);
	ASSERT_EQ(buffer, ptr[0]);
	uint16_t * i16 = (uint16_t *)alloc.alloc(2*sizeof(uint16_t));
	ASSERT_NOTNULL(i16);
	ASSERT_EQ(buffer+6, (char *)i16);
	i16[0] = 0x1234;
	i16[1] = 0xBEEF;
	alloc.free(ptr[0]);
	i16 = (uint16_t *)alloc.realloc(i16, 3*sizeof(uint16_t));
	ASSERT_NOTNULL(i16);
	ASSERT_EQ(buffer, (char *)i16);
	ASSERT_EQ(0x1234, i16[0]);
	ASSERT_EQ(0xBEEF, i16[1]);
	alloc.free(i16);

	std::cout << "OK" << std::endl;

	return 0;
}
