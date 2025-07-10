
# https://open.kattis.com/problems/cats 

class Edge:
  def __init__(self, edgeFrom, edgeTo, weight):
    self.edgeFrom = edgeFrom
    self.edgeTo = edgeTo
    self.weight = weight

def sortFunc(e):
   return e.weight


testCases = input()
milkAndCats = input()
milkAndCats = milkAndCats.split()

milk = float(milkAndCats[0])
cats = float(milkAndCats[1])

testCases = float(testCases)


edgeList = []


edges = (cats * (cats - 1)) / 2

for i in range(edges) :
    edge = input()
    edge = edge.split()
    edgeList.insert(Edge(float(edge[0]), float(edge[1]), float(edge[2])))
    edgeList.insert(Edge(float(edge[1]), float(edge[0]), float(edge[2])))

edgeList.sort(key=sortFunc)










