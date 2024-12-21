package CompleteBinaryTree
import "math"
import "fmt"

type Node struct {
	Value string
	Next *Node
	Prev *Node
	Left *Node
	Right *Node
}

func NewNode(value string) Node {
	return Node{value, nil, nil, nil, nil}
}

type List struct {
	Head *Node
	Tail *Node
	CurrentSize int32
	LeftorRight int32
	Depth int32
}

func NewList() List {
	return List{nil, nil, 0, 0, 1}
}

func (l *List) IsEmpty() bool {
	return l.Head == nil
}

func (l * List) Push(Value string) {
	var newNd Node = NewNode(Value)
	if l.IsEmpty() {
		l.Head = &newNd
		l.Tail = &newNd
		return
	}
	l.Tail.Next = &newNd
	newNd.Prev = l.Tail
	l.Tail = &newNd
	l.CurrentSize = l.CurrentSize + 1
	l.Depth = (int32) (1 + math.Floor(math.Log2((float64)(l.CurrentSize))))
	var tempNd Node = *(l.Tail)
	for i := 0; (int32)(i) < l.CurrentSize; i = i + 1 {
		tempNd = *(tempNd.Prev)
	}
	if l.LeftorRight == 0 {
		tempNd.Left = &newNd
	}
	if l.LeftorRight == 1 {
		tempNd.Right = &newNd
	}
}

func (l *List) Pop() {
	if l.IsEmpty() {
		fmt.Print("Tree is empty")
		return
	}
	l.Tail = l.Tail.Prev
	l.Tail.Next = nil
}

func (l *List) Size() int32 {
	var Size int32 = 0
	var tempNd *Node = l.Head
	for ;tempNd != nil; {
		tempNd = tempNd.Next
		Size = Size + 1
	}
	return Size
}

func (l *List) Find(Value string) string {
	var tempNd *Node = l.Head
	for ; tempNd != nil; {
		if tempNd.Value == Value {
			return Value
		}
		tempNd = tempNd.Next
	}
	fmt.Print("The element is missing in the tree")
	return ""
}

func (l* List) Chek() bool {
	var tempNd *Node = l.Head
	l.Depth = (int32)(math.Floor(math.Log2((float64)(l.CurrentSize))))
	var SizeCurrentDepth int32 = (int32)(math.Pow(2, (float64)(l.Depth)))
	for i := 0; i < (int)(math.Pow(2, (float64)(l.Depth - 1))); i = i + 1 {
		tempNd = tempNd.Next
	}
	for i := 0; (int32)(i) < SizeCurrentDepth; i = i + 1 {
		if tempNd.Left == nil && tempNd.Right != nil {
			return false
		}
	}
	return true
}

func (l *List) Print() {
	var tempNd *Node = l.Head
	var SizeNode *Node = l.Head
	var Size int32 = 0
	for ;SizeNode != nil; {
		SizeNode = SizeNode.Next
		Size = Size + 1
	}
	var Depth int32 = 1 + (int32)(math.Floor(math.Log2((float64)(Size))))
	var Space = 15 * (Depth - 2)
	var y int32 = (int32)(math.Pow(2, (float64)(Depth)))
	var CurrentDepth int32 = 0
	for ; CurrentDepth < Depth; CurrentDepth = CurrentDepth + 1 {
		var AmountOfItemsPerLevel int32 = (int32)(math.Pow(2, (float64)(CurrentDepth)))
		for i := 0; tempNd != nil && (int32)(i) < AmountOfItemsPerLevel; i = i + 1 {
			if i == 0 {
				for j:= 0; (int32)(j) < y; j = j + 1 {
					fmt.Print(" ")
				}
			}
			fmt.Print(tempNd.Value)
			for j := 0;(int32)(j) < Space; j = j + 1 {
				fmt.Print(" ")
			}
			tempNd = tempNd.Next
		}
		fmt.Println()
		Space = (int32)(math.Floor((float64)(Space / 2)))
		y = y / 2
	}
}

/*type CompleteBinaryTree struct {
	BinaryTree List
}

func NewCompleteBinaryTree() CompleteBinaryTree {
	return CompleteBinaryTree{}
}

func (t *CompleteBinaryTree) Insert(Value string) {
	t.push(Value)
}*/
