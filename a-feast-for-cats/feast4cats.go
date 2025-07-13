package main

import (
	"fmt"
	"sort"
	"container/heap"
)

func kruskals() string {
	var milk, cats int
	fmt.Scanf("%d %d%n", &milk, &cats)
	numOfEdges := int((cats * (cats - 1)) / 2)

	if cats > milk {
		for i := 0; i < numOfEdges; i++ {
			fmt.Scanf("%d %d")
		}
		return "no\n"
	}

	edges := make([]Edge, numOfEdges)
	j := 0

	adjList := make([][]Edge, numOfEdges)
	visited := make([]bool, cats)

	for i := range numOfEdges {
		adjList[i] = make([]Edge, cats - 1)
		var edge Edge
		var from, to, weight int
		fmt.Scanf("%d %d %d", &from, &to, &weight)
		adjList[from] = append(edges[from], Edge{from, to, weight})
		adjList[to] = append(edges[to], Edge{to, from, weight})

	}



	cost := 0
	queue := &EdgeHeap{}
	heap.Init(queue)
	heap.Push()

	while()
	for _, edge := range edges {
		if dsu.find(edge.from) != dsu.find(edge.to) {
			dsu.union(edge.from, edge.to)
			cost += edge.weight
			count++
			if count == cats - 1 {
				break
			}
			if cost > milk {
				return "no\n"
			}
		}
	}

	return "yes\n"
}

func main() {
	var testCases int

	fmt.Scanf("%d%n", &testCases)
	
	var out string

	for i:= 0; i < testCases; i++ {
		out += kruskals()
	}
	fmt.Print(out)
}

type Edge struct {
	from int
	to int
	weight int
}

// An EdgeHeap is a min-heap of ints.
type EdgeHeap []Edge

func (h EdgeHeap) Len() int           { return len(h) }
func (h EdgeHeap) Less(i, j int) bool { return h[i].weight < h[j].weight }
func (h EdgeHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }

func (h *EdgeHeap) Push(x any) {
	// Push and Pop use pointer receivers because they modify the slice's length,
	// not just its contents.
	*h = append(*h, x.(Edge))
}

func (h *EdgeHeap) Pop() any {
	old := *h
	n := len(old)
	x := old[n-1]
	*h = old[0 : n-1]
	return x
}
