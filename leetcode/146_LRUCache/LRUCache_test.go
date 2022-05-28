package main

import "testing"

func TestLRUCache(t *testing.T) {
	c := Constructor(2)
	c.Put(1, 1)
	c.Put(2, 2)
	t.Logf("first: %d", c.Get(1))
	c.Put(3, 3)
	t.Logf("second: %d", c.Get(2))
	c.Put(4, 4)
	t.Logf("third: %d", c.Get(1))
	t.Logf("fourth: %d", c.Get(3))
	t.Logf("fifth: %d", c.Get(4))

}

// LRUCache lRUCache = new LRUCache(2);
// lRUCache.put(1, 1); // 缓存是 {1=1}
// lRUCache.put(2, 2); // 缓存是 {1=1, 2=2}
// lRUCache.get(1);    // 返回 1
// lRUCache.put(3, 3); // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
// lRUCache.get(2);    // 返回 -1 (未找到)
// lRUCache.put(4, 4); // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
// lRUCache.get(1);    // 返回 -1 (未找到)
// lRUCache.get(3);    // 返回 3
// lRUCache.get(4);    // 返回 4
