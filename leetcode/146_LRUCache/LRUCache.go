package main

import "container/list"

type LRUCache struct {
	MaxEntries int
	ll         *list.List
	cache      map[int]*list.Element
}

type entry struct {
	key   int
	value int
}

func Constructor(capacity int) LRUCache {
	return LRUCache{
		MaxEntries: capacity,
		ll:         list.New(),
		cache:      make(map[int]*list.Element),
	}
}

func (this *LRUCache) Get(key int) int {
	if ele, hit := this.cache[key]; hit {
		this.ll.MoveToFront(ele)
		return ele.Value.(*entry).value
	}
	return -1
}

func (this *LRUCache) Put(key int, value int) {
	if ee, ok := this.cache[key]; ok {
		this.ll.MoveToFront(ee)
		ee.Value.(*entry).value = value
		return
	}
	ele := this.ll.PushFront(&entry{key, value})
	this.cache[key] = ele
	if this.MaxEntries != 0 && this.ll.Len() > this.MaxEntries {
		lastEle := this.ll.Back()
		if lastEle != nil {
			this.ll.Remove(lastEle)
			removeKey := lastEle.Value.(*entry).key
			delete(this.cache, removeKey)
		}
	}
}
