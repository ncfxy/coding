package main

type MinStack struct {
	valList []int
	minList []int
	length  int
}

func Constructor() MinStack {
	return MinStack{
		valList: make([]int, 0),
		minList: make([]int, 0),
		length:  0,
	}
}

func (this *MinStack) Push(val int) {
	this.valList = append(this.valList, val)
	if this.length == 0 {
		this.minList = append(this.minList, val)
	} else {
		currentMin := this.minList[this.length-1]
		if val < currentMin {
			this.minList = append(this.minList, val)
		} else {
			this.minList = append(this.minList, currentMin)
		}
	}
	this.length = len(this.valList)
}

func (this *MinStack) Pop() {
	this.valList = this.valList[:this.length-1]
	this.minList = this.minList[:this.length-1]
	this.length = len(this.valList)
}

func (this *MinStack) Top() int {
	return this.valList[this.length-1]
}

func (this *MinStack) GetMin() int {
	return this.minList[this.length-1]
}
