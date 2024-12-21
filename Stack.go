package Stack
import "fmt"

type Node struct {
	Value string
	Next *Node
	Prev *Node
}

func NewNode(value string) Node {
	return Node{value, nil, nil}
}

type Stack struct {
	Head *Node
	Tail *Node
}

func NewStack() Stack {
	return Stack{nil, nil}
}

func (s Stack) IsEmpty() bool {
		return s.Head == nil
}

func (s *Stack) Push(value string) {
	var newNd Node = NewNode(value)
	if s.IsEmpty() {
		s.Head = &newNd
		s.Tail = &newNd
		return
	}
	newNd.Next = s.Head
	s.Head.Prev = &newNd
	s.Head = &newNd
}

func (s *Stack) Pop() string {
	if s.IsEmpty() {
		fmt.Print("Stack is empty")
	}
	var temp *Node = s.Head
	if s.Head.Next != nil {
		s.Head = s.Head.Next
	}
	s.Head.Prev = nil
	var value string = temp.Value
	return value
}


func (s Stack) Print() {
	var tempNd *Node = s.Head
	for ;tempNd != nil; {
		fmt.Println(tempNd.Value)
		tempNd = tempNd.Next
	}
}
