package main

import (
	"fmt"
	"sort"
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

	dsu := DSU{}
	dsu.parent = make([]int, cats)
	dsu.rank = make([]int, cats)

	for i := 0; i < numOfEdges; i++ {
		var edge Edge
		fmt.Scanf("%d %d %d", &edge.edgeFrom, &edge.edgeTo, &edge.weight)
		edges[i] = edge
		if j < cats {
			dsu.parent[j] = j
			dsu.rank[j] = 0
			j++
		}
	}

	sort.Slice(edges[:], func(i, j int) bool {
  		return edges[i].weight < edges[j].weight
	})

	count := 0
	cost := 0
	for _, edge := range edges {
		if dsu.find(edge.edgeFrom) != dsu.find(edge.edgeTo) {
			dsu.union(edge.edgeFrom, edge.edgeTo)
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
	edgeFrom int
	edgeTo int
	weight int
}



type DSU struct {
	parent []int
	rank []int
}

func (self DSU) initiate(cats int) {
	self.parent = make([]int, cats)
	self.rank = make([]int, cats)
	for i := 0; i < cats; i++ {
		self.parent[i] = i
		self.rank[i] = 0
	}
}

func (self DSU) find(i int) int {
	if self.parent[i] != i {
		self.parent[i] = self.find(self.parent[i])
	}
	return self.parent[i]
}

func (self DSU) union(x int, y int) {
	s1 := self.find(x)
	s2 := self.find(y)
	if s1 != s2 {
		if self.rank[s1] < self.rank[s2] {
			self.parent[s1] = s2
		} else if self.rank[s1] > self.rank[s2] {
			self.parent[s2] = s1
		} else {
			self.parent[s2] = s1
			self.rank[s1] += 1
		}
	}
}