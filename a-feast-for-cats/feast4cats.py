
# https://open.kattis.com/problems/cats 

# optimize https://www.geeksforgeeks.org/dsa/introduction-to-disjoint-set-data-structure-or-union-find-algorithm/

from functools import cmp_to_key
import time

def comparator(a,b):
    return a[2] - b[2]


class Edge:
  def __init__(self, edgeFrom, edgeTo, weight):
    self.edgeFrom = edgeFrom
    self.edgeTo = edgeTo
    self.weight = weight

def sortFunc(e):
   return e[2]

class DSU:
  def __init__(self, n):
    self.parent = list(range(n))
    self.rank = [1] * n

  def find(self, i):
    if self.parent[i] != i:
      self.parent[i] = self.find(self.parent[i])
    return self.parent[i]

  def union(self, x, y):
    s1 = self.find(x)
    s2 = self.find(y)
    if s1 != s2:
      if self.rank[s1] < self.rank[s2]:
        self.parent[s1] = s2
      elif self.rank[s1] > self.rank[s2]:
        self.parent[s2] = s1
      else:
        self.parent[s2] = s1
        self.rank[s1] += 1

def kruskal(f):
  # milkAndCats = input()
  milkAndCats = f.readline()
  milkAndCats = milkAndCats.split()

  milk = int(milkAndCats[0])
  cats = int(milkAndCats[1])

  edgeList = []

  edges = int((cats * (cats - 1)) / 2)

  for i in range(edges) :
      edge = f.readline() # input()
      edge = edge.split()
      edgeList.append([int(edge[0]), int(edge[1]), int(edge[2])])
      edgeList.append([int(edge[1]), int(edge[0]), int(edge[2])])

  edgeList.sort(key=cmp_to_key(comparator))

  dsu = DSU(cats)
  cost = 0
  count = 0

  for edgeFrom, edgeTo, weight in edgeList:
    if(dsu.find(edgeFrom) != dsu.find(edgeTo)):
      dsu.union(edgeFrom, edgeTo)
      cost += weight
      count += 1
      if count == cats - 1:
        break

  if(milk >= cost):
    print('yes milk: {}, cost: {}'.format(milk, cost))
  else: 
    print('no milk: {}, cost: {}'.format(milk, cost))


if __name__ == '__main__':
  with open("graph-testdata.txt") as f: 
    start_time = time.time()
    testCases = f.readline()
    testCases = int(testCases)
    i = 0
    while i < testCases:
      kruskal(f)
      i = i + 1 
  print("time: {}".format(time.time() - start_time))